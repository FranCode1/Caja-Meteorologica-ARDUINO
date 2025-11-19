#ifndef _CONFIG_H
#define _CONFIG_H

// =====================================================
// CONFIGURACIÓN GLOBAL DEL PROYECTO
// =====================================================

// Modo DEBUG (para activar/desactivar mensajes Serial)
#define DEBUG_MODE false

// =====================================================
// MACROS PARA DEPURACIÓN
// =====================================================
#if DEBUG_MODE
  #define DEBUG_PRINT(x)    Serial.print(x)
  #define DEBUG_PRINTLN(x)  Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

#endif
