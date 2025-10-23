#include "multiplexor.h"
#include "lcd.h"
#include "navegacion.h"
#include "bmp280.h"
#include "ds18b20.h"
#include "csmsv2.h"
#include "bh1750.h"
// #include "ml8511.h"
#include "mq135.h"
#include "gy906.h"
#include "ds3231.h"
#include "microsd.h"

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  // Dispositivos que funcionan con i2c
  seleccionarCanal_i2c(CANAL_LCD);
  iniciarPantalla();

  seleccionarCanal_i2c(CANAL_RTC);
  iniciarRTC();

  seleccionarCanal_i2c(CANAL_BMP280);
  iniciarBMP();

  seleccionarCanal_i2c(CANAL_BH1750);
  iniciarBH1750();

  seleccionarCanal_i2c(CANAL_GY906);
  iniciarGY906();

  //Dispositivos que no funcionan con i2c
  iniciarDS18B20();
  iniciarCSMSV2();
  // iniciarML8511();
  iniciarMQ135();
  iniciarSD();
  // iniciarBateria();
  iniciarNavegacion();

  calibrarMQ135();

  // Mostrar pantalla de bienvenida
  menu.change_screen(0);  // pantalla0 = bienvenida
  menu.update();          // dibujar en pantalla
  delay(3000);            // esperar 3 segundos

  // Cambiar a pantalla principal (BME280)
  menu.change_screen(1);
  menu.update();
}
void loop()
{
  // Dispositivos que funcionan con i2c
  seleccionarCanal_i2c(CANAL_LCD);
  actualizarPantalla();

  seleccionarCanal_i2c(CANAL_RTC);
  fecha = rtc.now();
  leerRTC();

  seleccionarCanal_i2c(CANAL_BMP280);
  leerBMP();

  seleccionarCanal_i2c(CANAL_BH1750);
  leerBH1750();

  seleccionarCanal_i2c(CANAL_GY906);
  leerGY906();

  // Dispositivos que funcionan con i2c
  leerDS18B20();
  leerCSMSV2();
  // leerML8511();
  leerMQ135();
  leerNavegacion();
  // leerBateria();
  escribirSD("registro.txt");

  delay(1000);
}