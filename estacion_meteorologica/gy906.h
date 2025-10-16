#ifndef _GY906_H
#define _GY906_H

#include <Wire.h> //para protocolo i2c
#include <Adafruit.h>

Adafruit_MLX90614 gy906 = Adafruit_MLX90614();

void setup(){
    Serial.begin(9600);

    Serial.println("Adafruit MLX90614 test");

    gy906.begin(); //inicia el sensor gy906
}

void loop(){
    //mide en Celcius
    Serial.print("Ambient: ");
    Serial.print(gy906.readAmbientTestC());

    Serial.print("°C\tObject: ");
    Serial.print(gy906.readObjectTempC());
    Serial.println("°C");

    //mide en Farenheit
    Serial.print("Ambient: ");
    Serial.print(gy906.readAmbientTempF());

    Serial.print("°F\tObject: ");
    Serial.print(gy906.readObjectTempF());
    Serial.println("°F");

    Serial.println();
}

#endif