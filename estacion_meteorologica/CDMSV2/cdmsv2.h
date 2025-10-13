#ifndef _CDMSV2_H
#define _CDMSV2_H

// Capacitive Soil Moisture v2.0
int tierra = A0, lectura; // ubicacion del pin analogo
tierrad = 8, lecturad;

const int AirValue = 588;
const int WaterValue = 308;
int soilMoistureValue = 0;
int soilMoisturePercent = 0;

int HumedadTierra = analogRead(A0); // pin analogico del sensor

void setup()
{
    Serial.begin(9600);

    // Capacitive Soil Moisture v2.0
    pinMode(tierra, INPUT);
}

void loop() {
    // Capacitive Soil Moisture v2.0
    lectura = digitalRead(tierra);
    Serial.println(lectura);

    lectura = analogRead(tierra);
    lecturad = digitalRead(tierrad);
    int porcentaje = map(lectura, 0, 1023, 0, 100);

    if (lecturad)
    {
        Serial.println("Tierra Mojada");
    }
    else
    {
        Serial.println("Tierra Seca");
    }
    // estaria bueno poner umbrales de humedad, para asi saber el estado
    // de la tierra con precision
    soilMoistureValue = analogRead(A0);
    Serial.println(soilMoistureValue);
    soilMoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    // Humedad = map(Humedad, 0, 1023, 0, 100); //es de 0 a 1023 cuando hay valores maximos, a los que nunca se llega
    Humedad = map(Humedad, 50, 950, 0, 100);

    Serial.print("Humedad Tierra: ");
    if (soilMoisturePercent >= 100)
    {
        Serial.println("100");
    }
    else if (soilMoisturePercent <= 0)
    {
        Serial.println("0");
    }
    else if (soilMoisturePercent > 0 && soilMoisturePercent < 100)
    {
        Serial.print(soilMoisturePercent);
    }
    Serial.print("%");
}

#endif