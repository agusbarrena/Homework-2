#include <iostream>

class Numero{ //interfaz
public:
    virtual Numero* suma(Numero* num) = 0;
    virtual Numero* resta(Numero* num) = 0;
    virtual Numero* mult(Numero* num) = 0;
    virtual Numero* div(Numero* num) = 0;
    virtual std::string toString() = 0;
    virtual~Numero(){} // destructor virtual
};

class Entero : public Numero{
private:
    int valor;
public:
    Entero(int valor);
    Numero* suma(Numero* num) override;
    Numero* resta(Numero* num) override;
    Numero* mult(Numero* num) override;
    Numero* div(Numero* num) override;
    std::string toString() override;
};

class Real : public Numero{
private:
    double valor;
public:
    Real(double valor);
    Numero* suma(Numero* num) override;
    Numero* resta(Numero* num) override;
    Numero* mult(Numero* num) override;
    Numero* div(Numero* num) override;
    std::string toString() override;
};

class Complejo : public Numero{
private:
    double parteReal, parteImaginaria;
public:
    Complejo(double parteReal, double parteImaginaria);
    Numero* suma(Numero* num) override;
    Numero* resta(Numero* num) override;
    Numero* mult(Numero* num) override;
    Numero* div(Numero* num) override;
    std::string toString() override;
};
