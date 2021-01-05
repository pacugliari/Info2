/*
 * materiasAprobadas.c
 *
 *  Created on: 8 sep. 2020
 *      Author: PACugliari
 */

#include "../../lib/libMateriasAprobadas.h"
#include "../../lib/libAlumnos.h"
#include "../../lib/libMaterias.h"


int menuMateriaAprobada(void){
	int respuesta;
	printf ("\n***MATERIAS APROBADAS***\n\n");
	printf("1) ALTA MATERIA APROBADA\n");//LISTO
	printf("2) MOFICIACION MATERIA APROBADA\n");//LISTO
	printf("3) CONSULTA MATERIA APROBADA\n");//LISTO
	printf("4) BAJA MATERIA APROBADA\n");//LISTO
	printf("5) LISTAR MATERIAS APROBADAS \n\n");//LISTO

	printf("6) RECUPERACION MATERIA APROBADA\n");//LISTO
	printf("7) BAJA MATERIA APROBADA\n");//LISTO
	printf("8) LISTAR HISTORICO DE MATERIAS APROBADAS\n");//LISTO

	printf("\n0) SALIR \n");
	scanf("%d",&respuesta);
	fflush(stdin);
	return respuesta;
}

materiaAprobada_t pedirDatosMateria (materiaAprobada_t inicial){
	printf ("Ingrese la NOTA \n");
	scanf("%d",&inicial.nota);
	printf ("Ingrese la FECHA DE APROBACION \n");
	scanf ("%ld",&inicial.fecha);
	return inicial;
}


materiaAprobada_t buscarClaveMateria (FILE* archivo,int idMateria){
	materiaAprobada_t materia;

	fread(&materia,sizeof(materia),1,archivo);
	while(!feof(archivo)){
		if (materia.idMateria == idMateria && materia.b != 'R'){
			return materia;
		}
		fread(&materia,sizeof(materia),1,archivo);
	}
	materia.b = 'N'; //NO ENCONTRADO
	return materia;
}

void mensajeBajaMateria (void){
	printf("La materia fue aprobada pero esta dada de baja \n");
}

void mensajeAltaMateria (void){
	printf("La materia ya fue aprobada\n");
}

void altaMateriaAprobada(void){
	FILE* archivo = fopen(MAT_AP,"rb+");//VERIFICACION QUE EXISTA
	FILE* historico = fopen(MAT_AP_H,"rb");
	FILE* alumnos = fopen(ALUMNOS,"rb");
	FILE* materias = fopen (MATERIAS,"rb");
	materiaAprobada_t materiaAprobada;

	if (materias == NULL){
		printf("Error en la apertura del archivo %s, puede que no exista",MATERIAS);
		return;
	}

	if (alumnos == NULL){
		printf("Error en la apertura del archivo %s, puede que no exista",ALUMNOS);
		return;
	}

	if (archivo==NULL){
		archivo = fopen(MAT_AP,"wb+");//SI NO EXISTE LO CREA
		if (archivo == NULL){
			printf ("Error en la creacion del archivo %s \n",MAT_AP);
			return;
		}
	}

	int legajo = pedirLegajo();
	//VERIFICO QUE NO EXISTA EN ALUMNOS
	alumnos_t alumno;
	alumno = buscarClave(alumnos,legajo);

	if (alumno.b == 'N'){
		printf("Error , el legajo ingresado no existe");
	}else{
		int idMateria = ingreseIdMateria();
		materia_t materia = consultaMateria(idMateria);
		if (materia.b == 'N'){
			printf ("Error, la materia ingresada no existe");
		}else{
			materiaAprobada = buscarClaveMateria (archivo,idMateria);
			if (materiaAprobada.b == 'A'){
					mensajeAltaMateria();
				}else if (materiaAprobada.b == 'B'){
					mensajeBajaMateria();
				}else{
					//VERIFICO QUE NO EXISTA EN EL HISTORICO
					materiaAprobada.b = 'N';
					if (historico != NULL){
						materiaAprobada = buscarClaveMateria (historico,idMateria);
					}
					if (materiaAprobada.b == 'B'){
						mensajeBajaMateria();
					}else{
						materiaAprobada.legajo = legajo;
						materiaAprobada.idMateria = idMateria;
						materiaAprobada = pedirDatosMateria (materiaAprobada);
						materiaAprobada.b = 'A';
						fwrite(&materiaAprobada,sizeof(materiaAprobada),1,archivo);
					}
				}

		}
	}
	fclose(archivo);
	fclose(historico);
	fclose(alumnos);
	fclose(materias);
}

void imprimirTituloMateriaAprobada(void){
	printf ("***LISTADO DE MATERIAS APROBADAS***\n\n");
	printf ("LEGAJO			ID-MATERIA			NOTA			FECHA APROBACION\n");
	printf ("-------------------------------------------------------------------------------------------------\n");
}

void imprimirMateriaAprobada (materiaAprobada_t materiaAprobada){
	printf ("%04d			%04d				%d			%ld\n",materiaAprobada.legajo,materiaAprobada.idMateria,
			materiaAprobada.nota,materiaAprobada.fecha);
}

void listarMateriaAprobada(void){
	imprimirTituloMateriaAprobada();
	FILE* archivo = fopen(MAT_AP,"rb");
	materiaAprobada_t materiaAprobada;

	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",MAT_AP);
		return;
	}

	fread(&materiaAprobada,sizeof(materiaAprobada),1,archivo);
	while(!feof(archivo)){
		if (materiaAprobada.b == 'A'){
			imprimirMateriaAprobada (materiaAprobada);
		}
		fread(&materiaAprobada,sizeof(materiaAprobada),1,archivo);
	}
	printf("\n");
	fclose(archivo);
}

/*
 *


void mensajeNoExiste (void){
	printf ("El legajo ingresado no existe \n");
}

void mensajeRecuperacion(void){
	printf ("Error , no existe o ya esta dado de alta el legajo \n");
}


int pedirLegajo (void){
	int legajo;
	printf ("Ingrese el LEGAJO \n");
	scanf ("%d",&legajo);
	return legajo;
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
}*/

void materiasAprobadas(){
	do{
			switch(menuMateriaAprobada()){
				case 1:
					altaMateriaAprobada();
				break;
				case 2:
					//modificarMateriaAprobada();
				break;
				case 3:
					//consultaMateriaAprobada();
				break;
				case 4:
					//bajaMateriaAprobada();
				break;
				case 5:
					listarMateriaAprobada();
				break;
				case 6:
					//if (usuarioValido())
						//recuperacionMateriaAprobada();
				break;
				case 7:
					//if (usuarioValido())
						//bajaFisicaMateriaAprobada();
				break;
				case 8:
					//if (usuarioValido())
						//listarHistoricoMateriaAprobada();
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
