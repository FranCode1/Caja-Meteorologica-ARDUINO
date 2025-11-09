#ifndef _DS18B20_H
#define _DS18B20_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ===================== CONFIGURACIÓN =====================
#define DS18B20_PIN 2          // Pin de datos OneWire
#define TEMP_MAX_DS18B20 37.0  // Temperatura máxima segura
#define TEMP_MIN_DS18B20 -10.0 // Temperatura mínima opcional

// ===================== OBJETOS =====================
static OneWire oneWire(DS18B20_PIN);   // Comunicación OneWire
static DallasTemperature sensors(&oneWire); // Controlador del sensor

// ===================== VARIABLE =====================
static float temp_ds18b20 = 0.0; // Temperatura actual (°C)

// ===================== INICIO =====================
inline void iniciarDS18B20() {
    sensors.begin();  // Inicia comunicación
}

// ===================== LECTURA =====================
inline void leerDS18B20() {
    sensors.requestTemperatures();              // Solicita medición
    temp_ds18b20 = sensors.getTempCByIndex(0);  // Lee temperatura
}

#endif
