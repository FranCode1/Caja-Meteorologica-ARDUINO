#include "leds_guia.h"
#include "lcd.h"

// =====================================================
// ARREGLO DE LEDS (constante en tiempo de compilación)
// =====================================================
const uint8_t ledsPantalla[TOTAL_PANTALLAS] = {
    LED_PANTALLA1,
    LED_PANTALLA2,
    LED_PANTALLA3,
    LED_PANTALLA4,
    LED_PANTALLA5};

// =====================================================
// INICIALIZACIÓN
// =====================================================
void iniciarLedsPantalla()
{
    for (uint8_t i = 0; i < TOTAL_PANTALLAS; i++)
    {
        pinMode(ledsPantalla[i], OUTPUT);
        digitalWrite(ledsPantalla[i], LOW);
    }

    // Encender LED inicial (pantallaActual empieza en 1)
    if (pantallaActual >= 1 && pantallaActual <= TOTAL_PANTALLAS)
    {
        digitalWrite(ledsPantalla[pantallaActual - 1], HIGH);
    }

    //DEBUG_PRINTLN(F("✅ LEDs de pantalla inicializados"));
}

// =====================================================
// CAMBIAR LED SEGÚN LA PANTALLA
// =====================================================
void cambiarLedPantalla(uint8_t nuevaPantalla)
{
    static uint8_t pantallaPrev = 255; // inválido

    if (nuevaPantalla < 1 || nuevaPantalla > TOTAL_PANTALLAS)
        return;

    if (nuevaPantalla == pantallaPrev)
        return;

    // Apagar/encender
    for (uint8_t i = 0; i < TOTAL_PANTALLAS; i++)
    {
        digitalWrite(ledsPantalla[i], (i == nuevaPantalla - 1) ? HIGH : LOW);
    }

    //DEBUG_PRINT(F("🔵 LED activo para pantalla: "));
    //DEBUG_PRINTLN(nuevaPantalla);

    pantallaPrev = nuevaPantalla;
}
