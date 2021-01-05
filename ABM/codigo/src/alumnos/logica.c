/*
 * logica.c
 *
 *  Created on: 6 sep. 2020
 *      Author: PACugliari
 */

#include "../../lib/libAlumnos.h"

alumnos_t buscarClave (FILE* archivo,int legajo){
	alumnos_t alumno;

	fread(&alumno,sizeof(alumno),1,archivo);
	while(!feof(archivo)){
		if (alumno.legajo == legajo && alumno.b != 'R'){
			return alumno;
		}
		fread(&alumno,sizeof(alumno),1,archivo);
	}
	alumno.b = 'N'; //NO ENCONTRADO
	return alumno;
}



void alta(void){
	FILE* archivo = fopen(ALUMNOS,"rb+");//VERIFICACION QUE EXISTA
	FILE* historico = fopen(ALUMNOS_H,"rb");

	if (archivo==NULL){
		archivo = fopen(ALUMNOS,"wb+");//SI NO EXISTE LO CREA
		if (archivo == NULL){
			printf ("Error en la creacion del archivo %s \n",ALUMNOS);
			return;
		}
	}

	int legajo = pedirLegajo();
	//VERIFICO QUE NO EXISTA EN ALUMNOS
	alumnos_t alumno; alumno = buscarClave(archivo,legajo);
	if (alumno.b == 'A'){
		mensajeAlta();
	}else if (alumno.b == 'B'){
		mensajeBaja();
	}else{
		//VERIFICO QUE NO EXISTA EN EL HISTORICO
		alumno.b = 'N';
		if (historico != NULL){
			alumno = buscarClave (historico,legajo);
		}
		if (alumno.b == 'B'){
			mensajeBaja();
		}else{
			alumno.legajo = legajo;
			alumno = pedirDatos (alumno);
			if (alumno.idCarrera == errorIdCarrera){
				return;
			}
			alumno.b = 'A';
			fwrite(&alumno,sizeof(alumno),1,archivo);
		}
	}

	fclose(archivo);
	fclose(historico);
}


void modificar(void){
	FILE* archivo = fopen(ALUMNOS,"rb+");
	FILE* historico = fopen(ALUMNOS_H,"rb");

	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",ALUMNOS);
		return;
	}

	int legajo = pedirLegajo();
	alumnos_t alumno = buscarClave (archivo,legajo);
	char respuesta;

	if (alumno.b == 'A'){
		imprimirTitulo();
		imprimirAlumno (alumno);
		do{
			printf ("Seguro que desea modificar el alumno ? Y/N \n");
			fflush(stdin);
			scanf("%c",&respuesta);
		}while (respuesta !='Y' && respuesta !='N');
		if (respuesta=='Y'){
			alumno = pedirDatos (alumno);
			if (alumno.idCarrera == errorIdCarrera){
				return;
			}
			fseek(archivo,(-1L)*(long)sizeof(alumno),SEEK_CUR);
			fwrite(&alumno,sizeof(alumno),1,archivo);
		}
	}else if (alumno.b == 'B'){
		mensajeBaja();
	}else{
		alumno.b = 'N';
		if (historico != NULL){
			alumno = buscarClave(historico,legajo);
		}
		if (alumno.b == 'B'){
			mensajeBaja();
		}else{
			mensajeNoExiste();
		}
	}
	fclose(archivo);
	fclose(historico);
}

void listar(void){
	imprimirTitulo();
	FILE* archivo = fopen(ALUMNOS,"rb");
	alumnos_t alumno;

	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",ALUMNOS);
		return;
	}

	fread(&alumno,sizeof(alumno),1,archivo);
	while(!feof(archivo)){
		if (alumno.b == 'A'){
			imprimirAlumno (alumno);
		}
		fread(&alumno,sizeof(alumno),1,archivo);
	}
	printf("\n");
	fclose(archivo);
}


void consulta(void){
	FILE* archivo = fopen(ALUMNOS,"rb");
	FILE* historico = fopen(ALUMNOS_H,"rb");

	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",ALUMNOS);
		return;
	}

	int legajo = pedirLegajo();
	alumnos_t alumno = buscarClave (archivo,legajo);
	if (alumno.b == 'A'){
		imprimirTitulo();
		imprimirAlumno(alumno);
		printf("\n");
	}else if (alumno.b == 'B'){
		mensajeBaja();
	}else{
		alumno.b = 'N';
		if (historico != NULL){
			alumno = buscarClave (historico,legajo);

		}
		if (alumno.b == 'B'){
			mensajeBaja();
		}else
			mensajeNoExiste();
	}
	fclose(archivo);
	fclose(historico);
}



