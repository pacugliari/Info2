/*
 * materias.c
 *
 *  Created on: 8 sep. 2020
 *      Author: PACugliari
 */


#include "../../lib/libMaterias.h"
#include "../../lib/lib.h"

int menuMateria(void){
	int respuesta;
	printf ("\n***MATERIAS***\n\n");
	printf("1) ALTA MATERIA\n");//LISTO
	printf("2) MOFICIACION MATERIA\n");//LISTO
	printf("3) CONSULTA MATERIA\n");//LISTO
	printf("4) BAJA MATERIA\n");//LISTO
	printf("5) LISTAR MATERIAS \n\n");//LISTO

	printf("6) RECUPERACION MATERIA\n");//LISTO
	printf("7) CREAR ARCHIVO MATERIA\n");//LISTO

	printf("\n0) SALIR \n");
	scanf("%d",&respuesta);
	fflush(stdin);
	return respuesta;
}



void pedirMateria(char* materia){
	printf("Ingrese el nombre de la Materia \n");
	fflush(stdin);
	gets(materia);
	fflush(stdin);
}


void iniciarMateria(void){
	FILE* archivo = fopen(MATERIAS,"w");
	materia_t materia;

	if (archivo ==NULL){
		printf ("Error en la creacion del archivo %s",MATERIAS);
		return;
	}
	materia.idMateria = 0;
	materia.b = 'I';
	fwrite(&materia,sizeof(materia),1,archivo);
	fclose(archivo);
}

void altaMateria(void){
	FILE* archivo = fopen(MATERIAS,"rb+");//VERIFICACION QUE EXISTA
	materia_t materia;

	if (archivo==NULL){
		printf("Error en la apertura del archivo %s",MATERIAS);
		return;
	}

	//VERIFICO QUE NO EXISTA EN ALUMNOS
	fseek(archivo,(-1L)*(long)sizeof(materia),SEEK_END);
	fread(&materia,sizeof(materia),1,archivo);
	pedirMateria(materia.materia);
	materia.b = 'A';
	materia.idMateria++;
	fseek(archivo,0L,SEEK_END);
	fwrite(&materia,sizeof(materia),1,archivo);

	fclose(archivo);
}

void imprimirTituloMateria(void){
	printf ("***LISTADO DE MATERIAS***\n\n");
	printf ("ID-MATERIA			MATERIA\n");
	printf ("--------------------------------------------\n");
}

void imprimirMateria (materia_t materia){
	printf ("%04d				%-20s\n",materia.idMateria,materia.materia);
}

void listarMateria(void){
	imprimirTituloMateria();
	FILE* archivo = fopen(MATERIAS,"rb");
	materia_t materia;

	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",MATERIAS);
		return;
	}

	fread(&materia,sizeof(materia),1,archivo);
	while(!feof(archivo)){
		if (materia.b == 'A'){
			imprimirMateria (materia);
		}
		fread(&materia,sizeof(materia),1,archivo);
	}
	printf("\n");
	fclose(archivo);
}

int ingreseIdMateria(void){
	int id;
	printf("Ingrese el ID de la materia \n");
	scanf("%d",&id);
	return id;
}

materia_t consultaMateria(int idMateria){
	FILE* archivo = fopen(MATERIAS,"rb+");
	materia_t materia;

	materia.b = 'N';
	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",MATERIAS);
		materia.b = 'E';//E: ERROR
		return materia;
	}
	fseek(archivo,(long)(idMateria)*sizeof(materia),SEEK_SET);
	fread(&materia,sizeof(materia),1,archivo);
	if (materia.b != 'B' && materia.b != 'A'){
		materia.b = 'N';
	}
	fclose(archivo);
	return materia;
}

void modificarMateria(void){
	int id = ingreseIdMateria();
	materia_t materia;
	char respuesta;
	FILE* archivo = fopen (MATERIAS,"rb+");

	materia = consultaMateria(id);
	fseek (archivo,(materia.idMateria+1)*(long)sizeof(materia),SEEK_SET);

	imprimirTituloMateria();
	imprimirMateria(materia);

	if (materia.b =='A'){
		do{
			printf ("Seguro que desea modificar la materia ? Y/N \n");
			fflush(stdin);
			scanf("%c",&respuesta);
		}while (respuesta !='Y' && respuesta !='N');
		if (respuesta=='Y'){
			pedirMateria(materia.materia);
			fseek(archivo,(-1L)*(long)sizeof(materia),SEEK_CUR);
			fwrite(&materia,sizeof(materia),1,archivo);
		}
	}else if (materia.b =='B'){
		printf("La materia existe pero esta dada de baja \n");
	}else{
		printf("La materia no existe \n");
	}
	fclose(archivo);
}

void bajaMateria(void){
	int id = ingreseIdMateria();
	materia_t materia = consultaMateria(id);
	FILE* archivo = fopen (MATERIAS,"rb+");
	fseek (archivo,(materia.idMateria+1)*(long)sizeof(materia),SEEK_SET);
	char respuesta;

	imprimirTituloMateria();
	imprimirMateria(materia);

	if (materia.b == 'A'){
		do{
			printf ("Seguro que desea dar de baja la materia ? Y/N \n");
			fflush(stdin);
			scanf("%c",&respuesta);
		}while (respuesta !='Y' && respuesta !='N');
		if (respuesta=='Y'){
			materia.b = 'B';
			fseek(archivo,(-1L)*(long)sizeof(materia),SEEK_CUR);
			fwrite(&materia,sizeof(materia),1,archivo);
		}
	}else if (materia.b =='B'){
		printf("La materia existe pero esta dada de baja \n");
	}else{
		printf("La materia no existe \n");
	}
	fclose(archivo);
}

void recuperacionMateria(void){
	int id = ingreseIdMateria();
	materia_t materia;
	FILE* archivo = fopen (MATERIAS,"rb+");
	fseek (archivo,(materia.idMateria+1)*(long)sizeof(materia),SEEK_SET);
	materia = consultaMateria(id);

	if (materia.b == 'B'){
		materia.b = 'A';
		fseek(archivo,(-1L)*(long)sizeof(materia),SEEK_CUR);
		fwrite(&materia,sizeof(materia),1,archivo);
	}else if (materia.b =='A'){
		printf("La materia ya esta dada de alta\n");
	}else{
		printf("La materia no existe \n");
	}
	fclose(archivo);
}

void materias(void){
	int id;
	do{
			switch(menuMateria()){
				case 1:
					altaMateria();
				break;
				case 2:
					modificarMateria();
				break;
				case 3:
					id = ingreseIdMateria();
					consultaMateria(id);
				break;
				case 4:
					bajaMateria();
				break;
				case 5:
					listarMateria();
				break;
				case 6:
					if (usuarioValido())
						recuperacionMateria();
				break;
				case 7:
					if (usuarioValido())
						iniciarMateria();
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
