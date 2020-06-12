#include "../headers/clase8.h"

/*
Ejericio 24: Existe un archivo binario de organización secuencial con la siguiente estructura: id[6] (char), descripcion[60] (char), valor (float),
estado (unsigned char).

Nota: El id Alfanumerico es por ejemplo: "A0023"

Realizar una función que reciba como parámetro id que busque al registro y si no lo encuentra devuelva -1. Una vez ubicado, utilizando punteros,
 recorrer la descripción cambiando la letra 'a' por la letra 'e' y regrabar el registro. En este caso devuelve la posición en la que está guardado
 el registro.
 */

#define DIR_ARCH_DAT "archivos/clase8/ejercicio24.dat"

typedef struct{
	char id[6];
	char descripcion[60];
	float valor;
	unsigned char estado;
}registro_t;

void cargarDatos24(){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb+");
	registro_t reg;
	registro_t leido;

	if (datos == NULL){
		datos = fopen (DIR_ARCH_DAT,"wb+");
		if(datos == NULL){
			printf("Error, el archivos %s no se pudo crear \n",DIR_ARCH_DAT);
			return;
		}
	}

	printf("Ingrese el id: \n");
	scanf (" %s",reg.id);

	//VERIFICO SI EXISTE EL ID
	fread(&leido,sizeof(registro_t),1,datos);
	if (leido.id == reg.id && leido.estado == 'A'){
		printf("Error, el ID ingresado ya existe y esta dado de ALTA \n");
		fclose(datos);
		return;
	}
	while (!feof(datos)){
		fread(&leido,sizeof(registro_t),1,datos);
		if (leido.id == reg.id && leido.estado == 'A'){
			printf("Error, el ID ingresado ya existe y esta dado de ALTA \n");
			fclose(datos);
			return;
		}
	}
	//COMO NO EXISTE , CARGO LOS SIGUIENTES DATOS
	printf("Ingrese la descripcion \n");
	scanf(" %[^\n]s",reg.descripcion);

	printf("Ingrese el valor: \n");
	scanf (" %f",&(reg.valor));

	reg.estado = 'A';

	fwrite (&reg,sizeof(registro_t),1,datos);

	fclose(datos);
}

void mostrarDatos24(){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb");
	registro_t leido;
	if (datos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_DAT);
	}else{
		fread(&leido,sizeof(registro_t),1,datos);
		while (!feof(datos)){
			if (leido.estado == 'A')
				printf ("ID: %s 		 Valor: %f \nDescripcion: %s \n",leido.id,leido.valor,leido.descripcion);
			fread(&leido,sizeof(registro_t),1,datos);
		}
	}
	fclose(datos);
}

void invertirLetras(char* descripcion){

	for(int i=0;i<strlen(descripcion);i++){
		if (*(descripcion+i)=='a'){
			*(descripcion+i) = 'e';
		}
	}
}

int buscarId(char* id){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb+");
	registro_t leido;
	int posicion=0;
	if (datos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_DAT);
	}else{
		fread(&leido,sizeof(registro_t),1,datos);
		while (!feof(datos)){
			posicion++;
			if (!strcmp(leido.id,id) && leido.estado == 'A'){
				invertirLetras(leido.descripcion);
				int pos=ftell(datos)-sizeof(leido);
				fseek(datos,pos,SEEK_SET);
				fwrite(&leido,sizeof(registro_t),1,datos);
				fclose(datos);
				return posicion;
			}
			fread(&leido,sizeof(registro_t),1,datos);
		}
	}
	fclose(datos);
	return -1;
}

void ejercicio24(){
	char id[6];
	int opcion;
	do{
		//system("CLS");
		printf("1)Cargar dato \n2)Mostrar datos\n3)Buscar ID\n");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				cargarDatos24();
			break;
			case 2:
				mostrarDatos24();
			break;
			case 3:
				printf("Ingrese el id \n");
				scanf("%s",id);
				printf("Se encuentra en la posicion: %d \n",buscarId(id));
			break;
			default:
				printf("Error menu, ingrese una opcion valida");
			break;
		}
			printf("Desea seguir? (-1)Para terminar \n");
			scanf(" %d",&opcion);
	}while(opcion != -1);
}
