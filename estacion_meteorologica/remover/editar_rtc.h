#ifndef _EDITAR_RTC_H
#define _EDITAR_RTC_H

#include <Arduino.h>
#include "DS3231.h" // Necesita el objeto rtc y las variables globales

// Pines de control
#define PIN_LED_CONFIRM 2 // LED de confirmación
#define BOTON_UP 2
#define BOTON_DOWN 3
#define BOTON_OK 4
#define BOTON_BACK 5

// Estado de edición
int cursor = 0;           // posición del dígito o campo seleccionado
bool editandoHora = true; // true = hora, false = fecha

// Copias temporales de la fecha y hora actual
int diaTemp, mesTemp, anioTemp, horaTemp, minutoTemp, segundoTemp;

void iniciarEdicionRTC(bool editarHora)
{
    editandoHora = editarHora;
    DateTime now = rtc.now();

    diaTemp = now.day();
    mesTemp = now.month();
    anioTemp = now.year();
    horaTemp = now.hour();
    minutoTemp = now.minute();
    segundoTemp = now.second();

    cursor = 0;

    pinMode(PIN_LED_CONFIRM, OUTPUT);
    digitalWrite(PIN_LED_CONFIRM, LOW);
}

void mostrarEdicion()
{
    if (editandoHora)
    {
        Serial.printf("Editar Hora: %02d:%02d:%02d (Cursor: %d)\n", horaTemp, minutoTemp, segundoTemp, cursor);
    }
    else
    {
        Serial.printf("Editar Fecha: %02d/%02d/%04d (Cursor: %d)\n", diaTemp, mesTemp, anioTemp, cursor);
    }
}

// Cambia el valor del campo actual
void moverValor(int dir)
{
    if (editandoHora)
    {
        if (cursor == 0)
            horaTemp = constrain(horaTemp + dir, 0, 23);
        if (cursor == 1)
            minutoTemp = constrain(minutoTemp + dir, 0, 59);
        if (cursor == 2)
            segundoTemp = constrain(segundoTemp + dir, 0, 59);
    }
    else
    {
        if (cursor == 0)
            diaTemp = constrain(diaTemp + dir, 1, 31);
        if (cursor == 1)
            mesTemp = constrain(mesTemp + dir, 1, 12);
        if (cursor == 2)
            anioTemp = constrain(anioTemp + dir, 2020, 2099);
    }
    mostrarEdicion();
}

// Cambia el campo seleccionado
void moverCursor(int dir)
{
    if (editandoHora)
        cursor = (cursor + dir + 3) % 3;
    else
        cursor = (cursor + dir + 3) % 3;
    mostrarEdicion();
}

// Guarda los cambios y titila el LED
void confirmarCambios()
{
    rtc.adjust(DateTime(anioTemp, mesTemp, diaTemp, horaTemp, minutoTemp, segundoTemp));
    Serial.println("✅ RTC actualizado.");

    digitalWrite(PIN_LED_CONFIRM, HIGH);
    delay(1000);
    digitalWrite(PIN_LED_CONFIRM, LOW);
}

#endif
