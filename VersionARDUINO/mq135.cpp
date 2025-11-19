#include "mq135.h"
#include <string.h>

// ===================== VARIABLES INTERNAS =====================
// NOTA: estas NO se duplican, porque solo existen aquí

float RO = 10.0;
float RS = 0.0;
float ratio = 0.0;

char calidad[20] = "Desconocida";
char tendencia[20] = "Estable";

// Estado interno antibloqueante
static bool mq135_calibrado = false;
static unsigned long t_anterior_cal = 0;
static uint16_t contador_cal = 0;
static float RS_sum = 0.0;

// Filtro
static float RS_filtrado = 0.0;

// ===================== INICIO =====================
void iniciarMQ135()
{
    pinMode(MQ135_PIN, INPUT);
    //DEBUG_PRINTLN(F("Iniciando calibración no bloqueante del MQ135..."));
}

// ===================== CALIBRACIÓN =====================
bool calibrarMQ135()
{

    if (mq135_calibrado)
        return true;

    unsigned long ahora = millis();

    if (ahora - t_anterior_cal >= CALIB_INTERVAL)
    {

        t_anterior_cal = ahora;

        int adc = analogRead(MQ135_PIN);
        if (adc == 0)   adc = 1;

        float rs = RL * (1023.0 / adc - 1.0);

        RS_sum += rs;
        contador_cal++;

        //DEBUG_PRINT(F("Calibrando MQ135 ("));
        //DEBUG_PRINT(contador_cal);
        //DEBUG_PRINT(F("/"));
        //DEBUG_PRINT(CALIB_SAMPLES);
        //DEBUG_PRINT(F(") RS: "));
        //DEBUG_PRINTLN(rs);

        if (contador_cal >= CALIB_SAMPLES)
        {

            RS = RS_sum / CALIB_SAMPLES;
            RO = RS / CLEAN_AIR_RATIO;

            mq135_calibrado = true;
            //DEBUG_PRINTLN(F("✅ Calibración MQ135 completada"));
        }
    }

    return mq135_calibrado;
}

// ===================== LECTURA =====================
float leerMQ135()
{

    if (!mq135_calibrado)
    {
        //DEBUG_PRINTLN(F("⚠️ MQ135 aún calibrándose"));
        return -1;
    }

    int adc = analogRead(MQ135_PIN);
    if (adc == 0)   adc = 1;

    float RS_actual = RL * (1023.0 / adc - 1.0);
    RS_filtrado = 0.90 * RS_filtrado + 0.10 * RS_actual;

    RS = RS_filtrado;
    ratio = RS / RO;

    // Clasificación del aire
    if (ratio > 3.0)        strcpy(calidad, "Excelente");
    else if (ratio > 2.0)   strcpy(calidad, "Buena");
    else if (ratio > 1.5)   strcpy(calidad, "Regular");
    else if (ratio > 1.0)   strcpy(calidad, "Mala");
    else                    strcpy(calidad, "Crítica");

    // Tendencia (varía con respecto al último ratio)
    static float ratio_anterior = ratio;

    if (ratio > ratio_anterior + 0.10)      strcpy(tendencia, "Empeorando");
    else if (ratio < ratio_anterior - 0.10) strcpy(tendencia, "Mejorando");
    else                                    strcpy(tendencia, "Estable");

    ratio_anterior = ratio;

    //DEBUG_PRINT(F("MQ135 → RS: "));
    //DEBUG_PRINT(RS);
    //DEBUG_PRINT(F(" | Ratio: "));
    //DEBUG_PRINT(ratio);
    //DEBUG_PRINT(F(" | Calidad: "));
    //DEBUG_PRINT(calidad);
    //DEBUG_PRINT(F(" | Tendencia: "));
    //DEBUG_PRINTLN(tendencia);

    return ratio;
}

// if (RS_filtrado == 0.0) RS_filtrado = RS_actual; //esto es para evitar lecturas frias
