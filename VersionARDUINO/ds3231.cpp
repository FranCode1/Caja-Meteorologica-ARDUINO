#include "ds3231.h"
#include "config.h"
#include <RTClib.h>
#include <string.h>

// ===================== OBJETO DEL RTC =====================
static RTC_DS3231 rtc;
static DateTime fecha;

static bool rtcDisponible = false;

// ===================== VARIABLES GLOBALES =====================
int DIA = 0, MES = 0, ANIO = 0;
int HORA = 0, MINUTO = 0, SEGUNDO = 0;

char DIA_SEMANA[4] = "N/A";
char FECHA[11] = "00/00/0000";
char HORARIO[9] = "00:00:00";

// ===================== NOMBRE DEL DÍA =====================
static const char *obtenerNombreDia(uint8_t diaSemana)
{
    switch (diaSemana)
    {
    case 0:  return "Dom";
    case 1:  return "Lun";
    case 2:  return "Mar";
    case 3:  return "Mie";
    case 4:  return "Jue";
    case 5:  return "Vie";
    case 6:  return "Sab";
    default: return "???";
    }
}

// ===================== INICIO =====================
void iniciarRTC()
{
    if (!rtc.begin())
    {
        //DEBUG_PRINTLN(F("❌ Error: DS3231 no detectado (RTC apagado/desconectado)"));
        rtcDisponible = false;
        return;
    }

    rtcDisponible = true;
    //DEBUG_PRINTLN(F("✅ RTC inicializado correctamente"));

    if (rtc.lostPower())
    {
        //DEBUG_PRINTLN(F("⚠️ RTC perdió la hora, ajustando desde compilación..."));
        rtc.adjust(DateTime(__DATE__, __TIME__));
    }
}

// ===================== LECTURA =====================
void leerRTC()
{
    if (!rtcDisponible)
    {
        strncpy(DIA_SEMANA, "N/A", sizeof(DIA_SEMANA));
        strncpy(FECHA, "00/00/0000", sizeof(FECHA));
        strncpy(HORARIO, "00:00:00", sizeof(HORARIO));

        //DEBUG_PRINTLN(F("RTC no disponible, usando valores por defecto"));
        return;
    }

    fecha = rtc.now();

    DIA = fecha.day();
    MES = fecha.month();
    ANIO = fecha.year();
    HORA = fecha.hour();
    MINUTO = fecha.minute();
    SEGUNDO = fecha.second();

    strncpy(DIA_SEMANA, obtenerNombreDia(fecha.dayOfTheWeek()), sizeof(DIA_SEMANA));
    DIA_SEMANA[3] = '\0';

    snprintf(FECHA, sizeof(FECHA), "%02d/%02d/%04d", DIA, MES, ANIO);
    snprintf(HORARIO, sizeof(HORARIO), "%02d:%02d:%02d", HORA, MINUTO, SEGUNDO);

    //DEBUG_PRINT(F("RTC leído: "));
    //DEBUG_PRINT(FECHA);
    //DEBUG_PRINT(" ");
    //DEBUG_PRINTLN(HORARIO);
}
