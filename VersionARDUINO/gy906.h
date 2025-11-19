#ifndef _GY906_H
#define _GY906_H

#include <Arduino.h>
#include <Adafruit_MLX90614.h>

// ===================== OBJETO =====================
extern Adafruit_MLX90614 gy906;

// ===================== VARIABLES =====================
extern float temp_ambiente_gy906;
extern float temp_objeto_gy906;

// ===================== INICIO =====================
void iniciarGY906();

// ===================== LECTURA =====================
void leerGY906();

#endif
