#ifndef _DS3231_H
#define _DS3231_H

#include <Wire.h>
#include <RTClib.h>  // Librería para el módulo RTC DS3231

// ---------------------------------
// OBJETO DEL RELOJ
// ---------------------------------
RTC_DS3231 rtc;

// ---------------------------------
// VARIABLES DE TIEMPO
// ---------------------------------
int DIA, MES, ANIO, HORA, MINUTO, SEGUNDO;

// ---------------------------------
// INICIALIZACIÓN
// ---------------------------------
void iniciarRTC() {
    Wire.begin();

    if (!rtc.begin()) {
        Serial.println("Error: módulo RTC no encontrado");
        while (1);
    }

    // Solo descomentar una vez para ajustar manualmente la hora:
    // rtc.adjust(DateTime(2025, 11, 10, 6, 0, 0)); // Año, Mes, Día, Hora, Minuto, Segundo

    // Esta línea sincroniza con la hora de compilación (solo ejecutar una vez)
    // rtc.adjust(DateTime(__DATE__, __TIME__));

    Serial.println("RTC DS3231 iniciado correctamente");
}

// ---------------------------------
// ACTUALIZAR VARIABLES DE TIEMPO
// ---------------------------------
void leerRTC() {
    DateTime fecha = rtc.now();

    DIA = fecha.day();
    MES = fecha.month();
    ANIO = fecha.year();
    HORA = fecha.hour();
    MINUTO = fecha.minute();
    SEGUNDO = fecha.second();
}

// ---------------------------------
// MOSTRAR EN SERIAL (DEBUG), esta nunca se usa asi que esta bien borrarla
// ---------------------------------
void mostrarHoraRTC() {
    leerRTC();

    char buffer[25];
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d",
            DIA, MES, ANIO, HORA, MINUTO, SEGUNDO);

    Serial.println(buffer);
}

#endif
