#include "../headers/clase9.h"

/*


Ejericio 26: Hacer una Función que reciba como parámetro un int correspondiente a un id del archivo buscar.dat, de organización secuencial,
con la siguiente estructura: id (int), nombre (cadena char), nota (float), estado (unsigned int), b (char) y devuelva un long.

Nota: Estado debe tener valor A (alta), B (baja) o P (procesado)

La función debe buscar el registro del archivo correspondiente al id pasado como parámetro. Si el campo estado del registro tiene los bits 3, 5, 7 y 8
(0b110101000 / 0xD4)
 en valor 1, imprimirá el nombre en mayúculas y devolverá -1. Si esta marcado como Alta creará un registro en el archivo "procesado.dat" con el registro y
 devolverá el lugar donde se grabó. En caso de estar marcado como P se marcará al registro como baja y utilizando punteros devolver cuantas vocales tiene
  el campo nombre. Cualquier error debe devolver -2.

Nota: Los errores pueden ser de apertura del archivo o registro no encontrado, etc..
 */

typedef struct{
	int id;
	char nombre[10];
	float nota;
	unsigned int estado;
	char b;
}buscar_t;

typedef struct{
	int codigo;
	char tipo;
}retorno_t;

#define DIR_ARCH_DAT "archivos/clase9/buscar.dat"
#define DIR_ARCH_PRO "archivos/clase9/procesado.dat"


void cargarDatos26(){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb+");
	buscar_t reg;
	buscar_t leido;

	if (datos == NULL){
		datos = fopen (DIR_ARCH_DAT,"wb+");
		if(datos == NULL){
			printf("Error, el archivos %s no se pudo crear \n",DIR_ARCH_DAT);
			return;
		}
	}

	printf("Ingrese el id: \n");
	scanf (" %d",&reg.id);

	//VERIFICO SI EXISTE EL ID
	fread(&leido,sizeof(buscar_t),1,datos);
	if (leido.id == reg.id ){
		if (reg.b == 'A')
			printf("Error, el ID ingresado ya existe y esta dado de ALTA \n");
		else
			printf("Error, el ID ingresado ya existe y esta dado de BAJA \n");
		fclose(datos);
		return;
	}
	while (!feof(datos)){
		fread(&leido,sizeof(buscar_t),1,datos);
		if (leido.id == reg.id){
			if (reg.b == 'A')
				printf("Error, el ID ingresado ya existe y esta dado de ALTA \n");
			else
				printf("Error, el ID ingresado ya existe y esta dado de BAJA \n");
			fclose(datos);
			return;
		}
	}
	//COMO NO EXISTE , CARGO LOS SIGUIENTES DATOS
	printf("Ingrese el nombre \n");
	scanf(" %[^\n]s",reg.nombre);

	printf("Ingrese la nota: \n");
	scanf (" %f",&(reg.nota));

	reg.estado = 0;
	int respuesta;
	do{
		printf("Ingrese si se puede grabar el registro:  \n1)SI\n2)NO\n");
		scanf (" %d",&respuesta);
		switch (respuesta){
			case 1:
				reg.estado = reg.estado|0xD4;
			break;
			case 2:
			break;
			default:
				printf("Seleccione una respuesta valida \n");
				respuesta=-1;
			break;
		}
	}while(respuesta==-1);

	reg.b = 'A';

	fwrite (&reg,sizeof(buscar_t),1,datos);

	fclose(datos);
}

void mostrarDatos26(){
	printf("***Lista de datos***\n");
	FILE* datos = fopen (DIR_ARCH_DAT,"rb");
	buscar_t leido;
	if (datos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_DAT);
	}else{
		fread(&leido,sizeof(buscar_t),1,datos);
		while (!feof(datos)){
			if (leido.b != 'B'){
				printf("********************\n");
				printf ("ID: %d\nNombre: %s \nNota: %f \nGrabar:%x\nB:%c\n",leido.id,leido.nombre,leido.nota,leido.estado,leido.b);
			}
			fread(&leido,sizeof(buscar_t),1,datos);
		}
	}
	fclose(datos);
}

