#ifndef _MICROSD_H
#define _MICROSD_H

// =====================================================
//  LIBRERÍAS NECESARIAS
// =====================================================

#include <SPI.h>  // Permite la comunicación SPI (Serial Peripheral Interface)
#include <SD.h>   // Librería oficial de Arduino para manejar tarjetas SD

// =====================================================
//  LIBRERÍAS DE LOS SENSORES Y MÓDULOS USADOS
// =====================================================
// Se incluyen porque las funciones y variables de cada sensor se usarán
// dentro de las funciones que escriben datos en la tarjeta SD.

#include "buttons.h"            // Librería de manejo de botones físicos
#include "bme.h"                // Sensor BME280 → temperatura, humedad, presión atmosférica
#include "ds18b20.h"            // Sensor DS18B20 → temperatura del agua
#include "csmsv2.h"             // Sensor CSMSV2 → humedad del suelo
#include "bh1750.h"             // Sensor BH1750 → intensidad lumínica (lux)
#include "ml8511.h"             // Sensor ML8511 → radiación ultravioleta (UV)
#include "mq135.h"              // Sensor MQ-135 → gases / calidad del aire (CO₂)
#include "gy906.h"              // Sensor GY-906 → temperatura por infrarrojos
#include "ds3231.h"             // Módulo DS3231 → reloj en tiempo real (RTC)


// =====================================================
//  CONFIGURACIÓN DEL MÓDULO MICROSD
// =====================================================

// Pin Chip Select (SS) del módulo microSD.
// Este pin puede variar según la placa o el módulo SD que se use.
// Ejemplo común: 10 para Arduino UNO, 5 para ESP32, etc.
#define SD_CS_PIN 10   

// Variable global para manejar los archivos en la tarjeta SD.
// Se usa para abrir, leer y escribir archivos.
File archivo;


// =====================================================
//  FUNCIÓN: iniciarSD()
// -----------------------------------------------------
// Inicializa el módulo de tarjeta microSD y verifica que esté lista.
// Devuelve 'true' si se inicializa correctamente, o 'false' si ocurre un error.
// =====================================================
bool iniciarSD() {
    Serial.println("Inicializando tarjeta microSD...");

    // Intentamos inicializar la tarjeta SD con el pin de Chip Select
    if (!SD.begin(SD_CS_PIN)) {
        // Si falla la inicialización, mostramos un mensaje de error
        Serial.println("Error: no se pudo inicializar la tarjeta SD");
        return false;
    }

    // Si la inicialización fue exitosa, confirmamos por monitor serie
    Serial.println("Tarjeta microSD lista para usar");
    return true;
}


// =====================================================
//  FUNCIÓN: escribirSD(const char *nombreArchivo)
// -----------------------------------------------------
// Escribe en la tarjeta SD los valores actuales de los sensores.
// Crea el archivo si no existe, o agrega información al final si ya existe.
//
// Parámetro:
//   nombreArchivo → nombre del archivo a escribir (por ejemplo: "datos.txt")
//
// Devuelve:
//   true  → si se escribió correctamente
//   false → si hubo error al abrir o escribir el archivo
// =====================================================
bool escribirSD(const char *nombreArchivo) {
    // Abrimos el archivo en modo escritura. FILE_WRITE crea el archivo si no existe.
    archivo = SD.open(nombreArchivo, FILE_WRITE);

    if (archivo) {
        // =====================================================
        // BLOQUE DE ESCRITURA DE DATOS
        // =====================================================

        // --- Reloj RTC ---
        archivo.print("Hora y Fecha: ");
        archivo.println(leerRTC());  // leerRTC() viene del módulo DS3231

        // --- Sensor BME280 ---
        archivo.print("BME280 → ");
        archivo.print("Temp: "); archivo.print(temp_bme280); archivo.print(" °C ");
        archivo.print("Hum: "); archivo.print(humedad_bme280); archivo.print(" % ");
        archivo.print("Pres: "); archivo.print(presion_bme280); archivo.println(" hPa");

        // --- Sensor DS18B20 (agua) ---
        archivo.print("DS18B20 → ");
        archivo.print("Temp. Agua: "); archivo.print(temp_ds18b20); archivo.println(" °C");
        // NOTA: no se puede usar concatenación de strings con el operador '+'
        // como en otros lenguajes ("Temp: " + variable), ya que Arduino no lo soporta así.

        // --- Sensor CSMSV2 (humedad de tierra) ---
        archivo.print("CSMSV2 → ");
        archivo.print("Humedad Tierra: "); archivo.print(humedad_tierra); archivo.println(" %");

        // --- Sensor BH1750 (luz) ---
        archivo.print("BH1750 → ");
        archivo.print("Lux: "); archivo.print(lux); archivo.println(" lx");

        // --- Sensor ML8511 (rayos UV) ---
        archivo.print("ML8511 → ");
        archivo.print("Rayos UV: "); archivo.print(uvIndex); archivo.println(" uv");

        // --- Sensor MQ-135 (gases / CO₂) ---
        archivo.print("MQ-135 → ");
        archivo.print("Calidad Aire: "); archivo.print(ratio); archivo.println("% CO2");

        // --- Sensor GY-906 (infrarrojos) ---
        archivo.print("GY-906 → ");
        archivo.print("Temp. Infrarroja: "); archivo.print(TEMP_OBJETO_GY906); archivo.println(" °C");

        // =====================================================
        // FINALIZACIÓN
        // =====================================================

        archivo.close();  // Cerramos el archivo (¡siempre cerrar tras escribir!)
        Serial.print("Escrito correctamente en ");
        Serial.println(nombreArchivo);

        return true;  // Éxito

    } else {
        // Si el archivo no se pudo abrir, informamos el error
        Serial.print("Error al abrir ");
        Serial.println(nombreArchivo);
        return false;
    }
}


// =====================================================
//  FUNCIÓN: leerSD(const char *nombreArchivo)
// -----------------------------------------------------
// Lee el contenido completo de un archivo en la tarjeta SD
// y lo muestra por el Monitor Serie.
//
// Parámetro:
//   nombreArchivo → nombre del archivo a leer (por ejemplo: "datos.txt")
// =====================================================
void leerSD(const char *nombreArchivo) {
    // Intentamos abrir el archivo en modo lectura
    archivo = SD.open(nombreArchivo);

    if (archivo) {
        Serial.print("Contenido de ");
        Serial.println(nombreArchivo);
        Serial.println("------------------------");

        // Leemos el contenido carácter por carácter y lo mostramos en el Serial
        while (archivo.available()) {
            Serial.write(archivo.read());
        }

        // Cerramos el archivo tras terminar de leer
        archivo.close();
        Serial.println("\n------------------------");
        Serial.println("Lectura finalizada");

    } else {
        // Si no se pudo abrir el archivo, mostramos el error
        Serial.print("Error al abrir ");
        Serial.println(nombreArchivo);
    }
}

#endif
