#include "funciones.h"
#include <iomanip>
#include <iostream>

Reloj::Reloj(){
    this->horas = 0;     
    this->minutos = 0;   
    this->segundos = 0;  
    this->momento = MOMENTO::AM;
}//constructor por default

// 4 tipos de relojes diferentes que el usuario puede solicitar
Reloj::Reloj(int horas) {
    this->horas = horas;
    this->minutos = 0;
    this->segundos = 0;
    this->momento = MOMENTO::AM;
}

Reloj::Reloj(int horas, int minutos) {
    this->horas = horas;
    this->minutos = minutos;
    this->segundos = 0;
    this->momento = MOMENTO::AM;
}

Reloj::Reloj(int horas, int minutos, int segundos) {
    this->horas = horas;
    this->minutos = minutos;
    this->segundos = segundos;
    this->momento = MOMENTO::AM;
}

Reloj::Reloj(int horas, int minutos, int segundos, MOMENTO momento) {
    this->horas = horas;
    this->minutos = minutos;
    this->segundos = segundos;
    this->momento = momento;
}

//setters
void Reloj::setHora(int hh){
    if(hh>=1 && hh<= 12){
        this->horas = hh;
    }else{
        std::cout<<"ERROR: La hora debe ser asignada de 1 a 12."<<std::endl;
    }
}

void Reloj::setMinutos(int mm){
    if(mm>=0 && mm<=59){
        this->minutos = mm;
    }else{
        std::cout<<"ERROR: Los minutos deben ser asignados entre 0 y 59."<<std::endl;
    }
}

void Reloj::setSegundos(int ss){
    if(ss>= 0 && ss<=59){
        this->segundos = ss;
    }else{
        std::cout<<"ERROR: Los segundos ser asignados entre 0 y 59."<<std::endl;
    }
}

void Reloj::setMomento(MOMENTO m){
    this->momento = m;
}

//getters
int Reloj::getHora() const{
    return this->horas;
}

int Reloj::getMinutos() const{
    return this->minutos;
}

int Reloj::getSegundos() const{
    return this->segundos;
}

MOMENTO Reloj::getMomento() const{
    return this->momento;
}

void Reloj::getFormato12() const{

    std::cout<<std::setw(2)<<std::setfill('0')<< this->horas << "hs:"
             <<std::setw(2)<<std::setfill('0')<< this->minutos << "ms:"
             <<std::setw(2)<<std::setfill('0')<< this->segundos << "ss "
             <<(momento == MOMENTO::AM ? "a.m": "p.m")<<std::endl;
}

void Reloj::getFormato24() const{
    int hora24;
    if(this->momento == MOMENTO::PM && this->horas != 12){// la idea es que se permita 12 pm para que en formato24 aparezca como 12:00:00 
       hora24 = this->horas + 12;
    }else{
        hora24 = this->horas;
    }

    if(this->momento==MOMENTO::AM && this->horas== 12){//ahora las 12 am serian las 00:00 en formato24
       hora24 = 0;
    }

    std::cout<<std::setw(2)<<std::setfill('0')<< hora24 << "hs:"
             <<std::setw(2)<<std::setfill('0')<< this->minutos << "ms:"
             <<std::setw(2)<<std::setfill('0')<< this->segundos << "ss"<<std::endl;
}

