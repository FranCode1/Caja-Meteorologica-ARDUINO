#ifndef _BMP280_H
#define _BMP280_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>    // Librería base de sensores Adafruit
#include <Adafruit_BMP280.h>    // Librería específica del BMP280

// -------------------------------------------------------------------
// OBJETO DEL SENSOR
// -------------------------------------------------------------------
/*
 * El objeto `bmp` permite acceder a las funciones de lectura del sensor BMP280.
 * Este módulo utiliza comunicación I2C (SDA y SCL).
 */
Adafruit_BMP280 bmp;

// -------------------------------------------------------------------
// VARIABLES GLOBALES DE LECTURA
// -------------------------------------------------------------------
/*
 * Estas variables almacenan los valores más recientes de las mediciones.
 * Se definen como `float` por la precisión de los datos que entrega el BME280.
 */
float temp_bmp280 = 0.0;    // Temperatura ambiental en grados Celsius (°C)
float presion_bmp280 = 0.0; // Presión atmosférica en hectopascales (hPa)
float altitud_bmp280 = 0.0; // Altitud calculada en metros (m)
float p0_bmp = 0.0;         // Presión de referencia (nivel del mar) usada para calcular altitud

// -------------------------------------------------------------------
// CONFIGURACIÓN DEL LED DE ALERTA
// -------------------------------------------------------------------
#define LED_ALERTA_BMP 6 // 🔴 numero de pin del led

// Umbrales de seguridad para activar el led
#define TEMP_MAX 35.0      // Temperatura máxima segura (°C)
#define PRESION_MIN 950.0  // Presión muy baja (posible tormenta)
#define PRESION_MAX 1050.0 // Presión muy alta (posible clima extremo)
#define ALTITUD_MAX 300.0  // Altitud fuera del rango esperado

// -------------------------------------------------------------------
// FUNCIÓN: Inicializar el sensor BME280
// -------------------------------------------------------------------
/*
 * Esta función configura la comunicación con el sensor BMP280.
 * - Usa la dirección I2C por defecto (0x76). Algunos módulos usan 0x77.
 * - Si el sensor no se detecta, el programa se detiene (loop infinito).
 * - Guarda la presión actual como referencia base para calcular altitud.
 */
void iniciarBMP() {
    Serial.begin(9600);
    Serial.println("Iniciando BMP280...");

    pinMode(LED_ALERTA_BMP, OUTPUT);
    digitalWrite(LED_ALERTA_BMP, LOW);

    // Dirección I2C: 0x76 o 0x77 según el módulo
    if (!bmp.begin(0x76)) {
        Serial.println("Error: No se detecta el sensor BMP280. Revisa las conexiones SDA y SCL.");
        while (1); // Detiene el programa (solo útil para depuración)
    }

    // Lee y guarda la presión actual como referencia (nivel del mar)
    p0_bmp = bmp.readPressure() / 100.0F;

    Serial.println("BMP280 iniciado correctamente.");
}

// -------------------------------------------------------------------
// FUNCIÓN: Leer datos del sensor BMP280
// -------------------------------------------------------------------
/*
 * Esta función obtiene las últimas mediciones del sensor:
 *  - Temperatura ambiente (°C)
 *  - Presión atmosférica (hPa)
 *  - Humedad relativa (%)
 *
 * Los valores se guardan en las variables globales, listas para ser
 * mostradas en pantalla o almacenadas en la microSD.
 */
void leerBMP() {
    temp_bmp280 = bmp.readTemperature();
    presion_bmp280 = bmp.readPressure() / 100.0F; // Conversión de Pa → hPa
    altitud_bmp280 = 44330 * (1.0 - pow(presion / 1013.25, 0.1903));

    bool peligro = false;

    // --- Condiciones peligrosas ---
    if (temp_bmp280 > TEMP_MAX)
        peligro = true;
    if (presion_bmp280 < PRESION_MIN || presion_bmp280 > PRESION_MAX)
        peligro = true;
    if (altitud_bmp280 > ALTITUD_MAX)
        peligro = true;

    // --- Control del LED ---
    if (peligro)
    {
        digitalWrite(LED_ALERTA_BMP, HIGH); // 🔴 Enciende LED de alerta
    }
    else
    {
        digitalWrite(LED_ALERTA_BMP, LOW); // 🟢 Apaga LED
    }
}

#endif
