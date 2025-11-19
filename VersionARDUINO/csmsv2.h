#ifndef _CSMSV2_H
#define _CSMSV2_H

#include <Arduino.h>

// ===================== CONFIGURACIÓN =====================
#define PIN_SENSOR_TIERRA A0 // Pin analógico del sensor
#define PIN_POWER_CSMS 7     // Pin digital para alimentar el sensor

#define HUMEDAD_MIN_SEGURA 25
#define HUMEDAD_MAX_SEGURA 90

#define CSMS_ESTABILIZACION_MS 50

constexpr int AIR_VALUE = 588;   // Sensor en aire seco
constexpr int WATER_VALUE = 308; // Sensor sumergido

// ===================== VARIABLE =====================
extern uint8_t humedad_tierra;

// ===================== INICIO =====================
void iniciarCSMSV2();

// ===================== LECTURA =====================
void leerCSMSV2();

#endif
