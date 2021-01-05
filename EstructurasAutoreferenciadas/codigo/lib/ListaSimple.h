/*
 * ListaSimple.h
 *
 *  Created on: 5 nov. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_LISTASIMPLE_H_
#define CODIGO_LIB_LISTASIMPLE_H_


#include "NodoSimple.h"

class ListaSimple{
	private:
		NodoSimple* primero;
		NodoSimple* ultimo;
	public:
		ListaSimple();
		void insertar(int dato);
		void recorrer();
		int atender(int dato);
		~ListaSimple();
};

#endif /* CODIGO_LIB_LISTASIMPLE_H_ */
