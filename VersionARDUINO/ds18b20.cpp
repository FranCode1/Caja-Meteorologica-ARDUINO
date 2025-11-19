#include "ds18b20.h"

// ====== OBJETOS ======
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// ====== VARIABLES ======
float temp_ds18b20 = 0.0;
unsigned long ultimoPedidoDS18B20 = 0;

// ====== INICIO ======
void iniciarDS18B20()
{
    sensors.begin();
    sensors.setResolution(10);
    sensors.setWaitForConversion(false);
    sensors.requestTemperatures();

    //DEBUG_PRINTLN(F("✅ DS18B20 inicializado correctamente"));
}

// ====== LECTURA NO BLOQUEANTE ======
void leerDS18B20()
{
    unsigned long ahora = millis();

    if (ahora - ultimoPedidoDS18B20 >= INTERVALO_DS18B20)
    {

        float lectura = sensors.getTempCByIndex(0);

        if (lectura != DEVICE_DISCONNECTED_C && lectura > -55 && lectura < 125)
        {
            temp_ds18b20 = lectura;

            //DEBUG_PRINT(F("DS18B20 → Temp: "));
            //DEBUG_PRINTLN(temp_ds18b20);
        }
        else
        {
            //DEBUG_PRINTLN(F("⚠️ DS18B20 no conectado o lectura inválida"));
        }

        sensors.requestTemperatures();
        ultimoPedidoDS18B20 = ahora;
    }
}
