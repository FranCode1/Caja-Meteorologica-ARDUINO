#ifndef _CSMSV2_H
#define _CSMSV2_H

#include <Arduino.h>

// ===================== CONFIGURACIÓN =====================
#define PIN_SENSOR_TIERRA A0   // Pin analógico del sensor
#define HUMEDAD_MIN_SEGURA 25  // Mínimo aceptable (%)
#define HUMEDAD_MAX_SEGURA 90  // Máximo aceptable (%)
const int AIR_VALUE = 588;     // Valor en aire seco
const int WATER_VALUE = 308;   // Valor en agua

// ===================== VARIABLE =====================
static uint8_t humedad_tierra = 0; // % de humedad actual

// ===================== INICIO =====================
inline void iniciarCSMSV2() {
    pinMode(PIN_SENSOR_TIERRA, INPUT);
}

// ===================== LECTURA =====================
inline void leerCSMSV2() {
    int lectura = analogRead(PIN_SENSOR_TIERRA); // Leer valor ADC
    humedad_tierra = map(lectura, AIR_VALUE, WATER_VALUE, 0, 100);
    humedad_tierra = constrain(humedad_tierra, 0, 100);
}

#endif
