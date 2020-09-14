/*
 * ABM.h
 *
 *  Created on: 29 jun. 2020
 *      Author: PACug
 */

#ifndef ARCHIVOSECUENCIALES_ABM_H_
#define ARCHIVOSECUENCIALES_ABM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define DIR_ARCH "archivos/archivosSecuenciales/alumnos.dat"
#define DIR_COPIA "archivos/archivosSecuenciales/alumnosCopia.dat"
#define DIR_HISTORICO "archivos/archivosSecuenciales/alumnosHistorico.dat"

typedef struct{
	int id;//CLAVE PRIMARIA
	char nombre[20];
	char apellido [20];
	char b;//INDICA ESTADO,BAJA,ALTA
}alumno_t;


void archivoSecuencial();

#endif /* ARCHIVOSECUENCIALES_ABM_H_ */
