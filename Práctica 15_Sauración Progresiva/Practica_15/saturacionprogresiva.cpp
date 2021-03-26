#include "saturacionprogresiva.h"
SaturacionProgresiva persona;
char llave[11];
long int base, pos;
bool existe_ = false;

SaturacionProgresiva::SaturacionProgresiva()
{

}

void SaturacionProgresiva::formula()//Listo Y Verificado
{
    ///Usaré la formula anterior, pero tego que cambiar por la sumatoria
    base = 0;
    for (int i = 0; i < strlen(llave); ++i) {
        base += llave[i];
    }
    base = base%100;
}

void SaturacionProgresiva::generar()//Listo Y Verificado
{
    strcpy(persona.activo, "0");
    strcpy(persona.curp, "-");
    strcpy(persona.nombre, "-");
    strcpy(persona.nacionalidad, "-");

    ofstream dis(DISP, ios::app);
    for (int i = 0; i < 100; ++i) {
        dis.write((char*)&persona, sizeof(persona));
    }dis.close();
}

void SaturacionProgresiva::insertar()//Listo Y Verificado
{
    string temp;
    cout << "Ingresa el Curp: ";
    getline(cin, temp);
    strcpy(persona.curp, temp.c_str());
    cout << "Ingresa el Nombre: ";
    getline(cin, temp);
    strcpy(persona.nombre, temp.c_str());
    cout << "Ingresa la Nacionalidad: ";
    getline(cin, temp);
    strcpy(persona.nacionalidad, temp.c_str());

    strcpy(llave, persona.curp);
    strcpy(persona.activo, "1");

    string validar(persona.curp);
    existe(validar);

    if (existe_ == false) {
        formula();
        SaturacionProgresiva persona2;
        fstream dis(DISP, ios::in|ios::out);
        base = base * sizeof(persona);
        dis.seekg(base, ios::beg);
        dis.read((char*)&persona2, sizeof(persona2));
        string status(persona2.activo);
        if (status == "1") {
            while (status == "1") {
                if (base == 100) {
                    base = 0;dis.seekg(base, ios::beg);
                    dis.write((char*)&persona2, sizeof(persona2));
                    base = base + sizeof(persona2);
                }
                base = base + sizeof(persona);
                dis.seekg(base, ios::beg);
                dis.read((char*)&persona2, sizeof(persona2));
                status = persona2.activo;

                if (base == 99) {
                    break;
                }
            }
        }
        dis.seekg(base, ios::beg);
        dis.write((char*)&persona, sizeof(persona));
        dis.close();
    }
    existe_ = false;
}

void SaturacionProgresiva::eliminar()
{
    string nombre; long int baseOriginar;
    cout << "Ingresa el Crup de la persona que deseas eliminar: ";
    getline(cin, nombre);
    strcpy(persona.curp, nombre.c_str());
    strcpy(llave, persona.curp);

    string validar(persona.curp);
    existe(validar);

    if (existe_ == true) {
        formula();
        baseOriginar = base;

        SaturacionProgresiva persona2;
        fstream dis(DISP, ios::in|ios::out);
        base = base * sizeof(persona);
        dis.seekg(base, ios::beg);
        dis.read((char*)&persona2, sizeof(persona2));
        string curpTemporal(persona2.curp);

        bool flag = false;
        if (curpTemporal == nombre) {
            flag = true;
        } else { flag = false;}

        if (flag) {
            strcpy(persona2.activo, "0");
            strcpy(persona2.curp, "-");
            strcpy(persona2.nombre, "-");
            strcpy(persona2.nacionalidad, "-");
            dis.seekg(base, ios::beg);
            dis.write((char*)&persona2, sizeof(persona2));//Ingreso los nuevos parametros de la persona eliminados logicamente
        } else {
            while (curpTemporal != nombre) {//Proceso para encontrar a la persona
                cout << curpTemporal << "|" << nombre << endl;
                system("pause");
                base = base + sizeof(persona2);
                dis.seekg(base, ios::beg);
                dis.read((char*)&persona2, sizeof(persona2));
                curpTemporal = persona2.curp;
            }
//            long int checkpoint = base;//Checkpoint de la base donde comienza la eliminacion
//            base = base - sizeof(persona);
            dis.seekg(base, ios::beg);
            strcpy(persona2.activo, "0");
            strcpy(persona2.curp, "-");
            strcpy(persona2.nombre, "-");
            strcpy(persona2.nacionalidad, "-");
            dis.seekg(base, ios::beg);
            dis.write((char*)&persona2, sizeof(persona2));//Aqui la persona ya fue eliminada

            ////Hasta aqui se eleimina bien la persona, el resto es retroceder las siguiente

        } dis.close();
        long int retro = base +sizeof(persona);
        long auxiliar;

        retroceso(retro, baseOriginar);

        string ultima;
        ifstream a("aux.txt", ios::in);
        if (a.is_open()) {
            while (!a.eof()) {
                string temp;
                getline(cin, temp);
                ultima = temp;
                if (a.eof()){break;}
            }
        }a.close();

//        long int xd = stol(ultima);
//        cout << xd << endl;

//        SaturacionProgresiva peraux;
//        fstream d(DISP, ios::in|ios::out);
//        d.seekg(xd, ios::beg);
//        strcpy(peraux.activo, "0");
//        strcpy(peraux.curp, "-");
//        strcpy(peraux.nombre, "-");
//        strcpy(peraux.nacionalidad, "-");
//        d.write((char*)&peraux, sizeof(peraux));
//        d.close();
    }
}

