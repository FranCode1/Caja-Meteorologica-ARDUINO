#ifndef _BH1750_H
#define _BH1750_H

#include <BH1750.h> //libreria del BH1750

// OBJETOS DE LAS LIBRERIAS
BH1750 sensor;

// VARIABLES DE SENSORES
// BH1750
#define UMBRAL 30

void setup()
{
    Serial.begin(9600);
    // BH1750
    Wire.begin();   // inicia la comunicacion i2c
    sensor.begin(); // parametros: tipo de escaneo, direccion i2c
}

void loop(){
    // BH1750
    unsigned int lux = sensor.readLightLevel();
    Serial.print("Nivel: ");
    Serial.print(lux);
    Serial.print(" lx");

    if (lux < UMBRAL)
    {
        digitalWrite(LED, HIGH); // luz baja
    }
    else if (lux > UMBRAL + 20)
    {
        digitalWrite(LED, LOW); // luz alta
    }
}

#endif