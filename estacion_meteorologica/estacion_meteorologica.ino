#include "lcd.h"
#include "buttons.h"
#include "bme280.h"
#include "ds18b20.h"
#include "csmsv2.h"
#include "bh1750.h"
#include "ml8511.h"
#include "mq135.h"
#include "gy906.h"
#include "ds3231.h"
#include "microsd.h"

void setup(){
  Serial.begin(9600);

  //funciones que inicien sensores
  iniciarPantalla();
  iniciarBME();
  iniciarDS18B20();
  iniciarCSMSV2();
  iniciarBH1750();
  iniciarML8511();
  iniciarMQ135();
  iniciarGY906();
  iniciarRTC();
  iniciarSD();


  calibrarMQ135();


  // Mostrar pantalla de bienvenida
  menu.change_screen(0);  // pantalla0 = bienvenida
  menu.update();          // dibujar en pantalla
  delay(3000);            // esperar 3 segundos

  // Cambiar a pantalla principal (BME280)
  menu.change_screen(1);
  menu.update();
}
void loop(){
  //funciones que actualizen la info de los sensores
  fecha = rtc.now();

  actualizarPantalla();
  leerBME();
  leerDS18B20();
  leerCSMSV2();
  leerBH1750();
  leerML8511();
  leerMQ135();
  leerGY906();
  leerRTC();
  
  // 5️⃣ Crear el texto de registro
  String registro = tiempo + ", Temp: " + String(temperatura, 1) + "°C, Hum: " + String(humedad, 1) + "%, Luz: " + String(luz) + " lx, Tierra: " + String(tierra) + "%, CO2: " + String(co2) + " ppm";
  
  escribir("registro.txt", registro)

  delay(1000);
}