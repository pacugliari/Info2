/*
 * ListaSimple.cpp
 *
 *  Created on: 5 nov. 2020
 *      Author: PACugliari
 */


#include "../lib/ListaSimple.h"

ListaSimple::ListaSimple(){
	this->primero = this->ultimo = NULL;
}

void ListaSimple::insertar(int dato){
	NodoSimple* aux = new NodoSimple(dato);
	NodoSimple* cursor;
	NodoSimple* anterior;

	if(!this->primero){//LISTA VACIA
		this->primero=this->ultimo=aux;
		aux->siguiente = NULL;
	}else{
		anterior = cursor = this->primero;
		while(cursor && cursor->dato < aux->dato){//MENOR A MAYOR
			anterior = cursor;
			cursor = cursor->siguiente;
		}
		if (cursor==this->primero){//PRINCIPIO LISTA
			aux->siguiente = this->primero;
			this->primero = aux;
		}else if (!cursor){//FINAL DE LISTA
			this->ultimo->siguiente = aux;
			aux->siguiente = NULL;
			this->ultimo = aux;
		}else{ // MEDIO
			aux->siguiente = anterior->siguiente;
			anterior->siguiente = aux;
		}
	}
}

void ListaSimple::recorrer(){
	NodoSimple* aux = this->primero;
	while(aux){
		cout << aux->dato <<" ";
		aux = aux->siguiente;
	}
}

ListaSimple::~ListaSimple(){
	NodoSimple* aux = this->primero;
	int contador = 0;
	while(this->primero){
		aux = this->primero;
		this->primero = this->primero->siguiente;
		delete(aux);
		contador++;
	}
	cout<< "Bloques liberados " << contador << endl;
}

int ListaSimple::atender(int dato){
	NodoSimple* aux;
	NodoSimple* cursor;
	NodoSimple* anterior;
	int retorno = 0;
	if(this->primero){
		anterior = cursor = this->primero;
		while(cursor->siguiente && cursor->dato != dato){//MENOR A MAYOR
			anterior = cursor;
			cursor = cursor->siguiente;
		}
		if (cursor->dato == dato){
			if (cursor==this->primero){//PRINCIPIO LISTA
				aux = cursor;
				this->primero = cursor->siguiente;
			}else if (!cursor){//FINAL DE LISTA
				anterior->siguiente = NULL;
				aux = this->ultimo;
				this->ultimo = anterior;
			}else{ // MEDIO
				aux = cursor;
				anterior->siguiente = cursor->siguiente;
			}
			retorno = aux->dato;
			delete aux;
		}else{
			//cout << "Dato no encontrado, retorno = 0"<< endl;
			retorno = -1;
		}
	}else{
		cout<< "Lista vacia, retorno= 0" << endl;
	}

	return retorno;
}
