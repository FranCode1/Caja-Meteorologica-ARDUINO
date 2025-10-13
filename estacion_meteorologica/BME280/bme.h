#ifndef _BME_H
#define _BME_H

#include <Adafruit_Sensor.h> //libreria del bme280
#include <Adafruit_BME280.h> //libreria del bme280

Adafruit_BME280 bme; // crea el objeto para el bme280

// VARIABLES DE SENSORES
// ser mas especifico con las variables

// BME280
float TEMPERATURA;
float PRESION, P0; // presion y presion 0 para medir altitud
float HUMEDAD;

void setup()
{
    Serial.begin(9600);

    // BME280
    Serial.prinln("Iniciando: ");
    if (!bme.begin())
    {
        Serial.println("BME280 no encontrado!");
        while (1)
            ;
    }
    P0 = bme.readPressure() / 100;
}

void loop()
{
    // BME280
    TEMPERATURA = bme.readTemperature();
    PRESION = bme.readPressure() / 100;
    HUMEDAD = bme.readHumidity();

    Serial.print("Temperatura: ");
    Serial.print(TEMPERATURA);
    Serial.print(" C ");

    Serial.print("Presión: ");
    Serial.print(PRESION);
    Serial.println(" hPa ");

    Serial.print("Humedad: ");
    Serial.print(HUMEDAD);
    Serial.println(" % ");

    Serial.print("Altitud aprox: ");
    Serial.print(bmp.readAltitude(P0));
    Serial.println(" m ");
}

#endif