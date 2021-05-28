#ifndef ANALIZADOR_H
#define ANALIZADOR_H
#include "Global.h"
#include <cstdlib>
#include "Lista.h"
#include "AdminDisk.h"
#include "Graficar.h"


class Analizador
{
private:
    Lista lista;
    /* data */
public:
    Analizador(/* args */);
    ~Analizador();
    void Lexico(string Texto);
    void Agregar(string entrada);
    void Sintactico(Lista *entrada);
    Lista Listado();
};

Analizador::Analizador(/* args */)
{
}

Analizador::~Analizador()
{
}

Lista Analizador::Listado(){
    return lista;
}

void Analizador::Lexico(string Texto){
    Texto += " ";
    string texto;
    for (int i = 0; i < Texto.size(); i++)
    {
        texto += tolower(Texto[i]);
    }
    Texto = "";
    int estado = 1;
    for (int i = 0; i < texto.size(); i++)
    {
        switch (estado)
        {
        case 1:
            if(texto[i] != ' '){
                Texto += texto[i];
            }
            if (texto[i] == '=')
            {
                Agregar(Texto);
                Texto = "";
            }
            
            if(texto[i] == '\"'){
                estado = 2;
            }
            if(isalpha(texto[i])){
                estado = 3;
            }
            if (isdigit(texto[i])) {
                estado = 4;
            }
            if (texto[i] == '-')
            {
                estado = 5;
            }
            if (texto[i] == '/')
            {
                estado = 6;
            }
            

            break;

        case 2:
            if (texto[i] != '\"')
            {
                Texto += texto[i];
            }else
            {
                Texto += texto[i];
                Agregar(Texto);
                Texto = "";
                estado = 1;
                i--;
            }
            

            break;
        case 3:
            if (texto[i] != ' ' && texto[i] != '=')
            {
                Texto += texto[i];
            }else
            {
                Agregar(Texto);
                Texto = "";
                estado = 1;
                i--;
            }
            
            

            break;
        case 4:
            if (isdigit(texto[i]))
            {
                Texto += texto[i];
            }
            else
            {
                if (texto[i] == ' ')
                {
                    Agregar(Texto);
                    Texto = "";
                    estado = 1;
                    i--;
                }
                else
                {
                    Texto += texto[i];
                    estado = 6;
                }
                
            }
            
            break;
        case 5:
            if (texto[i] != '=')
            {   
                Texto += texto[i];
            }
            else
            {
                Agregar(Texto);
                Texto = "";
                estado = 1;
                i--;
            }
            
            break;
        case 6:
            if (texto[i] == ' ')
            {
                Agregar(Texto);
                Texto = "";
                estado = 1;
                i--;
            }else{
                Texto += texto[i];
            }
            
            break;
        default:
            break;
        }
    }
    Sintactico(&lista);
}

void Analizador::Agregar(string entrada){
    Token nuevo;
    nuevo.nombre = entrada;
    nuevo.numero = 1;
    lista.Insertar(nuevo);
}


