#ifndef _BMP280_H
#define _BMP280_H

#include <Arduino.h>
#include <Adafruit_BMP280.h> // Librería del sensor BMP280

// ===================== SENSOR =====================
Adafruit_BMP280 bmp; // Comunicación I2C (SDA, SCL)

// ===================== VARIABLES =====================
static float temp_bmp280 = 0.0F;
static float presion_bmp280 = 0.0F;
static float altitud_bmp280 = 0.0F;
static float p0_bmp = 0.0F; // Presión base (nivel del mar)

// ===================== UMBRALES =====================
#define TEMP_MAX 35.0F
#define PRESION_MIN 950.0F
#define PRESION_MAX 1050.0F
#define ALTITUD_MAX 300.0F

// ===================== INICIO =====================
inline void iniciarBMP() {
    // Dirección I2C 0x76 (usa 0x77 según módulo)
    // if (!bmp.begin(0x76)) while (1); // Para debug
    p0_bmp = bmp.readPressure() / 100.0F;
}

// ===================== LECTURA =====================
inline void leerBMP() {
    temp_bmp280 = bmp.readTemperature();
    presion_bmp280 = bmp.readPressure() / 100.0F; // Pa → hPa
    altitud_bmp280 = 44330 * (1.0 - pow(presion_bmp280 / 1013.25, 0.1903));
}

#endif
