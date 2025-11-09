#ifndef _MQ135_H
#define _MQ135_H

#include <Arduino.h>

// ===================== CONFIGURACIÓN =====================
constexpr uint8_t MQ135_PIN = A2;     // Pin analógico del sensor
constexpr float RL = 1.0;             // Resistencia de carga (kΩ)
constexpr float CLEAN_AIR_RATIO = 9.8; // RS/RO en aire limpio

// ===================== VARIABLES =====================
float RO = 10.0;       // Resistencia base (aire limpio)
float RS = 0.0;        // Resistencia actual del sensor
float ratio = 0.0;     // Relación RS/RO
float ratio_anterior = 0;
String calidad = "Desconocida";
String tendencia = "Estable";

// ===================== CALIBRACIÓN =====================
inline void calibrarMQ135() {
    float RS_sum = 0.0;

    // Promedia 50 lecturas en aire limpio
    for (uint8_t i = 0; i < 50; i++) {
        int adc = analogRead(MQ135_PIN);
        if (adc == 0) adc = 1;
        float rs = RL * (1023.0 / adc - 1.0);
        RS_sum += rs;
        delay(100);
    }

    RS = RS_sum / 100.0;
    RO = RS / CLEAN_AIR_RATIO;
}

// ===================== LECTURA =====================
inline float leerMQ135() {
    int adc = analogRead(MQ135_PIN);
    if (adc == 0) adc = 1;

    RS = RL * (1023.0 / adc - 1.0);
    ratio = RS / RO;

    // Clasificación del aire
    if (ratio > 3.0)      calidad = F("Excelente");
    else if (ratio > 2.0) calidad = F("Buena");
    else if (ratio > 1.5) calidad = F("Regular");
    else if (ratio > 1.0) calidad = F("Mala");
    else                  calidad = F("Crítica");

    // Tendencia
    if (ratio > ratio_anterior + 0.1)      tendencia = F("Empeorando ↑");
    else if (ratio < ratio_anterior - 0.1) tendencia = F("Mejorando ↓");
    else                                   tendencia = F("Estable →");

    ratio_anterior = ratio;
    return ratio;
}

// ===================== INICIO =====================
inline void iniciarMQ135() {
    pinMode(MQ135_PIN, INPUT);
    calibrarMQ135();
}

#endif
