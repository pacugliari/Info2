/*
 * alumnos.c
 *
 *  Created on: 5 sep. 2020
 *      Author: PACugliari
 *
 *      ARCHIVO SECUENCIAL
 */
#include "../../lib/libAlumnos.h"

void alumnos(void){
	do{
		switch(menu()){
			case 1:
				alta();
			break;
			case 2:
				modificar();
			break;
			case 3:
				consulta();
			break;
			case 4:
				baja();
			break;
			case 5:
				listar();
			break;
			case 6:
				if (usuarioValido())
					recuperacion();
			break;
			case 7:
				if (usuarioValido())
					bajaFisica();
			break;
			case 8:
				if (usuarioValido())
					listarHistorico();
			break;
			case 0:
				return;
			break;
			default:
				printf("Opcion de menu invalida \n");
			break;
		}
	}while(1);

}
