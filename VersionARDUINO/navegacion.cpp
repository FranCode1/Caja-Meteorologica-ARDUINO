#include "navegacion.h"
#include "lcd.h" // mostrarPantalla()

// ===================== ANTIRREBOTE =====================
constexpr unsigned long debounceDelay = 100;
static unsigned long ultimoMovimiento = 0;

// ===================== ESTADOS DE BOTONES =====================
static bool prevIzq = LOW;  // Con pull-down, el estado inicial es LOW
static bool prevDer = LOW;

// =============================================================
// INICIALIZACIÓN
// =============================================================
void iniciarNavegacion()
{
    // Los botones tienen pull-down resistors externos, usar INPUT (no INPUT_PULLUP)
    pinMode(BTN_IZQ, INPUT);
    pinMode(BTN_DER, INPUT);

    //DEBUG_PRINTLN(F("✅ Navegación por botones iniciada"));
}

// =============================================================
// LECTURA DE BOTONES
// =============================================================
void leerNavegacion()
{
    // No permitir navegación durante la pantalla de bienvenida
    if (pantallaActual == 0 && !bienvenidaMostrada)
        return;

    unsigned long ahora = millis();
    if (ahora - ultimoMovimiento < debounceDelay)
        return;

    bool izq = digitalRead(BTN_IZQ);
    bool der = digitalRead(BTN_DER);

    // -------- BOTÓN IZQUIERDA --------
    // Con pull-down: LOW = no presionado, HIGH = presionado
    if (izq == HIGH && prevIzq == LOW)
    {
        uint8_t nuevaPantalla = (pantallaActual == 1)
                                   ? totalPantallas
                                   : pantallaActual - 1;

        if (nuevaPantalla != pantallaActual && nuevaPantalla > 0)
        {
            mostrarPantalla(nuevaPantalla);
            bloqueoRefresco = millis() + 500; // pausar refresco por 500ms
        }

        ultimoMovimiento = ahora;

        //DEBUG_PRINT(F("Botón IZQ → Pantalla: "));
        //DEBUG_PRINTLN(pantallaActual);
    }

    // -------- BOTÓN DERECHA --------
    // Con pull-down: LOW = no presionado, HIGH = presionado
    if (der == HIGH && prevDer == LOW)
    {
        uint8_t nuevaPantalla = pantallaActual + 1;
        if (nuevaPantalla > totalPantallas)
            nuevaPantalla = 1;

        if (nuevaPantalla != pantallaActual && nuevaPantalla > 0)
        {
            mostrarPantalla(nuevaPantalla);
            bloqueoRefresco = millis() + 500; // pausar refresco por 500ms
        }

        ultimoMovimiento = ahora;

        //DEBUG_PRINT(F("Botón DER → Pantalla: "));
        //DEBUG_PRINTLN(pantallaActual);
    }

    prevIzq = izq;
    prevDer = der;
}
