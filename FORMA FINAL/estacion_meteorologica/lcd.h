#ifndef _LCD_H
#define _LCD_H

// =====================================================
// LIBRERÍAS
// =====================================================
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// =====================================================
// VARIABLES EXTERNAS DE SENSORES
// =====================================================
extern float temp_bmp280, presion_bmp280, altitud_bmp280;
extern float temp_ds18b20;
extern uint8_t humedad_tierra;
extern float ratio;
extern String calidad, tendencia;
extern float lux;
extern float TEMP_OBJETO_GY906;
extern String FECHA, HORARIO, DIA_SEMANA;

// =====================================================
// LCD CONFIGURACIÓN
// =====================================================
LiquidCrystal_I2C lcd(0x27, 20, 4); // Dir I2C y tamaño (20x4)

// =====================================================
// FUNCIONES DE CONTROL LCD
// =====================================================

// Pantalla de bienvenida
inline void pantallaInicio() {
    lcd.clear();
    lcd.setCursor(4, 0); lcd.print("!Bienvenidos");
    lcd.setCursor(8, 1); lcd.print("a la");
    lcd.setCursor(6, 2); lcd.print("Estacion");
    lcd.setCursor(4, 3); lcd.print("Meteorologica!");
    delay(3000);
}

// =====================================================
// PANTALLAS DE INFORMACIÓN
// =====================================================

inline void pantallaBMP280() {
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("<=====BMP280=====>");
    lcd.setCursor(0, 1); lcd.print("Temp: "); lcd.print(temp_bmp280, 1); lcd.print(" C");
    lcd.setCursor(0, 2); lcd.print("Presion: "); lcd.print(presion_bmp280, 1); lcd.print(" hPa");
    lcd.setCursor(0, 3); lcd.print("Altitud: "); lcd.print(altitud_bmp280, 1); lcd.print(" m");
}

inline void pantallaDS18_CSMS() {
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("<=====DS18B20====>");
    lcd.setCursor(0, 1); lcd.print("Temp Agua: "); lcd.print(temp_ds18b20, 1); lcd.print(" C");
    lcd.setCursor(0, 2); lcd.print("<=====CSMSV2=====>");
    lcd.setCursor(0, 3); lcd.print("Humedad: "); lcd.print(humedad_tierra); lcd.print(" %");
}

inline void pantallaMQ135() {
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("<======MQ135======>");
    lcd.setCursor(0, 1); lcd.print("CO2: "); lcd.print(ratio, 1); lcd.print("%");
    lcd.setCursor(0, 2); lcd.print("Estado: "); lcd.print(calidad);
    lcd.setCursor(0, 3); lcd.print("Tendencia: "); lcd.print(tendencia);
}

inline void pantallaBH_GY() {
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("<=====BH1750=====>");
    lcd.setCursor(0, 1); lcd.print("Lux: "); lcd.print(lux, 1);
    lcd.setCursor(0, 2); lcd.print("<=====GY906======>");
    lcd.setCursor(0, 3); lcd.print("Temp IR: "); lcd.print(TEMP_OBJETO_GY906, 1); lcd.print(" C");
}

inline void pantallaRTC() {
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("<=======FECHA======>");
    lcd.setCursor(0, 1); lcd.print("Dia: "); lcd.print(DIA_SEMANA); lcd.print(" "); lcd.print(FECHA);
    lcd.setCursor(0, 2); lcd.print("<======HORARIO=====>");
    lcd.setCursor(0, 3); lcd.print("Hora: "); lcd.print(HORARIO);
}

// =====================================================
// INICIALIZACIÓN
// =====================================================
inline void iniciarPantalla() {
    lcd.begin(20, 4);
    lcd.backlight();
    lcd.clear();
    pantallaInicio();
}

// =====================================================
// CAMBIO DE PANTALLAS
// =====================================================
uint8_t pantallaActual = 0;

void mostrarPantalla(uint8_t id) {
    pantallaActual = id;
    switch (id) {
        case 0: pantallaBMP280(); break;
        case 1: pantallaDS18_CSMS(); break;
        case 2: pantallaMQ135(); break;
        case 3: pantallaBH_GY(); break;
        case 4: pantallaRTC(); break;
    }
}

#endif
