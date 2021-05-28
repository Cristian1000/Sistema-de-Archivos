#ifndef GRAFICA_H
#define GRAFICA_H
#include "Global.h"
#include <fstream>


class Graficar
{
private:
    /* data */
    
public:
    Graficar(/* args */);
    ~Graficar();
    void Graficar_MBR(string name, string path, string id);
    void Graficar_Disco(string name, string path, string id);
};

Graficar::Graficar(/* args */)
{
}

Graficar::~Graficar()
{
}

void Graficar::Graficar_MBR(string name, string path, string id){
    int dis;
    int par;
    bool encontrado = false;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if(discos[i].particon_montad[j].id == id){
                dis = i;
                par = j,
                encontrado = true;
                break;
            }
        }
        
    }
    
    
    if (encontrado)
    {
        string direccion = discos[dis].path;
        string nombre ="";
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
            nombre += direccion[i];
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

        FILE *archivo = fopen(discos[dis].path.c_str(),"rb+");
        MBR nuevo;
        fseek(archivo,0,SEEK_SET);
        fread(&nuevo, sizeof(MBR), 1, archivo);
        fclose(archivo);
        string fecha;
        for (int i = 0; i < 20; i++)
        {
            fecha += nuevo.fecha[i];
        }
        string nombre1;
        for (int i = 0; i < 16; i++)
        {
            nombre1 += nuevo.particion1.nombre[i];
        }
        string nombre2;
        for (int i = 0; i < 16; i++)
        {
            nombre2 += nuevo.particion2.nombre[i];
        }

        string archivo_dot= nombre + "/reporte1.dot";
        ofstream dot(archivo_dot);        
        
        dot<< "digraph D {\n node [fontname=\"Arial\", shape = record];"<<endl;
        dot<<" node_A [label=\"{"<<endl;
        dot<<"Nombre|"<<endl;
        dot<<"Tamano|"<<endl;
        dot<<"Fecha|"<<endl;
        dot<<"Asignature|"<<endl;
        dot<<"Fit|"<<endl;
        dot<<"Particion1_Status|"<<endl;
        dot<<"Particion1_Type|"<<endl;
        dot<<"Particion1_Fit|"<<endl;
        dot<<"Particion1_Start|"<<endl;
        dot<<"Particion1_Size|"<<endl;
        dot<<"Particion1_Nombre|"<<endl;
        dot<<"Particion2_Satus|"<<endl;
        dot<<"Particion2_Type|"<<endl;
        dot<<"Particion2_Fit|"<<endl;
        dot<<"Particion2_Start|"<<endl;
        dot<<"Particion2_Size|"<<endl;
        dot<<"Particion2_Nombre}|"<<endl;
        dot<<"{Valor|"<<endl;
        dot<<""<<to_string(nuevo.tamano)<<"|"<<endl;
        dot<<fecha<<"|"<<endl;
        dot<<""<<to_string(nuevo.asignature)<<"|"<<endl;
        dot<<""<<to_string(nuevo.fit[0])<<"|"<<endl;
        dot<<""<<to_string(nuevo.particion1.status)<<"|"<<endl;
        dot<<""<<to_string(nuevo.particion1.tipe)<<"|"<<endl;
        dot<<""<<to_string(nuevo.particion1.fit[0])<<"|"<<endl;
        dot<<""<<to_string(nuevo.particion1.start)<<"|"<<endl;
        dot<<""<<to_string(nuevo.particion1.size)<<"|"<<endl;
        dot<<""<<nombre1<<"|"<<endl;
        dot<<""<<to_string(nuevo.particion2.status)<<"|"<<endl;
        dot<<""<<to_string(nuevo.particion2.tipe)<<"|"<<endl;
        dot<<""<<to_string(nuevo.particion2.fit[0])<<"|"<<endl;
        dot<<""<<to_string(nuevo.particion2.start)<<"|"<<endl;
        dot<<""<<to_string(nuevo.particion2.size)<<"|"<<endl;
        dot<<""<<nombre2<<"}\"];\n}"<<endl;

        dot.close();
        string generar = "dot -Tpdf "+nombre+"/reporte1.dot -o "+nombre+"/reporte1.pdf";
        system(generar.c_str());

    }else
    {
        cout << "particion no encontrada"<<endl;
    }

}

