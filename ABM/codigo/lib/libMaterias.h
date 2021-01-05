/*
 * libMaterias.h
 *
 *  Created on: 8 sep. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_LIBMATERIAS_H_
#define CODIGO_LIB_LIBMATERIAS_H_

#include "../lib/lib.h"

//RUTA ARCHIVOS MATERIAS
#define MATERIAS "codigo/archivos/materias.dat"

//REGISTRO ESPECIALIDAD
typedef struct{
	int idMateria;
	char materia[30];
	char b;//FLAG ESTADO, A = ALTA , B = BAJA
}materia_t;


//ESPECIALIDADES
void materias(void);
materia_t consultaMateria(int);
int ingreseIdMateria(void);

#endif /* CODIGO_LIB_LIBMATERIAS_H_ */
