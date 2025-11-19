#include "bh1750.h"

// ====== OBJETO ======
BH1750 sensorBH1750;

// ====== VARIABLES ======
float lux = 0.0F;

// ====== INICIO ======
void iniciarBH1750()
{

    // El begin del Wire ya lo hace el programa principal
    if (!sensorBH1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE))
    {
        //DEBUG_PRINTLN(F("❌ Error: BH1750 no detectado"));
    }
    else
    {
        //DEBUG_PRINTLN(F("✅ BH1750 inicializado correctamente"));
    }
}

// ====== LECTURA ======
void leerBH1750()
{

    lux = sensorBH1750.readLightLevel();

    // Validación de lectura
    if (lux == 65535 || lux < 0 || lux > 65535)
    {
        //DEBUG_PRINTLN(F("⚠️ BH1750 → Lectura inválida o sensor desconectado"));
        return;
    }

    //DEBUG_PRINT(F("BH1750 → Lux: "));
    //DEBUG_PRINTLN(lux);
}
