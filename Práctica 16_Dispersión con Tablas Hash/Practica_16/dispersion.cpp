#include "dispersion.h"
Dispersion d;
char llave[12];
long int base, pos;
int cont = 0;

Dispersion::Dispersion() {}

void Dispersion::formula()//Ya
{
    int j=0;
    base=0;

    while((unsigned)j<strlen(llave))
    {
        base=base+(100*llave[j])+(llave[j+1]%84645);
        j=j+2;
    }
    base=base%100;
}

void Dispersion::generar()//Ya
{
    ofstream archivo(DISP, ios::app);
    for (int i = 0; i < 100; ++i) {
        archivo.write((char*)&cont, sizeof(int));
        for (int j = 0; j < 4; ++j) {
            strcpy(d.curp, "-");
            strcpy(d.nombre, "-");
            strcpy(d.nacionalidad, "-");
            archivo.write((char*)&d, sizeof(d));
        }
    }archivo.close();
}

void Dispersion::insertar()//Ya
{
    string temp;
    cout << "Ingresa Curp: ";
    getline(cin, temp);
    strcpy(d.curp, temp.c_str());
    cout << "Ingresa Nombre: ";
    getline(cin, temp);
    strcpy(d.nombre, temp.c_str());
    cout << "Ingresa Nacionalidad: ";
    getline(cin, temp);
    strcpy(d.nacionalidad, temp.c_str());

    strcpy(llave, d.curp);
    formula();

    fstream archivo(DISP, ios::in|ios::out);
    base=base*((sizeof(d)*4)+sizeof(int));
    archivo.seekg(base,ios::beg);
    archivo.read((char*)&cont,sizeof(int));
    if(cont==4)
    {
        cout<<endl<<"Ya no hay espacio para esta llave...!!!"<<endl<<endl;
    }
    else
    {
        pos=base+(cont*sizeof(d))+sizeof(int);
        archivo.seekp(pos,ios::beg);
        archivo.write((char*)&d,sizeof(d));
        cont++;
        pos=base;
        archivo.seekp(pos,ios::beg);
        archivo.write((char*)&cont,sizeof(int));
    }
    archivo.close();
    cont=0;
}

void Dispersion::eliminar()//Ya
{
    Dispersion d2;
    int i,j=0,val=0,retroceso,copiacont,distancia;
    string temp;
    cout<<endl<<"Ingrese Curp de la persona a Eliminar: ";
    getline(cin, temp);
    strcpy(llave, temp.c_str());

    fstream archivo(DISP,ios::in|ios::out);
    if(!archivo.good()){
        cout<<endl<<"No se pudo abrir el Archivo..."<<endl<<endl;
    } else{
        formula();
        base=base*((sizeof(d)*4)+sizeof(int));
        archivo.seekg(base,ios::beg);
        archivo.read((char*)&cont,sizeof(int));
        copiacont=cont;

        for(i=0; i<copiacont; i++){
            archivo.read((char*)&d,sizeof(d));
            if(strcmp(llave,d.curp)==0){
                val=1;
                distancia = cont - (i+1);
                cont--;
                do{
                    archivo.read((char*)&d,sizeof(d));
                    d2=d;
                    retroceso=sizeof(d)*2;
                    archivo.seekg(retroceso,ios::cur);
                    archivo.write((char*)&d2,sizeof(d2));
                    if(i == 0){
                        archivo.read((char*)&d,sizeof(d));
                    }
                    j++;
                }while(j<distancia);
                archivo.seekg(base,ios::beg);
                archivo.write((char*)&cont,sizeof(int));
                if(i==1){
                    archivo.read((char*)&d2,sizeof(d2));
                }
            }
        }
        if(val==0){
            cout<<endl;
            cout<<"No se encontro el Candidato..!!!";
        }
    }
    archivo.close();
    cont = 0;
}

