/*
 * ColaSimple.h
 *
 *  Created on: 5 nov. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_COLASIMPLE_H_
#define CODIGO_LIB_COLASIMPLE_H_

#include "NodoSimple.h"

class ColaSimple{
private:
	NodoSimple* primero;
	NodoSimple* ultimo;
public:
	ColaSimple();
	void acolar(int dato);
	int desacolar();
	void recorrer();
	~ColaSimple();
};

#endif /* CODIGO_LIB_COLASIMPLE_H_ */
