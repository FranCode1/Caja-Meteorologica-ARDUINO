#ifndef _MICROSD_H_
#define _MICROSD_H_

#include <Arduino.h>

// ===================== VARIABLES EXTERNAS =====================
// Definidas en otros módulos
extern int16_t temp_bmp280;
extern uint16_t presion_bmp280, altitud_bmp280;

// extern float temp_ds18b20;
extern uint8_t humedad_tierra;
extern float ratio;
extern float lux;
extern float temp_objeto_gy906;

extern char calidad[20];
extern char tendencia[20];

extern char DIA_SEMANA[4];
extern char FECHA[11];
extern char HORARIO[9];

extern void leerRTC();

// ===================== CONFIG SD =====================
#define SD_CS_PIN 10

// ===================== FUNCIONES =====================
bool iniciarSD();
bool escribirSD(const char *nombreArchivo);

#endif
