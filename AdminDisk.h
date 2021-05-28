#ifndef ADMINDISK_H
#define ADMINDISK_H
#include "Global.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


class AdminDisk
{
private:
    /* data */
public:
    AdminDisk(/* args */);
    ~AdminDisk();
    void Crear(int tamano, string f, char u, string direccion);
    void Eliminar(string direccion);
    void Crear_Particion(int tamano, char u, string path, string nombre, char type , char f);
    void Mount(string path, string name);
    void Unmount(string id);
    void MKFS(string id);
};

AdminDisk::AdminDisk(/* args */)
{
}

AdminDisk::~AdminDisk()
{
}

void AdminDisk::Crear(int tamano, string f, char u, string direccion){
    int fin;
    bool nom = false;
    string carpeta = "mkdir -p ";
    string nuevoDirec;
    for (int i = direccion.size()-1; i >= 0; i--)
    {
        if (direccion[i] == '\"' && nom == false)
        {
            nom = true;
        }
        
        if (direccion[i] == '/')
        {
            fin = i;
            break;
        }
        
    }
    for (int i = 0; i < fin; i++)
    {
        carpeta += direccion[i];
    }
    if (nom)
    {
        carpeta += "\"";
        for (int i = 1; i < direccion.size()-1; i++)
        {
            nuevoDirec += direccion[i];
        }
        direccion = nuevoDirec;
    }
    
    
    system(carpeta.c_str());

    FILE * file1= fopen(direccion.c_str(), "w+b");
    time_t t;
    struct tm *tm;
    char Fecha[20];

    t = time(NULL);
    tm = localtime(&t);
    strftime(Fecha, 20, "%Y/%m/%d %H:%M:%S", tm);

    MBR *mbr = new MBR;
    mbr->tamano = tamano;
    strcpy(mbr->fecha, Fecha);
    mbr->asignature =  rand() % 100;
    mbr->fit[0] = 'f';
    mbr->particion1.start = sizeof(MBR)+1;
    if (file1 != NULL) {
            if(u == '0'){
                tamano = tamano*1024;
                mbr->tamano = tamano*1024;
                char buffer[1024];
                for(int i = 0; i<1024; i++) buffer[i]='\0';
                for( int i = 0; i < tamano; i++)
                fwrite(&buffer,1024,1,file1);
            }else if (u == 'k')
            {
                mbr->tamano = tamano*1024;
                char buffer[1024];
                for(int i = 0; i<1024; i++) buffer[i]='\0';
                for( int i = 0; i < tamano; i++)
                fwrite(&buffer,1024,1,file1);
            }else if(u == 'm')
            {
                tamano = tamano*1024;
                mbr->tamano = tamano * 1024;
                char buffer[1024];
                for(int i = 0; i<1024; i++) buffer[i]='\0';
                for( int i = 0; i < tamano; i++)
                fwrite(&buffer,1024,1,file1);
            }
        }
        fclose(file1);
            FILE * file2= fopen(direccion.c_str(), "rb+");
            if (file2 != NULL) {
                fwrite(mbr, sizeof(MBR), 1, file2);
                fclose(file2);
                }
}

void AdminDisk::Eliminar(string direccion){
    string comado = "rm " +  direccion;
    system(comado.c_str());
}

