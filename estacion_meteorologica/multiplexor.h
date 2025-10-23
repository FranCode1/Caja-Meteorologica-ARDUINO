#ifndef _MULTIPLEXOR_H_
#define _MULTIPLEXOR_H_

// =====================================================================
// 📦 LIBRERÍAS NECESARIAS
// =====================================================================
// Solo necesitamos la librería Wire.h, ya que el TCA9548A funciona por I2C.
#include <Arduino.h>
#include <Wire.h>

// =====================================================================
// ⚙️ CONFIGURACIÓN DEL MUX TCA9548A
// =====================================================================
// Dirección base del multiplexor TCA9548A (por defecto 0x70).
// Si usás varios multiplexores, podés cambiar las líneas A0–A2 para
// variar la dirección (de 0x70 hasta 0x77).
#define TCA9548A_ADDR 0x70

// =====================================================================
// 🧭 DEFINICIÓN DE CANALES
// =====================================================================
// Esto permite usar nombres legibles en lugar de números al seleccionar
// un canal. Por ejemplo: seleccionarCanal(CANAL_LCD);
#define CANAL_LCD 7    // OLED o LCD (display principal)
#define CANAL_RTC 6    // DS3231
#define CANAL_BMP280 5 // Sensor ambiental (Temp/Pres/Alti)
#define CANAL_BH1750 4 // Sensor de luz
#define CANAL_GY906 3  // Sensor infrarrojo
// Los canales 0,1,2 quedan libres por si agregás más sensores I2C

// =====================================================================
// 🔌 FUNCIÓN PRINCIPAL: seleccionarCanal()
// =====================================================================
// Esta función activa uno de los 8 canales del TCA9548A (0–7).
// Solo un canal puede estar activo al mismo tiempo.
// ---------------------------------------------------------------------
// Ejemplo de uso:
//     seleccionarCanal(CANAL_RTC);  // Habilita el canal 6
// ---------------------------------------------------------------------
// Si se pasa un número mayor a 7, no hace nada (protección básica).
// =====================================================================
void seleccionarCanal(uint8_t canal)
{
    if (canal > 7)
        return; // Protección: evita canales inválidos
    Wire.beginTransmission(TCA9548A_ADDR);
    Wire.write(1 << canal); // Activa el canal indicado (bit-shift)
    Wire.endTransmission();
}

#endif
