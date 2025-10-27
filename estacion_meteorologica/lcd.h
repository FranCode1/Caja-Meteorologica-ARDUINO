#ifndef _LCD_H
#define _LCD_H

// =====================================================================
// 📦 LIBRERÍAS NECESARIAS
// =====================================================================
// Estas librerías permiten el control de la pantalla LCD, la comunicación
// I2C, y la gestión de menús con múltiples pantallas.
// Además, se incluyen todas las librerías de sensores y módulos utilizados
// para mostrar sus valores en pantalla.
#include <Arduino.h>            // Funciones base del entorno Arduino
//#include <Wire.h>               // Comunicación I2C (interfaz del LCD)
#include <LiquidCrystal_I2C.h>  // Manejo de pantallas LCD con módulo I2C
#include <LiquidMenu.h>         // Librería para menús dinámicos en pantallas LCD

// Librerías de módulos y sensores
#include "navegacion.h"         // Control de navegación por menú
#include "bmp280.h"             // Sensor de temperatura, humedad y presión atmosférica
#include "ds18b20.h"            // Sensor de temperatura del agua
#include "csmsv2.h"             // Sensor de humedad de la tierra
#include "bh1750.h"             // Sensor de luz ambiental
#include "mq135.h"              // Sensor de gases y CO2
#include "gy906.h"              // Sensor infrarrojo de temperatura
#include "ds3231.h"             // Módulo RTC (reloj en tiempo real)
#include "microsd.h"            // Módulo MicroSD para almacenamiento

// =====================================================================
// 💡 CONFIGURACIÓN DEL LCD
// =====================================================================
// Crea un objeto LCD con dirección I2C 0x3F (típica de pantallas 20x4).
// Si no funciona correctamente, se puede probar con 0x27 o 0x20.
LiquidCrystal_I2C lcd(0x3f, 20, 4);

// =====================================================================
// 🧭 DEFINICIÓN DE PANTALLAS Y LÍNEAS
// =====================================================================
// Cada pantalla (LiquidScreen) agrupa 4 líneas (LiquidLine).
// El texto y las variables se actualizan automáticamente mediante LiquidMenu.
// El orden de creación define el orden de navegación del menú.

// ---------------------------------------------------------------------
// PANTALLA 0 - MENSAJE DE BIENVENIDA
// ---------------------------------------------------------------------
LiquidLine linea1a(4, 0, "!Bienvenidos");
LiquidLine linea2a(8, 1, "a la");
LiquidLine linea3a(6, 2, "Estación");
LiquidLine linea4a(4, 3, "Meteorologica!");
LiquidScreen pantalla0(linea1a, linea2a, linea3a, linea4a);

// ---------------------------------------------------------------------
// PANTALLA 1 - SENSOR BME280
// ---------------------------------------------------------------------
// Muestra temperatura, humedad y presión atmosférica.
LiquidLine linea1b(0, 0, "<=====BMP280======>");
LiquidLine linea2b(0, 1, "Temperatura: ", temp_bmp280, " °C");
LiquidLine linea4b(0, 2, "Presión Atm: ", presion_bmp280, " hPa");
LiquidLine linea3b(0, 3, "Altitud: ", altitud_bmp280, "m");
LiquidScreen pantalla1(linea1b, linea2b, linea3b, linea4b);

// ---------------------------------------------------------------------
// PANTALLA 2 - TEMPERATURA DEL AGUA Y HUMEDAD DEL SUELO
// ---------------------------------------------------------------------
LiquidLine linea1c(0, 0, "<======Ds18b20=====>");
LiquidLine linea2c(0, 1, "Temp. Agua: ", temp_ds18b20, " °C");
LiquidLine linea3c(0, 2, "<======CSMSV2======>");
LiquidLine linea4c(0, 3, "Humedad Tierra: ", humedad_tierra, " %");
LiquidScreen pantalla2(linea1c, linea2c, linea3c, linea4c);

// ---------------------------------------------------------------------
// PANTALLA 3 - SENSOR MQ135 (GASES)
// ---------------------------------------------------------------------
LiquidLine linea1d(0, 0, "<======MQ-135======>");
LiquidLine linea2d(0, 1, "CO2: ", ratio, "%");
LiquidLine linea3d(0, 2, "Estado: ", calidad);
LiquidLine linea4d(0, 3, "Tendencia: ", tendencia);
LiquidScreen pantalla3(linea1d, linea2d, linea3d, linea4d);

