#include "csmsv2.h"
// #include "debug.h" // Si usás DEBUG_PRINT

// ===================== VARIABLE GLOBAL =====================
uint8_t humedad_tierra = 0;

// ===================== VARIABLES INTERNAS =====================
static unsigned long csmsUltimoTiempo = 0;
static bool csmsEncendido = false;

// ===================== INICIO =====================
void iniciarCSMSV2()
{
    pinMode(PIN_POWER_CSMS, OUTPUT);
    digitalWrite(PIN_POWER_CSMS, LOW);
    pinMode(PIN_SENSOR_TIERRA, INPUT);

    //DEBUG_PRINTLN(F("✅ CSMSV2 inicializado correctamente"));
}

// ===================== LECTURA =====================
void leerCSMSV2()
{
    unsigned long ahora = millis();

    if (!csmsEncendido)
    {
        // Encender sensor y comenzar estabilización
        digitalWrite(PIN_POWER_CSMS, HIGH);
        csmsUltimoTiempo = ahora;
        csmsEncendido = true;

        //DEBUG_PRINTLN(F("CSMSV2 → Sensor encendido, esperando estabilización"));
        return;
    }

    // Esperar estabilización
    if (ahora - csmsUltimoTiempo < CSMS_ESTABILIZACION_MS)
    {
        return;
    }

    // Leer valor analógico (múltiples lecturas para promediar y reducir ruido)
    int lectura1 = analogRead(PIN_SENSOR_TIERRA);
    delay(10);
    int lectura2 = analogRead(PIN_SENSOR_TIERRA);
    delay(10);
    int lectura3 = analogRead(PIN_SENSOR_TIERRA);
    int lectura = (lectura1 + lectura2 + lectura3) / 3;

    // Apagar sensor
    digitalWrite(PIN_POWER_CSMS, LOW);
    csmsEncendido = false;

    // Descartar lecturas absurdas
    if (lectura < 50 || lectura > 1023)
    {
        return; // Mantener el último valor válido
    }

    // Convertir lectura a porcentaje
    // AIR_VALUE (588) = 0% humedad (aire seco)
    // WATER_VALUE (308) = 100% humedad (agua)
    // Si la lectura es menor que WATER_VALUE, está en agua (100%)
    // Si la lectura es mayor que AIR_VALUE, está en aire seco (0%)
    
    if (lectura <= WATER_VALUE)
    {
        humedad_tierra = 100; // Completamente sumergido
    }
    else if (lectura >= AIR_VALUE)
    {
        humedad_tierra = 0; // Completamente seco
    }
    else
    {
        // Mapear entre WATER_VALUE y AIR_VALUE
        humedad_tierra = map(lectura, AIR_VALUE, WATER_VALUE, 0, 100);
        humedad_tierra = constrain(humedad_tierra, 0, 100);
    }

    //DEBUG_PRINT(F("CSMSV2 → Raw: "));
    //DEBUG_PRINT(lectura);
    //DEBUG_PRINT(F(" | Humedad: "));
    //DEBUG_PRINTLN(humedad_tierra);
}
