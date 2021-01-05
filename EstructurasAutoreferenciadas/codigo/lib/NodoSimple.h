/*
 * NodoSimple.h
 *
 *  Created on: 5 nov. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_NODOSIMPLE_H_
#define CODIGO_LIB_NODOSIMPLE_H_

#include <iostream>
using namespace std;

class NodoSimple{
	public:
		NodoSimple(int dato);
		int dato;
		NodoSimple* siguiente;
};

#endif /* CODIGO_LIB_NODOSIMPLE_H_ */
