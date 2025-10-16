#ifndef _GY906_H
#define _GY906_H

#include <Wire.h>
#include <Adafruit_MLX90614.h>  // Librería correcta para el MLX90614

// ---------------------------------
// OBJETO DEL SENSOR
// ---------------------------------
Adafruit_MLX90614 gy906 = Adafruit_MLX90614();

// ---------------------------------
// VARIABLES DE MEDICIÓN
// ---------------------------------
float TEMP_AMBIENTE_GY906 = 0.0;
float TEMP_OBJETO_GY906 = 0.0;

// ---------------------------------
// INICIALIZACIÓN
// ---------------------------------
void iniciarGY906() {
    Wire.begin();
    if (!gy906.begin()) {
        Serial.println("Error: no se pudo iniciar el sensor GY-906");
        while (1);
    }
    Serial.println("Sensor GY-906 iniciado correctamente");
}

// ---------------------------------
// LECTURA PRINCIPAL
// ---------------------------------
void leerGY906() {
    TEMP_AMBIENTE_GY906 = gy906.readAmbientTempC();
    TEMP_OBJETO_GY906 = gy906.readObjectTempC();

    // Serial.print("Temp. Ambiente: ");
    // Serial.print(TEMP_AMBIENTE);
    // Serial.print(" °C\tTemp. Objeto: ");
    // Serial.print(TEMP_OBJETO);
    // Serial.println(" °C");
}

// ---------------------------------
// OPCIONAL: Lectura en Fahrenheit
// ---------------------------------
// void leerGY906_F() {
//     float ambienteF = gy906.readAmbientTempF();
//     float objetoF = gy906.readObjectTempF();

//     Serial.print("Temp. Ambiente: ");
//     Serial.print(ambienteF);
//     Serial.print(" °F\tTemp. Objeto: ");
//     Serial.print(objetoF);
//     Serial.println(" °F");
// }

#endif
