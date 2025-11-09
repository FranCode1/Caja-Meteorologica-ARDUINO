#ifndef _CONCEPTOS_CPP_H
#define _CONCEPTOS_CPP_H

// ======================================================================
// 📘 ARCHIVO EDUCATIVO: CONCEPTOS FUNDAMENTALES DE C++ Y ARDUINO
// ======================================================================
// Este archivo explica con ejemplos los conceptos más usados en proyectos
// de Arduino y C++, con comentarios detallados para facilitar su comprensión.
// ======================================================================

#include <Arduino.h>  // Incluimos funciones básicas de Arduino
#include <EEPROM.h>   // Librería para manejo de memoria EEPROM


// ======================================================================
// 🧠 1. constexpr
// ----------------------------------------------------------------------
// 'constexpr' se usa para declarar constantes evaluadas en tiempo de
// compilación (no en tiempo de ejecución). Esto permite optimizar el código.
//
// Ejemplo: una constante que no cambia y se conoce desde el inicio.
// ======================================================================
constexpr int MAX_TEMPERATURA = 100;  // Valor fijo conocido antes de compilar


// ======================================================================
// 🌍 2. extern
// ----------------------------------------------------------------------
// 'extern' indica que una variable o función está definida en otro archivo.
// Se usa para compartir variables globales entre varios .h o .ino.
//
// Ejemplo:
// En 'variables.h':    extern int contador;
// En 'main.ino':       int contador = 0;
// ======================================================================
extern int contadorGlobal;  // Solo declaramos, la definición está en otro archivo


// ======================================================================
// 🔢 3. uint8_t
// ----------------------------------------------------------------------
// Es un tipo de dato entero sin signo de 8 bits (0 a 255).
// Equivale a 'unsigned char'.
//
// Se usa mucho en Arduino para ahorrar memoria.
// ======================================================================
uint8_t ledPin = 13;  // Guardamos el número de pin (0–255)


// ======================================================================
// 🌊 4. float
// ----------------------------------------------------------------------
// Representa números con decimales. Ocupa 4 bytes en Arduino UNO.
//
// Ejemplo: valores de sensores.
// ======================================================================
float temperatura = 23.7;  // Número con decimales


// ======================================================================
// 🔤 5. String
// ----------------------------------------------------------------------
// Tipo de dato para manejar texto (cadenas de caracteres).
// Se diferencia de 'char[]' por ser un objeto con métodos propios.
//
// Ejemplo: concatenar texto fácilmente.
// ======================================================================
String mensaje = "Temperatura: ";
String lectura = mensaje + String(temperatura) + "°C";  // "Temperatura: 23.7°C"


// ======================================================================
// 🔁 6. switch, case, default
// ----------------------------------------------------------------------
// Estructura de control que ejecuta diferentes bloques según un valor.
//
// Ejemplo: seleccionar acción según el modo actual.
// ======================================================================
uint8_t modo = 2;
void ejemploSwitch() {
    switch (modo) {
        case 1:
            Serial.println("Modo 1: Sensor");
            break;
        case 2:
            Serial.println("Modo 2: Guardar en SD");
            break;
        default:
            Serial.println("Modo desconocido");
            break;
    }
}


// ======================================================================
// ⚡ 7. inline y void
// ----------------------------------------------------------------------
// 'inline': sugiere al compilador que inserte el código directamente
//           para optimizar la ejecución (evita llamadas a función).
// 'void':   indica que la función NO devuelve ningún valor.
//
// Ejemplo:
// ======================================================================
inline void encenderLed(uint8_t pin) {
    digitalWrite(pin, HIGH);
}


// ======================================================================
// ⏱️ 8. millis()
// ----------------------------------------------------------------------
// Devuelve el número de milisegundos desde que Arduino se encendió.
// Se usa para medir tiempo sin usar delay().
//
// Ejemplo: parpadeo sin delay.
// ======================================================================
unsigned long tiempoPrevio = 0;
void parpadeoNoBloqueante(uint8_t pin) {
    unsigned long ahora = millis();
    if (ahora - tiempoPrevio >= 1000) {  // Cada 1000 ms = 1 segundo
        digitalWrite(pin, !digitalRead(pin)); // Cambia estado del LED
        tiempoPrevio = ahora;
    }
}


