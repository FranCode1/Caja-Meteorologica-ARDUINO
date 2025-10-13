#ifndef _MICROSD_H
#define _MICROSD_H

#include <SPI.h>
#include <SD.h>

#define SSpin 10

File archivo

void setup(){
    Serial.begin(9600);
    Serial.println("Inicializando tarjeta ...");
    if (!SD.begin(SSpin)){
        Serial.println("Fallo en inicializacion!");
        return;
    }

    Serial.println("Inicializacion correcta");
    archivo = SD.open("registro.txt", FILE_WRITE);

    // if(archivo){
    //     archivo.println("Probando 1, 2, 3");
    //     Serial.println("Escribiendo  en archivo prueba.txt ...");
    //     archivo.close();
    //     Serial.println("escritura correcta");
    // } else {
    //     Serial.println("error en apertura de prueba.txt");
    // }

    // archivo = SD.open("registro.txt");
    if (archivo){
        archivo.println("Probando 1, 2, 3"); //escribe en el archivo
        Serial.println("Contenido de prueba.txt: "); //escribe en la consola
        while (archivo.available()){
            Serial.write(archivo.read()); //de un caracter por vez hasta finalizar
        }
        archivo.close();
        Serial.println("escritura correcta");
    } else {
        Serial.println("error en apertura de registro.txt");
    }
}

void loop(){
    //nada xd
}

#endif