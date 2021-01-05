/*
 * libEspecialidad.h
 *
 *  Created on: 7 sep. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_LIBESPECIALIDAD_H_
#define CODIGO_LIB_LIBESPECIALIDAD_H_

#include "../lib/lib.h"

//RUTA ARCHIVOS ESPECIALIDAD
#define ESPECIALIDAD "codigo/archivos/especialidad.dat"

//REGISTRO ESPECIALIDAD
typedef struct{
	int idEspecialidad;
	char especialidad[20];
	char b;//FLAG ESTADO, A = ALTA , B = BAJA
}especialidad_t;


//ESPECIALIDADES
void especialidades(void);
especialidad_t consultaEspecialidad(int);


#endif /* CODIGO_LIB_LIBESPECIALIDAD_H_ */
