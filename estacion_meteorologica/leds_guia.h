#ifndef _LCD_GUIA_H
#define _LCD_GUIA_H

#include "lcd.h"



// =====================================================
//  CONTROL DE LEDS POR PANTALLA (usando LiquidMenu)
// =====================================================

extern LiquidScreen pantalla1;
extern LiquidScreen pantalla2;
extern LiquidScreen pantalla3;
extern LiquidScreen pantalla4;
extern LiquidScreen pantalla5;

extern LiquidMenu menu;

// =============================================================
// CONFIGURACIÓN DE LEDS POR PANTALLA
// =============================================================
// Cada pantalla del LCD tiene un LED asociado.
// Estos pines deben conectarse en la placa a los LEDs indicadores.
#define LED_PANTALLA1 6
#define LED_PANTALLA2 5
#define LED_PANTALLA3 4
#define LED_PANTALLA4 3
#define LED_PANTALLA5 2

// =============================================================
// VARIABLES GLOBALES
// =============================================================
unsigned long ultimoParpadeo = 0;
bool estadoLED = false;

// =============================================================
// FUNCIÓN: iniciarLedsPantalla()
// -------------------------------------------------------------
// Configura los pines de los LEDs como salidas y los apaga.
// =============================================================
void iniciarLedsPantalla()
{
    int leds[] = {LED_PANTALLA1, LED_PANTALLA2, LED_PANTALLA3, LED_PANTALLA4, LED_PANTALLA5};
    for (int i = 0; i < 5; i++)
    {
        pinMode(leds[i], OUTPUT);
        digitalWrite(leds[i], LOW);
    }
}

// =============================================================
// FUNCIÓN: activarLedPantalla(int id)
// -------------------------------------------------------------
// Enciende el LED correspondiente a la pantalla actual y apaga
// los demás. El parámetro 'id' es el número de pantalla activa.
// =============================================================
void actualizarLedsPantalla()
{
    LiquidScreen *pantallaActual = menu.get_currentScreen();

    // Apaga todos los LEDs primero
    digitalWrite(LED_PANTALLA1, LOW);
    digitalWrite(LED_PANTALLA2, LOW);
    digitalWrite(LED_PANTALLA3, LOW);
    digitalWrite(LED_PANTALLA4, LOW);
    digitalWrite(LED_PANTALLA5, LOW);

    // Enciende solo el LED correspondiente
    if (pantallaActual == &pantalla1)
        digitalWrite(LED_PANTALLA1, HIGH);
    else if (pantallaActual == &pantalla2)
        digitalWrite(LED_PANTALLA2, HIGH);
    else if (pantallaActual == &pantalla3)
        digitalWrite(LED_PANTALLA3, HIGH);
    else if (pantallaActual == &pantalla4)
        digitalWrite(LED_PANTALLA4, HIGH);
    else if (pantallaActual == &pantalla5)
        digitalWrite(LED_PANTALLA5, HIGH);
}

// =============================================================
// FUNCIÓN: parpadearLedActual(umbralSuperado)
// -------------------------------------------------------------
// Hace titilar el LED de la pantalla actual si el valor del
// sensor supera su umbral. Se usa dentro de las lecturas.
// =============================================================
void parpadearLedPantallaActual(bool umbralSuperado)
{
    LiquidScreen *pantallaActual = menu.get_currentScreen();
    if (pantallaActual == nullptr)
        return;

    int led = -1;

    if (pantallaActual < nullptr)
        return; // Evita errores si no hay pantalla activa
    else if (pantallaActual == &pantalla1)
        led = LED_PANTALLA1;
    else if (pantallaActual == &pantalla2)
        led = LED_PANTALLA2;
    else if (pantallaActual == &pantalla3)
        led = LED_PANTALLA3;
    else if (pantallaActual == &pantalla4)
        led = LED_PANTALLA4;
    else if (pantallaActual == &pantalla5)
        led = LED_PANTALLA5;

    if (led == -1)
        return;

    if (umbralSuperado)
    {
        unsigned long ahora = millis();
        if (ahora - ultimoParpadeo >= 250)
        { // cada 300 ms cambia
            estadoLED = !estadoLED;
            digitalWrite(led, estadoLED);
            ultimoParpadeo = ahora;
        }
    }
    else
    {
        digitalWrite(led, HIGH); // si no hay umbral, se mantiene fijo
        estadoLED = true;
    }
}

#endif //_LCD_GUIA_H