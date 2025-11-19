#ifndef _DS3231_H
#define _DS3231_H

#include <Arduino.h>

// ===================== VARIABLES GLOBALES =====================
extern int DIA, MES, ANIO, HORA, MINUTO, SEGUNDO;

extern char DIA_SEMANA[4]; // "Lun"
extern char FECHA[11];     // "01/12/2025"
extern char HORARIO[9];    // "23:45:09"

// ===================== FUNCIONES =====================
void iniciarRTC();
void leerRTC();

#endif
