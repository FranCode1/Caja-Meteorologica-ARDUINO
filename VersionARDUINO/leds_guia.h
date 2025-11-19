#ifndef _LEDS_GUIA_H
#define _LEDS_GUIA_H

#include <Arduino.h>

// =====================================================
// CANTIDAD DE PANTALLAS
// =====================================================
#define TOTAL_PANTALLAS 5 // valor fijo, compile-time

// =====================================================
// PINES PARA CADA LED
// =====================================================
#define LED_PANTALLA1 6
#define LED_PANTALLA2 5
#define LED_PANTALLA3 4
#define LED_PANTALLA4 3
#define LED_PANTALLA5 2

// Arreglo fijo
extern const uint8_t ledsPantalla[TOTAL_PANTALLAS];

// Pantalla actual (definida en lcd.cpp)
extern uint8_t pantallaActual;

// =====================================================
// FUNCIONES
// =====================================================
void iniciarLedsPantalla();
void cambiarLedPantalla(uint8_t nuevaPantalla);

#endif
