#ifndef _NAVEGACION_H_
#define _NAVEGACION_H_

#include <Arduino.h>

// ===================== PINES =====================
#define BTN_IZQ 4
#define BTN_DER 3

// ===================== VARIABLES EXTERNAS =====================
extern bool bienvenidaMostrada;
extern uint8_t pantallaActual;
extern const uint8_t totalPantallas;

extern unsigned long bloqueoRefresco;

class LiquidCrystal_I2C; // forward declaration
extern LiquidCrystal_I2C lcd;

// ===================== FUNCIONES =====================
void iniciarNavegacion();
void leerNavegacion();

#endif
