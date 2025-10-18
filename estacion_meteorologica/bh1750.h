#ifndef _BH1750_H
#define _BH1750_H

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

// ===================================================================
// MÓDULO: SENSOR DE LUZ BH1750
// -------------------------------------------------------------------
// Este sensor mide la intensidad de luz ambiental en *lux* (lx),
// utilizando comunicación I2C. Es un sensor muy preciso y rápido,
// ideal para proyectos donde se necesite detectar niveles de
// iluminación o ajustar el brillo de pantallas, por ejemplo.
// ===================================================================

// -------------------------------------------------------------------
// OBJETO DEL SENSOR
// -------------------------------------------------------------------
// Se crea una instancia del sensor BH1750 usando la librería oficial.
// Esta librería maneja internamente la comunicación I2C, por lo que
// solo es necesario iniciar el bus con Wire.begin().
BH1750 sensorBH1750;

// -------------------------------------------------------------------
// VARIABLES DE MEDICIÓN
// -------------------------------------------------------------------
// 'lux' almacenará la última lectura de luz ambiental en lux (lx).
// Los lux indican cuánta luz visible incide sobre el sensor.
// Valores comunes:
//   - 0 a 10 lx → Oscuridad casi total
//   - 100 lx → Luz tenue interior
//   - 400–1000 lx → Oficina iluminada
//   - 10,000 lx o más → Luz solar directa
float lux = 0;

// (Opcional) Umbral para activar una acción según el nivel de luz.
// const int UMBRAL_LUZ = 30;  // Si la luz cae por debajo de 30 lx, se considera baja.
// const int PIN_LED = 13;     // LED indicador (opcional)

// -------------------------------------------------------------------
// FUNCIÓN: iniciarBH1750()
// -------------------------------------------------------------------
// Inicializa el bus I2C y el sensor BH1750.
// Esta función debe llamarse una sola vez, normalmente dentro del
// setup() del programa principal.
//
// Pasos que realiza:
//  1. Inicia la comunicación I2C con Wire.begin().
//  2. Inicia el sensor con sensorBH1750.begin().
//  3. (Opcional) Configura pines de salida si se usan indicadores.
// -------------------------------------------------------------------
void iniciarBH1750() {
    Wire.begin();              // Inicia la comunicación I2C
    sensorBH1750.begin();      // Inicia el sensor BH1750
    // pinMode(PIN_LED, OUTPUT); // Configura LED opcional de aviso

    Serial.println("Sensor BH1750 iniciado correctamente.");
}

// -------------------------------------------------------------------
// FUNCIÓN: leerBH1750()
// -------------------------------------------------------------------
// Realiza una lectura del nivel de luz ambiental.
//
// Funcionamiento interno:
//  - El sensor mide la cantidad de luz visible mediante un fotodiodo.
//  - La función readLightLevel() devuelve el resultado en lux (lx).
//  - El valor se almacena en la variable global 'lux'.
//
// Ejemplo típico de uso:
//    leerBH1750();
//    Serial.println(lux);   // Muestra la luz actual en lux
//
// Nota: No es necesario usar 'delay' entre lecturas, pero en la
// práctica se recomienda leer cada 100–500 ms para evitar ruido.
// -------------------------------------------------------------------
void leerBH1750() {
    lux = sensorBH1750.readLightLevel();  // Lee la intensidad lumínica

    // Ejemplo de salida por serial:
    // Serial.print("Nivel de luz: ");
    // Serial.print(lux);
    // Serial.println(" lx");

    // ---------------------------------------------------------------
    // (OPCIONAL) Control simple por umbral:
    // Si la luz ambiental es menor al umbral definido,
    // se enciende un LED como indicador visual.
    // ---------------------------------------------------------------
    // if (lux < UMBRAL_LUZ) {
    //     digitalWrite(PIN_LED, HIGH);  // Luz ambiental baja
    // } else if (lux > UMBRAL_LUZ + 20) {
    //     digitalWrite(PIN_LED, LOW);   // Luz ambiental alta
    // }
}

#endif
