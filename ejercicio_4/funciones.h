#include <iostream>

class Banco{
public:
    Banco(double total,std::string titular, std::string tipo);
    virtual void depositar(double cant);
    virtual void retirar(double cant) = 0;
    virtual void mostrarInfo() = 0;
protected:
    double balance;
    std::string titularCuenta;
    std::string tipoCuenta;
};

//clases derivadas de Banco

class CajaDeAhorro : public Banco{
public:
    CajaDeAhorro(double total, std::string titularCuenta);
    void retirar(double cant) override;
    void mostrarInfo() override;

    friend class CuentaCorriente;

private:
    int contador = 0;
};

class CuentaCorriente : public Banco{
public:
    CuentaCorriente(double total, std::string titular, CajaDeAhorro& caja);
    void retirar(double cant) override;
    void mostrarInfo() override;
private:
    CajaDeAhorro &caja;
};


