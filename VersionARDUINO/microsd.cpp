#include "microsd.h"
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>
// #include "debug.h" // por DEBUG_PRINT y DEBUG_PRINTLN si lo usás

// =============================================================
// VARIABLES INTERNAS AL MÓDULO
// =============================================================
static File archivo;

static bool sdAvailable = false;
static bool sdInitAttempted = false;

static int registroID = 0;
static int eepromWriteCounter = 0;

constexpr int EEPROM_SAVE_INTERVAL = 100;

// =============================================================
// iniciarSD()
// =============================================================
bool iniciarSD()
{
    if (sdAvailable)
        return true;

    if (sdInitAttempted)
    {
        //DEBUG_PRINTLN(F("SD: intento previo fallido, no reintentando"));
        return false;
    }

    sdInitAttempted = true;
    //DEBUG_PRINTLN(F("Inicializando tarjeta MicroSD..."));

    if (!SD.begin(SD_CS_PIN))
    {
        //DEBUG_PRINTLN(F("Error: no se pudo inicializar la SD"));
        return false;
    }

    // Cargar último ID desde EEPROM
    EEPROM.get(0, registroID);
    if (registroID < 1)
        registroID = 1;

    sdAvailable = true;

    //DEBUG_PRINTLN(F("Tarjeta MicroSD lista"));
    return true;
}

// =============================================================
// escribirSD()
// =============================================================
bool escribirSD(const char *nombreArchivo)
{
    if (!sdAvailable)
    {
        //DEBUG_PRINTLN(F("SD no disponible, omitiendo escritura"));
        return false;
    }

    archivo = SD.open(nombreArchivo, FILE_WRITE);
    if (!archivo)
    {
        //DEBUG_PRINT(F("Error abriendo "));
        //DEBUG_PRINTLN(nombreArchivo);
        return false;
    }

    // --- ID ---
    archivo.print(F("Registro ID: "));
    archivo.println(registroID++);

    // --- RTC ---
    leerRTC();
    archivo.print(F("Hora y Fecha: "));
    archivo.print(FECHA);
    archivo.print(" ");
    archivo.println(HORARIO);

    // --- BMP280 ---
    archivo.print(F("BMP280 -> Temp: "));

    {
        char buf[16];
        snprintf(buf, sizeof(buf), "%.1f", temp_bmp280 / 10.0f);
        archivo.print(buf);
    }

    archivo.print(F(" °C  Pres: "));
    archivo.print(presion_bmp280);
    archivo.print(F(" hPa  Alti: "));
    archivo.print(altitud_bmp280);
    archivo.println(F(" m"));

    // --- DS18B20 ---
    archivo.print(F("DS18B20 -> Temp. Agua: "));
    // archivo.print(temp_ds18b20);
    archivo.print(0);
    archivo.println(F(" °C"));

    // --- Humedad tierra ---
    archivo.print(F("CSMSV2 -> Humedad Tierra: "));
    archivo.print(humedad_tierra);
    archivo.println(F(" %"));

    // --- BH1750 ---
    archivo.print(F("BH1750 -> Luz: "));
    archivo.print(lux);
    archivo.println(F(" lx"));

    // --- MQ-135 ---
    archivo.print(F("MQ-135 -> CO2: "));
    archivo.print(ratio);
    archivo.print(F("% | Estado: "));
    archivo.print(calidad);
    archivo.print(F(" | Tendencia: "));
    archivo.println(tendencia);

    // --- GY-906 ---
    archivo.print(F("GY-906 -> Temp. IR: "));
    archivo.print(temp_objeto_gy906);
    archivo.println(F(" °C"));

    archivo.close();

    // --- Guardado periódico del ID ---
    eepromWriteCounter++;
    if (eepromWriteCounter >= EEPROM_SAVE_INTERVAL)
    {
        EEPROM.put(0, registroID);
        eepromWriteCounter = 0;
        //DEBUG_PRINTLN(F("EEPROM: registroID guardado"));
    }

    //DEBUG_PRINTLN(F("Datos escritos en MicroSD"));
    return true;
}
