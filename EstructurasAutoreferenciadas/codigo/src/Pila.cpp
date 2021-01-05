/*
 * Pila.cpp
 *
 *  Created on: 5 nov. 2020
 *      Author: PACugliari
 */

#include "../lib/Pila.h"

void Pila::apilar(int dato){
	NodoSimple* aux = new NodoSimple(dato);
	if(!this->primero){//PILA VACIA
		aux->siguiente = NULL;
	}else{
		aux->siguiente = this->primero;
	}
	this->primero = aux;
}

int Pila::desapilar(){
	NodoSimple* aux;
	int retorno = 0;
	if (this->primero){
		aux = this->primero;
		this->primero = this->primero->siguiente;
		retorno = aux->dato;
		delete(aux);
	}else{
		cout << "Pila vacia, retorno = 0" << endl;
	}
	return retorno;
}

void Pila::recorrer(){
	NodoSimple* aux=this->primero;
	while(aux){
		cout << aux->dato <<" ";
		aux = aux->siguiente;
	}
}

Pila::~Pila(){
	int contador=0;
	NodoSimple* aux;
	while(this->primero){
		aux = this->primero;
		this->primero= this->primero->siguiente;
		delete(aux);
		contador++;
	}
	cout << "Bloques liberados " << contador << endl;
}
