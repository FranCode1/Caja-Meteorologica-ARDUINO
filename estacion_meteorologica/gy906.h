#ifndef _GY906_H
#define _GY906_H

#include <Wire.h>                    // Librería base para comunicación I2C
#include <Adafruit_MLX90614.h>       // Librería oficial para el sensor infrarrojo MLX90614
//#include <DFRobot_MLX90614.h> //libreria del sensor

// =====================================================================
// OBJETO DEL SENSOR
// =====================================================================
// Se crea un objeto "gy906" de la clase Adafruit_MLX90614.
// Este objeto permite comunicarse con el sensor GY-906 a través del bus I2C.
Adafruit_MLX90614 gy906 = Adafruit_MLX90614();
//DFRobot_MLX90614 gy906 = Adafruit_MLX90614();

// =====================================================================
// VARIABLES DE MEDICIÓN
// =====================================================================
// Guardan los valores de temperatura leídos por el sensor:
// - TEMP_AMBIENTE_GY906: temperatura del entorno (aire alrededor del sensor)
// - TEMP_OBJETO_GY906: temperatura del objeto al que apunta el sensor
float TEMP_AMBIENTE_GY906 = 0.0;
float TEMP_OBJETO_GY906 = 0.0;

// =====================================================================
// FUNCIÓN: iniciarGY906()
// =====================================================================
// Inicializa la comunicación con el sensor GY-906 (MLX90614) a través de I2C.
// Debe llamarse una sola vez en la función setup() del programa principal.
void iniciarGY906() {
    Wire.begin();  // Inicia la comunicación I2C

    // Intentamos iniciar el sensor. Si falla, el programa se detiene.
    if (!gy906.begin()) {
        Serial.println("Error: no se pudo iniciar el sensor GY-906 (MLX90614)");
        while (1); // Bucle infinito en caso de error crítico
    }

    Serial.println("Sensor GY-906 iniciado correctamente");
}

// =====================================================================
// FUNCIÓN: leerGY906()
// =====================================================================
// Realiza una lectura de las temperaturas ambiente y de objeto en grados Celsius.
// Los valores se guardan en las variables globales TEMP_AMBIENTE_GY906 y TEMP_OBJETO_GY906.
void leerGY906() {
    // Lectura de temperatura ambiente (aire)
    TEMP_AMBIENTE_GY906 = gy906.readAmbientTempC();

    // Lectura de temperatura del objeto apuntado por el sensor
    TEMP_OBJETO_GY906 = gy906.readObjectTempC();

    // Logica del umbral para el LED de alerta
    bool alertaTemp = (TEMP_OBJETO_GY906 > 40.0); // Temperatura peligrosa
    bool alertaLuz = (lux < UMBRAL_LUZ_BAJA);     // Luz muy baja

    if (alertaTemp || alertaLuz)
    {
        digitalWrite(LED_ALERTA_LUZ_TEMP, HIGH);
    }
    else
    {
        digitalWrite(LED_ALERTA_LUZ_TEMP, LOW);
    }

    // Las lecturas se almacenan en variables globales para poder usarlas
    // desde otros módulos, como el que registra los datos en la microSD.
    // Si quisieras depurar, podés descomentar las siguientes líneas:

    /*
    Serial.print("Temp. Ambiente: ");
    Serial.print(TEMP_AMBIENTE_GY906);
    Serial.print(" °C\tTemp. Objeto: ");
    Serial.print(TEMP_OBJETO_GY906);
    Serial.println(" °C");
    */
}

// =====================================================================
// (OPCIONAL) FUNCIÓN: leerGY906_F()
// =====================================================================
// Si se requiere obtener las temperaturas en Fahrenheit, se puede usar esta versión.
// Está comentada por defecto ya que el sistema trabaja en °C.
// Descomentar si se necesita para una aplicación específica.
/*
void leerGY906_F() {
    float ambienteF = gy906.readAmbientTempF();  // Lectura en Fahrenheit
    float objetoF = gy906.readObjectTempF();     // Lectura en Fahrenheit

    Serial.print("Temp. Ambiente: ");
    Serial.print(ambienteF);
    Serial.print(" °F\tTemp. Objeto: ");
    Serial.print(objetoF);
    Serial.println(" °F");
}
*/

#endif
