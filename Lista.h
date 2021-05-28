#ifndef LISTA_h
#define LISTA_H
#include "Global.h"

class Lista
{
private:
public:
    Nodo *inicio ;
    Lista();
    ~Lista();
    void Insertar(Token ent);
    void Imprimir();
    Nodo* Tokens();
    bool Buscar(string texto);
    void Limpiar();
};

Lista::Lista(/* args */)
{
    inicio = NULL;
}

Lista::~Lista()
{
}

void Lista::Limpiar(){
    inicio = NULL;
}

Nodo* Lista::Tokens(){
    return inicio;
}

void Lista::Insertar(Token ent){
    Token nu;
    nu = ent;
        Nodo *nuevo = new Nodo;
        nuevo->lexema = nu;
        if(inicio == NULL){
                inicio = nuevo;
        }else{
                Nodo *aux = (inicio);
                while(aux->sig != NULL){
                        aux = aux->sig;
                }
                aux->sig = nuevo;
        }
}

void Lista::Imprimir(){
    if (inicio == NULL)
    {
        cout <<"La lista esta vacia"<<endl;
    }else{
        Nodo *aux = (inicio);
        while(aux != NULL){
                cout << "Nombre: " <<aux->lexema.nombre<< " Numero: " <<  aux->lexema.numero <<endl;
                aux = aux->sig;
            }
    }
    
}

bool Lista::Buscar(string texto){
    bool estado = false;
    if (inicio == NULL)
    {
        cout <<"La lista esta vacia"<<endl;
    }else{
        Nodo *aux = (inicio);
        while(aux != NULL){
                if (aux->lexema.nombre == texto)
                {
                   estado = true;
                   return estado;
                }
                
                aux = aux->sig;
            }
    }
    return estado;
}


#endif