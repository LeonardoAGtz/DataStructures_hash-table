#ifndef DISPERSION_H
#define DISPERSION_H
#include <iostream>
#include <fstream>
#include <string.h>
#define DISP "dispersion.txt"

using namespace std;

class Dispersion
{
public:
    char curp[12];
    char nombre[15];
    char nacionalidad[15];

    Dispersion();
    void formula();
    void generar();
    void insertar();
    void eliminar();
    void modificar();
    void buscar();
    void mostrar();

};

#endif // DISPERSION_H
