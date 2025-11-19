#ifndef _BMP280_H
#define _BMP280_H

#include <Arduino.h>
#include <BMP280_DEV.h>
// #include "../config.h"

// ==== Sensor ====
extern BMP280_DEV bmp;

// ==== Variables ====
extern int16_t temp_bmp280;
extern uint16_t presion_bmp280;
extern uint16_t altitud_bmp280;
extern uint16_t p0_bmp;
extern bool bmp280_inicializado;

// ==== Umbrales ====
#define TEMP_MAX 350
#define PRESION_MIN 950
#define PRESION_MAX 1050
#define ALTITUD_MAX 300

// ==== Prototipos ====
void iniciarBMP();
void leerBMP();

#endif
