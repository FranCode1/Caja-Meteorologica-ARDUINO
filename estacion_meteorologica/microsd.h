#ifndef _MICROSD_H
#define _MICROSD_H

#include <SPI.h>  // Protocolo de comunicación para la SD
#include <SD.h>   // Librería que maneja archivos en la SD

#include "buttons.h"            // Libreria de los botones
#include "bme.h"                // Sensor de temperatura, humedad y presion atmosferica
#include "ds18b20.h"            // Sensor de temperatura del agua
#include "csmsv2.h"             // Sensor de temperatura de la tierra
#include "bh1750.h"             // Sensor de Luz
#include "ml8511.h"             // Sensor de Rayos Ultravioletas
#include "mq135.h"              // Sensor de Gases y Co2
#include "gy906.h"              // Sensor de temperatura infrarroja
#include "ds3231.h"             // Modulo RTC (reloj)

// Pin Chip Select (SS) del módulo microSD
#define SD_CS_PIN 10   

File archivo;  // Variable global que representa el archivo que vamos a leer o escribir


// =====================================================
// FUNCIÓN: Inicializar la microSD
// =====================================================
bool iniciarSD() {
    // Serial.begin(9600);
    Serial.println("Inicializando tarjeta microSD...");

    // Inicia la tarjeta microSD usando el pin CS
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("Error: no se pudo inicializar la tarjeta SD");
        return false;  // Si falla, devolvemos false
    }

    Serial.println("Tarjeta microSD lista para usar");
    return true;
}


// =====================================================
// FUNCIÓN: Escribir texto en un archivo de la SD
// =====================================================
// Recibe el nombre del archivo y el texto a escribir
bool escribirSD(const char *nombreArchivo) {
    // Abrimos el archivo en modo escritura (crea el archivo si no existe)
    archivo = SD.open(nombreArchivo, FILE_WRITE);

    if (archivo) {
        // archivo.println(texto);  // Escribimos el texto en una nueva línea

        // --- HORA ---
        archivo.print("Hora y Fecha: ");
        archivo.println(leerRTC());

        // --- BME280 ---
        archivo.print("BME280 → ");
        archivo.print("Temp: "); archivo.print(temp_bme280); archivo.print(" °C ");
        archivo.print("Hum: "); archivo.print(humedad_bme280); archivo.print(" % ");
        archivo.print("Pres: "); archivo.print(presion_bme280); archivo.println(" hPa");

        // --- Ds18b20 ---
        archivo.print("Ds18b20 → ");
        archivo.print("Temp. Agua: "); archivo.print(temp_ds18b20); archivo.print(" °C");
        // archivo.print("Temp. Agua: " + temp_ds18b20 + "°C  ");//no se puede asi

        // --- CSMSV2 ---
        archivo.print("CSMSV2 → ");
        archivo.print("Humedad Tierra: "); archivo.print(humedad_tierra); archivo.println(" %");

        // --- BH1750 ---
        archivo.print("BH1750 → ");
        archivo.print("Lux: "); archivo.print(lux); archivo.println(" lx");

        // --- ML8511 ---
        archivo.print("ML8511 → ");
        archivo.print("Rayos UV: "); archivo.print(uvIndex); archivo.println(" uv");

        // --- MQ-135 ---
        archivo.print("MQ-135 → ");
        archivo.print("Calidad Aire: "); archivo.print(ratio); archivo.println("% Co2");

        // --- GY-906 ---
        archivo.print("GY-906 → ");
        archivo.print("Temp. Infrarroja: "); archivo.print(TEMP_OBJETO_GY906); archivo.println(" °C");

        archivo.close();         // Cerramos el archivo (muy importante)
        Serial.print("Escrito correctamente en ");
        Serial.println(nombreArchivo);
        return true;

    } else {
        Serial.print("Error al abrir ");
        Serial.println(nombreArchivo);
        return false;
    }
}


// =====================================================
// FUNCIÓN: Leer el contenido de un archivo de la SD
// =====================================================
void leerSD(const char *nombreArchivo) {
    archivo = SD.open(nombreArchivo);  // Abrimos el archivo en modo lectura

    if (archivo) {
        Serial.print("Contenido de ");
        Serial.println(nombreArchivo);
        Serial.println("------------------------");

        // Leemos el contenido caracter por caracter
        while (archivo.available()) {
            Serial.write(archivo.read());
        }

        archivo.close();  // Cerramos el archivo
        Serial.println("\n------------------------");
        Serial.println("Lectura finalizada");
    } else {
        Serial.print("Error al abrir ");
        Serial.println(nombreArchivo);
    }
}

#endif
