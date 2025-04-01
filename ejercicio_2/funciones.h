#include <iostream>
#include <vector>

class Estudiante{
private:
    int legajo;
    std::string nombre;
    std::vector<std::pair<std::string, float>> cursos; // usar objeto curso 

public:
    Estudiante(const std::string& nombre, int legajo);
    
    std::string getNombre() const;
    int getLegajo() const;
    float getPromedioGeneral() const;
    void agregarCurso(const std::string curso, float nota);
    void imprimirEstudiante() const;

    friend std::ostream& operator<<(std::ostream& os, const Estudiante& estudiante);//sobrecargamos el operador lo que permite que ahora este pueda acceder a la parte private de Estudiante sin ser un metodo de la clase 

};

class Curso{
private:
    std::string nombre;
    std::vector<Estudiante*> estudiantes;
    static const int MAX_ESTUDIANTES = 20;

public:
    Curso(const std::string nombre);

    bool inscribirEstudiante(Estudiante* estudiante);
    bool desinscribirEstudiante(int legajo);
    bool estudianteInscripto(int legajo);
    bool cursoCompleto() const;
    void estudiantesOrdenados() const;
    static bool compararEstudiantesPorNombre(const Estudiante* a, const Estudiante* b);

    friend std::ostream& operator<<(std::ostream& os, const Curso& curso); //sobrecargamos el operador lo que permite que ahora este pueda acceder a la parte private de Curso sin ser un metodo de la clase 

    Curso(const Curso& rht);
    ~Curso();
};

void menu_interactivo();