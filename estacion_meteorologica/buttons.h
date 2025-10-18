#ifndef _BUTTONS_H
#define _BUTTONS_H

#include <Arduino.h>
#include "lcd.h"

// ===================================================
// CONFIGURACIÓN DE PINES DE LOS BOTONES
// ===================================================

#define PIN_BTN_IZQUIERDA 2
#define PIN_BTN_DERECHA   3
#define PIN_BTN_ARRIBA    4
#define PIN_BTN_ABAJO     5
#define PIN_BTN_OK        6
#define PIN_BTN_BACK      7

// ===================================================
// MACROS DE LECTURA RÁPIDA
// ===================================================

#define BTN_IZQUIERDA (!digitalRead(PIN_BTN_IZQUIERDA))
#define BTN_DERECHA   (!digitalRead(PIN_BTN_DERECHA))
#define BTN_ARRIBA    (!digitalRead(PIN_BTN_ARRIBA))
#define BTN_ABAJO     (!digitalRead(PIN_BTN_ABAJO))
#define BTN_OK        (!digitalRead(PIN_BTN_OK))
#define BTN_BACK      (!digitalRead(PIN_BTN_BACK))

// ===================================================
// DECLARACIÓN DE OBJETOS EXTERNOS
// ===================================================

// 🔹 Estas líneas le dicen al compilador que los objetos/fns
// están definidos en otro archivo (.h o .ino)
// extern LiquidMenu menu;  
// extern void fn_atras();

// ===================================================
// CONFIGURACIÓN INICIAL DE BOTONES
// ===================================================

void iniciarBotonera() {
    pinMode(PIN_BTN_IZQUIERDA, INPUT_PULLUP);
    pinMode(PIN_BTN_DERECHA,   INPUT_PULLUP);
    pinMode(PIN_BTN_ARRIBA,    INPUT_PULLUP);
    pinMode(PIN_BTN_ABAJO,     INPUT_PULLUP);
    pinMode(PIN_BTN_OK,        INPUT_PULLUP);
    pinMode(PIN_BTN_BACK,      INPUT_PULLUP);
}

// ===================================================
// FUNCIÓN PRINCIPAL DE NAVEGACIÓN
// ===================================================

void navegarMenu() {
    if (BTN_DERECHA) {
        menu.next_screen();
        delay(250);
    } 
    else if (BTN_IZQUIERDA) {
        menu.previous_screen();
        delay(250);
    } 
    else if (BTN_ARRIBA) {
        menu.switch_focus(true);
        delay(250);
    } 
    else if (BTN_ABAJO) {
        menu.switch_focus(false);
        delay(250);
    } 
    else if (BTN_OK) {
        menu.call_function(1);
        delay(250);
    } 
    else if (BTN_BACK) {
        fn_atras();
        delay(250);
    }
}

#endif
