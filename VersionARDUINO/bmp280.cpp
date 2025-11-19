#include "bmp280.h"

BMP280_DEV bmp;

int16_t temp_bmp280 = 0;
uint16_t presion_bmp280 = 0;
uint16_t altitud_bmp280 = 0;
uint16_t p0_bmp = 0;
bool bmp280_inicializado = false;

void iniciarBMP()
{
    bmp280_inicializado = false;
    
    // Intentar inicializar en dirección 0x76
    if (bmp.begin(0x76))
    {
        bmp280_inicializado = true;
    }
    // Si falla, intentar en dirección 0x77
    else if (bmp.begin(0x77))
    {
        bmp280_inicializado = true;
    }
    
    if (!bmp280_inicializado)
    {
        //DEBUG_PRINTLN("❌ Error: BMP280 no detectado");
        return;
    }

    // Esperar un poco para que el sensor se estabilice después de la inicialización
    delay(200);

    // Intentar obtener presión inicial para calcular altitud
    float presion;
    if (bmp.getPressure(presion))
    {
        p0_bmp = (uint16_t)(presion / 100.0f);
    }

    //DEBUG_PRINTLN(F("✅ BMP280 inicializado correctamente"));
}

void leerBMP()
{
    // Solo leer si el sensor está inicializado
    if (!bmp280_inicializado)
    {
        return;
    }

    float t = 0, p = 0, a = 0;
    bool lecturaExitosa = false;
    
    // Intentar leer las mediciones
    lecturaExitosa = bmp.getMeasurements(t, p, a);
    
    // Si la lectura fue exitosa y los valores son válidos
    if (lecturaExitosa && !isnan(t) && !isnan(p) && !isnan(a))
    {
        temp_bmp280 = (int16_t)(t * 10);
        presion_bmp280 = (uint16_t)(p / 100.0f);
        altitud_bmp280 = (uint16_t)a;
    }
    // Si la lectura falla, los valores se mantienen en 0 o en el último valor válido

    //DEBUG_PRINT(F("BMP280 → Temp: "));
    //DEBUG_PRINT(temp_bmp280 / 10.0);
    //DEBUG_PRINT(F(" °C | Pres: "));
    //DEBUG_PRINT(presion_bmp280);
    //DEBUG_PRINT(F(" hPa | Alt: "));
    //DEBUG_PRINTLN(altitud_bmp280);
}
