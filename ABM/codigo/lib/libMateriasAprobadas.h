/*
 * libMateriasAprobadas.h
 *
 *  Created on: 8 sep. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_LIBMATERIASAPROBADAS_H_
#define CODIGO_LIB_LIBMATERIASAPROBADAS_H_

#include "../lib/lib.h"

//RUTA ARCHIVOS
#define MAT_AP "codigo/archivos/materiasAprobadas.dat"
#define MAT_AP_H "codigo/archivos/materiasAprobadasHistorico.dat"
#define MAT_AP_A "codigo/archivos/materiasAprobadasAux.dat"


//REGISTRO ALUMNOS
typedef struct {
	int legajo;
	int idMateria;
	int nota;
	long fecha;//FORMATO FECHA ANIO-MES-DIA EJ: 20200905
	char b;//FLAG ESTADO, A = ALTA , B = BAJA LOGICA, R = RECUPERADO
}materiaAprobada_t;

void materiasAprobadas(void);

#endif /* CODIGO_LIB_LIBMATERIASAPROBADAS_H_ */
