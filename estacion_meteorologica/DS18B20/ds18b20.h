#ifndef _DS28B20_H
#define _DS18B20_H

#include <OneWire.h>           //sirve para la comunicacion del Ds18b20
#include <DallasTemperature.h> //libreria para el Ds18b20

OneWire ourWire(2); // crea un objeto para el ds18b20 o el sensor capacitivo, creo que para el ds18b20

// Ds18b20
DallasTemperature sensors(&ourWire);

void setup() {
    // Ds18b20
    sensors.begin();
}

void loop()
{
    // Ds18b20
    sensors.requestTemperatures();         // se envia el comando para leer la temperatura
    float temp sensors.getTempCByIndex(0); // se obtiene la temperatura en Celcius

    Serial.print("Temperatura= ");
    Serial.print(temp);
    Serial.println(" C");
}

#endif