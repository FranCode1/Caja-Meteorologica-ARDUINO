#ifndef _DS3231_H
#define _DS3231_H

#include <RTClib.h> //libreria para el reloj(Ds3231)

RTC_DS3231 rtc; // crea un objeto para el reloj

void setup()
{
    Serial.begin(9600);

    // RELOJ
    if (!rtc.begin())
    {
        Serial.println("Modulo RTC no encontrado!");
        while (1)
            ;
    }
    // rtc.adjust(DateTime(2025, 11, 10, 06, 0, 0)); //DateTime(año, dia, mes, hora, minutos, segundos);
    rtc.adjust(DateTime(__DATE__, __TIME__)); // esta linea solo se tiene que ejecutar una sola vez en el dispositivo
    // una vez ejecutada no hace falta que se ejecute otra vez porque el horario ya esta ajustado
}

void loop()
{
    // RELOJ
    DateTime fecha = rtc.now();

    Serial.print(fecha.day());
    Serial.print("/");
    Serial.print(fecha.month());
    Serial.print("/");
    Serial.print(fecha.year());
    Serial.print(" ");
    Serial.print(fecha.hour());
    Serial.print(":");
    Serial.print(fecha.minute());
    Serial.print(":");
    Serial.print(fecha.second());

    if (fecha.hour() == 22)
    {
        // guardar registro de la info en la Micro SD
    }

    // WARNING: creo que no hace falta tanto bardo, osea esto esta en las pantallas
    //  entonces cuando cargan las pantallas se actualizan los valores por el rtc.now()
}

#endif