void Dispersion::modificar()//Ya
{
    Dispersion  d2;
    int i, val=0;
    string temp;
    cout<<"Ingrese Curp de la persona a Modificar: ";
    getline(cin, temp);
    strcpy(llave, temp.c_str());

    fstream archivo(DISP,ios::in|ios::out);
    if(!archivo.good()){
        cout<<"Lo sentimos no se encontro el archivo!!!...";
    } else {
        formula();
        base = base*((sizeof(d)*4)+sizeof(int));
        archivo.seekg(base,ios::beg);
        archivo.read((char*)&cont,sizeof(int));
        for(i=0;i<cont;i++){
            archivo.read((char*)&d,sizeof(d));
            if(strcmp(llave,d.curp)==0){
                val=1;

                //////////////Eliminar
                int i,j=0,val=0,retroceso,copiacont,distancia;
                string temp;
                cout<<endl<<"Ingrese Curp de la persona a Eliminar: ";
                getline(cin, temp);
                strcpy(llave, temp.c_str());

                fstream archivo(DISP,ios::in|ios::out);
                if(!archivo.good()){
                    cout<<endl<<"No se pudo abrir el Archivo..."<<endl<<endl;
                } else{
                    formula();
                    base=base*((sizeof(d)*4)+sizeof(int));
                    archivo.seekg(base,ios::beg);
                    archivo.read((char*)&cont,sizeof(int));
                    copiacont=cont;

                    for(i=0; i<copiacont; i++){
                        archivo.read((char*)&d,sizeof(d));
                        if(strcmp(llave,d.curp)==0){
                            val=1;
                            distancia = cont - (i+1);
                            cont--;
                            do{
                                archivo.read((char*)&d,sizeof(d));
                                d2=d;
                                retroceso=sizeof(d)*2;
                                archivo.seekg(retroceso,ios::cur);
                                archivo.write((char*)&d2,sizeof(d2));
                                if(i == 0){
                                    archivo.read((char*)&d,sizeof(d));
                                }
                                j++;
                            }while(j<distancia);
                            archivo.seekg(base,ios::beg);
                            archivo.write((char*)&cont,sizeof(cont));
                            if(i==1){
                                archivo.read((char*)&d2,sizeof(d2));
                            }
                        }
                    }
                    if(val==0){
                        cout<<endl;
                        cout<<"No se encontro el Registro..!!!";
                    }
                }
                archivo.close();
                ///////////////////////////
                /// \brief insertar
                cout << "Ingrese nuevos valores..." << endl;
                insertar();
            }
        }
        if(val==0){
            cout<<endl<<endl;
            cout<<"Error: Registro NO Encontrado!";
            cout<<endl<<endl;
        }
    }
    pos=pos+(3*sizeof(d))+sizeof(int);
    archivo.close();
}

void Dispersion::buscar()//Ya
{
    string temp; int val;
    cout << "Ingresa el Curp de la persona que buscas: ";
    getline(cin, temp);
    strcpy(llave, temp.c_str());

    fstream archivo(DISP, ios::in|ios::out);
    if(!archivo.good()){
        cout<<endl<<"El archivo No se pudo Abrir..."<<endl<<endl;
    }else{
        formula();
        base = base * ((sizeof(d)*4)+sizeof(int));
        archivo.seekg(base,ios::beg);
        archivo.read((char*)&cont,sizeof(int));
        for(int i = 0; i < cont; i++){
            archivo.read((char*)&d,sizeof(d));
            if(strcmp(llave,d.curp)==0){
                val=1;
                cout<<endl;
                cout << "Curp: "<<d.curp << endl;
                cout << "Nombre: "<<d.nombre << endl;
                cout << "Nacionalidad: "<<d.nacionalidad << endl;
                cout<<endl;
            }
        }
        if(val==0){
            cout<<endl<<"Lo sentimos no fue encontrado el registro..."<<endl<<endl;
        }
    }
    archivo.close();
}

void Dispersion::mostrar()//Ya
{
    pos=0;
    ifstream archivo(DISP);
    if(!archivo.good()){
        cout<<endl<<"No se pudo Abrir el archivo..."<<endl<<endl;
    }else{
        while(!archivo.eof()){
            if(archivo.eof()){ break; }
            archivo.seekg(pos,ios::beg);
            archivo.read((char*)&cont,sizeof(int));
            if(cont == 0){
                pos = pos + (4*sizeof(d))+sizeof(int);
            }else{
                for (int i = 0; i < cont; ++i) {
                    archivo.read((char*)&d,sizeof(d));
                    cout << endl;
                    cout << "Curp: "<<d.curp << endl;
                    cout << "Nombre: "<<d.nombre << endl;
                    cout << "Nacionalidad: "<<d.nacionalidad << endl;
                    cout << "Posicion: "<<pos%100 << endl << endl;
                    pos=pos+(4*sizeof(d))+sizeof(int);
                }
            }
            if(archivo.eof()){break;}
        }
    }archivo.close();
}