void menu_1(Reloj& reloj){
    int opcion;
    int horas, minutos, segundos;
    std::string momento;

    std::cout << "--- Elija una opción de Reloj para ingresar la hora ---" << std::endl;
    std::cout << "1. Reloj por default." << std::endl;
    std::cout << "2. Reloj solo con hora." << std::endl;
    std::cout << "3. Reloj solo con hora y minutos." << std::endl;
    std::cout << "4. Reloj con hora, minutos y segundos." << std::endl;
    std::cout << "5. Reloj con hora, minutos, segundos con AM/PM." << std::endl;
    
    
    std::cout << "Ingrese la opción: ";
    std::cin >> opcion;
    
    switch (opcion) {
        case 1: 
            reloj = Reloj();
            std::cout << "Hora: " << std::setw(2) << std::setfill('0') << reloj.getHora() << " hs" << std::endl; 
            break;
        
        case 2:
            std::cout << "Ingrese la hora: ";
            std::cin >> horas;
            reloj.setHora(horas);
            break;
        
        case 3:
            std::cout << "Ingrese la hora: ";
            std::cin >> horas;
            reloj.setHora(horas);
            std::cout << "Ingrese los minutos: ";
            std::cin >> minutos;
            reloj.setMinutos(minutos);
            break;
        
        case 4:
            std::cout << "Ingrese la hora: ";
            std::cin >> horas;
            reloj.setHora(horas);
            std::cout << "Ingrese los minutos: ";
            std::cin >> minutos;
            reloj.setMinutos(minutos);
            std::cout << "Ingrese los segundos: ";
            std::cin >> segundos;
            reloj.setSegundos(segundos);
            break;
        
        case 5:
            std::cout << "Ingrese la hora: ";
            std::cin >> horas;
            reloj.setHora(horas);
            std::cout << "Ingrese los minutos: ";
            std::cin >> minutos;
            reloj.setMinutos(minutos);
            std::cout << "Ingrese los segundos: ";
            std::cin >> segundos;
            reloj.setSegundos(segundos);

            std::cout << "Ingrese AM o PM: ";
            std::cin >> momento;
            if (momento == "am" || momento == "AM") {
                reloj.setMomento(MOMENTO::AM);
            } else if (momento == "pm" || momento == "PM") {
                reloj.setMomento(MOMENTO::PM);
            } else {
                std::cout << "Entrada inválida, se usará la default (AM)." << std::endl;
                reloj.setMomento(MOMENTO::AM);
            }
            break;
        
        default:
            std::cout << "Opción no válida, intente de nuevo." << std::endl;
            break;
    }
}

void menu_2(Reloj& reloj){
    int opcion;
    bool salir = false;

    while (!salir) {
        std::cout << "\n--- Menú de opciones ---" << std::endl;
        std::cout << "1. Modificar la hora" << std::endl;
        std::cout << "2. Modificar los minutos" << std::endl;
        std::cout << "3. Modificar los segundos" << std::endl;
        std::cout << "4. Modificar AM/PM" << std::endl;
        std::cout << "5. Ver solo la hora" << std::endl;
        std::cout << "6. Ver solo los minutos" << std::endl;
        std::cout << "7. Ver solo los segundos" << std::endl;
        std::cout << "8. Ver solo AM/PM" << std::endl;
        std::cout << "9. Mostrar reloj en formato 12 horas" << std::endl;
        std::cout << "10. Mostrar reloj en formato 24 horas" << std::endl;
        std::cout << "11. Salir" << std::endl;

        std::cout << "Ingrese la opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                int horas;
                std::cout << "Nueva hora: ";
                std::cin >> horas;
                reloj.setHora(horas);
                break;
            }
            case 2: {
                int minutos;
                std::cout << "Nuevos minutos: ";
                std::cin >> minutos;
                reloj.setMinutos(minutos);
                break;
            }
            case 3: {
                int segundos;
                std::cout << "Nuevos segundos: ";
                std::cin >> segundos;
                reloj.setSegundos(segundos);
                break;
            }
            case 4: {
                std::string momento;
                std::cout << "Ingrese AM o PM: ";
                std::cin >> momento;
                reloj.setMomento((momento == "am" || momento == "AM") ? MOMENTO::AM : MOMENTO::PM);
                break;
            }
            case 5: 
                std::cout << "Hora: " << std::setw(2) << std::setfill('0') << reloj.getHora() << " hs" << std::endl;
                break;
            case 6: 
                std::cout << "Minutos: " << std::setw(2) << std::setfill('0') << reloj.getMinutos() << " min" << std::endl;
                break;
            case 7: 
                std::cout << "Segundos: " << std::setw(2) << std::setfill('0') << reloj.getSegundos() << " seg" << std::endl;
                break;
            case 8: 
                std::cout << "Momento: " << (reloj.getMomento() == MOMENTO::AM ? "AM" : "PM") << std::endl;
                break;
            case 9: 
                reloj.getFormato12(); 
                break;
            case 10: 
                reloj.getFormato24(); 
                break;
            case 11: 
                salir = true; 
                break;
            default: 
                std::cout << "Opción no válida." << std::endl;
                break;
        }
    }
}