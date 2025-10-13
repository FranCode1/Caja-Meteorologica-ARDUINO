#ifndef _MQ135_H
#define _MQ135_H

// MQ-135
int VALOR;

const int MQ_PIN = A0;              // pin analogico elegido
const float RL = 1.0;               // 1k kohm module
const float CLEAN_AIR_RATIO = 9.80; // Taken from the datasheet graph
float RS;                           // kohm
float RO;                           // kohm
int ADC;                            // 0 to 1023

ADC = analogRead(MQ_PIN);
RS = ((float)RL * (1023 - ADC) / ADC); // esto es el divisor de voltaje

RO = RS / CLEAN_AIR_RATIO; // Do only once while measuring clear air

void setup()
{
    Serial.begin(9600);
}

void loop(){
    // MQ-135
    // no se si tengo que hacer una variable para cada tipo de gas

    VALOR = analogRead(A0); // aca iria el pin analogo al que esta conectado
    Serial.println(VALOR);
    if (VALOR > 400)
    {
        digitalWrite(LED_ALERTA_GAS, HIGH);
    }
    else
    {
        digitalWrite(LED_ALERTA_GAS, LOW);
    }

    float sensor_volt;
    float RS_air; // Get the value of RS via in a clear air
    float R0;     // Get the value of R0 via in H2
    // float sensorValue;
    float sensorValue = analogRead(A0); // esta variable esta mas arriba, no se porque la hacer denuevo aca
    sensor_volt = (float)sensorValue / 1024 * 5.0;
    RS_gas = (5.0 - sensor_volt) / sensor_volt;

    ration = RS_gas / 0.75;

    Serial.print("sensor_volt = ");
    Serial.println(sensor_volt);
    Serial.print("RS_ratio = ");
    Serial.println(RS_gas);
    Serial.print("Rs/R0 = ");
    Serial.println(ratio);

    Serial.print("\n\n");

    // Get a average data by testing 100 times
    for (int x = 0, x < 100; x++)
    {
        sensorValue = sensorValue + analogRead(A0);
    }
    sensorValue = sensorValue / 100.0;

    sensor_volt = sensorValue / 1024 * 5.0;
    RS_air = (5.0 - sensor_volt) / sensor_volt; // omit * RL
    R0 = RS_air / 9.8;                          // The ratio of RS/R0 is 9.8 in a clear air from Graph (Found using WebPlotDigitizer)

    Serial.print("sensor_volt = ");
    Serial.print(sensor_volt);
    Serial.println("V");
}


#endif