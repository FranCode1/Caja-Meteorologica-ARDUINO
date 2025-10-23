#ifndef _NAVEGACION_H_
#define _NAVEGACION_H_

#include <Arduino.h>
#include "lcd.h" // Para controlar el menú desde acá

// ===================================================
// CONFIGURACIÓN DE PINES DEL JOYSTICK KY-023
// ===================================================

// Ejes analógicos
#define JOY_X A10
#define JOY_Y A9
#define PIN_BTN_OK 8
#define PIN_BTN_BACK 7

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
        ultimoMovimiento = ahora;
    }
    else if (joyX > 600)
    { // DERECHA
        menu.next_screen();
        ultimoMovimiento = ahora;
    }

    // --- Movimiento vertical ---
    else if (joyY < 400)
    { // ARRIBA
        menu.switch_focus(true);
        ultimoMovimiento = ahora;
    }
    else if (joyY > 600)
    { // ABAJO
        menu.switch_focus(false);
        ultimoMovimiento = ahora;
    }
    else if (BTN_OK)
    {
        menu.call_function(1); // Ejecutar la función asociada al ítem seleccionado
        delay(250);
    }
    else if (BTN_BACK)
    {
        fn_atras(); // Acción personalizada: volver / cancelar
        delay(250);
    }
}

#endif
