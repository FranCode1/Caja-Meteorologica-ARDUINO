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
#include "leds_guia.h"

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  // Dispositivos que funcionan con i2c
  iniciarPantalla();
  iniciarRTC();
  iniciarBMP();
  iniciarBH1750();
  iniciarGY906();

  //Dispositivos que no funcionan con i2c
  iniciarLedsPantalla();
  iniciarDS18B20();
  iniciarCSMSV2();
  // iniciarML8511();
  iniciarMQ135();
  iniciarSD();
  // iniciarBateria();
  iniciarNavegacion();

  calibrarMQ135();

  // Mostrar pantalla de bienvenida
  menu.change_screen(&pantalla0);  // pantalla0 = bienvenida
  menu.update();          // dibujar en pantalla
  delay(3000);            // esperar 3 segundos

  // Cambiar a pantalla principal (BME280)
  menu.change_screen(&pantalla1);
  menu.update();
}
void loop()
{
  // Dispositivos que funcionan con i2c
  actualizarPantalla();
  fecha = rtc.now();
  leerRTC();
  leerBMP();
  leerBH1750();
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