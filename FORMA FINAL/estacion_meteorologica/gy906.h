#ifndef _GY906_H
#define _GY906_H

#include <Adafruit_MLX90614.h>

// =====================================================================
// OBJETO DEL SENSOR
// =====================================================================
static Adafruit_MLX90614 gy906;

// =====================================================================
// VARIABLES DE MEDICIÓN
// =====================================================================
// Notas:
// - Se usa 'static' para limitar el alcance al archivo (evita duplicaciones)
// - Se usa 'float' porque la librería devuelve ese tipo
static float TEMP_AMBIENTE_GY906 = 0;
static float TEMP_OBJETO_GY906 = 0;

// =====================================================================
// FUNCIONES
// =====================================================================

// Inicializa el sensor (llamar una sola vez)
inline void iniciarGY906() {
    if (!gy906.begin()) {
        Serial.println(F("Error GY-906"));
        while (true); // Error crítico
    }
    Serial.println(F("GY-906 OK"));
}

// Lee las temperaturas ambiente y de objeto
inline void leerGY906() {
    TEMP_AMBIENTE_GY906 = gy906.readAmbientTempC();
    TEMP_OBJETO_GY906 = gy906.readObjectTempC();
}

#endif