void Graficar::Graficar_Disco(string name, string path, string id){
    
    int dis;
    int par;
    bool encontrado = false;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if(discos[i].particon_montad[j].id == id){
                dis = i;
                par = j,
                encontrado = true;
                break;
            }
        }
        
    }
    if (encontrado)
    {
        string direccion = discos[dis].path;
        string nombre ="";
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
            nombre += direccion[i];
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

        FILE *archivo = fopen(discos[dis].path.c_str(),"rb+");
        MBR nuevo;
        fseek(archivo,0,SEEK_SET);
        fread(&nuevo, sizeof(MBR), 1, archivo);
        fclose(archivo);
        string tmano1 = "Libre";
        string tmano2 = "Libre";
        string tmano3 = "Libre";
        string tmano4 = "Libre";

        if (nuevo.particion1.size > 0)
        {
            float p1 = ((float)nuevo.particion1.size/(float)nuevo.tamano)*100;
            tmano1 = to_string(p1)+"%";
        }
        if (nuevo.particion2.size > 0)
        {
            float p2 = ((float)nuevo.particion2.size/(float)nuevo.tamano)*100;
            tmano2 = to_string(p2)+"%";
        }
        if (nuevo.particion3.size > 0)
        {
            float p3 = ((float)nuevo.particion3.size/(float)nuevo.tamano)*100;
            tmano3 = to_string(p3)+"%";
        }
        if (nuevo.particion4.size > 0)
        {
            float p4 = ((float)nuevo.particion4.size/(float)nuevo.tamano)*100;
            tmano4 = to_string(p4)+"%";
        }
        string archivo_dot= nombre + "/reporte2.dot";
        ofstream dot(archivo_dot);
        
        dot << "digraph {\n  tbl [\n shape=plaintext\n label=<"<<endl;
        dot<< "<table border='0' cellborder='1' color='blue' cellspacing='0'>\n"<<endl;
        dot<<"<tr><td>MBR</td><td>Particion 1 </td><td>Particion 2</td><td>Particion 3</td><td>Particion 4 E</td></tr>\n"<<endl;
        dot<<"<tr><td cellpadding='1'>\n <table color='black' cellspacing='0'>\n"<<endl;
        dot<<"<tr><td>MBR </td></tr>\n</table>\n";
        dot<<"</td>\n<td cellpadding='1'>\n<table color='black' cellspacing='0'>\n"<<endl;
        dot<<"<tr><td>"+tmano1+"</td></tr>\n"<<endl;
        dot<<"</table>\n</td>\n"<<endl;
        dot<<"<td cellpadding='1'>\n<table color='black' cellspacing='0'>\n"<<endl;
        dot<<"<tr><td>"+tmano2+"</td></tr>\n"<<endl;
        dot<<"</table>\n </td>"<<endl;
        dot<<"<td cellpadding='1'>\n<table color='black' cellspacing='0'>\n"<<endl;
        dot<<"<tr><td>"+tmano3+"</td></tr>\n"<<endl;
        dot<<"</table>\n </td>"<<endl;
        dot<<"<td cellpadding='1'>\n<table color='black' cellspacing='0'>\n"<<endl;
        dot<<"<tr><td>"+tmano4+"</td></tr>\n"<<endl;
        dot<<"</table>\n </td>\n"<<endl;
        dot<<"</tr>\n</table>\n>];\n}"<<endl;

        dot.close();
    
    string generar = "dot -Tpdf "+nombre+"/reporte2.dot -o "+nombre+"/reporte2.pdf";
    system(generar.c_str());
    
}
}

#endif