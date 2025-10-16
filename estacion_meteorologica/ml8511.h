#ifndef _ML8511_H
#define _ML8511_H

#include <Arduino.h>

// Pines
const int UVOUT = A0;
const int REF_3V3 = A1;
const int LED_ALERTA = 3;

// Variables
float voltaje = 0.0;
float uvIndex = 0.0;
String riesgo = "";

// ---------------------------
// Inicialización del sensor
// ---------------------------
void iniciarML8511() {
    pinMode(UVOUT, INPUT);
    pinMode(REF_3V3, INPUT);
    // pinMode(LED_ALERTA, OUTPUT);
    // digitalWrite(LED_ALERTA, LOW);
    Serial.println("Sensor UV ML8511 iniciado");
}

// ---------------------------
// Lectura promedio analógica
// ---------------------------
int averageAnalogRead(int pinToRead) {
    const byte numberOfReadings = 8;
    unsigned int runningValue = 0;

    for (int x = 0; x < numberOfReadings; x++) {
        runningValue += analogRead(pinToRead);
        delay(5);
    }
    return runningValue / numberOfReadings;
}

// ---------------------------
// Mapeo flotante (como map())
// ---------------------------
// float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
//     return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

// ---------------------------
// Cálculo del índice UV
// ---------------------------
float calcularIndiceUV(float voltaje) {
    float indice = (voltaje - 1.0) * (15.0 / (2.9 - 1.0)); // 1V → 0UV, 2.9V → 15UV
    if (indice < 0) indice = 0;
    return indice;
}

// ---------------------------
// Clasificación del riesgo
// ---------------------------
// String calcularRiesgo(float indice) {
//     if (indice <= 0) return "Ninguno";
//     else if (indice <= 2) return "Bajo";
//     else if (indice <= 5) return "Moderado";
//     else if (indice <= 7) return "Alto";
//     else if (indice <= 10) return "Muy Alto";
//     else return "Extremo";
// }

// ---------------------------
// Lectura general del sensor
// ---------------------------
// void leerUV() {
void leerML8511() {
    int uvLevel = averageAnalogRead(UVOUT);
    int refLevel = averageAnalogRead(REF_3V3);

    float outputVoltage = 3.3 / refLevel * uvLevel;
    uvIndex = calcularIndiceUV(outputVoltage);
    // riesgo = calcularRiesgo(uvIndex);

    // if (uvIndex >= 6)
    //     digitalWrite(LED_ALERTA, HIGH);
    // else
    //     digitalWrite(LED_ALERTA, LOW);

    // Serial.print("Voltaje: ");
    // Serial.print(outputVoltage, 2);
    // Serial.print(" V | UV Index: ");
    // Serial.print(uvIndex, 1);
    // Serial.print(" | Riesgo: ");
    // Serial.println(riesgo);
}

#endif
