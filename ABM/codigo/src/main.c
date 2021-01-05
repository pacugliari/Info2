/*
 * main.c
 *
 *  Created on: 5 sep. 2020
 *      Author: PACugliari
 */

#include "../lib/libAlumnos.h"
#include "../lib/libMaterias.h"
#include "../lib/libEspecialidad.h"
#include "../lib/lib.h"

int menuInicio(void){
	int respuesta;
	printf ("\n***INICIO***\n\n");
	printf("1) ABM ALUMNOS\n");//LISTO
	printf("2) ABM ESPECIALIDADES\n");//LISTO
	printf("3) ABM MATERIAS\n");//LISTO
	printf("4) ABM MATERIAS APROBADAS\n");//LISTO

	printf("\n0) SALIR \n");
	scanf("%d",&respuesta);
	fflush(stdin);
	return respuesta;
}

int main(){
	bool_t salir = false;
	setvbuf(stdout, NULL, _IONBF, 0);//AGREGADO PARA EVITAR BUG CONSOLA ECLIPSE

	do{
				switch(menuInicio()){
					case 1:
						alumnos();
					break;
					case 2:
						especialidades();
					break;
					case 3:
						materias();
					break;
					case 4:
						materiasAprobadas();
					break;
					case 0:
						salir= true;
					break;
					default:
						printf("Opcion de menu invalida \n");
					break;
				}
			}while(!salir);
	return 0;
}
