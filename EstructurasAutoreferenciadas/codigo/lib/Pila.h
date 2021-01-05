/*
 * Pila.h
 *
 *  Created on: 5 nov. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_PILA_H_
#define CODIGO_LIB_PILA_H_

#include "NodoSimple.h"


class Pila{
	private:
		NodoSimple* primero;
	public:
		Pila(){this->primero=NULL;}
		void apilar(int dato);
		int desapilar();
		void recorrer();
		~Pila();
};


#endif /* CODIGO_LIB_PILA_H_ */
