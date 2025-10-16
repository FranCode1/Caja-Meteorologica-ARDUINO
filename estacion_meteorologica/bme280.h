#ifndef _BME280_H
#define _BME280_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;  // Objeto del sensor BME280

// Variables globales del sensor BME280
float temp_bme;       // Temperatura en °C
float presion_bme;    // Presión en hPa
float humedad_bme;    // Humedad en %
float p0_bme;         // Presión base (para calcular altitud)

// -------------------------------------------------------------------
// Inicialización del sensor
// -------------------------------------------------------------------
void iniciarBME() {
    Serial.begin(9600);
    Serial.println("Iniciando BME280...");

    if (!bme.begin(0x76)) { // Dirección típica: 0x76 o 0x77
        Serial.println("⚠️ Error: BME280 no encontrado.");
        while (1);
    }

    // Guarda la presión actual como referencia (nivel del mar)
    p0_bme = bme.readPressure() / 100.0F;
    Serial.println("BME280 iniciado correctamente.");
}

// -------------------------------------------------------------------
// Lectura del sensor
// -------------------------------------------------------------------
void leerBME() {
    temp_bme = bme.readTemperature();
    presion_bme = bme.readPressure() / 100.0F;
    humedad_bme = bme.readHumidity();

    // Serial.print("Temperatura: ");
    // Serial.print(temp_bme);
    // Serial.print(" °C | Presión: ");
    // Serial.print(presion_bme);
    // Serial.print(" hPa | Humedad: ");
    // Serial.print(humedad_bme);
    // Serial.print(" % | Altitud: ");
    // Serial.print(bme.readAltitude(p0_bme));
    // Serial.println(" m");
}

#endif

