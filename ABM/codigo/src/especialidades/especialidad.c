/*
 * especialidad.c
 *
 *  Created on: 7 sep. 2020
 *      Author: PACugliari
 */

#include "../../lib/libEspecialidad.h"
#include "../../lib/libMaterias.h"
#include "../../lib/lib.h"


int menuEspecialidad(void){
	int respuesta;
	printf ("\n***ESPECIALIDADES***\n\n");
	printf("1) ALTA ESPECIALIDAD\n");//LISTO
	printf("2) MOFICIACION ESPECIALIDAD\n");//LISTO
	printf("3) CONSULTA ESPECIALIDAD\n");//LISTO
	printf("4) BAJA ESPECIALIDAD\n");//LISTO
	printf("5) LISTAR ESPECIALIDAD \n\n");//LISTO

	printf("6) RECUPERACION ESPECIALIDAD\n");//LISTO
	printf("7) CREAR ARCHIVO ESPECIALIDAD\n");//LISTO

	printf("\n0) SALIR \n");
	scanf("%d",&respuesta);
	fflush(stdin);
	return respuesta;
}



void pedirEspecialidad(char* nombre){
	printf("Ingrese el nombre \n");
	scanf("%s",nombre);
	fflush(stdin);
}


void iniciarEspecialidad(void){
	FILE* archivo = fopen(ESPECIALIDAD,"w");
	especialidad_t especialidad;

	if (archivo ==NULL){
		printf ("Error en la creacion del archivo %s",ESPECIALIDAD);
		return;
	}
	especialidad.idEspecialidad = 0;
	especialidad.b = 'I';
	fwrite(&especialidad,sizeof(especialidad),1,archivo);
	fclose(archivo);
}


void altaEspecialidad(void){
	especialidad_t especialidad;
	FILE* archivo = fopen(ESPECIALIDAD,"rb+");//VERIFICACION QUE EXISTA

	if (archivo==NULL){
		printf("Error en la apertura del archivo %s",ESPECIALIDAD);
		return;
	}

	//VERIFICO QUE NO EXISTA EN ALUMNOS
	fseek(archivo,(-1L)*(long)sizeof(especialidad),SEEK_END);
	fread(&especialidad,sizeof(especialidad),1,archivo);
	pedirEspecialidad(especialidad.especialidad);
	especialidad.b = 'A';
	especialidad.idEspecialidad++;
	fseek(archivo,0L,SEEK_END);
	fwrite(&especialidad,sizeof(especialidad),1,archivo);

	fclose(archivo);
}

void imprimirTituloEspecialidad(void){
	printf ("***LISTADO DE ESPECIALIDAD***\n\n");
	printf ("ID-ESPECIALIDAD			ESPECIALIDAD\n");
	printf ("--------------------------------------------\n");
}

void imprimirEspecialidad (especialidad_t especialidad){
	printf ("%04d				%-20s\n",especialidad.idEspecialidad,especialidad.especialidad);
}

void listarEspecialidad(void){
	imprimirTituloEspecialidad();
	FILE* archivo = fopen(ESPECIALIDAD,"rb");
	especialidad_t especialidad;

	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",ESPECIALIDAD);
		return;
	}

	fread(&especialidad,sizeof(especialidad),1,archivo);
	while(!feof(archivo)){
		if (especialidad.b == 'A'){
			imprimirEspecialidad (especialidad);
		}
		fread(&especialidad,sizeof(especialidad),1,archivo);
	}
	printf("\n");
	fclose(archivo);
}

int ingreseId(void){
	int id;
	printf("Ingrese el ID de la especialidad \n");
	scanf("%d",&id);
	return id;
}

