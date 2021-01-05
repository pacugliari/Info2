/*
 * main.cpp
 *
 *  Created on: 5 nov. 2020
 *      Author: PACugliari
 */


#include <iostream>
#include "../lib/Pila.h"
#include "../lib/ColaSimple.h"
#include "../lib/ListaSimple.h"

int main(){

	Pila pila;
	//APILO
	for(int i=0;i<10;i++){
		pila.apilar(i+1);
	}
	cout << "PILA"<< endl;
	//RECORRO
	pila.recorrer();
	cout << endl;
	//DESAPILO
	for(int i=0;i<10;i++){
		cout << pila.desapilar() <<" ";
	}
	cout << endl;

	ColaSimple cola;
	//ACOLO
	for(int i=0;i<10;i++){
		cola.acolar(i+1);
	}
	cout << "COLA "<<endl;
	//RECORRO
	cola.recorrer();
	cout << endl;
	//DESACOLO
	for(int i=0;i<10;i++){
		cout << cola.desacolar() <<" ";
	}
	cout << endl;



	cout << "LISTA "<<endl;
	ListaSimple lista;
	//INSERTO
	int valor;
	for(int i=0;i<10;i++){
		valor = (int)rand()%(10)+1;
		cout << valor << " ";
		lista.insertar(valor);
	}
	cout << endl;
	//RECORRO
	lista.recorrer();
	cout << endl;

    //ATIENDO
	for(int i=0;i<10;i++){
		cout << lista.atender(i+1) << " ";
	}
	cout << endl;
	lista.recorrer();
	cout << endl;

	return 0;
}
