#include "funciones.h"
#include "iostream"

int main() {
    //creo los objetos de tipo Entero, Real, Complejo
    Entero e1(9), e2(10);
    Real r1(3.54), r2(8.90);
    Complejo c1(2.0, 3.0), c2(1.0, 4.0);
    
    std::cout << "Operaciones con  numeros Enteros:" << std::endl;
    Numero* sumaEnteros = e1.suma(&e2);
    std::cout << "Suma: " << sumaEnteros->toString() << std::endl;
    
    Numero* restaEnteros = e1.resta(&e2);
    std::cout << "Resta: " << restaEnteros->toString() << std::endl;
    
    Numero* multEnteros = e1.mult(&e2);
    std::cout << "Multiplicacion: " << multEnteros->toString() << std::endl;
    
    try {
        Numero* divEnteros = e1.div(&e2);
        std::cout << "Division: " << divEnteros->toString() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\nOperaciones con numeros Reales:" << std::endl;
    Numero* sumaReales = r1.suma(&r2);
    std::cout << "Suma: " << sumaReales->toString() << std::endl;
    
    Numero* restaReales = r1.resta(&r2);
    std::cout << "Resta: " << restaReales->toString() << std::endl;
    
    Numero* multReales = r1.mult(&r2);
    std::cout << "Multiplicacion: " << multReales->toString() << std::endl;
    
    try {
        Numero* divReales = r1.div(&r2);
        std::cout << "Division: " << divReales->toString() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\nOperaciones con numeros Complejos:" << std::endl;
    Numero* sumaComplejos = c1.suma(&c2);
    std::cout << "Suma: " << sumaComplejos->toString() << std::endl;
    
    Numero* restaComplejos = c1.resta(&c2);
    std::cout << "Resta: " << restaComplejos->toString() << std::endl;
    
    Numero* multComplejos = c1.mult(&c2);
    std::cout << "Multiplicacion: " << multComplejos->toString() << std::endl;

    Numero* divComplejos = c1.div(&c2);
    std::cout << "Division: " << divComplejos->toString() << std::endl;

    return 0;
}