// ---------------------------------------------------------------------
// PANTALLA 4 - SENSOR DE LUZ (BH1750) Y GY906 (INFRARROJO)
// ---------------------------------------------------------------------
LiquidLine linea1e(0, 0, "<======BH1750======>");
LiquidLine linea2e(0, 1, "Lux: ", lux, " lx");
LiquidLine linea3e(0, 2, "<======GY-906======>");
LiquidLine linea4e(0, 3, "Temp. Infrarroja: ", TEMP_OBJETO_GY906, " °C");
LiquidScreen pantalla4(linea1e, linea2e, linea3e, linea4e);

// ---------------------------------------------------------------------
// PANTALLA 5 - AJUSTES GENERALES
// ---------------------------------------------------------------------
// Incluye fecha, hora y batería (opcional).
LiquidLine linea1f(0, 0, "<======AJUSTES=====>");
LiquidLine linea2f(1, 1, "Día: ", FECHA);
LiquidLine linea3f(1, 2, "Hora: ", HORARIO);
LiquidLine linea4f(0, 3, "BATERIA: %"); // (opcional)
LiquidScreen pantalla5(linea1f, linea2f, linea3f, linea4f);

// ---------------------------------------------------------------------
// PANTALLAS 6 a 11 - MENSAJES DE AJUSTE, CONFIRMACIÓN Y ALERTA
// ---------------------------------------------------------------------
// Estas pantallas se usan para configurar o mostrar estados del sistema.
// Pueden ser llamadas desde botones o eventos de sistema.

LiquidLine linea1l(0, 0, "");
LiquidLine linea2l(0, 1, "");
LiquidLine linea3l(0, 2, "<===Hasta Luego!===>");
LiquidLine linea4l(0, 3, "");
LiquidScreen pantalla11(linea1l, linea2l, linea3l, linea4l);

// =====================================================================
// 🧩 CREACIÓN DEL MENÚ PRINCIPAL
// =====================================================================
// Se crea el menú "menu" con todas las pantallas definidas arriba.
// El orden aquí determina cómo se navega con los botones.
LiquidMenu menu(
    lcd,
    pantalla0, pantalla1, pantalla2, pantalla3, pantalla4,
    pantalla5, pantalla11
);

// =====================================================================
// ⚙️ FUNCIONES PRINCIPALES DE CONTROL DEL LCD
// =====================================================================

// ---------------------------------------------------------------------
// Función: iniciarPantalla()
// ---------------------------------------------------------------------
// Inicializa la pantalla LCD y el menú de pantallas.
// Se debe llamar dentro del setup() del programa principal.
void iniciarPantalla() {
    lcd.init();       // Inicializa la comunicación con el LCD
    lcd.backlight();  // Enciende la retroiluminación
    lcd.clear();      // Limpia la pantalla
    menu.init();      // Inicializa el sistema de menús
    menu.update();    // Actualiza la primera visualización
}

// ---------------------------------------------------------------------
// Función: mostrarInicio()
// ---------------------------------------------------------------------
// Muestra la pantalla de bienvenida (pantalla0) durante 3 segundos
// antes de pasar a la pantalla principal (pantalla1).
void mostrarInicio() {
    menu.change_screen(&pantalla0);
    menu.update();
    delay(3000); // Tiempo de bienvenida
    menu.change_screen(&pantalla1);
    menu.update();
}

// ---------------------------------------------------------------------
// Función: actualizarPantalla()
// ---------------------------------------------------------------------
// Actualiza el contenido del menú. 
// Debe llamarse periódicamente dentro del loop() para refrescar valores.
void actualizarPantalla() {
    menu.update();
}

// =====================================================================
// 🧠 NOTAS Y FUNCIONES OPCIONALES
// =====================================================================
// Las líneas comentadas a continuación fueron usadas en pruebas o como
// referencia para agregar funciones avanzadas (por ejemplo, control de
// enfoque de línea, creación de caracteres personalizados o navegación).
//
//    menu.switch_focus(false);        // Mover foco entre líneas
//    menu.set_focusedLine(0);         // Establecer línea enfocada
//    linea3_2.attach_function(1, fn_atras); // Asignar función a línea
//    menu.add_screen(pantalla1);      // Agregar nueva pantalla al menú
//    lcd.createChar(0, arrow);        // Crear carácter personalizado
//    pantalla1.set_displayLineCount(4); // Definir líneas visibles
//

// void fn_atras() {
//     if (menu.get_currentScreen() == $pantalla6 || menu.get_currentScreen() == &pantalla8) {
//         // Define qué hace el botón BACK
//         menu.change_screen(5); // Ejemplo: volver a la pantalla AJUSTES
//     } else
//     {
//         return; // No hacer nada
//     }
// }
#endif
