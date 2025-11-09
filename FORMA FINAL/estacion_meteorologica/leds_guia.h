#ifndef _LCD_GUIA_H
#define _LCD_GUIA_H

#include "lcd.h"  // Tu archivo donde inicializás LiquidCrystal

// =====================================================
// CONTROL DE LEDS SEGÚN LA "PANTALLA" ACTUAL
// =====================================================
// Cada pantalla del LCD tendrá un LED indicador asociado.
// Por ejemplo, si mostrás distintas lecturas de sensores,
// podés prender el LED correspondiente a la pantalla activa.

#define LED_PANTALLA1 6
#define LED_PANTALLA2 5
#define LED_PANTALLA3 4
#define LED_PANTALLA4 3
#define LED_PANTALLA5 2

// Variables globales
static unsigned long ultimoParpadeo = 0;
static bool estadoLED = false;
extern uint8_t pantallaActual;  // declarada en lcd.h

// -------------------------------------------------------------
// Inicializa los pines de los LEDs como salidas
// -------------------------------------------------------------
void iniciarLedsPantalla() {
    const uint8_t leds[5] = {LED_PANTALLA1, LED_PANTALLA2, LED_PANTALLA3, LED_PANTALLA4, LED_PANTALLA5};
    for (uint8_t i = 0; i < 5; i++) {
        pinMode(leds[i], OUTPUT);
        digitalWrite(leds[i], LOW);
    }
}

// -------------------------------------------------------------
// Cambia la pantalla activa y enciende su LED correspondiente
// -------------------------------------------------------------
void cambiarLedPantalla(uint8_t nuevaPantalla) {
    if (nuevaPantalla < 1 || nuevaPantalla > 5) return;
    pantallaActual = nuevaPantalla;

    // Apaga todos los LEDs
    digitalWrite(LED_PANTALLA1, LOW);
    digitalWrite(LED_PANTALLA2, LOW);
    digitalWrite(LED_PANTALLA3, LOW);
    digitalWrite(LED_PANTALLA4, LOW);
    digitalWrite(LED_PANTALLA5, LOW);

    // Enciende solo el LED de la pantalla activa
    switch (pantallaActual) {
        case 1: digitalWrite(LED_PANTALLA1, HIGH); break;
        case 2: digitalWrite(LED_PANTALLA2, HIGH); break;
        case 3: digitalWrite(LED_PANTALLA3, HIGH); break;
        case 4: digitalWrite(LED_PANTALLA4, HIGH); break;
        case 5: digitalWrite(LED_PANTALLA5, HIGH); break;
    }
}

#endif