// ======================================================================
// 🔌 9. INPUT_PULLUP
// ----------------------------------------------------------------------
// Modo de pin que activa una resistencia interna de 10kΩ.
// Evita lecturas flotantes en botones.
//
// Ejemplo: configurar un botón sin resistencia externa.
// ======================================================================
const uint8_t BOTON = 2;
void configurarBoton() {
    pinMode(BOTON, INPUT_PULLUP);  // Botón conectado a GND
}


// ======================================================================
// 📦 10. static
// ----------------------------------------------------------------------
// Mantiene el valor de una variable entre ejecuciones de la función,
// o limita el alcance a solo ese archivo.
//
// Ejemplo: contar llamadas sin variable global.
// ======================================================================
void contarLlamadas() {
    static int veces = 0;  // Se conserva entre ejecuciones
    veces++;
    Serial.println(veces);
}


// ======================================================================
// 🔢 11. unsigned
// ----------------------------------------------------------------------
// Indica que un número no puede ser negativo.
// Ejemplo: 'unsigned int' va de 0 a 65535.
// ======================================================================
unsigned int contador = 0;


// ======================================================================
// 🕒 12. long
// ----------------------------------------------------------------------
// Entero largo de 4 bytes (−2,147,483,648 a 2,147,483,647).
// En Arduino se usa mucho con millis().
// ======================================================================
long tiempoTotal = 0;


// ======================================================================
// ✅ 13. bool
// ----------------------------------------------------------------------
// Tipo de dato lógico: solo puede ser true o false.
// ======================================================================
bool sensorActivo = true;


// ======================================================================
// 💾 14. EEPROM
// ----------------------------------------------------------------------
// Permite guardar datos en memoria no volátil (no se borra al apagar).
//
// Ejemplo: guardar un número entre reinicios.
// ======================================================================
void ejemploEEPROM() {
    int valor = 42;
    EEPROM.put(0, valor);   // Guardar en dirección 0
    EEPROM.get(0, valor);   // Leer desde dirección 0
    Serial.println(valor);
}


// ======================================================================
// 🧭 15. Punteros (* y &)
// ----------------------------------------------------------------------
// Un puntero guarda la dirección de memoria de otra variable.
//
// Ejemplo:
//   * → accede al contenido de la dirección.
//   & → obtiene la dirección de una variable.
// ======================================================================
int numero = 10;
int *ptr = &numero;   // Guarda la dirección de 'numero'

void ejemploPunteros() {
    Serial.print("Valor: "); Serial.println(*ptr);   // Muestra 10
    Serial.print("Dirección: "); Serial.println((uintptr_t)ptr, HEX);
}


// ======================================================================
// 🔠 16. char
// ----------------------------------------------------------------------
// Tipo de dato que representa un solo carácter o una cadena C clásica.
//
// Ejemplo: texto con 'char[]'.
// ======================================================================
char texto[] = "Hola";
char letra = 'A';  // Un solo carácter


// ======================================================================
// 🧰 17. Buffer
// ----------------------------------------------------------------------
// Es un espacio de memoria temporal usado para almacenar datos antes
// de procesarlos o transmitirlos.
//
// Ejemplo: recibir una cadena de caracteres.
// ======================================================================
char buffer[20];  // Espacio para 20 caracteres

void guardarEnBuffer() {
    strcpy(buffer, "Mensaje OK");  // Copia texto al buffer
    Serial.println(buffer);
}


// ======================================================================
// 🧮 18. sprintf()
// ----------------------------------------------------------------------
// Función para formatear texto en un arreglo 'char' (como printf pero
// sin imprimir directamente).
//
// Ejemplo: crear una cadena con variables.
// ======================================================================
void ejemploSprintf() {
    char salida[50];
    int temperatura = 25;
    float humedad = 60.5;

    sprintf(salida, "Temp: %d°C | Hum: %.1f%%", temperatura, humedad);
    Serial.println(salida);  // Imprime: Temp: 25°C | Hum: 60.5%
}

#endif
