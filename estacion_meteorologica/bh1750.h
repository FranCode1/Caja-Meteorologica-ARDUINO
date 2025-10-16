#ifndef _BH1750_H
#define _BH1750_H

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

// -------------------------------------------------------------------
// CONFIGURACIÓN DEL SENSOR DE LUZ BH1750
// -------------------------------------------------------------------
BH1750 sensorBH1750;

float lux = 0;              // Variable global para guardar el valor medido
// const int UMBRAL_LUZ = 30;  // Umbral para detección de baja luz
// const int PIN_LED = 13;     // Pin de LED de aviso (puedes cambiarlo)

// -------------------------------------------------------------------
// INICIALIZACIÓN DEL SENSOR
// -------------------------------------------------------------------
void iniciarBH1750() {
    Wire.begin();
    sensorBH1750.begin();
    // pinMode(PIN_LED, OUTPUT);
    Serial.println("Sensor BH1750 iniciado correctamente.");
}

// -------------------------------------------------------------------
// LECTURA DEL SENSOR DE LUZ
// -------------------------------------------------------------------
void leerBH1750() {
    lux = sensorBH1750.readLightLevel();

    // Serial.print("Nivel de luz: ");
    // Serial.print(lux);
    // Serial.println(" lx");

    // // Lógica de control según el nivel de luz
    // if (lux < UMBRAL_LUZ) {
    //     digitalWrite(PIN_LED, HIGH);  // Luz ambiental baja
    // } else if (lux > UMBRAL_LUZ + 20) {
    //     digitalWrite(PIN_LED, LOW);   // Luz ambiental alta
    // }
}

#endif
