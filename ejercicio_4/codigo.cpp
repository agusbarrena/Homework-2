#include <iostream>
#include "funciones.h"

Banco::Banco(double total,std::string titular, std::string tipo) : balance(total), titularCuenta(titular), tipoCuenta(tipo) {}

void Banco::depositar(double cant){
    if(cant > 0){
        balance += cant;
    }
    else{
        std::cout<<"El monto para depositar debe ser mayor a 0.\n"<<std::endl;
    }
}

CajaDeAhorro::CajaDeAhorro(double total, std::string titular) : Banco(total, titular, "Caja De Ahorro") {}

void CajaDeAhorro::retirar(double cant){
    if(cant > balance){
        std::cout<<"No hay fondos suficientes para retirar ese monto de dinero."<<std::endl;
    }else{
        balance -= cant;
    } 
}

void CajaDeAhorro::mostrarInfo(){
    contador++;
    
    if(contador > 2){
        std::cout<<"Se ha mostrado la informacion de la cuenta mas de una vez. Descuento de $20."<<std::endl;
        this->balance -= 20;
        std::cout<<"Titular: "<< titularCuenta <<", Tipo de cuenta: "<< tipoCuenta <<", Total: $"<< balance <<std::endl;
    }else{
        std::cout<<"Titular: "<< titularCuenta <<", Tipo de cuenta: "<< tipoCuenta <<", Total: $"<< balance <<std::endl;
    }
}

CuentaCorriente::CuentaCorriente(double total, std::string titular, CajaDeAhorro& caja) : Banco(total, titular, "Cuenta Corriente"), caja(caja) {}

void CuentaCorriente::retirar(double cant){
    if(cant <= balance){
        balance -= cant;
    }else if(cant <= (balance + caja.balance)){
        double faltan = cant - balance;
        balance = 0;
        caja.balance -= faltan;
    }else{
        std::cout<<"No tiene fondos ni en la Cuenta Corriente ni en su Caja De Ahorros para retirar este monto.\n"<<std::endl;
    }
}

void CuentaCorriente::mostrarInfo(){
    std::cout<<"Titular: "<< titularCuenta <<", Tipo de cuenta: "<< tipoCuenta <<", Total: $"<< balance <<std::endl;
}