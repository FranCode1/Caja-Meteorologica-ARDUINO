#ifndef _LCD_H
#define _LCD_H

#include <Wire.h>              //sirve para la comunicacion i2c
#include <LiquidCrystal_I2C.h> //libreria de la pantalla
#include <LiquidMenu.h>        //libreria para menus

// OBJETOS DE LAS LIBRERIAS
LiquidCrystal_I2C lcd(0x3f, 20, 4); // sino funciona, usar la direccion 0x27 o 0x20

// codigo

// MENUS
// String menu1[] = {"<", "======","BME280", "======",">"};

LiquidLine linea1a(4, 0, "!Bienvenidos");
LiquidLine linea2a(8, 1, "a la");
LiquidLine linea3a(6, 2, "Estación");
LiquidLine linea4a(4, 3, "Meteorologica!");
LiquidScreen pantalla0(linea1a, linea2a, linea3a, linea4a);

LiquidLine linea1b(0, 0, "<=====BME280======>");
LiquidLine linea2b(0, 1, "Temperatura: ", temp_normal);
LiquidLine linea3b(0, 2, "Humedad: ", humedad);
LiquidLine linea4b(0, 3, "Presión Atm: ", presion_atm);
LiquidScreen pantalla1(linea1b, linea2b, linea3b, linea4b);

LiquidLine linea1c(0, 0, "<======Ds18b20=====>");
LiquidLine linea2c(0, 1, "Temp. Agua: ", temp_agua);
LiquidLine linea3c(0, 2, "<======CSMSV2======" >);
LiquidLine linea4c(0, 3, "Temp. Tierra: ", temp_tierra);
LiquidScreen pantalla2(linea1c, linea2c, linea3c, linea4c);

LiquidLine linea1d(0, 0, "<======BH1750======>");
LiquidLine linea2d(0, 1, "Lux: ", medicion_luz);
LiquidLine linea3d(0, 2, "<======ML8511======>");
LiquidLine linea4d(0, 3, "Rayos UV", uv_ray);
LiquidScreen pantalla3(linea1d, linea2d, linea3d, linea4d);

LiquidLine linea1e(0, 0, "<======MQ-135======>");
LiquidLine linea2e(0, 1, "Calidad Aire: ", tipo_aire);
LiquidLine linea3e(0, 2, "<======GY-906======>");
LiquidLine linea4e(0, 3, "Temp. Infrarroja: ", temp_infra);
LiquidScreen pantalla4(linea1e, linea2e, linea3e, linea4e);

LiquidLine linea1f(0, 0, "<======AJUSTES=====>");
LiquidLine linea2f(1, 1, "Día: ", fecha.day(), "/", fecha.month(), "/", fecha.year());
LiquidLine linea3f(1, 2, "Hora: ", fecha.hour(), ":", fecha.minute(), ":", fecha.second());
LiquidLine linea4f(0, 3, "BATERIA: ", bateria, "%");
LiquidScreen pantalla5(linea1f, linea2f, linea3f, linea4f);

LiquidLine linea1g(0, 0, "<===CAMBIAR FECHA==>");
LiquidLine linea2g(0, 1, "");
LiquidLine linea3g(0, 2, fecha.day(), "/", fecha.month(), "/", fecha.year());
LiquidLine linea4g(0, 3, "");
LiquidScreen pantalla6(linea1g, linea2g, linea3g, linea4g);

LiquidLine linea1h(0, 0, "");
LiquidLine linea2h(0, 1, "");
LiquidLine linea3h(0, 2, "<==FECHA CAMBIADA==>");
LiquidLine linea4h(0, 3, "");
LiquidScreen pantalla7(linea1h, linea2h, linea3h, linea4h);

LiquidLine linea1i(0, 0, "<==CAMBIAR HORARIO=>");
LiquidLine linea2i(0, 1, "");
LiquidLine linea3i(0, 2, fecha.hour(), ":", fecha.minute(), ":", fecha.second());
LiquidLine linea4i(0, 3, "");
LiquidScreen pantalla8(linea1i, linea2i, linea3i, linea4i);

