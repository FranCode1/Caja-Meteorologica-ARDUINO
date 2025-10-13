#ifndef _ML8511_H
#define _ML8511_H

// ML8511
int UVOUT = A0;   // pin analogico del sensor
int REF_3V3 = A1; // segundo pin analogico del sensor

const int PIN_UV = A0;
const int LED_ALERTA = 3;

float voltaje; // Voltaje real leído del sensor
float uvIndex; // Índice UV calculado
String riesgo; // Nivel de riesgo textual

void setup()
{
    // ML8511
    pinMode(UVOUT, INPUT);
    pinMode(REF_3V3, INPUT);
    Serial.println("ML8511 example");

    pinMode(PIN_UV, INPUT);
    pinMode(LED_ALERTA, OUTPUT);
}

void loop(){
    // ML8511
    int uvLevel = averageAnalogRead(UVOUT);
    int refLevel = averageAnalogRead(REF_3V3);

    // Usa los 3.3v como referencia para conseguir un valor de output acertado para el sensor
    float outputVoltage = 3.3 / refLevel * uvLevel;

    // Convierte el voltage a intensidad del UV
    float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);

    Serial.print("output: ");
    Serial.print(refLevel);

    Serial.print("ML8511 output: ");
    Serial.print(uvLevel);

    Serial.print(" / ML8511 voltage: ");
    Serial.print(outputVoltage);

    Serial.print(" / UVIntensity (mW/cm^2): ");
    Serial.print(uvIntensity);
    lcd.clear();
    lcd.print("UV Ray Intensity");
    lcd.setCursor(0, 1);
    lcd.print(uvIntensity);
    lcd.print(" mW/cm^2");

    Serial.println();

    // codigo con el puenteo para tener info mas precisa
    int uvLevel = averageAnalogRead(UVOUT);
    float voltaje = lectura * (3.3 / 669);
    int logOnda = map(lectura, 0, 669, 0, 1023);
    int indice = map(longOnda, 0, 1023, 0, 10); // esto es para medicion precisa
    // Serial.println(lectura); //lectura seria UVOUT
    // Serial.println("Voltaje: " + String(voltaje) + "V");
    // Serial.println("Rango: " + String(longOnda));
    Serial.println("Indice UV: " + String(indice) + "Rango: " + String(longOnda));

    int lectura = analogRead(PIN_UV);

    // Si usás 3.3V como referencia:
    voltaje = lectura * (3.3 / 1023.0);

    uvIndex = calcularIndiceUV(voltaje);
    riesgo = calcularRiesgo(uvIndex);

    // Control de LED según umbral de peligro
    if (uvIndex >= 6)
        digitalWrite(LED_ALERTA, HIGH);
    else
        digitalWrite(LED_ALERTA, LOW);

    // Mostrar resultados
    Serial.print("Lectura: ");
    Serial.print(lectura);
    Serial.print("\tVoltaje: ");
    Serial.print(voltaje, 2);
    Serial.print(" V\tIndice UV: ");
    Serial.print(uvIndex, 1);
    Serial.print("\tRiesgo: ");
    Serial.println(riesgo);
}

// ML8511
int averageAnalogRead(int pinToRead)
{
    byte numbreOfReadiings = 8;
    unsigned int runningValue = 0;

    for (int x = 0; x < numberOfReadings; x++)
    {
        runningValue += analogRead(pinToRead);
    }

    runningValue /= numberOfReadings;

    return (runningValue);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// ------------------------------------------------
// Función para calcular el índice UV a partir del voltaje
// Fórmula basada en documentación del ML8511
// ------------------------------------------------
float calcularIndiceUV(float voltaje)
{
    // El ML8511 suele entregar:
    // 1.0 V ≈ 0 UV
    // 2.9 V ≈ 15 UV
    // Ajustá los valores según tu referencia real (3.3V o 5V)
    float indice = (voltaje - 1.0) * (15.0 / (2.9 - 1.0));
    if (indice < 0)
        indice = 0;
    return indice;
}

// ------------------------------------------------
// Clasifica el riesgo UV según el índice
// ------------------------------------------------
String calcularRiesgo(float indice)
{
    if (indice <= 0)
        return "Ninguno";
    else if (indice <= 2)
        return "Bajo";
    else if (indice <= 5)
        return "Moderado";
    else if (indice <= 7)
        return "Alto";
    else if (indice <= 10)
        return "Muy Alto";
    else
        return "Extremadamente Alto";
}

#endif