void convertirMay26(char* descripcion){

	for(int i=0;i<strlen(descripcion);i++){
		(*(descripcion+i))= toupper(*(descripcion+i));
	}
}

int contarVocales(char* nombre){
	int contador=0;
	char letra;
	for(int i=0;i<strlen(nombre);i++){
		letra = nombre[i];
		if (letra=='A' || letra=='E' || letra=='I' || letra=='O' || letra=='U' ||
				letra=='a' || letra=='e' || letra=='i' || letra=='o' || letra=='u'){
			contador++;
		}
	}
	return contador;
}
retorno_t buscarId26(long id){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb+");
	buscar_t leido;
	int posicion=0;
	retorno_t retorno;
	retorno.codigo = -2;
	if (datos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_DAT);
	}else{
		fread(&leido,sizeof(buscar_t),1,datos);
		while (!feof(datos)){
			posicion++;
			if (leido.id==id){
				if ((leido.estado & 0xD4)){
					convertirMay26(leido.nombre);
					leido.estado=0;
					printf("Nombre: %s \n",leido.nombre);
					retorno.codigo = -1;
					retorno.tipo = 'E';
				}else if (leido.b=='A'){
					FILE* procesado = fopen(DIR_ARCH_PRO,"ab+");
					if (procesado == NULL){
						printf("Error, no se pudo crear o abrir el archivo: %s ",DIR_ARCH_PRO);
					}
					leido.b='P';
					fwrite(&leido,sizeof(buscar_t),1,procesado);
					int pos=ftell(procesado)/sizeof(buscar_t);
					fclose(procesado);
					retorno.codigo = pos;
					retorno.tipo = 'A';
				}else if (leido.b=='P'){
					leido.b='B';
					int vocales=contarVocales(leido.nombre);
					retorno.codigo = vocales;
					retorno.tipo = 'P';
				}else if (leido.b=='B'){
					printf("El registro esta dado de baja \n");
				}

				int pos=ftell(datos)-sizeof(leido);
				fseek(datos,pos,SEEK_SET);
				fwrite(&leido,sizeof(buscar_t),1,datos);
				fclose(datos);
				return retorno;
			}
			fread(&leido,sizeof(buscar_t),1,datos);
		}
	}
	fclose(datos);
	return retorno;
}

void mostrarProcesado(){
	printf("***Lista de procesados***\n");
	FILE* datos = fopen (DIR_ARCH_PRO,"rb");
	buscar_t leido;
	if (datos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_PRO);
	}else{
		fread(&leido,sizeof(buscar_t),1,datos);
		while (!feof(datos)){
			printf("********************\n");
			printf ("ID: %d\nNombre: %s \nNota: %f \nGrabar:%x\nB:%c\n",leido.id,leido.nombre,leido.nota,leido.estado,leido.b);
			fread(&leido,sizeof(buscar_t),1,datos);
		}
	}
	fclose(datos);
}
void ejercicio26(){
	long id;
	int opcion;
	retorno_t retorno;
	do{
		//system("CLS");
		printf("1)Cargar dato \n2)Mostrar datos\n3)Buscar ID\n4)Mostrar procesados\n");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				cargarDatos26();
			break;
			case 2:
				mostrarDatos26();
			break;
			case 3:
				printf("Ingrese el id \n");
				scanf("%ld",&id);
				retorno = buscarId26(id);
				switch (retorno.tipo){
				case 'A':
					printf("La posicion almacenada en el archivo procesado es: %d \n",retorno.codigo);
				break;
				case 'P':
					printf("La cantidad de vocales que posee el nombre es: %d\n",retorno.codigo);
				break;
				case 'E':
					printf("Retorno de codigo: %d\n",retorno.codigo);
				break;
				default:
					printf("Error, codigo %d\n",retorno.codigo);
				break;
				}
			break;
			case 4:
				mostrarProcesado();
			break;
			default:
				printf("Error menu, ingrese una opcion valida");
			break;
		}
			printf("Desea seguir? (-1)Para terminar \n");
			scanf(" %d",&opcion);
	}while(opcion != -1);
}

