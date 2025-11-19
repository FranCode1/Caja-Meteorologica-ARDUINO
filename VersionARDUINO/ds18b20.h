#ifndef _DS18B20_H
#define _DS18B20_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// #include "config.h"

// ===================== CONFIGURACIÓN =====================
#define DS18B20_PIN 2
#define TEMP_MAX_DS18B20 37.0
#define TEMP_MIN_DS18B20 -10.0
#define INTERVALO_DS18B20 1000

// ===================== OBJETOS (Declaración) =====================
extern OneWire oneWire;
extern DallasTemperature sensors;

// ===================== VARIABLES =====================
extern float temp_ds18b20;
extern unsigned long ultimoPedidoDS18B20;

// ===================== PROTOTIPOS =====================
void iniciarDS18B20();
void leerDS18B20();

#endif
