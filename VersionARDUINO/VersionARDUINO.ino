// =====================================================
// ESTACIÓN METEOROLÓGICA - PROGRAMA PRINCIPAL
// =====================================================
#include "config.h"

// ---------------- LIBRERÍAS ----------------
#include <Wire.h>
#include "lcd.h"
#include "navegacion.h"

// ---------------- MÓDULOS ----------------
#include "bmp280.h"
// #include "ds18b20.h"
#include "csmsv2.h"
#include "bh1750.h"
#include "mq135.h"
#include "gy906.h"
#include "ds3231.h"
#include "microsd.h"
#include "leds_guia.h"

// =====================================================
// SETUP
// =====================================================
void setup()
{
    Serial.begin(9600);
    Wire.begin();

    iniciarLCD();
    iniciarLedsPantalla();

    iniciarRTC();
    iniciarBMP();
    iniciarBH1750();
    iniciarGY906();
    // iniciarDS18B20();
    iniciarCSMSV2();
    iniciarMQ135();
    iniciarNavegacion();
    iniciarSD();
}

// =====================================================
// LOOP PRINCIPAL
// =====================================================
void loop()
{
    // leerNavegacion(); // Deshabilitado - cambio automático de pantallas
    leerRTC();
    leerBMP();
    delay(10); // Pequeño delay para evitar interferencia entre I2C y analógico
    leerBH1750();
    leerGY906();
    // leerDS18B20();
    leerCSMSV2();
    calibrarMQ135();
    leerMQ135();

    // --- Escritura controlada en SD cada 5 segundos ---
    static unsigned long ultimoSD = 0;
    if (millis() - ultimoSD >= 5000)
    {
        escribirSD("registro.txt");
        ultimoSD = millis();
    }

    // --- LED indicador de pantalla ---
    cambiarLedPantalla(pantallaActual);

    // --- Actualizar pantalla cada 500 ms ---
    static unsigned long ultimoLCD = 0;
    if (millis() - ultimoLCD >= 500)
    {
        actualizarLCD();
        ultimoLCD = millis();
    }
}
