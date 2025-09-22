# 🌦️ Estación meteorológica con Arduino UNO → Módulos por etapas

## 🔹 **Módulo 0 – Teoria y Protocolos**
* UART, I2C, SPI → protocolos de informacion:[https://www.youtube.com/watch?v=G7aQB6x0LHc]

## 🔹 **Módulo 1 – Núcleo base**

👉 Este será el “corazón” del proyecto.
**Componentes**

* Arduino Uno
* RTC DS3231 (I2C): [https://www.youtube.com/watch?v=KlOLbpqgX6M]
* Módulo microSD (SPI): [https://www.youtube.com/watch?v=nNDqRpfEy40] [https://www.youtube.com/watch?v=nNDqRpfEy40] [https://www.youtube.com/watch?v=0rKL5UWUAzk]
* Pantalla LCD 20x4 con I2C: [https://www.youtube.com/watch?v=TED_deoKkfo]

**Funciones**

* Llevar la hora y fecha exacta.
* Guardar datos en la tarjeta SD.
* Mostrar datos en pantalla.

---

## 🔹 **Módulo 2 – Clima básico**

👉 Medición de condiciones atmosféricas.
**Componentes**

* BME280 (I2C) → temperatura, humedad, presión: [https://www.youtube.com/watch?v=LtZ_b2WVMrU]
* DHT22 → Sensor de Humedad: [https://www.youtube.com/watch?v=2tdsg_K-oQQ]

**Funciones**

* Registrar los datos básicos del clima.
* Guardarlos con timestamp en SD.
* Mostrarlos en LCD.

---

## 🔹 **Módulo 3 – Viento y lluvia**

👉 Medición de parámetros meteorológicos clásicos.
**Componentes**

* Anemómetro (reed switch → velocidad del viento).
* Veleta (potenciómetro o switch → dirección del viento).
* Pluviómetro basculante (reed switch → lluvia acumulada).

**Funciones**

* Detectar pulsos (anemómetro + pluviómetro).
* Medir dirección analógica (veleta).
* Guardar en SD junto con clima básico.

> 💡 Aquí vas a usar **interrupciones** en los pines 2 y 3 (para anemómetro y pluviómetro). La veleta puede ir a un pin analógico.

---

## 🔹 **Módulo 4 – Luz y radiación**

👉 Ampliación de parámetros solares.
**Componentes**

* BH1750 (I2C) → intensidad lumínica.
* ML8511 (analógico) → radiación ultravioleta.

**Funciones**

* Medir luminosidad y radiación UV.
* Guardar y mostrar en pantalla.

---

## 🔹 **Módulo 5 – Calidad del aire**

👉 Parámetros ambientales extra.
**Componentes**

* MQ-135 (gases básicos, VOCs).
* SDS011 o PMS5003 (PM2.5 y PM10, calidad del aire).
* CCS811 (CO₂ y VOCs más preciso, I2C).

**Funciones**

* Monitorear calidad del aire.
* Mostrar alertas en pantalla si pasan umbrales.

> ⚠️ Este módulo puede ser pesado para el UNO (por memoria y librerías). Acá conviene decidir si **lo mantenés en UNO** o si se hace con un **segundo microcontrolador (ej. ESP32)** y se comunica por serial/I2C.

---

## 🔹 **Módulo 6 – Suelo (opcional, agrícola)**

👉 Para agricultura o control ambiental avanzado.
**Componentes**

* DS18B20 (OneWire) → temperatura del suelo: [https://www.youtube.com/watch?v=WKpMxtr5-BU]
* Sensor de humedad capacitivo (analógico): [https://www.youtube.com/watch?v=z4ciPHk8jBU] [https://www.youtube.com/watch?v=IGP38bz-K48] [https://www.youtube.com/watch?v=PRiyYTIXf2g]

**Funciones**

* Guardar estado del suelo junto con clima general.

---

## 🔹 **Módulo 7 – Comunicación**

👉 Para que la estación sea accesible desde afuera.
**Opciones**

* ESP8266 (WiFi como módulo del UNO).
* SIM800L (enviar datos por SMS o GPRS).
* LoRa (comunicación a larga distancia).

**Funciones**

* Subir datos a un servidor (ThingSpeak, Blynk, Home Assistant, etc.).
* Consultar valores en tiempo real desde celular/PC.

> ⚠️ El UNO se queda corto si además de sensores querés comunicaciones WiFi + servidor web. En este punto puede convenir migrar **todo a ESP32** o dejar que el UNO mida y un **ESP8266/ESP32 solo envíe datos**.

---

# ⚙️ Resumen de organización de módulos

1. **Núcleo base** → Reloj, SD, pantalla.
2. **Clima básico** → Temperatura, humedad, presión.
3. **Viento y lluvia** → Anemómetro, veleta, pluviómetro.
4. **Luz y radiación** → BH1750, ML8511.
5. **Calidad del aire** → MQ-135, CCS811, SDS011.
6. **Suelo** → Temperatura y humedad del suelo.
7. **Comunicación** → WiFi, GSM, LoRa.
