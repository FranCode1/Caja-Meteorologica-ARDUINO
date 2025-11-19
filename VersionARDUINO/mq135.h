#ifndef _MQ135_H
#define _MQ135_H

#include <Arduino.h>
// #include "config.h"

// ===================== CONFIGURACIÓN =====================
constexpr uint8_t MQ135_PIN = A2;
constexpr float RL = 1.0;
constexpr float CLEAN_AIR_RATIO = 9.8;
constexpr uint16_t CALIB_SAMPLES = 50;
constexpr uint16_t CALIB_INTERVAL = 100;

// ===================== VARIABLES EXTERNAS =====================
extern float RO;
extern float RS;
extern float ratio;

extern char calidad[20];
extern char tendencia[20];

// ===================== PROTOTIPOS =====================
void iniciarMQ135();
bool calibrarMQ135(); // retorna true cuando se completa
float leerMQ135();    // devuelve ratio (RS/RO)

#endif
