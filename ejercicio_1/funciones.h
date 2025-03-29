enum MOMENTO {AM,PM};
class Reloj{
private:
    int horas;
    int minutos;
    int segundos;
    MOMENTO momento;

public:
    Reloj();
    Reloj(int horas);
    Reloj(int horas, int minutos);
    Reloj(int horas, int minutos, int segundos);
    Reloj(int horas, int minutos, int segundos, MOMENTO);

    void setHora(int hh);
    void setMinutos(int mm);
    void setSegundos(int ss);
    void setMomento(MOMENTO);

    int getHora() const; 
    int getMinutos() const;
    int getSegundos() const;
    MOMENTO getMomento() const;

    void getFormato12() const;
    void getFormato24() const;
    void ingresarTiempo();

};

void menu_1(Reloj& reloj);
void menu_2(Reloj& reloj);