void baja(void){
	FILE* archivo = fopen(ALUMNOS,"rb+");
	FILE* historico = fopen(ALUMNOS_H,"rb");
	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",ALUMNOS);
		return;
	}
	int legajo = pedirLegajo();
	alumnos_t alumno = buscarClave (archivo,legajo);
	char respuesta;

	if (alumno.b == 'A'){
		imprimirTitulo();
		imprimirAlumno(alumno);
		do{
			printf ("Seguro que desea dar de baja el alumno ? Y/N \n");
			fflush(stdin);
			scanf("%c",&respuesta);
		}while (respuesta !='Y' && respuesta !='N');
		if (respuesta=='Y'){
			alumno.b = 'B';
			fseek(archivo,(-1L)*(long)sizeof(alumno),SEEK_CUR);
			fwrite(&alumno,sizeof(alumno),1,archivo);
		}
	}else if (alumno.b == 'B'){
		mensajeBaja();
	}else{
		alumno.b = 'N';
		if (historico != NULL){
			alumno = buscarClave (historico,legajo);
		}
		if (alumno.b == 'B'){
			mensajeBaja();
		}else
			mensajeNoExiste();
	}
	fclose(archivo);
	fclose(historico);
}

bool_t usuarioValido(void){
	char psw [20];
	printf("Ingrese la contrasenia \n");
	scanf("%s",psw);
	if (!strcmp (psw,PSW))
		return true;
	return false;
}

void bajaFisica(void){
	FILE* archivo = fopen(ALUMNOS,"rb");
	FILE* historico = fopen(ALUMNOS_H,"ab+");
	FILE* aux = fopen (ALUMNOS_A,"w");
	alumnos_t alumno;

	//VERIFICO APERTURA DE LOS ARCHIVOS
	if (historico ==NULL){
		printf ("Error en la apertura/creacion del archivo %s \n",ALUMNOS_H);
		return;
	}
	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",ALUMNOS);
		return;
	}
	if (aux == NULL){
		printf ("Error creacion del archivo %s \n",ALUMNOS_A);
		return;
	}

	fread(&alumno,sizeof(alumno),1,archivo);
	while(!feof(archivo)){
		if (alumno.b == 'B'){
			fwrite(&alumno,sizeof(alumno),1,historico);
		}else{
			fwrite(&alumno,sizeof(alumno),1,aux);
		}
		fread(&alumno,sizeof(alumno),1,archivo);
	}
	fclose(archivo);
	fclose(aux);
	fclose(historico);
	remove(ALUMNOS);
	rename(ALUMNOS_A,ALUMNOS);
}

void listarHistorico(void){
	imprimirTitulo();
	FILE* archivo = fopen(ALUMNOS_H,"rb");
	alumnos_t alumno;

	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",ALUMNOS_H);
		return;
	}
	fread(&alumno,sizeof(alumno),1,archivo);
	while(!feof(archivo)){
		if (alumno.b != 'R'){
			imprimirAlumno(alumno);
		}
		fread(&alumno,sizeof(alumno),1,archivo);
	}
	printf("\n");
	fclose(archivo);
}

void recuperacion(void){
	FILE* archivo = fopen(ALUMNOS,"rb+");//VERIFICACION QUE EXISTA
	FILE* historico = fopen(ALUMNOS_H,"rb+");
	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s \n",ALUMNOS);
		return;
	}
	int legajo = pedirLegajo();

	//VERIFICO LA EXISTENIA EN ALUMNOS
	alumnos_t alumno = buscarClave(archivo,legajo);
	if (alumno.b == 'B'){
		alumno.b = 'A';
		fseek(archivo,(-1L)*(long)sizeof(alumno),SEEK_CUR);
		fwrite(&alumno,sizeof(alumno),1,archivo);
	}else{
		//VERIFICO LA EXISTENCIA EN HISTORICO
		alumno.b = 'N';
		if (historico != NULL){
			while (!feof(historico) && alumno.b != 'B')
				alumno = buscarClave (historico,legajo);
		}
		if (alumno.b == 'B'){
			alumno.b = 'R';
			fseek(historico,(-1L)*(long)sizeof(alumno),SEEK_CUR);
			fwrite(&alumno,sizeof(alumno),1,historico);
			alumno.b = 'A';
			fseek(archivo,(long)sizeof(alumno),SEEK_END);
			fwrite(&alumno,sizeof(alumno),1,archivo);
		}else{
			mensajeRecuperacion();
		}
	}
	fclose(archivo);
	fclose(historico);
}
