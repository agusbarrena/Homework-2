#include "funciones.h"
#include <iostream>

int main(){
    //creo una caja de ahorro y cuenta dorriente
    CajaDeAhorro caja(10000, "Agustina");
    CuentaCorriente cuenta(7000, "Agustina", caja);

    std::cout<<"Depositan $4000 en mi cuenta"<<std::endl;
    cuenta.depositar(4000);
    cuenta.mostrarInfo();

    std::cout<<"\nRetiro $11000, mas de lo que tengo en mi caja de ahorro"<<std::endl;
    caja.retirar(11000);
    caja.mostrarInfo();

    std::cout<<"\nRetiro $3000 desde mi cuenta corriente"<<std::endl;
    cuenta.retirar(3000);
    cuenta.mostrarInfo();

    std::cout<<"\nRetiro $10000, mas dinero del que tengo en mi cuenta corriente"<<std::endl;
    cuenta.retirar(10000);
    cuenta.mostrarInfo();
    caja.mostrarInfo();

    std::cout<<"\nDescuento de $20 por mostar la informacion de la caja mas de una vez:"<<std::endl;
    caja.mostrarInfo();
    return 0;
}