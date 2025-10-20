#ifndef _DS18B20_H
#define _DS18B20_H

#include <Arduino.h>
#include <OneWire.h>           // Librería base para la comunicación OneWire
#include <DallasTemperature.h> // Librería para manejar el sensor DS18B20

// ===================================================================
//  MÓDULO: DS18B20 - Sensor Digital de Temperatura
// -------------------------------------------------------------------
// Este archivo gestiona la lectura del sensor de temperatura DS18B20
// utilizando el protocolo OneWire. Permite inicializar el sensor y
// obtener lecturas de temperatura precisas en grados Celsius.
//
//  Requiere las librerías:
//    - OneWire
//    - DallasTemperature
//
//  Conexión típica:
//    - Rojo (VCC) → 5V o 3.3V
//    - Negro (GND) → GND
//    - Amarillo (DATA) → Pin digital definido en DS18B20_PIN
//    - Entre DATA y VCC debe colocarse una resistencia de 4.7kΩ
//
// ===================================================================

// -------------------------------------------------------------------
// CONFIGURACIÓN DEL PIN DE DATOS
// -------------------------------------------------------------------
#define DS18B20_PIN 2 // Pin digital del bus OneWire

// -------------------------------------------------------------------
// OBJETOS DE CONTROL DEL SENSOR
// -------------------------------------------------------------------

// Gestiona la comunicación en el pin definido
OneWire oneWire(DS18B20_PIN);

// Controlador del sensor DS18B20 (usa el bus OneWire anterior)
DallasTemperature sensors(&oneWire);

// -------------------------------------------------------------------
// VARIABLE GLOBAL DE LECTURA
// -------------------------------------------------------------------

// Guarda la temperatura actual medida (en grados Celsius)
float temp_ds18b20 = 0.0;

// -------------------------------------------------------------------
// FUNCIÓN: iniciarDS18B20()
// -------------------------------------------------------------------
/**
 * @brief Inicializa la comunicación con el sensor DS18B20.
 *
 * Esta función debe llamarse una vez, generalmente dentro del setup().
 * Configura el bus OneWire y detecta automáticamente los sensores
 * conectados en la línea de datos.
 *
 * En caso de haber múltiples sensores en el mismo bus, se pueden leer
 * individualmente mediante su dirección o índice.
 */
void iniciarDS18B20() {
    sensors.begin();  // Inicia la comunicación con el sensor
    Serial.println("Sensor DS18B20 iniciado correctamente.");
}

// -------------------------------------------------------------------
// FUNCIÓN: leerDS18B20()
// -------------------------------------------------------------------
/**
 * @brief Lee la temperatura actual desde el sensor DS18B20.
 *
 * Envía una solicitud de medición de temperatura y actualiza el valor
 * global `temp_ds18b20` con el resultado.
 *
 * @note Si hay más de un sensor en el mismo bus, puedes leer otros
 *       sensores cambiando el índice en `getTempCByIndex(n)`.
 *
 * @example
 *     leerDS18B20();
 *     Serial.println(temp_ds18b20);
 */
void leerDS18B20() {
    sensors.requestTemperatures();           // Envía comando de lectura
    temp_ds18b20 = sensors.getTempCByIndex(0); // Lee la temperatura del primer sensor

    // --- DEBUG OPCIONAL ---
    // Serial.print("🌡️ Temperatura DS18B20: ");
    // Serial.print(temp_ds18b20);
    // Serial.println(" °C");
}

#endif
