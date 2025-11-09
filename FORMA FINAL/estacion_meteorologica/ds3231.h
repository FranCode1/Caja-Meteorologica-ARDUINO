#ifndef _DS3231_H
#define _DS3231_H

#include <Arduino.h>
#include <RTClib.h>

// ===================== OBJETO DEL RTC =====================
RTC_DS3231 rtc;
DateTime fecha;

// ===================== VARIABLES GLOBALES =====================
int DIA, MES, ANIO, HORA, MINUTO, SEGUNDO;
String DIA_SEMANA, FECHA, HORARIO;

// ===================== INICIO =====================
inline void iniciarRTC() {
    // Wire.begin(); // Si no se inicializa en otro módulo

    // Inicializa y ajusta automáticamente con la hora de compilación
    rtc.begin();
    rtc.adjust(DateTime(__DATE__, __TIME__));
}

// ===================== NOMBRE DEL DÍA =====================
inline String obtenerNombreDia(uint8_t diaSemana) {
    switch (diaSemana) {
        case 1: return "Dom";
        case 2: return "Lun";
        case 3: return "Mar";
        case 4: return "Mie";
        case 5: return "Jue";
        case 6: return "Vie";
        case 7: return "Sab";
        default: return "???";
    }
}

// ===================== LECTURA =====================
inline String leerRTC() {
    fecha = rtc.now();

    DIA = fecha.day();
    MES = fecha.month();
    ANIO = fecha.year();
    HORA = fecha.hour();
    MINUTO = fecha.minute();
    SEGUNDO = fecha.second();
    DIA_SEMANA = obtenerNombreDia(fecha.dayOfTheWeek() + 1);

    char buffer[35];
    sprintf(buffer, "%s %02d/%02d/%04d %02d:%02d:%02d",
            DIA_SEMANA.c_str(), DIA, MES, ANIO, HORA, MINUTO, SEGUNDO);

    return String(buffer);
}

#endif
