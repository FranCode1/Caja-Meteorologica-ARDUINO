#ifndef _MICROSD_H
#define _MICROSD_H

// =====================================================================
// MÓDULO MICROSD - LECTURA Y ESCRITURA DE DATOS
// =====================================================================
// Este módulo maneja la escritura de los datos de los sensores en una
// tarjeta microSD y la lectura opcional de registros. También utiliza
// la memoria EEPROM para conservar el número de registro más reciente.
// =====================================================================


// ---------------------------------------------------------------------
// LIBRERÍAS NECESARIAS
// ---------------------------------------------------------------------
#include <Arduino.h>
#include <SPI.h>       // Comunicación SPI (Serial Peripheral Interface)
#include <SD.h>        // Librería oficial de Arduino para manejo de tarjetas SD
#include <EEPROM.h>    // Permite leer y escribir en la memoria EEPROM interna


// ---------------------------------------------------------------------
// 🌡️ VARIABLES EXTERNAS DE SENSORES
// ---------------------------------------------------------------------
// Se traen únicamente las variables necesarias desde los módulos de
// sensores, para reducir el peso total del programa. Cada variable es
// declarada como 'extern' porque su definición real está en otro archivo.
extern float temp_bmp280, presion_bmp280, altitud_bmp280;  // BMP280 → temperatura, presión y altitud
extern float temp_ds18b20;                                 // DS18B20 → temperatura del agua
extern uint8_t humedad_tierra;                             // CSMSV2 → humedad del suelo
extern float ratio;                                        // MQ-135 → relación de CO₂
extern String calidad, tendencia;                          // MQ-135 → estado y tendencia del aire
extern float lux;                                          // BH1750 → luz ambiental (lux)
extern float TEMP_OBJETO_GY906;                            // GY-906 → temperatura infrarroja
extern String FECHA, HORARIO;                              // DS3231 → fecha y hora actual


// ---------------------------------------------------------------------
// CONFIGURACIÓN DEL MÓDULO MICROSD
// ---------------------------------------------------------------------

// Pin Chip Select (SS) del módulo microSD.
// Nota: este valor puede variar según la placa o el módulo utilizado.
// Ejemplo común: 10 para Arduino UNO, 5 para ESP32, etc.
#define SD_CS_PIN 10

// Contador de registros (se conserva el valor entre reinicios usando EEPROM)
int registroID = 0;

// Objeto global para manejar archivos en la tarjeta SD
File archivo;


// ---------------------------------------------------------------------
// FUNCIÓN: iniciarSD()
// ---------------------------------------------------------------------
// Inicializa la tarjeta microSD y carga el último ID guardado desde EEPROM.
// Devuelve:
//   true  → si la inicialización fue exitosa
//   false → si falló la inicialización
// ---------------------------------------------------------------------
bool iniciarSD() {
    // Serial.println(F("Inicializando tarjeta microSD...")); // DEBUG opcional

    // Intentar inicializar la tarjeta (descomentá si necesitás verificar)
    /*
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println(F("Error: no se pudo inicializar la tarjeta SD"));
        return false;
    }
    */

    // Leer último ID guardado desde la EEPROM
    EEPROM.get(0, registroID);

    // Si el valor leído no es válido, comenzar desde 1
    if (registroID < 1)
        registroID = 1;

    // Serial.println(F("Tarjeta microSD lista para usar")); // DEBUG opcional
    return true;
}


// ---------------------------------------------------------------------
// FUNCIÓN: escribirSD(const char *nombreArchivo)
// ---------------------------------------------------------------------
// Escribe en la tarjeta SD los valores actuales de los sensores.
// Crea el archivo si no existe, o agrega información al final si ya existe.
//
// Parámetros:
//   nombreArchivo → nombre del archivo donde guardar (ej: "datos.txt")
//
// Devuelve:
//   true  → si la escritura fue exitosa
//   false → si hubo error al abrir o escribir el archivo
// ---------------------------------------------------------------------
bool escribirSD(const char *nombreArchivo) {
    // Abrir archivo en modo escritura (crea si no existe)
    archivo = SD.open(nombreArchivo, FILE_WRITE);

    if (archivo) {
        // =====================================================
        // BLOQUE DE ESCRITURA DE DATOS
        // =====================================================

        // --- ID del registro ---
        archivo.print("Registro ID: ");
        archivo.println(String(registroID++)); // Incrementa para el siguiente registro

        // --- Fecha y hora del RTC ---
        archivo.print("Hora y Fecha: ");
        archivo.println(leerRTC());  // Función proveniente del módulo DS3231

        // --- Sensor BMP280 ---
        archivo.print("BMP280 → ");
        archivo.print("Temp: "); archivo.print(temp_bmp280); archivo.print(" °C ");
        archivo.print("Pres: "); archivo.print(presion_bmp280); archivo.print(" hPa ");
        archivo.print("Alti: "); archivo.print(altitud_bmp280); archivo.println(" m");

        // --- Sensor DS18B20 ---
        archivo.print("DS18B20 → ");
        archivo.print("Temp. Agua: "); archivo.print(temp_ds18b20); archivo.println(" °C");

        // --- Sensor CSMSV2 ---
        archivo.print("CSMSV2 → ");
        archivo.print("Humedad Tierra: "); archivo.print(humedad_tierra); archivo.println(" %");

        // --- Sensor BH1750 ---
        archivo.print("BH1750 → ");
        archivo.print("Luz: "); archivo.print(lux); archivo.println(" lx");

        // --- Sensor MQ-135 ---
        archivo.print("MQ-135 → ");
        archivo.print("CO₂: "); archivo.print(ratio); archivo.print("% | ");
        archivo.print("Estado: "); archivo.print(calidad);
        archivo.print(" | Tendencia: "); archivo.println(tendencia);

        // --- Sensor GY-906 ---
        archivo.print("GY-906 → ");
        archivo.print("Temp. Infrarroja: "); archivo.print(TEMP_OBJETO_GY906); archivo.println(" °C");

        // =====================================================
        // FINALIZACIÓN
        // =====================================================
        archivo.close();  // Siempre cerrar tras escribir
        EEPROM.put(0, registroID); // Guardar nuevo ID en EEPROM

        // Serial.print(F("Datos escritos en ")); Serial.println(nombreArchivo); // DEBUG
        return true;
    }

    // Si el archivo no se pudo abrir:
    // Serial.print(F("Error al abrir ")); Serial.println(nombreArchivo); // DEBUG
    return false;
}


// ---------------------------------------------------------------------
// FUNCIÓN OPCIONAL: leerSD(const char *nombreArchivo)
// ---------------------------------------------------------------------
// Lee el contenido completo de un archivo de la tarjeta SD y lo muestra
// por el monitor serie. Ideal para depuración o pruebas.
// ---------------------------------------------------------------------
/*
void leerSD(const char *nombreArchivo) {
    archivo = SD.open(nombreArchivo);

    if (archivo) {
        Serial.print(F("Contenido de ")); Serial.println(nombreArchivo);
        Serial.println(F("------------------------"));

        while (archivo.available()) {
            Serial.write(archivo.read());
        }

        archivo.close();
        Serial.println(F("\n------------------------"));
        Serial.println(F("Lectura finalizada"));
    } else {
        Serial.print(F("Error al abrir ")); Serial.println(nombreArchivo);
    }
}
*/

#endif
