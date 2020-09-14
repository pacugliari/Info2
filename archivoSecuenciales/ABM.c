#include "ABM.h"
/*
 * ABM.c
 *
 *  Created on: 29 jun. 2020
 *      Author: PACug
 *
 *      ABM (ALTA BAJA Y MODIFICACION, SISTEMA USADO EN BASE DE DATOS PARA  MANTENER ACTUALIZADO LA BASE DE DATOS)
 *      EJEMPLO DE UN ABM ALUMNOS, LEGAJO , NOMBRE,APELLIDO
 */

typedef enum{
	true = 1,
	false = 0
}bool;

alumno_t buscar (int id,FILE* archivo){
	alumno_t alumno,retorno;
	retorno.b='N';
	if (archivo != NULL){
		fread (&alumno,sizeof(alumno),1,archivo);
		while (!feof(archivo)){
			if (alumno.id == id){
				retorno = alumno;
				break;
			}
			fread (&alumno,sizeof(alumno),1,archivo);
		}
	}
	return retorno;
}

int pedirId(){
	int id;
	printf ("Ingrese el id: \n");
	scanf (" %d",&id);
	return id;
}

void alta(){
	FILE* archivo = fopen (DIR_ARCH,"ab+");
	FILE* archivoHistorico = fopen (DIR_HISTORICO,"rb");
	alumno_t alumno;
	int id;

	if (archivo==NULL){
		printf ("Error en la apertura del archivo %s \n",DIR_ARCH);
	}else{
		id = pedirId();
		alumno = buscar(id,archivo);
		if (alumno.b == 'A'){
			printf ("Error, el id ya existe y esta dado de alta \n");
		}else if (alumno.b == 'B' || buscar(id,archivoHistorico).b != 'N'){
			printf ("Error, el id ya existe y esta dado de baja \n");
		}else{
			alumno.id = id;
			printf ("Ingrese el nombre: \n");
			scanf(" %s",alumno.nombre);
			printf ("Ingrese el apellido: \n");
			scanf(" %s",alumno.apellido);
			alumno.b = 'A';
			fwrite (&alumno,sizeof(alumno),1,archivo);
			printf ("Alta realizada con exito \n");
		}
	}
	fclose (archivo);
	fclose(archivoHistorico);
}

void listar (char* direccion){
	FILE* archivo = fopen (direccion,"rb");
	alumno_t alumno;
	if (archivo==NULL){
		printf ("Error en la apertura del archivo %s \n",direccion);
	}else{
		printf ("\t*** LISTA DE ALUMNOS **** \n\n");
		if (!strcmp(direccion,DIR_ARCH)){
			printf ("ID\t\tNOMBRE\t\tAPELLIDO\n\n");
		}else{
			printf ("ID\t\tNOMBRE\t\tAPELLIDO\tESTADO\n\n");
		}
		fread (&alumno,sizeof(alumno),1,archivo);
		while (!feof(archivo)){
			if (!strcmp(direccion,DIR_ARCH)){
				if (alumno.b == 'A'){
					printf ("%d\t\t%s\t\t%s\n",alumno.id,alumno.nombre,alumno.apellido);
				}
			}else{
				printf ("%d\t\t%s\t\t%s\t\t%c\n",alumno.id,alumno.nombre,alumno.apellido,alumno.b);
			}

			fread (&alumno,sizeof(alumno),1,archivo);
		}
	}
	fclose (archivo);
}



void consulta(){
	FILE* archivo = fopen (DIR_ARCH,"rb");
	FILE* archivoHistorico = fopen (DIR_HISTORICO,"rb");
	alumno_t alumno;
	int id = pedirId();

	alumno = buscar (id,archivoHistorico);
	if (alumno.b != 'N' ){
		printf ("El ID del alumno existe pero esta dado de baja\n");
	}
	alumno = buscar (id,archivo);
	if (alumno.b == 'N' ){
		printf ("El ID del alumno no existe \n");
	}else if (alumno.b == 'A'){
		printf ("ID\t\tNOMBRE\t\tAPELLIDO\n\n");
		printf ("%d\t\t%s\t\t%s\n",alumno.id,alumno.nombre,alumno.apellido);
	}else{
		printf ("El ID del alumno existe pero esta dado de baja\n");
	}
	fclose(archivo);
	fclose (archivoHistorico);
}

void modificacion(){
	alumno_t alumno;
	int id,respuesta,retorno=false;
	id = pedirId();
	FILE* archivo = fopen (DIR_ARCH,"rb+");

	if (archivo==NULL){
		printf ("Error en la apertura del archivo %s \n",DIR_ARCH);
		return;
	}else{
		fread (&alumno,sizeof(alumno),1,archivo);
		while (!feof(archivo)){
			if (alumno.id == id){
				if (alumno.b == 'A'){
					do{
						printf ("Desea modificar el registro? 1)SI 2)NO \n");
						printf ("ID\t\tNOMBRE\t\tAPELLIDO\n\n");
						printf ("%d\t\t%s\t\t%s\n",alumno.id,alumno.nombre,alumno.apellido);
						scanf("%d",&respuesta);
						if (respuesta ==2){
							retorno=true;
							break;
						}
					}while(respuesta >2 && respuesta < 1);
					printf ("Ingrese el nuevo Nombre: \n");
					scanf ("%s",alumno.nombre);
					printf ("Ingrese el nuevo Apellido: \n");
					scanf ("%s",alumno.apellido);
					fseek (archivo,(long)((-1)*sizeof(alumno)),1);
					fwrite(&alumno,sizeof(alumno),1,archivo);
					printf ("Modificacion realizada con exito \n");
					retorno = true;
					break;
				}else{
					printf ("Error, el registro esta dado de baja \n");
				}
			}
			fread (&alumno,sizeof(alumno),1,archivo);
		}
	}
	if (retorno==false){
		printf ("Error, el ID a modificar no se encuentra \n");
	}
	fclose (archivo);
}

