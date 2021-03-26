#ifndef SATURACIONPROGRESIVA_H
#define SATURACIONPROGRESIVA_H
#define DISP "Dispersion.txt"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class SaturacionProgresiva
{
public:
    char activo[2];
    char curp[11];
    char nombre[15];
    char nacionalidad[15];

    SaturacionProgresiva();

    void formula();

    void generar();
    void insertar();
    void eliminar();
    void modificar();
    void buscar();
    void mostrar();
    void existe(const string &curp);
    void retroceso(long &pos, long int &baseOriginal);
};

#endif // SATURACIONPROGRESIVA_H
