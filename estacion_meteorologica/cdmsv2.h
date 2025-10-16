#ifndef _CSMSV2_H
#define _CSMSV2_H

#include <Arduino.h>

// -------------------------------------------------------------------
// Configuración del sensor de humedad de suelo (Capacitive Soil Moisture v2.0)
// -------------------------------------------------------------------
#define PIN_SENSOR_TIERRA A0  // Pin analógico del sensor

// Valores calibrados (ajústalos según tus mediciones)
const int AIR_VALUE = 588;   // Lectura en aire seco
const int WATER_VALUE = 308; // Lectura sumergido en agua

// Variable global para guardar el porcentaje de humedad
int humedad_tierra = 0;

// -------------------------------------------------------------------
// Inicialización del sensor
// -------------------------------------------------------------------
void iniciarCSMSV2() {
    pinMode(PIN_SENSOR_TIERA, INPUT);
    Serial.println("Sensor de humedad de tierra iniciado correctamente.");
}

// -------------------------------------------------------------------
// Lectura de humedad de suelo (devuelve porcentaje 0-100)
// -------------------------------------------------------------------
void leerCSMSV2() {
    int lectura = analogRead(PIN_SENSOR_TIERRA);

    // Convierte el valor analógico a porcentaje (ajustado con tus valores de calibración)
    humedad_tierra = map(lectura, AIR_VALUE, WATER_VALUE, 0, 100);

    // Limita el rango (por seguridad)
    if (humedad_tierra > 100) humedad_tierra = 100;
    if (humedad_tierra < 0)   humedad_tierra = 0;

    // // Muestra el resultado
    // Serial.print("Humedad de tierra: ");
    // Serial.print(humedad_tierra);
    // Serial.println(" %");

    // // Estado de humedad
    // if (humedad_tierra > 70) {
    //     Serial.println("🌱 Tierra muy húmeda");
    // } else if (humedad_tierra > 40) {
    //     Serial.println("🌿 Tierra húmeda");
    // } else {
    //     Serial.println("🌾 Tierra seca");
    // }
}

#endif
