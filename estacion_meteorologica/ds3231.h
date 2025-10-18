#ifndef _DS3231_H
#define _DS3231_H

// =====================================================
//  LIBRERÍAS NECESARIAS
// =====================================================

#include <Wire.h>     // Comunicación I2C entre el microcontrolador y el RTC
#include <RTClib.h>   // Librería oficial para trabajar con el módulo DS3231


// =====================================================
//  OBJETO PRINCIPAL DEL RTC (RELOJ EN TIEMPO REAL)
// =====================================================
// Este objeto maneja todas las funciones del módulo DS3231.
RTC_DS3231 rtc;


// =====================================================
//  VARIABLES GLOBALES DE TIEMPO
// =====================================================
// Se actualizan cada vez que se lee la hora actual desde el módulo RTC.
int DIA, MES, ANIO, HORA, MINUTO, SEGUNDO;
String DIA_SEMANA; // Texto con el nombre del día (Lunes, Martes, etc.)


// =====================================================
//  FUNCIÓN: iniciarRTC()
// -----------------------------------------------------
// Inicializa la comunicación con el módulo DS3231.
// Verifica que esté correctamente conectado y funcionando.
//
// Si el módulo no responde, se queda en un bucle infinito.
// =====================================================
void iniciarRTC() {
    Wire.begin();  // Inicia la comunicación I2C

    // Intentamos detectar el módulo RTC
    if (!rtc.begin()) {
        Serial.println("Error: módulo RTC DS3231 no encontrado");
        while (1); // Se detiene el programa si no se detecta el RTC
    }

    // =====================================================
    // OPCIONES DE CONFIGURACIÓN DE HORA
    // -----------------------------------------------------
    // 🔹 Solo usar UNA de las siguientes líneas UNA VEZ
    //     para establecer la hora correcta en el módulo RTC.
    // 🔹 Luego, comentar nuevamente la línea para evitar
    //     que se sobrescriba la hora cada vez que inicies el Arduino.
    // =====================================================

    // Ajuste manual (ejemplo: 10 de noviembre de 2025, 06:00:00)
    // rtc.adjust(DateTime(2025, 11, 10, 6, 0, 0));

    // Ajuste automático con la hora de compilación del código
    // rtc.adjust(DateTime(__DATE__, __TIME__));

    Serial.println("RTC DS3231 iniciado correctamente");
}


// =====================================================
//  FUNCIÓN: obtenerNombreDia()
// -----------------------------------------------------
// Devuelve el nombre del día de la semana según el valor
// numérico que entrega el módulo (1 = Domingo, 7 = Sábado).
// =====================================================
String obtenerNombreDia(uint8_t diaSemana) {
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


// =====================================================
//  FUNCIÓN: leerRTC()
// -----------------------------------------------------
// Actualiza las variables globales con la fecha y hora actual
// leídas directamente del módulo DS3231.
// Además, devuelve la fecha y hora formateadas como String,
// incluyendo el día de la semana.
//
// Ejemplo de salida: "Vie 17/10/2025 15:42:09"
// =====================================================
String leerRTC() {
    // Obtenemos la fecha y hora actuales desde el RTC
    DateTime fecha = rtc.now();

    // Guardamos los valores en las variables globales
    DIA = fecha.day();
    MES = fecha.month();
    ANIO = fecha.year();
    HORA = fecha.hour();
    MINUTO = fecha.minute();
    SEGUNDO = fecha.second();
    DIA_SEMANA = obtenerNombreDia(fecha.dayOfTheWeek() + 1); // +1 por compatibilidad con RTClib

    // Creamos un "buffer" (una caja temporal) en memoria RAM
    // donde vamos a guardar una cadena de texto formateada.
    // El número 25 indica la cantidad máxima de caracteres
    // que puede almacenar (suficiente para "DD/MM/AAAA HH:MM:SS\0").
    char buffer[35];

    // La función sprintf() "escribe texto dentro del buffer"
    // con el formato que le indiquemos:
    // %02d = número entero de 2 dígitos (rellena con 0 si hace falta)
    // %04d = número entero de 4 dígitos (para el año)
    sprintf(buffer, "%s %02d/%02d/%04d %02d:%02d:%02d",
            DIA_SEMANA.c_str(), DIA, MES, ANIO, HORA, MINUTO, SEGUNDO);

    // Convertimos el buffer (que es un arreglo de caracteres tipo C)
    // en un objeto String de Arduino, que es más cómodo de usar
    // para imprimir, guardar en SD, o concatenar con otros textos.
    return String(buffer);
}


// // =====================================================
// //  FUNCIÓN: mostrarHoraRTC()
// // -----------------------------------------------------
// // Muestra la fecha y hora actual por el Monitor Serie.
// // Solo se usa para depuración y pruebas.
// // =====================================================
// void mostrarHoraRTC() {
//     String horaActual = leerRTC();  // Leemos la hora en formato texto
//     Serial.print("Hora actual → ");
//     Serial.println(horaActual);
// }

#endif
