#ifndef _LCD_H
#define _LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// ========================== SENSORES (extern) ==========================
extern int16_t temp_bmp280;
extern uint16_t presion_bmp280, altitud_bmp280;

extern float temp_ds18b20;
extern uint8_t humedad_tierra;
extern float ratio;
extern float lux;
extern float temp_objeto_gy906;

extern char calidad[20];
extern char tendencia[20];

extern char DIA_SEMANA[4];
extern char FECHA[11];
extern char HORARIO[9];

// ========================== CONTROL ==========================
extern uint8_t pantallaActual;
extern const uint8_t totalPantallas;

// ========================== FUNCIONES ==========================
void iniciarLCD();
void mostrarPantalla(uint8_t id);
void actualizarLCD();

#endif
