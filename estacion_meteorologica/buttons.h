#ifndef _BUTTONS_H
#define _BUTTONS_H

void navegarMenu() {
    if (BTN_DERECHA) {
        menu.next_screen();
    } else if (BTN_IZQUIERDA) {
        menu.previous_screen();
    } else if (BTN_ARRIBA) {
        menu.switch_focus(true);
    } else if (BTN_ABAJO) {
        menu.switch_focus(false);
    } else if (BTN_OK) {
        menu.call_function(1);
    } else if (BTN_BACK) {
        fn_atras();
    }
}

#endif
