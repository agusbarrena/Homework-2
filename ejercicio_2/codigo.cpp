#include "funciones.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

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

std::string Curso::getNombreCurso() const{
    return nombre;
}
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
//Realicé una deep copy y no una shallow copy porque en mi implementación, Curso tiene un vector que contiene punteros a estudiantes. Por lo tanto, si yo hiciera una shallow copy haciendo que tanto mi curso como la copia apunten al mismo vector, si llego a eliminar un estudiante en la copia, lo estaría también eliminando en el curso original. Esto se llama problemas de aliasing. Para que no ocurra esto, necesitamos con una deep copy asegurar que ambos cursos sean independientes creando nuevos objetos Estudiante en la copia del curso.
Curso::~Curso(){ //si yo elimino el curso, al hacer una deep copy debo eliminar el vector de estudiantes al que estaba asociado, sino me quedaria memoria colgada 
    for(auto* estudiante : estudiantes){
        delete estudiante;
    }
}
//Respuesta (c): El tipo de relación entre los objetos curso y estudiante es de agregación.Esto se debe a que vemos representada una relacion del tipo has-a entre un objeto que actúa como un todo (whole) y sus partes (parts). Como podemos ver en este caso, Curso almacena punteros a Estudiante, y estos pueden existir en múltiples cursos o fuera de ellos. Por lo tanto, existe una acción entre ambos objetos pero tienen ciclos de vida independientes el uno del otro.

void menu_interactivo() {
    
    std::vector<Estudiante*> estudiantes;
    std::vector<Curso*> cursos = {
        new Curso("Paradigmas"),
        new Curso("Fisica"),
        new Curso("Estadistica"),
        new Curso("Literatura")
    };

    int opcion;
    int legajo;
    float nota;
    std::string nombreCurso;
    std::string curso;
    std::string cursoNombre;
    do {
        std::cout << "\n---Menu---\n"
                  << "1. Agregar estudiante\n"
                  << "2. Inscribir estudiante a un curso\n"
                  << "3. Ingresar notas de un estudiante\n"
                  << "4. Desinscribir estudiante de un curso\n"
                  << "5. Buscar estudiante por legajo\n"
                  << "6. Verificar si un curso está completo\n"
                  << "7. Imprimir lista de estudiantes ordenados\n"
                  << "8. Mostrar promedio general\n"
                  << "9. Copiar curso\n"
                  << "10. Salir\n"
                  << "Opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                std::string nombre;
                std::cout << "Ingrese nombre: ";
                std::cin >> nombre;
                std::cout << "Ingrese legajo: ";
                std::cin >> legajo;
                estudiantes.push_back(new Estudiante(nombre, legajo));
                break;
            }
            case 2: {
                std::cout << "Ingrese legajo del estudiante: ";
                std::cin >> legajo;
                
                std::cout << "Cursos disponibles:\n";
                for (auto& curso : cursos) {
                    std::cout << "- " << curso->getNombreCurso() << "\n";
                }
                std::cout << "Ingrese nombre del curso: ";
                std::cin >> nombreCurso;
                
                bool encontrado = false;
                for (auto& curso : cursos) {
                    if (curso->getNombreCurso() == nombreCurso) {
                        for (auto& estudiante : estudiantes) {
                            if (estudiante->getLegajo() == legajo) {
                                if (curso->inscribirEstudiante(estudiante)) {
                                    std::cout << "Estudiante " << estudiante->getNombre() << " inscrito en " << curso->getNombreCurso() << ".\n";
                                } else {
                                    std::cout << "Error: El estudiante ya está inscrito en este curso o el curso está lleno.\n";
                                }
                                encontrado = true;
                                break;
                            }
                        }
                    }
                }
                if (!encontrado) {
                    std::cout << "Error: No se encontró el estudiante o el curso ingresado.\n";
                }
                break;
            }
            case 3: {
                std::cout << "Ingrese legajo: ";
                std::cin >> legajo;
                std::cout << "Ingrese curso: ";
                std::cin >> curso;
                std::cout << "Ingrese nota: ";
                std::cin >> nota;
            
                Estudiante* estudiante = nullptr;
                for (auto& est : estudiantes) {
                    if (est->getLegajo() == legajo) {
                        estudiante = est;
                        break;
                    }
                }
            
                if (!estudiante) {
                    std::cout << "Estudiante no encontrado.\n";
                    break;
                }

                bool encontrado = false;
                for (auto& c : cursos) {
                    if (c->getNombreCurso() == curso) {
                        if (c->estudianteInscripto(legajo)) {
                            estudiante->agregarCurso(curso, nota);
                            std::cout << "Nota agregada exitosamente.\n";
                        } else {
                            std::cout << "El estudiante no está inscripto en ese curso.\n";
                        }
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "El curso ingresado no existe.\n";
                }
                break;
            }
            
            
            case 4: {
                std::cout << "Ingrese legajo del estudiante a desinscribir: ";
                std::cin >> legajo;
                
                std::cout << "Cursos disponibles:\n";
                for (auto& curso : cursos) {
                    std::cout << "- " << curso->getNombreCurso() << "\n";
                }
                std::cout << "Ingrese nombre del curso: ";
                std::cin >> nombreCurso;
            
                bool encontrado = false;
                for (auto& curso : cursos) {
                    if (curso->getNombreCurso() == nombreCurso) {
                        if (curso->desinscribirEstudiante(legajo)) {
                            std::cout << "Estudiante con legajo " << legajo << " ha sido desinscrito de " << curso->getNombreCurso() << ".\n";
                        } else {
                            std::cout << "Error: El estudiante no estaba inscrito en este curso.\n";
                        }
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "Error: Curso no encontrado.\n";
                }
                break;
            }
            case 5: {
                std::cout << "Ingrese legajo: ";
                std::cin >> legajo;
                for (auto& estudiante : estudiantes) {
                    if (estudiante->getLegajo() == legajo) {
                        estudiante->imprimirEstudiante();
                        break;
                    }
                }
                break;
            }
            case 6: {
                for (auto& curso : cursos) {
                    std::cout << curso->getNombreCurso() << " esta " 
                              << (curso->cursoCompleto() ? "lleno" : "hay vacantes") << "\n";
                }
                break;
            }
            case 7: {
                std::cout << "Cursos disponibles:\n";
                for (auto& c : cursos) {
                    std::cout << "- " << c->getNombreCurso() << "\n";
                }
            
                std::cout << "Ingrese el nombre del curso a imprimir: ";
                std::cin >> cursoNombre;
            
                bool encontrado = false;
                for (auto& c : cursos) {
                    if (c->getNombreCurso() == cursoNombre) {
                        c->estudiantesOrdenados();
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "Curso no encontrado.\n";
                }
                break;
            }
            case 8: {
                for (auto& estudiante : estudiantes) {
                    std::cout << estudiante->getNombre() << " - Promedio: " 
                              << estudiante->getPromedioGeneral() << "\n";
                }
                break;
            }
            case 9: {
                std::cout << "Ingrese curso a copiar: ";
                std::cin >> cursoNombre;
                for (auto& curso : cursos) {
                    if (curso->getNombreCurso() == cursoNombre) {
                        cursos.push_back(new Curso(*curso));
                        std::cout << "Curso copiado.\n";
                        break;
                    }
                }
                break;
            }
            case 10:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opción invalida.\n";
                break;
        }
    } while (opcion != 10);

    for (auto& estudiante : estudiantes) {
        delete estudiante;
    }
    for (auto& curso : cursos) {
        delete curso;
    }
}


