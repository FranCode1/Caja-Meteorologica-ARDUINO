// =====================================================
// ESTACIÓN METEOROLÓGICA - PROGRAMA PRINCIPAL
// =====================================================
// Control central de sensores, pantalla y almacenamiento.
// Lectura modular, navegación y registro optimizado.
// =====================================================

// =====================================================
// LIBRERÍAS PRINCIPALES
// =====================================================
#include <Wire.h>         // Comunicación I2C
#include "lcd.h"          // Pantalla LCD
#include "navegacion.h"   // Botones y control de pantallas

// =====================================================
// MÓDULOS ACTIVOS
// =====================================================
#include "bmp280.h"       // Temp, presión y altitud
#include "ds18b20.h"      // Temp del agua
#include "csmsv2.h"       // Humedad del suelo
#include "bh1750.h"       // Luz ambiental
#include "mq135.h"        // Gases / CO₂
#include "gy906.h"        // Temp infrarroja
#include "ds3231.h"       // Reloj en tiempo real
#include "microsd.h"      // Registro en tarjeta SD
#include "leds_guia.h"    // Indicadores LED por pantalla

// =====================================================
// CONFIGURACIÓN INICIAL
// =====================================================
void setup() {
  Serial.begin(9600);
  Wire.begin();

  // modoSimulacion();  // 👈 Carga valores de prueba

  iniciarPantalla();          // LCD
  iniciarLedsPantalla();      // LEDs
  cambiarLedPantalla(1);      // LED inicial
  iniciarRTC();               // Reloj
  iniciarBMP();               // BMP280
  iniciarBH1750();            // BH1750
  iniciarGY906();          // Si está conectado
  iniciarDS18B20();           // DS18B20
  iniciarCSMSV2();            // Humedad suelo
  iniciarMQ135();             // MQ135
  iniciarNavegacion();        // Botones
  calibrarMQ135();            // Calibración gases
  mostrarPantalla(1);         // Pantalla inicial
  iniciarSD();                // Inicia microSD
}

// =====================================================
// BUCLE PRINCIPAL
// =====================================================
void loop() {
  leerNavegacion();           // Botones / cambio de pantallas
  leerRTC();                  // Hora y fecha
  leerBMP();                  // Presión y altitud
  leerBH1750();               // Luz
  leerGY906();                // Infrarrojo
  leerDS18B20();              // Temp agua
  leerCSMSV2();               // Humedad tierra
  leerMQ135();                // CO₂
  escribirSD("registro.txt"); // Guarda datos
  cambiarLedPantalla(pantallaActual); // LED activo

  actualizarPantalla(); // 👈 Esto refresca el LCD cada segundo
  // delay(1000);                // Actualización cada segundo
}


// void modoSimulacion() {
//   temp_bmp280 = 23.5;
//   presion_bmp280 = 1013.2;
//   altitud_bmp280 = 50.0;

//   temp_ds18b20 = 24.0;
//   humedad_tierra = 65;

//   ratio = 0.03;
//   calidad = "Buena";
//   tendencia = "Estable";

  // lux = 250.0;
  // TEMP_OBJETO_GY906 = 25.5;

  // FECHA = "08/11/2025";
  // HORARIO = "15:45:00";
  // DIA_SEMANA = "Sabado";
// }