especialidad_t consultaEspecialidad(int idEspecialidad){
	FILE* archivo = fopen(ESPECIALIDAD,"rb+");
	especialidad_t especialidad;

	especialidad.b = 'N';
	if (archivo == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",ESPECIALIDAD);
		especialidad.b = 'E';//E: ERROR
		return especialidad;
	}
	fseek(archivo,(long)(idEspecialidad)*sizeof(especialidad),SEEK_SET);
	fread(&especialidad,sizeof(especialidad),1,archivo);

	fclose(archivo);
	return especialidad;
}

void modificarEspecialidad(void){
	int id = ingreseId();
	especialidad_t especialidad;
	char respuesta;
	FILE* archivo = fopen (ESPECIALIDAD,"rb+");

	especialidad = consultaEspecialidad(id);
	fseek (archivo,(especialidad.idEspecialidad+1)*(long)sizeof(especialidad),SEEK_SET);

	imprimirTituloEspecialidad();
	imprimirEspecialidad(especialidad);

	if (especialidad.b =='A'){
		do{
			printf ("Seguro que desea modificar la especialdiad ? Y/N \n");
			fflush(stdin);
			scanf("%c",&respuesta);
		}while (respuesta !='Y' && respuesta !='N');
		if (respuesta=='Y'){
			pedirEspecialidad(especialidad.especialidad);
			fseek(archivo,(-1L)*(long)sizeof(especialidad),SEEK_CUR);
			fwrite(&especialidad,sizeof(especialidad),1,archivo);
		}
	}else if (especialidad.b =='B'){
		printf("La especialidad existe pero esta dada de baja \n");
	}else{
		printf("La especialidad no existe \n");
	}
	fclose(archivo);
}

void bajaEspecialidad(void){
	int id = ingreseId();
	especialidad_t especialidad = consultaEspecialidad(id);
	FILE* archivo = fopen (ESPECIALIDAD,"rb+");
	fseek (archivo,(especialidad.idEspecialidad+1)*(long)sizeof(especialidad),SEEK_SET);
	char respuesta;

	imprimirTituloEspecialidad();
	imprimirEspecialidad(especialidad);

	if (especialidad.b == 'A'){
		do{
			printf ("Seguro que desea dar de baja la especialdiad ? Y/N \n");
			fflush(stdin);
			scanf("%c",&respuesta);
		}while (respuesta !='Y' && respuesta !='N');
		if (respuesta=='Y'){
			especialidad.b = 'B';
			fseek(archivo,(-1L)*(long)sizeof(especialidad),SEEK_CUR);
			fwrite(&especialidad,sizeof(especialidad),1,archivo);
		}
	}else if (especialidad.b =='B'){
		printf("La especialidad existe pero esta dada de baja \n");
	}else{
		printf("La especialidad no existe \n");
	}
	fclose(archivo);
}

void recuperacionEspecialidad(void){
	int id = ingreseId();
	especialidad_t especialidad;
	FILE* archivo = fopen (ESPECIALIDAD,"rb+");
	fseek (archivo,(especialidad.idEspecialidad+1)*(long)sizeof(especialidad),SEEK_SET);
	especialidad = consultaEspecialidad(id);


	if (especialidad.b == 'B'){
		especialidad.b = 'A';
		fseek(archivo,(-1L)*(long)sizeof(especialidad),SEEK_CUR);
		fwrite(&especialidad,sizeof(especialidad),1,archivo);
	}else if (especialidad.b =='A'){
		printf("La especialidad ya esta dada de alta\n");
	}else{
		printf("La especialidad no existe \n");
	}
	fclose(archivo);
}





void especialidades(void){
	int id;
	do{
			switch(menuEspecialidad()){
				case 1:
					altaEspecialidad();
				break;
				case 2:
					modificarEspecialidad();
				break;
				case 3:
					id = ingreseId();
					consultaEspecialidad(id);
				break;
				case 4:
					bajaEspecialidad();
				break;
				case 5:
					listarEspecialidad();
				break;
				case 6:
					if (usuarioValido())
						recuperacionEspecialidad();
				break;
				case 7:
					if (usuarioValido())
						iniciarEspecialidad();
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