void AdminDisk::Crear_Particion(int tamano, char u, string path, string nombre, char type , char f){
    FILE *archivo = fopen(path.c_str(),"rb+");
    MBR nuevo;
    //Se lee el archivo
    fseek(archivo,0,SEEK_SET);
    fread(&nuevo, sizeof(MBR), 1, archivo);
    fclose(archivo);

    if (u == 'b')
    {
        /* code */
    }
    else if (u == 'k')
    {
        tamano *= 1024;
    }
    else if(u == 'm')
    {
        tamano *= 1024 * 1024;
    }
    else{
        tamano *= 1024;
    }

    switch (type)
    {
    case 'e':
        if (nuevo.particion4.status == 'N')
        {
            int tamano_libre = nuevo.tamano - nuevo.particion1.size - nuevo.particion2.size - nuevo.particion3.size - sizeof(MBR);
            if (tamano < tamano_libre)
            {
                for (int i = 0; i < 16; i++)
                {
                    nuevo.particion1.nombre[i] = nombre[i];
                }
                nuevo.particion1.tipe = 'E';
                nuevo.particion1.fit[0] = 'F';
                nuevo.particion1.size = tamano;
                nuevo.particion1.status = 'Y';
                nuevo.particion1.start = nuevo.tamano - tamano +1;
            }
            else
            {
                cout << "No hay espacio disponible para la particion"<<endl;
            }
            
        }
        else
        {
            cout << "No se puede crear otra particion extendida porque ya existe 1"<<endl;
        }
        
        break;
    case 'l':
        if (nuevo.particion4.status != 'N')
        {
            EBR ebr;
            fseek(archivo,nuevo.particion4.start,SEEK_SET);
            fread(&ebr, sizeof(EBR), 1, archivo);
            fclose(archivo);
        }
        else
        {
            cout << "No hay una particion Extendida para crear una particion logica." << endl;
        }
        

        break;
    default:
        if (nuevo.particion1.status == 'N')
        {
            int tamano_libre = nuevo.tamano - sizeof(MBR);
            if (tamano < tamano_libre)
            {
                for (int i = 0; i < 16; i++)
                {
                    nuevo.particion1.nombre[i] = nombre[i];
                }

                nuevo.particion1.tipe = 'P';
                nuevo.particion1.fit[0] = 'F';
                nuevo.particion1.size = tamano;
                nuevo.particion1.status = 'Y';
                nuevo.particion1.start = sizeof(MBR)+1;
            }else{
                cout << "No hay suficiente espacio para crear la particion" << endl;
            }
            
            
        }
        else if (nuevo.particion2.status == 'N')
        {
            int tamano_Libre = nuevo.tamano - nuevo.particion1.start+nuevo.particion1.size-1;
            if (tamano < tamano_Libre)
            {
                for (int i = 0; i < 16; i++)
                {
                    nuevo.particion2.nombre[i] = nombre[i];
                }

                nuevo.particion2.tipe = 'P';
                nuevo.particion2.fit[0] = 'F';
                nuevo.particion2.size = tamano;
                nuevo.particion2.status = 'Y';
                nuevo.particion2.start = nuevo.particion1.start+nuevo.particion1.size+1;
            }else{
                cout << "No hay suficiente espacio para crear la particion" << endl;
            }
            
        }
        else if (nuevo.particion3.status == 'N')
        {
            int tamano_Libre = nuevo.tamano - (nuevo.particion2.start+nuevo.particion1.size+nuevo.particion4.size)-2;
            if (tamano < tamano_Libre)
            {
                for (int i = 0; i < 16; i++)
                {
                    nuevo.particion3.nombre[i] = nombre[i];
                }

                nuevo.particion3.tipe = 'P';
                nuevo.particion3.fit[0] = 'F';
                nuevo.particion3.size = tamano;
                nuevo.particion3.status = 'Y';
                nuevo.particion3.start = nuevo.particion2.start+nuevo.particion3.size+1;
            }else{
                cout << "No hay suficiente espacio para crear la particion" << endl;
            }
        }else{
            cout << "Se alcanzo el maximo de particiones" << endl;
        }
        

        break;
    }


    
    //Se Sobre escribe el MBR
    archivo = fopen(path.c_str(),"r+b");
    fseek(archivo,0,SEEK_SET);
    fwrite(&nuevo, sizeof(MBR), 1, archivo);
    fclose(archivo);

    //Se corrobora que se haya echo el cambio
    archivo = fopen(path.c_str(),"rb+");
    fseek(archivo,0,SEEK_SET);
    fread(&nuevo, sizeof(MBR), 1, archivo);
    fclose(archivo);
    
}

void AdminDisk::Mount(string path, string name){
    FILE *archivo = fopen(path.c_str(),"rb+");
    MBR nuevo;
    bool encontrado = false;
    string id = "03";
    //Se lee el archivo
    /*
    fseek(archivo,0,SEEK_SET);
    fread(&nuevo, sizeof(MBR), 1, archivo);
    fclose(archivo);
    */
   if (archivo != NULL)
   {
       int pos = 0;
        for (int i = 0; i < 26; i++)
        {
            if (discos[i].path == path)
            {
                pos = i;
                encontrado = true;
                break;
            }
        }
        if (encontrado)
        {
            for (int i = 0; i < 50; i++)
            {
                if (discos[pos].particon_montad[i].nombre == "")
                {
                    id = id + std::to_string(discos[pos].num) + letras[i];
                    ParticionM montado;
                    
                    discos[pos].particon_montad[i].id = id;
                    discos[pos].particon_montad[i].nombre = name;
                    break;
                }
                
            }
            
        }
        else
        {
            for (int i = 0; i < 26; i++)
            {
                if (discos[i].path == "")
                {
                    pos = i;
                }
            }
            discos[pos].path = path;
            discos[pos].num = pos +1 ;
            for (int i = 0; i < 50; i++)
            {
                if (discos[pos].particon_montad[i].id == "")
                {
                    id = id + std::to_string(discos[pos].num) + letras[i];
                    ParticionM montado;
                    discos[pos].particon_montad[i].id = id;
                    discos[pos].particon_montad[i].nombre = name;
                    break;
                }
                
            }
        }
        

   }else
   {
       cout << "No exite el disco solicitado" << endl;
   }
    fclose(archivo);
    cout <<"id: "<<id<<" nombre: "<<name<<endl;
}

void AdminDisk::Unmount(string id){
    for (int i = 0 ; i < 26; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (discos[i].particon_montad[j].id == id)
            {
                ParticionM nuevo;
                discos[i].particon_montad[j] = nuevo;
            }
            
        }
        
    }
    
}

void AdminDisk::MKFS(string id){

}

#endif
