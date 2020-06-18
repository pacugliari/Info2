#include "../headers/clase9.h"

/*
Ejercicio 25: Existe un archivo binario de organización directa con la siguiente Estructura.

typedef struct {
  long id;
  char cadena[60];
  float valor;
  unsigned char estado;0b00000100
}data_t;
Realizar una función que pase como parámetro el id. La función debe ubicar el registro, si no lo encuentra devolver -1.
Una vez encontrado, utilizando punteros recorrer el campo cadena colocandolo en mayúscula y regrabar el registro si el bit 3 del campo estado está en 1.
 En este caso devolver la cantidad de registros restantes desde que se encontró el id. (ej. si hay 100 registros y el id pasado es 10 devolverá 90).
 */

typedef struct {
  long id;
  char cadena[60];
  float valor;
  unsigned char estado;
}data_t;

#define DIR_ARCH_DAT "archivos/clase9/ejercicio25.dat"


void cargarDatos25(){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb+");
	data_t reg;
	data_t leido;

	if (datos == NULL){
		datos = fopen (DIR_ARCH_DAT,"wb+");
		if(datos == NULL){
			printf("Error, el archivos %s no se pudo crear \n",DIR_ARCH_DAT);
			return;
		}
	}

	printf("Ingrese el id: \n");
	scanf (" %ld",&reg.id);

	//VERIFICO SI EXISTE EL ID
	fread(&leido,sizeof(data_t),1,datos);
	if (leido.id == reg.id ){
		printf("Error, el ID ingresado ya existe y esta dado de ALTA \n");
		fclose(datos);
		return;
	}
	while (!feof(datos)){
		fread(&leido,sizeof(data_t),1,datos);
		if (leido.id == reg.id){
			printf("Error, el ID ingresado ya existe y esta dado de ALTA \n");
			fclose(datos);
			return;
		}
	}
	//COMO NO EXISTE , CARGO LOS SIGUIENTES DATOS
	printf("Ingrese la descripcion \n");
	scanf(" %[^\n]s",reg.cadena);

	printf("Ingrese el valor: \n");
	scanf (" %f",&(reg.valor));

	reg.estado = 0;
	int respuesta;
	do{
		printf("Ingrese si se puede grabar el registro:  \n1)SI\n2)NO\n");
		scanf (" %d",&respuesta);
		switch (respuesta){
			case 1:
				reg.estado = reg.estado|(1<<2);
			break;
			case 2:
			break;
			default:
				printf("Seleccione una respuesta valida \n");
				respuesta=-1;
			break;
		}
	}while(respuesta==-1);

	fwrite (&reg,sizeof(data_t),1,datos);

	fclose(datos);
}

void mostrarDatos25(){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb");
	data_t leido;
	if (datos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_DAT);
	}else{
		fread(&leido,sizeof(data_t),1,datos);
		while (!feof(datos)){
			//if (leido.estado == 'A')
			printf ("ID: %ld 		 Valor: %f \nDescripcion: %s \n",leido.id,leido.valor,leido.cadena);
			fread(&leido,sizeof(data_t),1,datos);
		}
	}
	fclose(datos);
}

void convertirMay(char* descripcion){

	for(int i=0;i<strlen(descripcion);i++){
		(*(descripcion+i))= toupper(*(descripcion+i));
	}
}

int buscarId25(long id){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb+");
	data_t leido;
	int posicion=0;
	if (datos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_DAT);
	}else{
		fread(&leido,sizeof(data_t),1,datos);
		while (!feof(datos)){
			posicion++;
			if (leido.id==id && (leido.estado & 0b00000100)){
				convertirMay(leido.cadena);
				int pos=ftell(datos)-sizeof(leido);
				fseek(datos,pos,SEEK_SET);
				fwrite(&leido,sizeof(data_t),1,datos);
				fseek(datos, 0L, SEEK_END);
				int tamanio = ftell(datos)/sizeof(data_t);
				fclose(datos);
				return tamanio-posicion;
			}else if (leido.id==id){
				return -2;
			}
			fread(&leido,sizeof(data_t),1,datos);
		}
	}
	fclose(datos);
	return -1;
}

void ejercicio25(){
	long id;
	int opcion;
	do{
		//system("CLS");
		printf("1)Cargar dato \n2)Mostrar datos\n3)Buscar ID\n");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				cargarDatos25();
			break;
			case 2:
				mostrarDatos25();
			break;
			case 3:
				printf("Ingrese el id \n");
				scanf("%ld",&id);
				opcion = buscarId25(id);
				if (opcion == -1){
					printf("Error, el id no se encuentra\n");
				}else if (opcion ==-2){
					printf("El registro no se puede grabar\n");
				}else
					printf("Cantidad de registros restantes: %d \n",opcion);
			break;
			default:
				printf("Error menu, ingrese una opcion valida");
			break;
		}
			printf("Desea seguir? (-1)Para terminar \n");
			scanf(" %d",&opcion);
	}while(opcion != -1);
}


