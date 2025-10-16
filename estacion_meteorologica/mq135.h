#ifndef _MQ135_H
#define _MQ135_H

#include <Arduino.h>

// -----------------------------
// CONFIGURACIÓN DEL SENSOR
// -----------------------------
#define MQ135_PIN A0
#define LED_ALERTA_GAS 3   // LED indicador de gas
#define RL 1.0              // Resistencia de carga (kΩ)
#define CLEAN_AIR_RATIO 9.8 // Relación RS/RO en aire limpio (del datasheet)

// -----------------------------
// VARIABLES GLOBALES
// -----------------------------
float RO = 10.0;  // Valor inicial de RO (se calibra una vez)
float RS = 0.0;   // Resistencia medida
int VALOR = 0;    // Lectura analógica

// -----------------------------
// CALIBRACIÓN DEL SENSOR
// -----------------------------
// Se llama solo una vez, en aire limpio, para obtener RO
void calibrarMQ135() {
    Serial.println("Calibrando MQ-135... Espera 10 segundos en aire limpio...");
    float RS_sum = 0.0;

    for (int i = 0; i < 100; i++) {
        int adc = analogRead(MQ135_PIN);
        float rs = RL * (1023.0 / adc - 1.0);
        RS_sum += rs;
        delay(100);
    }

    RS = RS_sum / 100.0;
    RO = RS / CLEAN_AIR_RATIO;

    // Serial.print("Calibración completada. RO = ");
    // Serial.print(RO);
    // Serial.println(" kΩ");
}

// -----------------------------
// FUNCIÓN: Leer valor actual
// -----------------------------
float leerMQ135() {
    int adc = analogRead(MQ135_PIN);
    RS = RL * (1023.0 / adc - 1.0);
    float ratio = RS / RO; // Relación RS/RO

    // Estimación de calidad del aire (más ratio = aire más limpio)
    // int calidad;
    // if (ratio > 3.0)
    //     calidad = 1; // Muy buena
    // else if (ratio > 2.0)
    //     calidad = 2; // Buena
    // else if (ratio > 1.5)
    //     calidad = 3; // Regular
    // else
    //     calidad = 4; // Mala

    // Activar LED si hay contaminación alta
    // if (calidad >= 4)
    //     digitalWrite(LED_ALERTA_GAS, HIGH);
    // else
    //     digitalWrite(LED_ALERTA_GAS, LOW);

    // Mostrar por consola
    // Serial.print("RS: ");
    // Serial.print(RS, 2);
    // Serial.print(" kΩ  |  RO: ");
    // Serial.print(RO, 2);
    // Serial.print(" kΩ  |  RS/RO: ");
    // Serial.print(ratio, 2);
    // Serial.print("  |  Calidad: ");
    // Serial.println(calidad);

    // Devolver el ratio (útil para guardar en SD)
    return ratio;
}

// -----------------------------
// SETUP DEL SENSOR
// -----------------------------
void iniciarMQ135() {
    pinMode(MQ135_PIN, INPUT);
    pinMode(LED_ALERTA_GAS, OUTPUT);
    calibrarMQ135(); // calibrar al inicio (solo una vez idealmente)
}

#endif
