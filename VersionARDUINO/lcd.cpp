#include "lcd.h"
#include "config.h"
#include <LiquidCrystal_I2C.h>

// ====================== OBJETO LCD ======================
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// LiquidCrystal_I2C lcd(0x27, 20, 4);

// ====================== VARIABLES INTERNAS ======================
bool bienvenidaMostrada = false;
static unsigned long inicioBienvenida = 0;

uint8_t pantallaActual = 0; // pantalla de bienvenida
const uint8_t totalPantallas = 5;

unsigned long bloqueoRefresco = 0;

// ====================== PANTALLAS ======================
static void pantallaInicio()
{
    // No hacer clear aquí, mostrarPantalla() ya lo hace
    lcd.setCursor(4, 0); lcd.print(F("!Bienvenidos"));
    lcd.setCursor(8, 1); lcd.print(F("a la"));
    lcd.setCursor(6, 2); lcd.print(F("Estacion"));
    lcd.setCursor(4, 3); lcd.print(F("Meteorologica!"));

    if (!bienvenidaMostrada)
    {
        inicioBienvenida = millis();
        bienvenidaMostrada = true;
    }
}

static void pantallaBMP280()
{
    lcd.setCursor(0, 0); lcd.print(F("<======BMP280======>"));
    lcd.setCursor(0, 1); lcd.print(F("Temp: ")); 
    lcd.print(temp_bmp280 / 10.0, 1); lcd.print(F(" C"));
    lcd.setCursor(0, 2); lcd.print(F("Presion: ")); lcd.print(presion_bmp280); lcd.print(F(" hPa"));
    lcd.setCursor(0, 3); lcd.print(F("Altitud: ")); lcd.print(altitud_bmp280); lcd.print(F(" m"));
}

static void pantallaDS18_CSMS()
{
    lcd.setCursor(0, 0); lcd.print(F("<======DS18B20=====>"));
    lcd.setCursor(0, 1); lcd.print(F("Temp Agua: ")); lcd.print(temp_ds18b20); lcd.print(F(" C"));
    lcd.setCursor(0, 1); lcd.print(F("Temp Agua: ")); lcd.print(0); lcd.print(F(" C"));
    lcd.setCursor(0, 2); lcd.print(F("<======CSMSV2======>"));
    lcd.setCursor(0, 3); lcd.print(F("Humedad: ")); lcd.print(humedad_tierra); lcd.print(F(" %"));
}

static void pantallaMQ135()
{
    lcd.setCursor(0, 0); lcd.print(F("<======MQ135=======>"));
    lcd.setCursor(0, 1); lcd.print(F("CO2: ")); lcd.print(ratio); lcd.print(F("%"));
    lcd.setCursor(0, 2); lcd.print(F("Estado: ")); lcd.print(calidad);
    lcd.setCursor(0, 3); lcd.print(F("Tendencia: ")); lcd.print(tendencia);
}

static void pantallaBH_GY()
{
    lcd.setCursor(0, 0); lcd.print(F("<======BH1750======>"));
    lcd.setCursor(0, 1); lcd.print(F("Luz: ")); lcd.print(lux); lcd.print(F(" lx"));
    lcd.setCursor(0, 2); lcd.print(F("<======GY906=======>"));
    lcd.setCursor(0, 3); lcd.print(F("Temp IR: ")); lcd.print(temp_objeto_gy906); lcd.print(F(" C"));
}

static void pantallaRTC()
{
    lcd.setCursor(0, 0); lcd.print(F("<=======FECHA======>"));
    lcd.setCursor(0, 1); lcd.print(F("Dia: ")); lcd.print(DIA_SEMANA); lcd.print(F(" ")); lcd.print(FECHA);
    lcd.setCursor(0, 2); lcd.print(F("<======HORARIO=====>"));
    lcd.setCursor(0, 3); lcd.print(F("Hora: ")); lcd.print(HORARIO);
}

// ====================== INICIO ======================
void iniciarLCD()
{
    lcd.begin(20, 4);
    lcd.backlight();
    lcd.clear();

    pantallaInicio();

    //DEBUG_PRINTLN(F("LCD inicializado y pantalla de bienvenida mostrada"));
}

// ====================== CAMBIO DE PANTALLA ======================
void mostrarPantalla(uint8_t id)
{
    if (id > totalPantallas)  return;

    static uint8_t ultimaPantallaMostrada = 255; // Valor inicial que nunca coincidirá

    // Si cambió la pantalla, limpiar el LCD
    if (ultimaPantallaMostrada != id)
    {
        lcd.clear();
        ultimaPantallaMostrada = id;
    }

    // Actualizar pantallaActual si es una pantalla válida
    if (id > 0)
    {
        pantallaActual = id;
    }

    // Siempre mostrar la pantalla solicitada (necesario para refresco de datos)
    switch (id)
    {
        case 0: pantallaInicio();      break;
        case 1: pantallaBMP280();      break;
        case 2: pantallaDS18_CSMS();   break;
        case 3: pantallaMQ135();       break;
        case 4: pantallaBH_GY();       break;
        case 5: pantallaRTC();         break;
    }
}

// ====================== REFRESCO AUTOMÁTICO ======================
void actualizarLCD()
{
    static unsigned long ultimoRefresco = 0;
    static unsigned long ultimoCambioPantalla = 0;
    const unsigned long INTERVALO_REFRESCO = 1000;      // Refrescar datos cada 1 segundo
    const unsigned long INTERVALO_CAMBIO_PANTALLA = 5000; // Cambiar pantalla cada 5 segundos

    unsigned long ahora = millis();

    // =====================
    // CONTROL DE BIENVENIDA
    // =====================
    if (pantallaActual == 0 && bienvenidaMostrada)
    {
        if (ahora - inicioBienvenida >= 2500)
        {
            // Transición automática a la primera pantalla después de 2.5 segundos
            pantallaActual = 1;
            bienvenidaMostrada = false;
            ultimoCambioPantalla = ahora; // Iniciar contador de cambio automático
            lcd.clear();
            mostrarPantalla(pantallaActual);
            return;
        }
        else
        {
            // Seguir mostrando la pantalla de bienvenida
            pantallaInicio();
            return;
        }
    }

    // =====================
    // CAMBIO AUTOMÁTICO DE PANTALLA (cada 5 segundos)
    // =====================
    if (pantallaActual > 0 && ahora - ultimoCambioPantalla >= INTERVALO_CAMBIO_PANTALLA)
    {
        // Avanzar a la siguiente pantalla
        pantallaActual++;
        if (pantallaActual > totalPantallas)
        {
            pantallaActual = 1; // Volver a la primera pantalla después de la última
        }
        
        ultimoCambioPantalla = ahora;
        lcd.clear();
        mostrarPantalla(pantallaActual);
        return;
    }

    // =====================
    // REFRESCO DE DATOS (cada 1 segundo, sin cambiar de pantalla)
    // =====================
    if (pantallaActual > 0 && ahora - ultimoRefresco >= INTERVALO_REFRESCO)
    {
        ultimoRefresco = ahora;
        // Refrescar el contenido de la pantalla actual sin limpiarla
        mostrarPantalla(pantallaActual);
    }
}
