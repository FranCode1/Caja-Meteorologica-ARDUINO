#ifndef _NAVEGACION_H_
#define _NAVEGACION_H_

#include <Arduino.h>
#include "lcd.h" // Para controlar el menú desde acá

// ===================================================
// CONFIGURACIÓN DE PINES DEL JOYSTICK KY-023
// ===================================================

// Ejes analógicos
#define JOY_X A11 // Pin del eje X
#define JOY_Y A10 // Pin del eje Y
#define PIN_BTN_OK 8 // Pin del botón de aceptar
#define PIN_BTN_BACK 7  // Pin del botón de retroceso

// =====================================================================
// MACROS DE LECTURA RÁPIDA
// =====================================================================
// Estas macros simplifican la lectura de los botones.
// Usan negación lógica (!) porque los botones están activos en LOW.
// =====================================================================
#define BTN_OK (!digitalRead(PIN_BTN_OK))
#define BTN_BACK (!digitalRead(PIN_BTN_BACK))

// ===================================================
// VARIABLES GLOBALES
// ===================================================

int joyX = 0;  // Valor del eje X (izquierda / derecha)
int joyY = 0;  // Valor del eje Y (arriba / abajo)

// Para evitar múltiples lecturas seguidas al mantener el joystick
unsigned long ultimoMovimiento = 0;
const unsigned long debounceDelay = 250; // milisegundos entre movimientos

// ===================================================
// INICIALIZACIÓN DEL MÓDULO KY-023
// ===================================================

void iniciarNavegacion()
{
    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);
    pinMode(PIN_BTN_OK, INPUT_PULLUP);
    pinMode(PIN_BTN_BACK, INPUT_PULLUP);

    Serial.println("Joystick KY-023 iniciado correctamente.");
}

// ===================================================
// FUNCIÓN DE LECTURA Y NAVEGACIÓN
// ===================================================

void leerNavegacion()
{
    joyX = analogRead(JOY_X); // Rango 0–1023
    joyY = analogRead(JOY_Y);

    unsigned long ahora = millis();

    // Solo permite un movimiento cada 250 ms
    if (ahora - ultimoMovimiento < debounceDelay)
        return;

    // --- Movimiento horizontal ---
    if (joyX < 400)
    { // IZQUIERDA
        menu.previous_screen();
        // activarLedPantalla(2);
        ultimoMovimiento = ahora;
    }
    else if (joyX > 600)
    { // DERECHA
        menu.next_screen();
        ultimoMovimiento = ahora;
    }
    // --- Movimiento vertical ---
    else if (joyY < 400) // ARRIBA
        return;          // No hacer nada por ahora
    else if (joyY > 600) // ABAJO
        return; // No hacer nada por ahora
    else if (BTN_OK)
        return; // No hacer nada por ahora
    else if (BTN_BACK)
        return; // No hacer nada por ahora
}

#endif
