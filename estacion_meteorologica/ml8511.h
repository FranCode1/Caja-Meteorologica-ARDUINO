#ifndef _ML8511_H
#define _ML8511_H

#include <Arduino.h>

// ===================================================================
// ☀️ MÓDULO: ML8511 - Sensor de Radiación Ultravioleta (UV)
// -------------------------------------------------------------------
// Este archivo permite inicializar y leer el sensor ML8511,
// el cual mide el nivel de radiación UV ambiental y devuelve
// un índice UV estimado de 0 a 15.
//
// ✅ Requiere alimentación de 3.3V (no 5V directamente)
// ✅ El pin de salida UVOUT debe conectarse a una entrada analógica
//
// 📘 Conexión típica:
//   - 3.3V  → VCC
//   - GND   → GND
//   - A0    → UVOUT
//   - A1    → REF_3V3 (referencia de 3.3V)
//
// ===================================================================

// -------------------------------------------------------------------
// DEFINICIÓN DE PINES
// -------------------------------------------------------------------
const int UVOUT = A0;       // Pin analógico conectado a la salida del sensor
const int REF_3V3 = A1;     // Pin conectado a una referencia estable de 3.3V
const int LED_ALERTA = 3;   // (Opcional) LED de advertencia por radiación alta

// -------------------------------------------------------------------
// VARIABLES GLOBALES
// -------------------------------------------------------------------
float uvIndex = 0.0;        // Último valor de índice UV medido

// -------------------------------------------------------------------
// FUNCIÓN: iniciarML8511()
// -------------------------------------------------------------------
/**
 * @brief Inicializa el sensor ML8511 y sus pines.
 *
 * Configura los pines de entrada para el sensor UV y la referencia.
 * Puede activarse un LED de alerta (opcional).
 */
void iniciarML8511() {
    pinMode(UVOUT, INPUT);
    pinMode(REF_3V3, INPUT);
    // pinMode(LED_ALERTA, OUTPUT);
    // digitalWrite(LED_ALERTA, LOW);

    Serial.println("Sensor UV ML8511 iniciado correctamente.");
}

// -------------------------------------------------------------------
// FUNCIÓN: averageAnalogRead()
// -------------------------------------------------------------------
/**
 * @brief Realiza una lectura analógica promediada para reducir ruido.
 *
 * @param pinToRead Pin analógico a leer.
 * @return Valor promedio (0–1023).
 */
int averageAnalogRead(int pinToRead) {
    const byte numberOfReadings = 8;
    unsigned int runningValue = 0;

    for (int i = 0; i < numberOfReadings; i++) {
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

// -------------------------------------------------------------------
// FUNCIÓN: calcularIndiceUV()
// -------------------------------------------------------------------
/**
 * @brief Convierte el voltaje de salida del sensor en índice UV.
 *
 * Rango típico del ML8511:
 *   - 1.0 V → 0 UV
 *   - 2.9 V → 15 UV
 *
 * @param voltaje Voltaje medido (en voltios).
 * @return Índice UV estimado (0–15).
 */
float calcularIndiceUV(float voltaje) {
    float indice = (voltaje - 1.0) * (15.0 / (2.9 - 1.0));
    //quizas la formula del mapeo flotante es mejor
    //float indice = (voltaje - 1.0) * (15.0 / (2.9 - 1.0)); // 1V → 0UV, 2.9V → 15UV
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

// -------------------------------------------------------------------
// FUNCIÓN: leerML8511()
// -------------------------------------------------------------------
/**
 * @brief Lee el nivel de radiación UV y actualiza la variable global `uvIndex`.
 *
 * Promedia las lecturas analógicas de salida y referencia, calcula el
 * voltaje relativo del sensor, y estima el índice UV usando la curva típica.
 *
 * @note Si `LED_ALERTA` está habilitado, puede encenderse cuando el índice
 *       UV es mayor o igual a 6 (riesgo alto).
 */
void leerML8511() {
    int uvLevel = averageAnalogRead(UVOUT);
    int refLevel = averageAnalogRead(REF_3V3);

    // Conversión a voltaje real (referido a 3.3V)
    float outputVoltage = 3.3 * ((float)uvLevel / (float)refLevel);

    // Cálculo del índice UV
    uvIndex = calcularIndiceUV(outputVoltage);

    // --- LED de advertencia opcional ---
    // if (uvIndex >= 6)
    //     digitalWrite(LED_ALERTA, HIGH);
    // else
    //     digitalWrite(LED_ALERTA, LOW);

    // --- DEBUG OPCIONAL ---
    // Serial.print("☀️ Voltaje: ");
    // Serial.print(outputVoltage, 2);
    // Serial.print(" V | Índice UV: ");
    // Serial.println(uvIndex, 1);
}

#endif
