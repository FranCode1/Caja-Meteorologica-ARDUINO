#ifndef _MICROSD_H
#define _MICROSD_H

#include <SPI.h>  // Protocolo de comunicación para la SD
#include <SD.h>   // Librería que maneja archivos en la SD

// Pin Chip Select (SS) del módulo microSD
#define SD_CS_PIN 10   

File archivo;  // Variable global que representa el archivo que vamos a leer o escribir


// =====================================================
// FUNCIÓN: Inicializar la microSD
// =====================================================
bool iniciarSD() {
    Serial.begin(9600);
    Serial.println("📀 Inicializando tarjeta microSD...");

    // Inicia la tarjeta microSD usando el pin CS
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("❌ Error: no se pudo inicializar la tarjeta SD");
        return false;  // Si falla, devolvemos false
    }

    Serial.println("✅ Tarjeta microSD lista para usar");
    return true;
}


// =====================================================
// FUNCIÓN: Escribir texto en un archivo de la SD
// =====================================================
// Recibe el nombre del archivo y el texto a escribir
bool escribirSD(const char *nombreArchivo, const String &texto) {
    // Abrimos el archivo en modo escritura (crea el archivo si no existe)
    archivo = SD.open(nombreArchivo, FILE_WRITE);

    if (archivo) {
        archivo.println(texto);  // Escribimos el texto en una nueva línea
        archivo.close();         // Cerramos el archivo (muy importante)
        Serial.print("📝 Escrito correctamente en ");
        Serial.println(nombreArchivo);
        return true;
    } else {
        Serial.print("❌ Error al abrir ");
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
        Serial.print("📄 Contenido de ");
        Serial.println(nombreArchivo);
        Serial.println("------------------------");

        // Leemos el contenido caracter por caracter
        while (archivo.available()) {
            Serial.write(archivo.read());
        }

        archivo.close();  // Cerramos el archivo
        Serial.println("\n------------------------");
        Serial.println("✅ Lectura finalizada");
    } else {
        Serial.print("❌ Error al abrir ");
        Serial.println(nombreArchivo);
    }
}

#endif