void SaturacionProgresiva::modificar()
{
    string nombre;
    cout << "Ingresa el Curp de la persona que deseas modificar: ";
    getline(cin, nombre);

    /////////////Paso de eleiminacion
    long int baseOriginar, baseTemporal;
    strcpy(persona.curp, nombre.c_str());
    strcpy(llave, persona.curp);

    string validar(persona.curp);
    existe(validar);

    if (existe_ == true) {
        cout << "existe es true" << endl;
    } else if (existe_ == false) {
        cout << "existe es false" << endl;
    }

    if (existe_ == true) {
        formula();
        baseOriginar = base;

        SaturacionProgresiva persona2;
        fstream dis(DISP, ios::in|ios::out);
        base = base * sizeof(persona);
        dis.seekg(base, ios::beg);
        dis.read((char*)&persona2, sizeof(persona2));
        string curpTemporal(persona2.curp);
        if (curpTemporal == nombre) {
            base = base - sizeof(persona); //Regreso a la posicion antes de leer
            strcpy(persona.activo, "0");
            strcpy(persona.curp, "-");
            strcpy(persona.nombre, "-");
            strcpy(persona.nacionalidad, "-");
            dis.seekg(base, ios::beg);
            dis.write((char*)&persona, sizeof(persona));//Ingreso los nuevos parametros de la persona eliminados logicamente
        } else {
            while (curpTemporal != nombre) {//Proceso para encontrar a la persona
                base = base + sizeof(persona);
                dis.seekg(base, ios::beg);
                dis.read((char*)&persona, sizeof(persona));
                curpTemporal = persona.curp;
            }
            base = base - sizeof(persona);
            long int checkpoint = base;//Checkpoint de la base donde comienza la eliminacion
            dis.seekg(base, ios::beg);
            strcpy(persona.activo, "0");
            strcpy(persona.curp, "-");
            strcpy(persona.nombre, "-");
            strcpy(persona.nacionalidad, "-");
            dis.seekg(base, ios::beg);
            dis.write((char*)&persona, sizeof(persona));//Aqui la persona ya fue eliminada
            ////Hay que verificar si registros posteriores tienen la misma base;
            while (baseTemporal == baseOriginar) {
                dis.read((char*)&persona2, sizeof(persona2));
                strcpy(llave, persona2.curp);
                formula();
                baseTemporal = base;//Obtengo la base
                if (baseTemporal == baseOriginar) {
                    dis.seekg(checkpoint, ios::beg);
                    dis.write((char*)&persona2, sizeof(persona2));
                    checkpoint = checkpoint - sizeof(persona2);
                }
            }
        } dis.close();
    }
    //////////////////////////////////

    ///////Paso de insercion de nuevo elemento
    string temp;
    cout << "Ingresa el Curp Nuevo: ";
    getline(cin, temp);
    strcpy(persona.curp, temp.c_str());
    cout << "Ingresa el Nombre Nuevo: ";
    getline(cin, temp);
    strcpy(persona.nombre, temp.c_str());
    cout << "Ingresa la Nacionalidad Nueva: ";
    getline(cin, temp);
    strcpy(persona.nacionalidad, temp.c_str());

    strcpy(llave, persona.curp);
    strcpy(persona.activo, "1");

    string validar2(persona.curp);
    existe(validar2);

    if (existe_ == false) {
        formula();
        SaturacionProgresiva persona2;
        fstream dis(DISP, ios::in|ios::out);
        base = base * sizeof(persona);
        dis.seekg(base, ios::beg);
        dis.read((char*)&persona2, sizeof(persona2));
        string status(persona2.activo);
        if (status == "1") {
            while (status == "1") {
                base = base + sizeof(persona);
                dis.seekg(base, ios::beg);
                dis.read((char*)&persona2, sizeof(persona2));
                status = persona2.activo;
            }
        }
        base = base - sizeof(persona);
        dis.seekg(base, ios::beg);
        dis.write((char*)&persona, sizeof(persona));
        dis.close();
    }
    existe_ = false;
    ///////////////////////////////////////////
}

