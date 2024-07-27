//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "global_defines.h"

#include "system.h"
#include "non_blocking_delay.h"
#include "tranquera.h"
#include "scale.h"
#include "MQTT.h"
#include "rfid.h"
#include "mode_selector.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declarations (prototypes) of private functions]========================

void parse_message_received(const char * topic, const char * message);
void send_tranquera_position();
void send_system_mode();

//=====[Declaration and initialization of public global objects]===============

// ---Módulos---
static Tranquera tranquera(PIN_TRANQUERA, PIN_BOTON_ABRIR, MODE_PIN_BOTON_ABRIR, PIN_BOTON_CERRAR, MODE_PIN_BOTON_CERRAR);
static Scale scale(PIN_BALANZA, PIN_SWITCH_BALANZA, MODE_PIN_SWITCH_BALANZA);
static RFID rfid_reader(PIN_RFID_MOSI, PIN_RFID_MISO, PIN_RFID_SCLK, PIN_RFID_CS, PIN_RFID_RESET, PIN_LED_LECTURA);
static MQTT mqtt(PIN_MQTT_TX, PIN_MQTT_RX, MQTT_BAUDRATE, PIN_MQTT_STATUS, PIN_LED_WIFI_CONECTADO, PIN_LED_WIFI_SIN_CONEXION, PIN_LED_MENSAJE_MQTT);
static ModeSelector system_mode(PIN_SWITCH_SOLO_LECTURA, MODE_PIN_SWITCH_SOLO_LECTURA, PIN_LED_MODO_NORMAL, PIN_LED_MODO_SOLO_LECTURA);
// ---

// ---Delays---
static nonBlockingDelay RFID_read_delay(RFID_READ_TRY_DELAY_TIME_MS);
// ---

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

char * lectura_rfid = nullptr;
char lectura_scale [256] = "";
char msg [256] = "";
char topic_received[256] = "";
char message_received[256] = "";

//=====[Implementations of public functions]===================================

void system_init()
{
    RFID_read_delay.Start();

    mqtt.subscribe(TOPIC_TRANQUERA);
    mqtt.subscribe(TOPIC_SYSTEM_MODE);
}

void system_update()
{
    if(RFID_read_delay.isReady()){
        RFID_read_delay.Start();

        lectura_rfid = rfid_reader.read();
        if(lectura_rfid != nullptr){
            scale.read(lectura_scale);
            strcpy(msg, lectura_rfid);
            strcat(msg, ":");
            strcat(msg, lectura_scale);
            mqtt.publish(TOPIC_RFID_LECTURA, msg);
        }

        if(tranquera.position_changed){
            send_tranquera_position();
            tranquera.position_changed = false;
        }

        if(system_mode.mode_changed){
            send_system_mode();
            system_mode.mode_changed = false;
        }

    }

    mqtt.processPendings();

    if(mqtt.receive(topic_received, message_received)){
        parse_message_received(topic_received, message_received);
    }
}

//=====[Implementations of private functions]==================================

void parse_message_received(const char * topic, const char * message)
{
    if (strcmp(topic, "subscribed") == 0) {
        mqtt.confirmSubscription(message);
    }
    else if (strcmp(topic, "unsubscribed") == 0) {
        mqtt.confirmUnsubscription(message);
    }

    else if (strcmp(topic, TOPIC_TRANQUERA) == 0) {
        if(strcmp(message, MESSAGE_TRANQUERA_ABRIR) == 0 && system_mode == IDLE){
            tranquera = ABIERTO;
        }
        else if(strcmp(message, MESSAGE_TRANQUERA_CERRAR) == 0 && system_mode == IDLE){
            tranquera = CERRADO;
        }
        else if(strcmp(message, MESSAGE_TRANQUERA_PEDIR_ESTADO) == 0){
            send_tranquera_position();
        }
    }

    else if (strcmp(topic, TOPIC_SYSTEM_MODE) == 0) {
        if(strcmp(message, MESSAGE_SYSTEM_MODE) == 0){
            send_system_mode();
        }
    }
}

void send_tranquera_position()
{
    position_t position = tranquera;
    switch (position){
        case ABIERTO:
            mqtt.publish(TOPIC_TRANQUERA_ESTADO, MESSAGE_TRANQUERA_ABIERTO);
            break;
        case CERRADO:
            mqtt.publish(TOPIC_TRANQUERA_ESTADO, MESSAGE_TRANQUERA_CERRADO);
            break;
        default:
            break;
    }
    
}

void send_system_mode()
{
    system_mode_t mode = system_mode;
    switch (mode){
        case IDLE:
            mqtt.publish(TOPIC_SYSTEM_MODE_ESTADO, MESSAGE_SYSTEM_MODE_IDLE);
            break;
        case SOLO_LECTURA:
            mqtt.publish(TOPIC_SYSTEM_MODE_ESTADO, MESSAGE_SYSTEM_MODE_SOLO_LECTURA);
            break;
        default:
            break;
    }
    
}