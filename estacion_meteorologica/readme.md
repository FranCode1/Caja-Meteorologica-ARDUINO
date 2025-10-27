# 🌱 Sistema de Monitoreo Ambiental con Arduino

Este proyecto utiliza un Arduino para monitorear variables ambientales como temperatura, humedad, luminosidad, calidad del aire y humedad del suelo. 
Los datos se registran en una tarjeta SD y pueden visualizarse por consola o pantalla LCD/OLED. 
El sistema está pensado para aplicaciones agrícolas, invernaderos o estaciones meteorológicas caseras.

## ✨ Características

- ⏰ RTC DS3231 — Reloj en tiempo real
- 🌡️ MLX90614 — Sensor de temperatura infrarrojo
- 💨 MQ-135 — Sensor de calidad del aire
- 💧 DHT22 / DHT11 — Sensor de temperatura y humedad
- 🌞 BH1750 — Sensor de luminosidad
- 🌱 Capacitive Soil Moisture v2 — Humedad del suelo
- 💾 Módulo SD — Registro de datos
- ⚡ Comunicación I2C y monitoreo por Serial

## 🗂️ Estructura del Proyecto

├── src/
│   ├── main.ino
│   ├── DS3231.h
│   ├── GY906.h
│   ├── MQ135.h
│   ├── BH1750.h
│   ├── CSMSV2.h
│   ├── DHT22.h
│   └── SDCard.h
├── README.md
└── /docs
    └── esquema_circuito.png

Cada sensor tiene su propio archivo `.h` modularizado, con funciones:
- `iniciarX()` → Inicializa el sensor
- `leerX()` → Lee los valores y los guarda en variables globales

## ⚙️ Requisitos

- Arduino UNO / Mega / Nano
- Librerías:
  - `Wire.h`
  - `RTClib.h`
  - `Adafruit_MLX90614.h`
  - `BH1750.h`
  - `DHT.h`
  - `SD.h`
- Fuente de 5V estable

## 🔌 Conexiones

| Componente          | Tipo  | Pin Arduino |
|---------------------|-------|--------------|
| DS3231 (RTC)        | I2C   | SDA / SCL    |
| GY-906 (Temp IR)    | I2C   | SDA / SCL    |
| BH1750 (Luz)        | I2C   | SDA / SCL    |
| MQ-135 (Gas)        | Analógico | A1       |
| Sensor Tierra       | Analógico | A0       |
| SD Card Module      | SPI   | CS, MOSI, MISO, SCK |

## Diagrama del circuito

![Diagrama del circuito](docs/esquema_circuito.png)

## 🧠 Funcionamiento del Código

1. Se inicializan todos los módulos (`iniciarX()`).
2. En el `loop()`, se leen los valores de cada sensor (`leerX()`).
3. Los datos se imprimen por Serial y se guardan en la tarjeta SD.
4. El reloj RTC agrega la marca de tiempo (`DD/MM/YYYY HH:MM:SS`).

## 📟 Ejemplo de salida Serial

Fecha: 17/10/2025 - Hora: 13:45:22
BME280 => Temp: 24.6 °C, Humedad: 52%, Presión: 1012 hPa
DS18B20 => Temp Agua: 23.1 °C
CSMSV2 => Humedad Tierra: 71 %
BH1750 => Luz: 580 lx
ML8511 => UV: 1.2 uv
MQ135 => Calidad Aire: 345 ppm CO2
GY906 => Temp IR: 25.9 °C
-----------------------------

## 🔧 Calibración

- **MQ135:** Ejecutar `calibrarMQ135()` una sola vez en aire limpio.
- **Sensor de suelo:** Medir valores de `AIR_VALUE` (seco) y `WATER_VALUE` (mojado) y ajustar en `CSMSV2.h`.

## 🚀 Posibles Mejoras

- Enviar datos a un servidor IoT (ThingSpeak, Blynk, etc.)
- Agregar pantalla OLED para mostrar lecturas y reemplazar la botonera
- Sistema de riego automático según humedad del suelo

## 👨‍💻 Autor
**Franco Lugo** — Diseñador y desarrollador web / IoT enthusiast  

## 📜 Licencia
Este proyecto está bajo la licencia MIT — ver el archivo [LICENSE](LICENSE) para más detalles.



link de fritzing necesario: https://www.mediafire.com/file/of6y8ojzf2p2hle/Windows-fritzing-1.0.4.zip/file