void SaturacionProgresiva::buscar()//Listo Y Verificado
{
    string temp;
    cout << "Ingresa el Curp que buscas: ";
    getline(cin, temp);

    pos = 0;
    SaturacionProgresiva persona3;
    ifstream dis(DISP);
    if (dis.good()) {
        while (!dis.eof()) {
            if (dis.eof()) {break;}
            dis.seekg(pos, ios::beg);
            dis.read((char*) &persona3, sizeof(persona3));
            string temporal(persona3.curp);
            if (temporal == temp) {
                cout << "Curp Encontrada: " << persona3.curp << endl;
                cout << "Nombre: " << persona3.nombre << endl;
                cout << "Nacionalidad: " << persona3.nacionalidad << endl;
            }
            pos = pos + sizeof(persona3);
            if (dis.eof()) {break;}
        }
    }dis.close();
}

void SaturacionProgresiva::mostrar()//Listo Y Verificado
{
    pos = 0;
    ifstream dis(DISP);
    if (dis.good()) {
        while (!dis.eof()) {
            if (dis.eof()) {break;}
            dis.seekg(pos, ios::beg);
            dis.read((char*) &persona, sizeof(persona));
            string status(persona.activo);
            if (status == "1") {
                cout << "Curp: " << persona.curp << endl;
                cout << "Nombre: " << persona.nombre << endl;
                cout << "Nacionalidad: " << persona.nacionalidad << endl << endl;
            }
            pos = pos + sizeof(persona);
            if (dis.eof()) {break;}
        }
    }dis.close();
}

void SaturacionProgresiva::existe(const string &curp)//Listo Y Verificado
{
    pos = 0;
    existe_ = false;
    SaturacionProgresiva persona3;
    ifstream dis(DISP);
    if (dis.good()) {
        while (!dis.eof()) {
            if (dis.eof()) {break;}
            dis.seekg(pos, ios::beg);
            dis.read((char*) &persona3, sizeof(persona3));
            string temporal(persona3.curp);
            if (temporal == curp) {
                existe_ = true;
            }
            pos = pos + sizeof(persona3);
            if (dis.eof()) {break;}
        }
    }dis.close();
}

void SaturacionProgresiva::retroceso(long &pos, long &baseOriginal)
{
    long int baseTemporal = pos;
    SaturacionProgresiva personax;
    fstream dis(DISP, ios::in|ios::out);
    dis.seekg(pos, ios::beg);
    dis.read((char*)&personax, sizeof(personax));
    strcpy(llave, personax.curp);
    formula();
    long int basex = base;

    if (basex == baseOriginal) {
        baseTemporal = baseTemporal - sizeof(personax);
        dis.seekg(baseTemporal, ios::beg);
        dis.write((char*)&personax, sizeof(personax));
        dis.close();
        pos = pos + sizeof(personax);
//        int a = pos;
//        char mypos[4];
//        sprintf(mypos, "%d", a);
//        string paux(mypos);

//        ofstream s("aux.txt", ios::app);
//        s << paux << endl;;
//        s.close();

        retroceso(pos, baseOriginal);
    }
}
