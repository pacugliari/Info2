/*
 * lib.h
 *
 *  Created on: 7 sep. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_LIB_H_
#define CODIGO_LIB_LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PSW "1234" //CONTRASENIA PARA LAS FUNCIONES ESPECIALES DE ABM


typedef enum {
	true =1,
	false =0
}bool_t;


bool_t usuarioValido(void);

#endif /* CODIGO_LIB_LIB_H_ */
