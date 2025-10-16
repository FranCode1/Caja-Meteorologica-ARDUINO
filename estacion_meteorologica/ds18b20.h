#ifndef _DS18B20_H
#define _DS18B20_H

#include <Arduino.h>
#include <OneWire.h>           
#include <DallasTemperature.h> 

// Pin de datos del DS18B20
#define DS18B20_PIN 2 //pin digital, esta parte se puede acortar

// Objetos del sensor
OneWire oneWire(DS18B20_PIN); //aca solo iria el numero del pin digital conectado
DallasTemperature sensors(&oneWire);

// Variable global
float temp_ds18b20 = 0.0;

// -------------------------------------------------------------------
// Inicialización del sensor DS18B20
// -------------------------------------------------------------------
void iniciarDS18B20() {
    sensors.begin();
    Serial.println("Sensor DS18B20 iniciado correctamente.");
}

// -------------------------------------------------------------------
// Lectura de la temperatura
// -------------------------------------------------------------------
void leerDS18B20() {
    sensors.requestTemperatures(); // Envía el comando para leer
    temp_ds18b20 = sensors.getTempCByIndex(0); // Obtiene la temperatura

    // Serial.print("Temperatura DS18B20: ");
    // Serial.print(temp_ds18b20);
    // Serial.println(" °C");
}

#endif
