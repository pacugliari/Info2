/*
 * mensajes.c
 *
 *  Created on: 6 sep. 2020
 *      Author: PACugliari
 */


#include "../../lib/libAlumnos.h"
#include "../../lib/libEspecialidad.h"

int menu(void){
	int respuesta;
	printf ("\n***ALUMNOS***\n\n");
	printf("1) ALTA ALUMNO\n");//LISTO
	printf("2) MOFICIACION ALUMNO\n");//LISTO
	printf("3) CONSULTA ALUMNO\n");//LISTO
	printf("4) BAJA ALUMNO\n");//LISTO
	printf("5) LISTAR ALUMNOS \n\n");//LISTO

	printf("6) RECUPERACION ALUMNO\n");//LISTO
	printf("7) BAJA FISICA\n");//LISTO
	printf("8) LISTAR HISTORICO\n");//LISTO

	printf("\n0) SALIR \n");
	scanf("%d",&respuesta);
	fflush(stdin);
	return respuesta;
}

void mensajeBaja (void){
	printf("El legajo ingresado existe pero esta dado de baja \n");
}

void mensajeAlta (void){
	printf("El legajo ingresado ya existe\n");
}

void mensajeNoExiste (void){
	printf ("El legajo ingresado no existe \n");
}

void mensajeRecuperacion(void){
	printf ("Error , no existe o ya esta dado de alta el legajo \n");
}

alumnos_t pedirDatos (alumnos_t inicial){
	int id;
	printf ("Ingrese el APELLIDO \n");
	scanf("%s",inicial.apellido);
	printf ("Ingrese el NOMBRE \n");
	scanf ("%s",inicial.nombre);
	printf ("Ingrese la FECHA DE NACIMIENTO \n");
	scanf ("%ld",&inicial.fecha);
	printf ("Ingrese el ID CARRERA \n");
	scanf ("%d",&id); //VERIFICAR CON EL ARCHIVO ESPECIALIDAD CUANDO EXISTA

	if (consultaEspecialidad(id).b != 'A') {
		printf("La especialidad ingresada no existe, ingrese nuevamente \n");
		inicial.idCarrera = -1;
	}else{
		inicial.idCarrera = id;
	}
	return inicial;
}

int pedirLegajo (void){
	int legajo;
	printf ("Ingrese el LEGAJO \n");
	scanf ("%d",&legajo);
	return legajo;
}

void imprimirTitulo(void){
	printf ("***LISTADO DE ALUMNOS***\n\n");
	printf ("LEGAJO			APELLIDO			NOMBRE			FECHA NACIMIENTO		CARRERA\n");
	printf ("--------------------------------------------------------------------------------------"
			"---------------------------------\n");
}

void imprimirAlumno (alumnos_t alumno){

	printf ("%04d			%-15s			%-15s		%-ld			%d\n",alumno.legajo,alumno.apellido,
			alumno.nombre,alumno.fecha,alumno.idCarrera);
}
