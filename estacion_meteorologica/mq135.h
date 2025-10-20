#ifndef _MQ135_H
#define _MQ135_H

#include <Arduino.h>

// =====================================================================
// CONFIGURACIÓN DEL SENSOR MQ-135
// =====================================================================
// El sensor MQ-135 detecta gases como CO2, amoníaco, benceno, alcohol, humo, etc.
// Funciona midiendo la variación de su resistencia interna (RS) según la concentración de gases.
// Su salida analógica se conecta a un pin ADC (A0, por ejemplo).

#define MQ135_PIN A0              // Pin analógico donde está conectado el sensor MQ-135
#define LED_ALERTA_GAS 3          // Pin del LED indicador que se enciende si hay alta concentración
#define RL 1.0                    // Resistencia de carga del circuito en kiloohmios (valor típico: 1kΩ)
#define CLEAN_AIR_RATIO 9.8       // Relación RS/RO en aire limpio según el datasheet del MQ-135

// =====================================================================
// VARIABLES GLOBALES
// =====================================================================
// Estas variables guardan los valores medidos y calibrados para ser reutilizadas
float RO = 10.0;  // Valor de RO (resistencia del sensor en aire limpio) - se obtiene en la calibración
float RS = 0.0;   // Resistencia actual del sensor (en funcionamiento)
int VALOR = 0;    // Valor leído del ADC (0 a 1023)
float ratio = 0.0;  // Relación RS/RO actual

// =====================================================================
// FUNCIÓN: calibrarMQ135()
// =====================================================================
// Objetivo: Calibrar el sensor en aire limpio para determinar el valor base RO.
// - RO representa la resistencia del sensor cuando el aire está limpio.
// - Este valor se utiliza luego para calcular la relación RS/RO, que indica el nivel de gases.
// - Esta calibración debe hacerse una sola vez, idealmente al iniciar el sistema o en laboratorio.
//
// ⚠️ IMPORTANTE: No calibrar si el sensor está en un ambiente contaminado, ya que eso alterará los resultados.
void calibrarMQ135() {
    Serial.println("Calibrando MQ-135... Espera 10 segundos en aire limpio...");
    float RS_sum = 0.0;

    // Se toman 100 muestras del sensor para hacer un promedio más estable
    for (int i = 0; i < 100; i++) {
        int adc = analogRead(MQ135_PIN);               // Leer valor analógico (0–1023)
        if (adc == 0) adc = 1;  // Evita división por cero
        float rs = RL * (1023.0 / adc - 1.0);          // Calcular resistencia RS usando la fórmula del divisor de tensión
        RS_sum += rs;                                  // Acumular lecturas
        delay(100);                                    // Pequeña pausa entre lecturas
    }

    // Promedio de todas las lecturas
    RS = RS_sum / 100.0;

    // Calcular RO (resistencia en aire limpio)
    RO = RS / CLEAN_AIR_RATIO;

    // Serial.print("Calibración completada. RO = ");
    // Serial.print(RO);
    // Serial.println(" kΩ");
}

// =====================================================================
// FUNCIÓN: leerMQ135()
// =====================================================================
// Lee el valor actual del sensor, calcula la relación RS/RO y devuelve un valor numérico.
//
// - RS (resistencia instantánea del sensor) cambia según la concentración de gases.
// - RO (resistencia en aire limpio) es el valor de referencia calculado en la calibración.
// - La relación RS/RO se usa como indicador de calidad del aire:
//     >3.0  → Aire muy limpio
//     2.0–3.0 → Bueno
//     1.5–2.0 → Regular
//     <1.5  → Contaminado
//
// Esta función devuelve solo el *ratio RS/RO*, que se puede registrar o usar en condiciones de control.
float leerMQ135() {
    int adc = analogRead(MQ135_PIN);             // Leer señal analógica del sensor (0–1023)
    if (adc == 0) adc = 1; // Previene división por cero

    RS = RL * (1023.0 / adc - 1.0);              // Calcular RS a partir del valor analógico
    ratio = RS / RO;                       // Calcular la relación RS/RO

    // --- OPCIONAL: Determinar calidad del aire ---
    // int calidad;
    // if (ratio > 3.0)
    //     calidad = 1; // Muy buena
    // else if (ratio > 2.0)
    //     calidad = 2; // Buena
    // else if (ratio > 1.5)
    //     calidad = 3; // Regular
    // else
    //     calidad = 4; // Mala

    // --- OPCIONAL: Encender LED si el aire está contaminado ---
    // if (calidad >= 4)
    //     digitalWrite(LED_ALERTA_GAS, HIGH);
    // else
    //     digitalWrite(LED_ALERTA_GAS, LOW);

    // --- OPCIONAL: Mostrar datos por Serial ---
    // Serial.print("RS: ");
    // Serial.print(RS, 2);
    // Serial.print(" kΩ  |  RO: ");
    // Serial.print(RO, 2);
    // Serial.print(" kΩ  |  RS/RO: ");
    // Serial.print(ratio, 2);
    // Serial.print("  |  Calidad: ");
    // Serial.println(calidad);

    // Retornar el valor RS/RO para guardar en SD o mostrar en LCD
    return ratio;
}

// =====================================================================
// FUNCIÓN: iniciarMQ135()
// =====================================================================
// Inicializa los pines del sensor y realiza la calibración inicial.
// Esta función debe llamarse en setup().
void iniciarMQ135() {
    pinMode(MQ135_PIN, INPUT);           // Configura el pin de lectura analógica
    pinMode(LED_ALERTA_GAS, OUTPUT);     // Configura el LED indicador de gas
    calibrarMQ135();                     // Calibrar el sensor (solo una vez idealmente)
}

#endif
