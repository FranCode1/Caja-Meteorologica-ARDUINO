#ifndef _NAVEGACION_H_
#define _NAVEGACION_H_

#include <Arduino.h>
#include "lcd.h"  // Para usar mostrarPantalla()

// ===================================================
// CONFIGURACIÓN DE PINES DE LOS BOTONES
// ===================================================
// Usa resistencias pull-up internas. 
// Los botones se conectan entre el pin y GND.
#define BTN_IZQ 4
#define BTN_DER 3

// ===================================================
// VARIABLES DE CONTROL (Antirrebote)
// ===================================================
unsigned long ultimoMovimiento = 0;
const unsigned long debounceDelay = 250; // milisegundos entre movimientos

// ===================================================
// VARIABLES DE CONTROL DE PANTALLA
// ===================================================
extern uint8_t pantallaActual;  // declarada en lcd.h
const uint8_t totalPantallas = 5; // cantidad total de pantallas (ajustá si cambian)

// ===================================================
// INICIALIZACIÓN DE BOTONES
// ===================================================
inline void iniciarNavegacion() {
    pinMode(BTN_IZQ, INPUT_PULLUP);
    pinMode(BTN_DER, INPUT_PULLUP);
    // Serial.println(F("Navegación por botones iniciada correctamente."));
}

// ===================================================
// LECTURA DE BOTONES Y NAVEGACIÓN
// ===================================================
inline void leerNavegacion() {
    unsigned long ahora = millis();
    if (ahora - ultimoMovimiento < debounceDelay)
        return;

    // Botón IZQUIERDA
    if (!digitalRead(BTN_IZQ)) {
        if (pantallaActual == 0) pantallaActual = totalPantallas - 1;
        else pantallaActual--;
        mostrarPantalla(pantallaActual);
        ultimoMovimiento = ahora;
        return;
    }

    // Botón DERECHA
    if (!digitalRead(BTN_DER)) {
        pantallaActual = (pantallaActual + 1) % totalPantallas;
        mostrarPantalla(pantallaActual);
        ultimoMovimiento = ahora;
        return;
    }
}

#endif
