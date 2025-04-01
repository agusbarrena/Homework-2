#include <iostream>
#include "funciones.h"
#include <memory>
Entero::Entero(int valor) : valor(valor) {}

std::unique_ptr<Numero> Entero::suma(Numero* num){
    Entero* e = dynamic_cast<Entero*>(num);

    if(e){
        return std::make_unique<Entero>(this->valor + e->valor);
    }
    std::cout<<"Fallo el cast de num en la suma de enteros.\n"<<std::endl;
    return nullptr;
    
}

std::unique_ptr<Numero> Entero::resta(Numero* num){
    Entero* e = dynamic_cast<Entero*>(num);

    if(e){
        return std::make_unique<Entero>(this->valor - e->valor);
    }
    std::cout<<"Fallo el cast de num en la resta de enteros.\n"<<std::endl;
    return nullptr;

}

std::unique_ptr<Numero> Entero::mult(Numero* num){
    Entero* e = dynamic_cast<Entero*>(num);

    if(e){
        return std::make_unique<Entero>(this->valor * e->valor);
    }else
    std::cout<<"Fallo el cast de num en la multiplicacion de enteros.\n"<<std::endl;
    return nullptr;
}

std::unique_ptr<Numero> Entero::div(Numero* num){
    Entero* e = dynamic_cast<Entero*>(num);

    if(e){
        if(e->valor != 0){
            return std::make_unique<Entero>(this->valor/e->valor);
        }else{
            throw std::runtime_error("Division sobre 0 no se puede.\n");
        }
    }
    std::cout<<"Fallo el cast de num en la division de enteros.\n"<<std::endl;
    return nullptr;
}

std::string Entero::toString(){
    return std::to_string(this->valor);
}

Real::Real(double valor) : valor(valor) {}

std::unique_ptr<Numero> Real::suma(Numero* num){
    Real* r = dynamic_cast<Real*>(num);

    if(r){
        return std::make_unique<Real>(this->valor + r->valor);
    }
    std::cout<<"Fallo el cast de num en la suma de reales.\n"<<std::endl;
    return nullptr;
}

std::unique_ptr<Numero> Real::resta(Numero* num){
    Real* r = dynamic_cast<Real*>(num);

    if(r){
        return std::make_unique<Real>(this->valor - r->valor);
    }
    std::cout<<"Fallo el cast de num en la resta de reales.\n"<<std::endl;
    return nullptr;
}

std::unique_ptr<Numero> Real::mult(Numero* num){
    Real* r = dynamic_cast<Real*>(num);

    if(r){
        return std::make_unique<Real>(this->valor * r->valor);
    }
    std::cout<<"Fallo el cast de num en la multiplicacion de reales.\n"<<std::endl;
    return nullptr;
}

std::unique_ptr<Numero> Real::div(Numero* num){
    Real* r = dynamic_cast<Real*>(num);

    if(r){
        if(r->valor == 0.0){
            throw std::runtime_error("Error: Division sobre 0 en Reales\n");
        }
        return std::make_unique<Real>(this->valor/r->valor);
    }
    std::cout<<"Fallo el cast de num en la division de reales.\n"<<std::endl;
    return nullptr;
}

std::string Real::toString(){
    return std::to_string(this->valor);
}

Complejo::Complejo(double parteReal, double parteImaginaria) : parteReal(parteReal), parteImaginaria(parteImaginaria) {}

std::unique_ptr<Numero> Complejo::suma(Numero* num){
    Complejo* c = dynamic_cast<Complejo*>(num);
    
    if(c){
        return std::make_unique<Complejo>(this->parteReal + c->parteReal, this->parteImaginaria + c->parteImaginaria);
    }
    std::cout<<"Fallo el cast de num en la suma de complejos.\n"<<std::endl;
    return nullptr;
}

std::unique_ptr<Numero> Complejo::resta(Numero* num){
    Complejo* c = dynamic_cast<Complejo*>(num);

    if(c){
        return std::make_unique<Complejo>(this->parteReal - c->parteReal, this->parteImaginaria - c->parteImaginaria);
    }
    std::cout<<"Fallo el cast de num en la resta de complejos.\n"<<std::endl;
    return nullptr;
}

std::unique_ptr<Numero> Complejo::mult(Numero* num){
    Complejo* c = dynamic_cast<Complejo*>(num);

    if(c){
        return std::make_unique<Complejo>(this->parteReal * c->parteReal - this->parteImaginaria * c->parteImaginaria, this->parteReal * c->parteImaginaria + this->parteImaginaria* c->parteReal );
    }
    std::cout<<"Fallo el cast de num en la multiplicacion de complejos.\n"<<std::endl;
    return nullptr;
}

std::unique_ptr<Numero> Complejo::div(Numero* num){
    Complejo* c = dynamic_cast<Complejo*>(num);
    if(c){
        double a = this->parteReal;
        double b = this->parteImaginaria;
        double d = c->parteReal;
        double e = c->parteImaginaria;
    
        double deno = d*d + e*e;
    
        if(deno == 0.0){
            throw std::runtime_error("Error: Division sobre 0 no es posible.");
        }
    
        double real = (a*d + e*b)/deno;
        double img = (b*d - e*a)/deno;
    
        return std::make_unique<Complejo>(real, img);
    }
    std::cout<<"Fallo el cast de num en la division de complejos.\n"<<std::endl;
    return nullptr;

} // (a+ bi)/(d+ ei) = ((a+ bi)*(d - ei))/(d^2 + e^2) uso esta definicion

std::string Complejo::toString(){
    std::string resultado = std::to_string(this->parteReal);
    
    if (this->parteImaginaria >= 0) { //esto para que no me quede en la terminal parte real +- parte img cuando es negativa la parte binaria
        resultado += " + " + std::to_string(this->parteImaginaria) + "i";
    } else {
        resultado += " - " + std::to_string(-this->parteImaginaria) + "i";  
    }
    return resultado;
}


