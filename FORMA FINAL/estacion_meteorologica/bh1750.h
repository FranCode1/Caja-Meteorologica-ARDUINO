#ifndef _BH1750_H
#define _BH1750_H

#include <Arduino.h>
#include <BH1750.h>

// ===================== SENSOR =====================
BH1750 sensorBH1750; // Comunicación I2C (SDA, SCL)

// ===================== VARIABLES =====================
float lux = 0.0F; // Nivel de luz ambiental en lux

// ===================== INICIO =====================
inline void iniciarBH1750() {
    // Wire.begin(); // Si no se inicializa en otro módulo
    sensorBH1750.begin();
}

// ===================== LECTURA =====================
inline void leerBH1750() {
    lux = sensorBH1750.readLightLevel();
}

#endif
