#include "funciones.h"
#include <iostream>

int main() {
    int continuar = 1;
    Reloj reloj;

    while (continuar == 1) {
        menu_1(reloj);
        menu_2(reloj);

        std::cout << "¿Desea realizar otro ingreso de hora? [SI = 1, NO = 0]: ";
        std::cin >> continuar;
    }

    std::cout << "Saliendo del programa." << std::endl;
    return 0;
}