void bajaLogica (){
	alumno_t alumno;
	int id= pedirId();
	int respuesta,retorno=false;
	FILE* archivo = fopen (DIR_ARCH,"rb+");

	if (archivo==NULL){
		printf ("Error en la apertura del archivo %s \n",DIR_ARCH);
		return;
	}else{
		fread (&alumno,sizeof(alumno),1,archivo);
		while (!feof(archivo)){
			if (alumno.id == id){
				if (alumno.b == 'A'){
					do{
						printf ("Desea eliminar el registro? 1)SI 2)NO \n");
						printf ("ID\t\tNOMBRE\t\tAPELLIDO\n\n");
						printf ("%d\t\t%s\t\t%s\n",alumno.id,alumno.nombre,alumno.apellido);
						scanf("%d",&respuesta);
						if (respuesta ==2){
							retorno=true;
							break;
						}
					}while(respuesta >2 && respuesta < 1);
					alumno.b = 'B';
					fseek (archivo,(long)((-1)*sizeof(alumno)),1);
					fwrite(&alumno,sizeof(alumno),1,archivo);
					printf ("La baja fue dada de manera exitosa \n");
				}else{
					printf ("Error, el registro esta dado de baja \n");
				}
				retorno = true;
				break;
			}
			fread (&alumno,sizeof(alumno),1,archivo);
		}
	}
	if (retorno == false)
		printf ("Error, el ID a dar de baja no se encuentra \n");
	fclose (archivo);
}

void bajaFisica(){
	alumno_t alumno;
	FILE* archivoOriginal = fopen (DIR_ARCH,"rb");
	FILE* archivoCopia = fopen (DIR_COPIA,"wb");
	FILE* archivoHistorico = fopen (DIR_HISTORICO,"ab+");
	if (!archivoOriginal || !archivoCopia || !archivoHistorico){
		printf ("Error en la apertura/creacion de archivo en baja fisica \n");
		return;
	}else{
		fread (&alumno,sizeof(alumno),1,archivoOriginal);
		while (!feof(archivoOriginal)){
			if (alumno.b == 'A'){
				fwrite(&alumno,sizeof(alumno),1,archivoCopia);
			}else{
				fwrite(&alumno,sizeof(alumno),1,archivoHistorico);
			}
			fread (&alumno,sizeof(alumno),1,archivoOriginal);
		}
	}
	fclose (archivoOriginal);
	fclose (archivoCopia);
	fclose (archivoHistorico);
	remove (DIR_ARCH);
	rename ("archivos/archivosSecuenciales/alumnosCopia.dat",DIR_ARCH);
	printf ("Bajas fisicas realizadas con exito \n");
}

void recuperacion(){
	alumno_t alumno;
	int id= pedirId();
	int retorno = false;
	FILE* archivo = fopen (DIR_ARCH,"rb+");

	if (archivo == NULL){
		printf ("Error en la apertura del archivo \n");
		return;
	}else{
		fread (&alumno,sizeof(alumno),1,archivo);
		while(!feof(archivo)){
			if (alumno.id == id ){
				if (alumno.b == 'B'){
					alumno.b = 'A';
					fseek (archivo,(long)(-1*sizeof(alumno)),1);
					fwrite (&alumno,sizeof(alumno),1,archivo);
					printf ("Recuperacion exitosa \n");
					retorno = true;
					break;
				}
			}
			fread (&alumno,sizeof(alumno),1,archivo);
		}
		if (retorno == false){
			FILE* archivoHistorico = fopen (DIR_HISTORICO,"rb+");
			if (archivoHistorico == NULL){
				printf ("Error apertura archivo historico \n");
				return;
			}else{
				fread(&alumno,sizeof(alumno),1,archivoHistorico);
				while (!feof(archivoHistorico)){
					if (alumno.id == id){
						if (alumno.b == 'B'){
							fseek (archivoHistorico,(long)(-1*sizeof(alumno)),1);
							alumno.b = 'R';//MARCO EL REGISTRO COMO RECUPERADO
							fwrite (&alumno,sizeof(alumno),1,archivoHistorico);
							alumno.b = 'A';
							fwrite (&alumno,sizeof(alumno),1,archivo);
							printf ("Recuperacion exitosa \n");
						}else{
							printf ("Error, el ID ya fue recuperado \n");
						}
						retorno = true;
						break;
					}
					fread(&alumno,sizeof(alumno),1,archivoHistorico);
				}
				if (retorno == false)
					printf ("Error, el ID ingresado no existe en el historico \n");
			}
			fclose (archivoHistorico);
		}
	}
	fclose (archivo);
}

void archivoSecuencial(){
	int respuesta,respuestaSalir=false;
	do{
		printf ("\n1)ALTA\n2)LISTAR\n3)CONSULTA\n4)MODIFICACION\n5)BAJA\n6)SALIR\n");
		scanf (" %d",&respuesta);
		switch(respuesta){
			case 1:
				alta();
			break;
			case 2:
				listar(DIR_ARCH);
			break;
			case 3:
				consulta();
			break;
			case 4:
				modificacion();
			break;
			case 5:
				bajaLogica();
			break;
			case 6:
				respuestaSalir = true;
			break;
			case 7://MENU OCULTO DE BAJA FISICA 'B'
				bajaFisica();
			break;
			case 8://MENU OCULTO DE RECUPERACION 'R'
				recuperacion();
			break;
			case 9://LISTAR EL HISTORICO 'L'
				listar(DIR_HISTORICO);
			break;
			default:
				printf ("Ingrese una respuesta valida \n");
			break;
		}
	}while(respuestaSalir == false);
}


