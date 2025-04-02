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

//En la clase Banco (clase base), usamos protected en vez de private porque los miembros protected pueden ser accedidos dentro de Banco y dentro de CajaDeAhorro y CuentaCorriente (clases derivadas). Además permite que ambas subclases accedan a los datos y métodos de Banco sin la necesidad de hacerlos públicos. Notemos que CajaDeAhorro y CuentaCorriente sobrescriben métodos de la clase Banco.Por el otro lado, tanto en CajaDeAhorro como en CuentaCorriente usamos private porque los miembros private solo pueden ser accedidos dentro de la misma clase a la cual pertenecen. Por lo tanto, no permitimos que los datos dentro de estas clases derivadas puedan ser manipulados por otras subclases de manera directa.


