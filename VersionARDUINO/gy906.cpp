#include "gy906.h"
// #include "debug.h" // Solo si usás DEBUG_PRINT

// ===================== OBJETO =====================
Adafruit_MLX90614 gy906;

// ===================== VARIABLES =====================
float temp_ambiente_gy906 = 0.0f;
float temp_objeto_gy906 = 0.0f;

// ===================== INICIO =====================
void iniciarGY906()
{
    if (!gy906.begin())
    {
        //DEBUG_PRINTLN(F("❌ Error: GY-906 no detectado"));
        return;
    }
    //DEBUG_PRINTLN(F("✅ GY-906 inicializado correctamente"));
}

// ===================== LECTURA =====================
void leerGY906()
{
    float amb = gy906.readAmbientTempC();
    float obj = gy906.readObjectTempC();

    bool ambValido = !isnan(amb) && amb > -40 && amb < 125;
    bool objValido = !isnan(obj) && obj > -70 && obj < 380;

    if (ambValido)
        temp_ambiente_gy906 = amb;
    if (objValido)
        temp_objeto_gy906 = obj;

    if (!ambValido && !objValido)
    {
        //DEBUG_PRINTLN(F("⚠️ GY906 → Lecturas inválidas"));
    }

    //DEBUG_PRINT(F("GY906 → Ambiente: "));
    //DEBUG_PRINT(temp_ambiente_gy906);
    //DEBUG_PRINT(F(" °C | Objeto: "));
    //DEBUG_PRINTLN(temp_objeto_gy906);
}
