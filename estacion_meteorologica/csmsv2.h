#ifndef _CSMSV2_H
#define _CSMSV2_H

#include <Arduino.h>
#include "ds18b20.h" // Para compartir el LED de alerta

// ===================================================================
// MÓDULO: SENSOR DE HUMEDAD DE SUELO CAPACITIVO (V2.0)
// -------------------------------------------------------------------
// Este sensor mide la humedad del suelo mediante variaciones en su
// capacitancia. A diferencia de los sensores resistivos, este modelo
// no se corroe con el tiempo, ya que no tiene partes metálicas
// expuestas al agua.
//
// Funciona con salida analógica: cuanto más húmedo está el suelo,
// menor será la lectura analógica (valor ADC).
// ===================================================================

// -------------------------------------------------------------------
// PINES Y CONFIGURACIÓN
// -------------------------------------------------------------------
// Se define el pin analógico donde está conectado el sensor.
// Puede cambiarse según el proyecto (por ejemplo, A0, A1, A2...).
#define PIN_SENSOR_TIERRA A0 // Pin analógico del sensor
#define LED_ALERTA_TEMP 5 // 🔴 Mismo LED compartido con el DS18B20

// Umbrales de alerta
#define HUMEDAD_MIN_SEGURA 25 // Por debajo de este valor, el suelo está demasiado seco
#define HUMEDAD_MAX_SEGURA 90 // Por encima de este valor, el suelo está saturado o hay exceso de agua

// -------------------------------------------------------------------
// CALIBRACIÓN
// -------------------------------------------------------------------
// Los valores de "aire" y "agua" sirven como referencia para convertir
// la lectura analógica (0–1023 en Arduino UNO) en un porcentaje.
//
// Para calibrar correctamente:
//  1. Coloca el sensor completamente SECO (al aire libre) y anota
//     el valor leído → este será AIR_VALUE.
//  2. Luego sumérgelo en agua → ese valor será WATER_VALUE.
//
// Cuanto más húmedo el suelo, menor es la lectura.
// -------------------------------------------------------------------
const int AIR_VALUE = 588;   // Lectura típica en aire seco
const int WATER_VALUE = 308; // Lectura típica completamente sumergido

// -------------------------------------------------------------------
// VARIABLES GLOBALES
// -------------------------------------------------------------------
// Se guarda el porcentaje de humedad en esta variable global.
// Su valor será entre 0% (suelo completamente seco) y 100% (suelo húmedo).
int humedad_tierra = 0;
bool alerta_tierra = false; // Guarda si el sensor activó alerta (para compartir con otros sensores)

// -------------------------------------------------------------------
// FUNCIÓN: iniciarCSMSV2()
// -------------------------------------------------------------------
// Inicializa el sensor de humedad de suelo.
//
// Pasos que realiza:
//  - Configura el pin del sensor como entrada analógica.
//  - Imprime por Serial un mensaje de confirmación.
//
// NOTA: Aunque los pines analógicos no necesitan pinMode(INPUT),
//       mantenerlo explícito mejora la legibilidad y evita errores.
// -------------------------------------------------------------------
void iniciarCSMSV2() {
    pinMode(PIN_SENSOR_TIERRA, INPUT);
    pinMode(LED_ALERTA_TEMP, OUTPUT); // Compartido
    digitalWrite(LED_ALERTA_TEMP, LOW);
    Serial.println("Sensor de humedad de tierra iniciado correctamente.");
}

// -------------------------------------------------------------------
// FUNCIÓN: leerCSMSV2()
// -------------------------------------------------------------------
// Realiza una lectura analógica del sensor y convierte el valor en
// un porcentaje de humedad.
//
// Proceso:
//  1. Se lee el valor analógico con analogRead() (rango 0–1023).
//  2. Se aplica una transformación con la función map() para
//     convertir la lectura en porcentaje 0–100.
//  3. Se limita el resultado al rango válido (0–100%).
//
// Ejemplo de valores típicos:
//  - 580 → 0% (suelo completamente seco)
//  - 450 → 50% (suelo moderadamente húmedo)
//  - 320 → 100% (suelo saturado de agua)
// -------------------------------------------------------------------
void leerCSMSV2() {
    int lectura = analogRead(PIN_SENSOR_TIERRA);  // Lectura analógica del sensor
    
    humedad_tierra = map(lectura, AIR_VALUE, WATER_VALUE, 0, 100); // Convierte el valor analógico (AIR→WATER) a porcentaje (0→100)
    humedad_tierra = constrain(humedad_tierra, 0, 100); // Limita el valor dentro del rango 0–100%

    // Evaluar condición peligrosa
    alerta_tierra = (humedad_tierra < HUMEDAD_MIN_SEGURA || humedad_tierra > HUMEDAD_MAX_SEGURA);

    // --- Control del LED compartido ---
    if (alerta_tierra){
        digitalWrite(LED_ALERTA_TEMP, HIGH); // ⚠️ Enciende LED si hay peligro
    }
    else{
        // Solo apagar si el otro sensor (DS18B20) tampoco está en alerta
        // Esto requiere que el DS18B20 exponga su variable de estado
        extern bool alerta_temp;
        if (!alerta_temp){
            digitalWrite(LED_ALERTA_TEMP, LOW);
        }
    }

    // ---------------------------------------------------------------
    // (Opcional) Mostrar información por Serial
    // ---------------------------------------------------------------
    // Serial.print("Humedad tierra: ");
    // Serial.print(humedad_tierra);
    // Serial.print(" % | LED: ");
    // Serial.println(alerta_tierra ? "ENCENDIDO" : "OK");

    // ---------------------------------------------------------------
    // (Opcional) Estado del suelo según el nivel de humedad
    // ---------------------------------------------------------------
    // if (humedad_tierra > 70) {
    //     Serial.println("Tierra muy húmeda");
    // } else if (humedad_tierra > 40) {
    //     Serial.println("Tierra húmeda");
    // } else {
    //     Serial.println("Tierra seca");
    // }
}

#endif
