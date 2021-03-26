#include <iostream>
#include "saturacionprogresiva.h"

using namespace std;

int main()
{
    string op;
    SaturacionProgresiva dispersion;
    dispersion.generar();
    while (true) {
        system("cls");
        cout << "Menu Practica 15 by EvoSenpai(Leonardo Aranda 217761528 INNI)" << endl;
        cout << "1) Insertar Persona" << endl;
        cout << "2) Mostrar Personas" << endl;
        cout << "3) Buscar Persona" << endl;
        cout << "4) Eliminar Persona" << endl;
        getline(cin, op);

        if (op == "1") {
            dispersion.insertar();
        } else if (op == "2") {
            dispersion.mostrar();
        } else if (op == "3") {
            dispersion.buscar();
        } else if (op == "4") {
            dispersion.eliminar();
        }
    }
    return 0;
}
