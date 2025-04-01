#include <iostream>
#include <memory>

class Numero{ //interfaz 
public:
    virtual std::unique_ptr<Numero> suma(Numero* num) = 0; //uso unique_ptr para evitar perdidas de memoria
    virtual std::unique_ptr<Numero> resta(Numero* num) = 0;
    virtual std::unique_ptr<Numero> mult(Numero* num) = 0;
    virtual std::unique_ptr<Numero> div(Numero* num) = 0;
    virtual std::string toString() = 0;
    virtual~Numero(){} // destructor virtual
};

class Entero : public Numero{
private:
    int valor;
public:
    Entero(int valor);
    std::unique_ptr<Numero> suma(Numero* num) override;
    std::unique_ptr<Numero> resta(Numero* num) override;
    std::unique_ptr<Numero> mult(Numero* num) override;
    std::unique_ptr<Numero> div(Numero* num) override;
    std::string toString() override;
};

class Real : public Numero{
private:
    double valor;
public:
    Real(double valor);
    std::unique_ptr<Numero> suma(Numero* num) override;
    std::unique_ptr<Numero> resta(Numero* num) override;
    std::unique_ptr<Numero> mult(Numero* num) override;
    std::unique_ptr<Numero> div(Numero* num) override;
    std::string toString() override;
};

class Complejo : public Numero{
private:
    double parteReal, parteImaginaria;
public:
    Complejo(double parteReal, double parteImaginaria);
    std::unique_ptr<Numero> suma(Numero* num) override;
    std::unique_ptr<Numero> resta(Numero* num) override;
    std::unique_ptr<Numero> mult(Numero* num) override;
    std::unique_ptr<Numero> div(Numero* num) override;
    std::string toString() override;
};
