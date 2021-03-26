#include <iostream>
#include "dispersion.h"

using namespace std;

int main()
{
    string op;
    Dispersion dis;
    dis.generar();
    while (true) {
        system("cls");
        cout << "Menu Practica 16 by EvoSenpai(Leonardo Aranda 217761528 INNI)" << endl;
        cout << "1) Agregar Registro" << endl;
        cout << "2) Mostrar Registros" << endl;
        cout << "3) Buscar Registro" << endl;
        cout << "4) Modificar Registro" << endl;
        cout << "5) Eliminar Registro" << endl;
        getline(cin, op);

        if (op == "1") {
            dis.insertar();
        } else if (op == "2") {
            dis.mostrar();
            system("pause");
        } else if (op == "3") {
            dis.buscar();
            system("pause");
        } else if (op == "4") {
            dis.modificar();
        } else if (op == "5") {
            dis.eliminar();
        }
    }
    return 0;
}
