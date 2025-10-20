#ifndef _BME280_H
#define _BME280_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>    // Librería base de sensores Adafruit
#include <Adafruit_BME280.h>    // Librería específica del BME280

// -------------------------------------------------------------------
// OBJETO DEL SENSOR
// -------------------------------------------------------------------
/*
 * El objeto `bme` permite acceder a las funciones de lectura del sensor BME280.
 * Este módulo utiliza comunicación I2C (SDA y SCL).
 */
Adafruit_BME280 bme;

// -------------------------------------------------------------------
// VARIABLES GLOBALES DE LECTURA
// -------------------------------------------------------------------
/*
 * Estas variables almacenan los valores más recientes de las mediciones.
 * Se definen como `float` por la precisión de los datos que entrega el BME280.
 */
float temp_bme280 = 0.0;    // Temperatura ambiental en grados Celsius (°C)
float presion_bme280 = 0.0; // Presión atmosférica en hectopascales (hPa)
float humedad_bme280 = 0.0; // Humedad relativa en porcentaje (%)
float p0_bme = 0.0;         // Presión de referencia (nivel del mar) usada para calcular altitud

// -------------------------------------------------------------------
// FUNCIÓN: Inicializar el sensor BME280
// -------------------------------------------------------------------
/*
 * Esta función configura la comunicación con el sensor BME280.
 * - Usa la dirección I2C por defecto (0x76). Algunos módulos usan 0x77.
 * - Si el sensor no se detecta, el programa se detiene (loop infinito).
 * - Guarda la presión actual como referencia base para calcular altitud.
 */
void iniciarBME() {
    Serial.begin(9600);
    Serial.println("Iniciando BME280...");

    // Dirección I2C: 0x76 o 0x77 según el módulo
    if (!bme.begin(0x76)) {
        Serial.println("⚠️ Error: No se detecta el sensor BME280. Revisa las conexiones SDA y SCL.");
        while (1); // Detiene el programa (solo útil para depuración)
    }

    // Lee y guarda la presión actual como referencia (nivel del mar)
    p0_bme = bme.readPressure() / 100.0F;

    Serial.println("BME280 iniciado correctamente.");
}

// -------------------------------------------------------------------
// FUNCIÓN: Leer datos del sensor BME280
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
void leerBME() {
    temp_bme280 = bme.readTemperature();
    presion_bme280 = bme.readPressure() / 100.0F; // Conversión de Pa → hPa
    humedad_bme280 = bme.readHumidity();

    // --- DEBUG OPCIONAL ---
    // Serial.print("Temperatura: ");
    // Serial.print(temp_bme280);
    // Serial.print(" °C | Presión: ");
    // Serial.print(presion_bme280);
    // Serial.print(" hPa | Humedad: ");
    // Serial.print(humedad_bme280);
    // Serial.print(" % | Altitud: ");
    // Serial.print(bme.readAltitude(p0_bme)); // Calcula altitud estimada
    // Serial.println(" m");
}

#endif
