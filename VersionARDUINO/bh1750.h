#ifndef _BH1750_H
#define _BH1750_H

#include <Arduino.h>
#include <BH1750.h>
// #include "config.h"

// ===================== OBJETOS (solo declaración) =====================
extern BH1750 sensorBH1750;

// ===================== VARIABLES =====================
extern float lux;

// ===================== PROTOTIPOS =====================
void iniciarBH1750();
void leerBH1750();

#endif
