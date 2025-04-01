#include "funciones.h"
#include <iostream>
#include <algorithm>
#include <vector>
Estudiante::Estudiante(const std::string& nombre, int legajo) : legajo(legajo), nombre(nombre) {}

std::string Estudiante::getNombre() const{
    return nombre;
}

int Estudiante::getLegajo() const{
    return legajo;
}

float Estudiante::getPromedioGeneral() const{
    if (cursos.empty()) return 0.0;
    
    float suma_notas = 0;
    for(const auto& curso: cursos){
        suma_notas += curso.second;
    }

    float promedio = suma_notas/cursos.size();
    return promedio;
}

void Estudiante::agregarCurso(const std::string curso, float nota){
    cursos.push_back({curso, nota});
}

void Estudiante::imprimirEstudiante() const{
    std::cout << "Nombre: " << nombre << "\nLegajo: " << legajo
              << "\nPromedio: " << getPromedioGeneral() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Estudiante& estudiante){
    os << estudiante.nombre << " (Legajo: " << estudiante.legajo << ") - Promedio: " << estudiante.getPromedioGeneral();
    return os;
}

//Implento Curso

Curso::Curso(const std::string nombre): nombre(nombre){}

bool Curso::inscribirEstudiante(Estudiante* estudiante){
    if (cursoCompleto() || estudianteInscripto(estudiante->getLegajo())){
        return false;
    }
    estudiantes.push_back(estudiante);
    return true;
}

bool Curso::desinscribirEstudiante(int legajo){
    for(auto temp = estudiantes.begin(); temp != estudiantes.end(); ++temp){
        if((*temp)->getLegajo() == legajo){
            estudiantes.erase(temp);
            return true;
        }
    }
    return false;
}

bool Curso::estudianteInscripto(int legajo){
    for(auto& estudiante : estudiantes){
        if(estudiante->getLegajo()== legajo){
            return true;
        }
    }
    return false;
}

bool Curso::cursoCompleto() const{
    return estudiantes.size() >= MAX_ESTUDIANTES;
}

bool Curso::compararEstudiantesPorNombre(const Estudiante* a, const Estudiante* b) {
    return a->getNombre() < b->getNombre();
}

void Curso::estudiantesOrdenados() const{
    std::vector<Estudiante*> copia = estudiantes;
    std::sort(copia.begin(), copia.end(), compararEstudiantesPorNombre);

    for (const auto& estudiante : copia) {
        std::cout << *estudiante << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Curso& curso) {
    os << "Curso: " << curso.nombre << "\nEstudiantes:\n";
    curso.estudiantesOrdenados();
    return os;
}

Curso::Curso(const Curso& rht) : nombre(rht.nombre){
    for(const auto& estudiante : rht.estudiantes){
        estudiantes.push_back(new Estudiante (*estudiante));
    }
}

Curso::~Curso(){ //si yo elimino el curso, al hacer una deep copy debo eliminar los estudiantes 
    for(auto* estudiante : estudiantes){
        delete estudiante;
    }
}
//Respuesta (c): El tipo de relación entre los objetos curso y estudiante es de agregación.Esto se debe a que vemos representada una relacion del tipo has-a entre un objeto que actúa como un todo (whole) y sus partes (parts). Como podemos ver en este caso, Curso almacena punteros a Estudiante, y estos pueden existir en múltiples cursos o fuera de ellos. Por lo tanto, exitse una acción entre ambos objetos pero tienen ciclos de vida independientes el uno del otro.

void menu_interactivo(){
    std::vector<Estudiante*> estudiantes;
    int opcion;
    int legajo;
    float nota;
    std::string nombre;
    std::string nombreCurso;

    do{
        std::cout << "\n---Menu---\n";
        std::cout << "1. Agregar estudiante\n";
        std::cout << "2. Inscribir estudiante en un curso\n";
        std::cout << "3. Agregar nota del estudiante\n";
        std::cout << "4. Desinscribir estudiante de un curso\n";
        std::cout << "5. Buscar estudiante inscripto por su legajo\n";
        std::cout << "6. Verificar si el curso esta completo\n";
        std::cout << "7. Imprimir lista de estudiantes ordenados alfabeticamente\n";
        std::cout << "8. Copiar un curso\n";
        std::cout << "9. Salir\n";
        std::cout << "Seleccione una opcion: ";

        std::cin>> opcion;

        switch(opcion){
            case 1: {  
                std::cout << "Ingrese el nombre del estudiante: ";
                std::cin.ignore();
                std::getline(std::cin, nombre);
                std::cout << "Ingrese el legajo: ";
                std::cin >> legajo;
                estudiantes.push_back(new Estudiante(nombre, legajo));
                std::cout << "El estudiante fue agregado.\n";
                break;
            }

            case 2: {  
                std::cout << "Ingrese el legajo del estudiante a inscribir: ";
                std::cin >> legajo;
                bool encontrado = false;

                for (Estudiante* alumno : estudiantes) {
                    if (alumno->getLegajo() == legajo) {
                        if (curso.inscribirEstudiante(alumno)) {
                            std::cout << "El estudiante fue inscrito con éxito.\n";
                        } else {
                            std::cout << "No se pudo inscribir (curso lleno o ya inscrito).\n";
                        }
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) std::cout << "El estudiante no fue encontrado.\n";
                break;
            }

            case 3: {
                std::cout << "Ingrese legajo del estudiante: ";
                std::cin >> legajo;

                for (auto& est : estudiantes) {
                    if (est->getLegajo() == legajo) {
                        std::cout << "Ingrese nombre del curso de la respectiva nota: ";
                        std::cin.ignore();
                        std::getline(std::cin, nombreCurso);
                        std::cout << "Ingrese la nota: ";
                        std::cin >> nota;
                        est->agregarCurso(nombreCurso, nota);
                        std::cout << "Nota agregada correctamente.\n";
                        break;
                    }
                }
                break;
            }

            case 4: {  
                std::cout << "Ingrese el legajo del estudiante a desinscribir: ";
                std::cin >> legajo;

                if (curso.desinscribirEstudiante(legajo)) {
                    std::cout << "El estudiante fue desinscrito con éxito.\n";
                } else {
                    std::cout << "No se encontró al estudiante en el curso.\n";
                }
                break;
            }

            case 5: {  
                std::cout << "Ingrese el legajo del estudiante: ";
                std::cin >> legajo;

                if (curso.estudianteInscripto(legajo)) {
                    std::cout << "El estudiante con legajo " << legajo << " está inscrito en el curso.\n";
                } else {
                    std::cout << "El estudiante no está inscrito en el curso.\n";
                }
                break;
            }

            case 6: {  
                if (curso.cursoCompleto()) {
                    std::cout << "El curso está completo.\n";
                } else {
                    std::cout << "Todavía hay cupos disponibles.\n";
                }
                break;
            }

            case 7: {  
                std::cout << curso << "\n";  // Usa la sobrecarga del operador <<
                break;
            }

            case 8: {  
                Curso cursoCopia = curso;  // Llamamos al constructor de copia
                std::cout << "Se creó una copia del curso. Mostrando lista de estudiantes:\n";
                std::cout << cursoCopia << "\n";
                break;
            }

            case 9:
                std::cout << "Saliendo del programa.\n";
                break;

            default:
                std::cout << "Opción no válida. Por favor, ntente nuevamente.\n";
        }
    } while (opcion != 9);

    for (Estudiante* alumno : estudiantes) { //se libera la memoria de los alumnos creados 
        delete alumno;
    }

}


