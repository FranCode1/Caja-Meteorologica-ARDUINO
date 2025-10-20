#ifndef _BUTTONS_H
#define _BUTTONS_H

#include <Arduino.h>
#include "lcd.h"  // Necesario para acceder al objeto 'menu' y a la función 'fn_atras'

// =====================================================================
// CONFIGURACIÓN DE PINES DE LOS BOTONES
// =====================================================================
// Cada botón se conecta a un pin digital configurado con PULLUP interno.
// Esto significa que:
//   - Estado normal (no presionado) → HIGH
//   - Estado presionado → LOW
// =====================================================================

#define PIN_BTN_IZQUIERDA 2
#define PIN_BTN_DERECHA   3
#define PIN_BTN_ARRIBA    4
#define PIN_BTN_ABAJO     5
#define PIN_BTN_OK        6
#define PIN_BTN_BACK      7

// =====================================================================
// MACROS DE LECTURA RÁPIDA
// =====================================================================
// Estas macros simplifican la lectura de los botones.
// Usan negación lógica (!) porque los botones están activos en LOW.
// =====================================================================

#define BTN_IZQUIERDA (!digitalRead(PIN_BTN_IZQUIERDA))
#define BTN_DERECHA   (!digitalRead(PIN_BTN_DERECHA))
#define BTN_ARRIBA    (!digitalRead(PIN_BTN_ARRIBA))
#define BTN_ABAJO     (!digitalRead(PIN_BTN_ABAJO))
#define BTN_OK        (!digitalRead(PIN_BTN_OK))
#define BTN_BACK      (!digitalRead(PIN_BTN_BACK))

// =====================================================================
// DECLARACIONES EXTERNAS
// =====================================================================
// Estas referencias apuntan a elementos definidos en otros módulos.
//
// - 'menu' se declara y configura en lcd.h
// - 'fn_atras()' debe ser una función definida por el usuario
//   (por ejemplo, para volver a una pantalla anterior o cancelar una acción)
// =====================================================================

extern LiquidMenu menu;
extern void fn_atras();

// =====================================================================
// FUNCIÓN: iniciarBotonera()
// =====================================================================
// Inicializa todos los pines de la botonera en modo INPUT_PULLUP.
// Debe llamarse una sola vez en setup().
// =====================================================================

void iniciarBotonera() {
    pinMode(PIN_BTN_IZQUIERDA, INPUT_PULLUP);
    pinMode(PIN_BTN_DERECHA,   INPUT_PULLUP);
    pinMode(PIN_BTN_ARRIBA,    INPUT_PULLUP);
    pinMode(PIN_BTN_ABAJO,     INPUT_PULLUP);
    pinMode(PIN_BTN_OK,        INPUT_PULLUP);
    pinMode(PIN_BTN_BACK,      INPUT_PULLUP);
}

// =====================================================================
// FUNCIÓN: navegarMenu()
// =====================================================================
// Esta función gestiona la navegación dentro del menú LCD.
// Debe llamarse en el loop() principal, idealmente en cada iteración.
//
// Cada botón realiza una acción específica:
//
//  🔹 Derecha → Avanza a la siguiente pantalla
//  🔹 Izquierda → Retrocede a la pantalla anterior
//  🔹 Arriba / Abajo → Cambia el foco entre elementos del menú
//  🔹 OK → Ejecuta la función asociada al elemento actual
//  🔹 BACK → Llama a la función personalizada 'fn_atras()'
//
// Incluye un pequeño delay (debounce) para evitar rebotes mecánicos.
// =====================================================================

void navegarMenu() {
    if (BTN_DERECHA) {
        menu.next_screen();     // Avanzar a la siguiente pantalla
        delay(250);             // Antirrebote simple
    } 
    else if (BTN_IZQUIERDA) {
        menu.previous_screen(); // Retroceder a la pantalla anterior
        delay(250);
    } 
    else if (BTN_ARRIBA) {
        menu.switch_focus(true);  // Cambiar el foco hacia arriba
        delay(250);
    } 
    else if (BTN_ABAJO) {
        menu.switch_focus(false); // Cambiar el foco hacia abajo
        delay(250);
    } 
    else if (BTN_OK) {
        menu.call_function(1);    // Ejecutar la función asociada al ítem seleccionado
        delay(250);
    } 
    else if (BTN_BACK) {
        fn_atras();               // Acción personalizada: volver / cancelar
        delay(250);
    }
}

#endif
