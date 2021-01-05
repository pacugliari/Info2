/*
 * colaSimple.cpp
 *
 *  Created on: 5 nov. 2020
 *      Author: PACugliari
 */


#include "../lib/ColaSimple.h"

ColaSimple::ColaSimple(){
	this->primero = this->ultimo = NULL;
}

void ColaSimple::acolar(int dato){
	NodoSimple* aux = new NodoSimple(dato);

	if(!this->primero){//COLA VACIA
		this->primero=aux;
	}else{
		this->ultimo->siguiente=aux;
	}
	aux->siguiente=NULL;
	this->ultimo= aux;
}

int ColaSimple::desacolar(){
	NodoSimple* aux;
	int retorno = 0;
	if(this->primero){
		aux= this->primero;
		this->primero = this->primero->siguiente;
		retorno = aux->dato;
		delete(aux);
	}else{
		cout << "Cola vacia, retorno = 0 " << endl;
	}
	return retorno;
}

void ColaSimple::recorrer(){
	NodoSimple* aux = this->primero;
	while(aux){
		cout << aux->dato <<" ";
		aux = aux->siguiente;
	}
}

ColaSimple::~ColaSimple(){
	NodoSimple* aux;
	int contador=0;
	while(this->primero){
		aux = this->primero;
		this->primero = this->primero->siguiente;
		delete(aux);
		contador++;
	}
	cout << "Bloques liberados " << contador << endl;
}