void Analizador::Sintactico(Lista *entrada){
    string comando = entrada->inicio->lexema.nombre;
    if (comando == "mkdisk"){

        bool error = false;
        int tamano=0;
        string f = "";
        char u = '0';
        string direccion = "";
        entrada->inicio = entrada->inicio->sig;
        while (entrada->inicio != NULL)
        {
            if (entrada->inicio->lexema.nombre == "–path")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                direccion = entrada->inicio->lexema.nombre;
            } else if(entrada->inicio->lexema.nombre == "–size"){
                entrada->inicio = entrada->inicio->sig->sig;
                tamano = atoi( entrada->inicio->lexema.nombre.c_str());
            }else if(entrada->inicio->lexema.nombre == "–f"){
                entrada->inicio = entrada->inicio->sig->sig;
                f =  entrada->inicio->lexema.nombre.at(0);
            }else if(entrada->inicio->lexema.nombre == "–u"){
                entrada->inicio = entrada->inicio->sig->sig;
                u = entrada->inicio->lexema.nombre.at(0);
            } else if (entrada->inicio->lexema.nombre == "-path")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                direccion = entrada->inicio->lexema.nombre;
            } else if(entrada->inicio->lexema.nombre == "-size"){
                entrada->inicio = entrada->inicio->sig->sig;
                tamano = atoi( entrada->inicio->lexema.nombre.c_str());
            }else if(entrada->inicio->lexema.nombre == "-f"){
                entrada->inicio = entrada->inicio->sig->sig;
                f =  entrada->inicio->lexema.nombre.at(0);
            }else if(entrada->inicio->lexema.nombre == "-u"){
                entrada->inicio = entrada->inicio->sig->sig;
                u = entrada->inicio->lexema.nombre.at(0);
            }else
            {
                error = true;
                cout << "Error parametro no reconocido: "<<entrada->inicio->lexema.nombre<<endl;
                break;
            }
            entrada->inicio = entrada->inicio->sig;
        }
        
        if (!error)
        {
            if (direccion != "" && tamano > 0)
            {
                AdminDisk crear;
                crear.Crear(tamano, f, u, direccion);
            }
            else
            {
                if (direccion == "")
                {
                    cout << "Directorio no especificado"<<endl;
                }
                else
                {
                    cout << "No se especifico el tamano"<<endl;
                }
                
            }
            
        }
        
    }else if (comando == "rmdisk")
    {
        bool error = false;
        string path = "";
        entrada->inicio = entrada->inicio->sig;
        if (entrada->inicio->lexema.nombre == "-path")
        {
            entrada->inicio = entrada->inicio->sig->sig;
            path = entrada->inicio->lexema.nombre;
        }
        else if (entrada->inicio->lexema.nombre == "–path")
        {
            entrada->inicio = entrada->inicio->sig->sig;
            path = entrada->inicio->lexema.nombre;
        }
        else
        {
            error = true;
            cout << "Parametro incorrecto"<<endl;
        }
        
        if (!error)
        {
            if (path != "")
            {
                AdminDisk nuevo;
                nuevo.Eliminar(path);
            }
            
        }
        

    }else if (comando == "rep")
    {
        string id;
        string path;
        string name;
        bool error = false;
        entrada->inicio = entrada->inicio->sig;
        while (entrada->inicio != NULL)
        {
            if (entrada->inicio->lexema.nombre == "-id")
        {
            entrada->inicio = entrada->inicio->sig->sig;
            id = entrada->inicio->lexema.nombre;
        }else if (entrada->inicio->lexema.nombre == "–id")
        {
            entrada->inicio = entrada->inicio->sig->sig;
            id = entrada->inicio->lexema.nombre;
        }else if (entrada->inicio->lexema.nombre == "-path")
        {
            entrada->inicio = entrada->inicio->sig->sig;
            path = entrada->inicio->lexema.nombre;
        }else if (entrada->inicio->lexema.nombre == "–path")
        {
            entrada->inicio = entrada->inicio->sig->sig;
            path = entrada->inicio->lexema.nombre;
        }else if (entrada->inicio->lexema.nombre == "-name")
        {
            entrada->inicio = entrada->inicio->sig->sig;
            name = entrada->inicio->lexema.nombre;
        }else if (entrada->inicio->lexema.nombre == "–name")
        {
            entrada->inicio = entrada->inicio->sig->sig;
            name = entrada->inicio->lexema.nombre;
        }else{
            error = true;
            cout << "Parametro incorrecto "<< entrada->inicio->lexema.nombre <<endl;
        }
        entrada->inicio = entrada->inicio->sig;
        }
        
        if (!error)
        {
            if (name == "mbr")
            {
                Graficar grafica;
                grafica.Graficar_MBR(name, path, id);   
            }else if (name == "disk")
            {
                Graficar grafica;
                grafica.Graficar_Disco(name, path, id); 
            }
            
            
        }
        
    }else if (comando == "fdisk")
    {
        int tamano = 0;
        bool error = false;
        char u;
        string path = "";
        string name = "";
        char type;
        char f;
        entrada->inicio = entrada->inicio->sig;
        while (entrada->inicio != NULL)
        {
            if (entrada->inicio->lexema.nombre == "–size")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                tamano = atoi(entrada->inicio->lexema.nombre.c_str());
            }else if (entrada->inicio->lexema.nombre == "-size")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                tamano = atoi(entrada->inicio->lexema.nombre.c_str());
            }else if (entrada->inicio->lexema.nombre == "–u")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                u = entrada->inicio->lexema.nombre.at(0);
            }else if (entrada->inicio->lexema.nombre == "-u")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                u = entrada->inicio->lexema.nombre.at(0);
            }else if (entrada->inicio->lexema.nombre == "–path")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                path = entrada->inicio->lexema.nombre;
            }else if (entrada->inicio->lexema.nombre == "-path")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                path = entrada->inicio->lexema.nombre;
            }else if (entrada->inicio->lexema.nombre == "–type")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                type = entrada->inicio->lexema.nombre.at(0);
            }else if (entrada->inicio->lexema.nombre == "-type")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                type = entrada->inicio->lexema.nombre.at(0);
            }else if (entrada->inicio->lexema.nombre == "–f")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                f = entrada->inicio->lexema.nombre.at(0);
            }else if (entrada->inicio->lexema.nombre == "-f")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                f = entrada->inicio->lexema.nombre.at(0);
            }else if (entrada->inicio->lexema.nombre == "–name")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                name = entrada->inicio->lexema.nombre;
            }else if (entrada->inicio->lexema.nombre == "-name")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                name = entrada->inicio->lexema.nombre;
            }else
            {
                error = true;
                cout << "Parametro incorrecto: "<< entrada->inicio->lexema.nombre<<endl;
            }
            entrada->inicio = entrada->inicio->sig;
        }
        if (!error)
            {
                if (tamano > 0 && path != "" && name != "")
                {
                    AdminDisk nuevo;
                    nuevo.Crear_Particion(tamano, u, path, name, type, f);
                }else
                {
                    cout << "Faltan parametros"<<endl ;
                }
                
                

            }

    }else if (comando == "mount")
    {
        string path;
        string name;
        bool error;
        entrada->inicio = entrada->inicio->sig;
        while (entrada->inicio != NULL)
        {
            if (entrada->inicio->lexema.nombre == "–name")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                name = entrada->inicio->lexema.nombre;
            }else if (entrada->inicio->lexema.nombre == "-name")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                name = entrada->inicio->lexema.nombre;
            }else if (entrada->inicio->lexema.nombre == "–path")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                path = entrada->inicio->lexema.nombre;
            }else if (entrada->inicio->lexema.nombre == "-path")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                path = entrada->inicio->lexema.nombre;
            }else
            {
                error = true;
                cout << "Parametro incorrecto: "<< entrada->inicio->lexema.nombre<<endl;
                entrada->inicio = entrada->inicio->sig->sig;
            }
            entrada->inicio = entrada->inicio->sig;
        }

        if (!error)
        {
            AdminDisk nuevo;
            nuevo.Mount(path, name);
        }
        
        
    }else if (comando == "unmount")
    {
        string id;
        bool error = false;
        entrada->inicio = entrada->inicio->sig;
        if (entrada->inicio->lexema.nombre == "–id")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                id = entrada->inicio->lexema.nombre;
            }else if (entrada->inicio->lexema.nombre == "-id")
            {
                entrada->inicio = entrada->inicio->sig->sig;
                id = entrada->inicio->lexema.nombre;
            }else
            {
                error = true;
                cout << "Parametro incorrecto: "<< entrada->inicio->lexema.nombre<<endl;
            }
        if (!error)
        {
            AdminDisk nuevo;
            nuevo.Unmount(id);
        }
        
    }
    
    
    
    
}

#endif