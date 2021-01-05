/*
 * lib.h
 *
 *  Created on: 5 sep. 2020
 *      Author: PACugliari
 */

#ifndef CODIGO_LIB_LIBALUMNOS_H_
#define CODIGO_LIB_LIBALUMNOS_H_

#include "../lib/lib.h"

//RUTA ARCHIVOS
#define ALUMNOS "codigo/archivos/alumnos.dat"
#define ALUMNOS_H "codigo/archivos/alumnosHistorico.dat"
#define ALUMNOS_A "codigo/archivos/alumnosAux.dat"


//REGISTRO ALUMNOS
typedef struct {
	int legajo;
	char apellido[30];
	char nombre[30];
	long fecha;//FORMATO FECHA ANIO-MES-DIA EJ: 20200905
	int idCarrera;
	char b;//FLAG ESTADO, A = ALTA , B = BAJA LOGICA, R = RECUPERADO
}alumnos_t;

typedef enum{
	errorIdCarrera = -1
}errores_t;


//ALUMNOS
void alumnos(void);

//INTERFACE
int pedirLegajo(void);
void mensajeAlta(void);
void mensajeBaja(void);
alumnos_t pedirDatos(alumnos_t);
void imprimirTitulo();
void imprimirAlumno(alumnos_t);
void mensajeNoExiste(void);
void mensajeRecuperacion(void);
int menu(void);

//LOGICA
void alta(void);
void baja(void);
void bajaFisica(void);
void consulta(void);
void listar(void);
void listarHistorico(void);
void modificar(void);
void recuperacion(void);
alumnos_t buscarClave (FILE*,int);

#endif /* CODIGO_LIB_LIBALUMNOS_H_ */