LiquidLine linea1j(0, 0, "");
LiquidLine linea2j(0, 1, "");
LiquidLine linea3j(0, 2, "<=HORARIO CAMBIADO=>");
LiquidLine linea4j(0, 3, "");
LiquidScreen pantalla9(linea1j, linea2j, linea3j, linea4j);

LiquidLine linea1k(0, 0, "");
LiquidLine linea2k(0, 1, "");
LiquidLine linea3k(0, 2, "<==MEMORIA LLENA!==>");
LiquidLine linea4k(0, 3, "");
LiquidScreen pantalla10(linea1k, linea2k, linea3k, linea4k);

LiquidLine linea1l(0, 0, "");
LiquidLine linea2l(0, 1, "");
LiquidLine linea3l(0, 2, "<===Hasta Luego!===>");
LiquidLine linea4l(0, 3, "");
LiquidScreen pantalla11(linea1l, linea2l, linea3l, linea4l);

LiquidMenu menu(lcd, pantalla0, pantalla1, pantalla2, pantalla3, pantalla4, pantalla5, pantalla6, pantalla7, pantalla8, pantalla9, pantalla10, pantalla11);

void setup()
{
    Serial.begin(9600);

    // PANTALLA
    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.createChar(0, arrow); // crea un caracter personalizado

    menu.init();

    linea1.set_focusPosition(Position::CUSTOM);
    linea2.set_focusPosition(Position::CUSTOM);
    linea3.set_focusPosition(Position::CUSTOM);
    linea4.set_focusPosition(Position::CUSTOM);

    linea1.attach_function(1, fn_led1);
    linea2.attach_function(1, fn_led2);
    linea3.attach_function(1, fn_led3);
    linea4.attach_function(1, fn_todos);

    linea1_2.attach_function(1, fn_on);
    linea2_2.attach_function(1, fn_off);
    linea3_2.attach_function(1, fn_atras);

    menu.add_screen(pantalla1);

    pantalla1.set_displayLineCount(4);
    pantalla2.set_displayLineCount(4);

    menu.set_focusedLine(0);

    menu.update();
}

void loop()
{
    // PANTALLA
    lcd.display();

    // Funcion para detectar cuando se presiona el boton de OK
    selectOption(); // solo sirve con un encoder, no con botones

    aState = digitalRead(outputA);
    if (aState != aLastState)
    {
        if (digitalRead(outputB) != aState)
        {
            menu.switch_focus(false);
        }
        else
        {
            menu.switch_focus(true);
        }
        menu.update();
        aLastState = aState;
    }
}

// Funciones:::::
// PANTALLA y botonera

void selectOption()
{
    if (digitalRead(sw) == LOW)
    {
        menu.call_function(1);
        delay(500);
    }
}

// Se puede hacer una funcion que haga lo mismo que estas tres funciones
//  para evitar repetir el codigo
void fn_led1()
{
    menu.change_screen(2);
    menu.set_focusedLine(0);
    menu_position = 0;
}
void fn_led2()
{
    menu.change_screen(2);
    menu.set_focusedLine(0);
    menu_position = 1;
}
void fn_led3()
{
    menu.change_screen(2);
    menu.set_focusedLine(0);
    menu_position = 2;
}

void fn_on()
{
    switch (led_seleccionado)
    {
    case 1:
        digitalWrite(led1, HIGH);
        break;
    case 2:
        digitalWrite(led2, HIGH);
        break;
    case 3:
        digitalWrite(led3, HIGH);
        break;
    case 0:
        digitalWrite(led4, HIGH);
        digitalWrite(led5, HIGH);
        digitalWrite(led6, HIGH);
        break;
    }
}

void fn_off()
{
    switch (led_seleccionado)
    {
    case 1:
        digitalWrite(led1, LOW);
        break;
    case 2:
        digitalWrite(led2, LOW);
        break;
    case 3:
        digitalWrite(led3, LOW);
        break;
    case 0:
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW);
        digitalWrite(led6, LOW);
        break;
    }
}

void fn_atras()
{
    menu.change_screen(1);
    menu.set_focusedLine(0);
}

#endif