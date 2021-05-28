#include <iostream>
#include "Global.h"
//#include "Lista.h"
#include "AdminDisk.h"
#include "Analizador.h"

void crear(FILE *file, int size){
    //size = size*1024;
    char buffer[1024];
    for(int i = 0; i<1024; i++) buffer[i]='\0';
    for( int i = 0; i < size; i++)
        fwrite(&buffer,1024,1,file);
}

int main(){
    string comando;
    string mi;
    while (comando != "exit")
    {

        Analizador analizar;
        cout<<"Ingrese un comando"<<endl;
        getline(cin, comando);
        analizar.Lexico(comando);
    }
    /*
    Analizador c = Analizador();
    c.Lexico("Mkdisk –size=10 –path=\"/home/mis discos/Disco4.dk\"");
    c.Listado().Imprimir();

    /*

     FILE *archivo = fopen("/home/disco.dk" ,"rb+");

    EBR *ebr;
    fseek(archivo,200,SEEK_SET);
    fread(ebr, sizeof(EBR), 1, archivo);
    fclose(archivo);

    AdminDisk nuevo;
    Token token;
    token.nombre="hola mundo";
    nuevo.Crear(5, "d", 'k', "/home/disco.dk");
    nuevo.Crear_Particion(50, "/home/disco.dk", "Cristian");
    /*
    int tamano = sizeof(int)*2+sizeof(char)*21;
    FILE *arch;
    arch=fopen("/home/disco.dk","rb+");
    MBR persona3;
   fseek(arch,tamano+100,SEEK_SET);
    fwrite(&token, sizeof(Token), 1, arch);
    fclose(arch);
    /*
    Analizador c = Analizador();
    c.Lexico("Mkdisk –size=10 –path=\"/home/mis discos/Disco4.dk\"");
    c.Listado().Imprimir();
    
    /*
    string comando;
    string mi;

    while (comando != "exit")
    {
        cout<<"ingrese un comando"<<endl;

        cin >> comando;

        for (int i = 0; i < comando.size(); i++)
        {
            mi += tolower(comando[i]);
        }
        comando = mi;
        mi = "";
        for (int i = 0; i < comando.size(); i++)
        {
            cout<<comando[i]<<endl;
        }
    }
    */

    return 0;
}