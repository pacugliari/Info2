#include "../headers/clase8.h"

/*
Ejericio 23: Existe un archivo secuencial datos.dat con la siguiente estructura: id (int), nombreyapellido (cadena char),
 nota (float) y b(char A: alta B: baja)

Nota el nombreyapellido se escribe separado por una coma. Ejemplo: “Juan, Pérez”.

Hacer una función que reciba como parámetro una cadena conteniendo parte del nombre del registro y retorne un entero.
 La función debe buscar todos los registros del archivo que coincidan con parte del nombre, omitiendo los dado de baja,
  y cada registro encontrado lo guarda en un archivo nuevo.dat, el cual también tiene que ser creado por la función.
   El nuevo registro guardado solo debe contener el id y el nombre, sin el apellido. La función devuelve el número de registros archivados.
 */

#define DIR_ARCH_DAT "archivos/clase8/datos.dat"
#define DIR_ARCH_NV "archivos/clase8/nuevo.dat"

typedef struct{
	int id;
	char nombreyapellido[30];
	float nota;
	char b;
}dato_t;

typedef struct{
	int id;
	char nombre[30];
	char b;
}nuevo_t;

typedef enum{
	true = 1,
	false = 0
}bool;

bool tieneComa(char* nombreyapellido){
	int cursor=0;
	while (nombreyapellido[cursor]!='\0'){
		if (nombreyapellido[cursor] == ','){
			return true;
		}
		cursor++;
	}
	return false;
}
void cargarDatos(){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb+");
	dato_t dato;
	dato_t leido;
	if (datos == NULL){
		datos = fopen (DIR_ARCH_DAT,"wb+");
		if(datos == NULL){
			printf("Error, el archivos %s no se pudo crear \n",DIR_ARCH_DAT);
			return;
		}
	}

	printf("Ingrese el id: \n");
	scanf ("%d",&(dato.id));

	//VERIFICO SI EXISTE EL ID
	fread(&leido,sizeof(dato_t),1,datos);
	if (leido.id == dato.id && leido.b == 'A'){
		printf("Error, el ID ingresado ya existe y esta dado de ALTA \n");
		fclose(datos);
		return;
	}
	while (!feof(datos)){
		fread(&leido,sizeof(dato_t),1,datos);
		if (leido.id == dato.id && leido.b == 'A'){
			printf("Error, el ID ingresado ya existe y esta dado de ALTA \n");
			fclose(datos);
			return;
		}
	}
	//COMO NO EXISTE , CARGO LOS SIGUIENTES DATOS
	do{
		printf("Ingrese el nombre y apellido separado por coma \n");
		scanf("%s",dato.nombreyapellido);
	}while (!tieneComa(dato.nombreyapellido));

	printf("Ingrese la nota: \n");
	scanf ("%f",&(dato.nota));

	dato.b = 'A';

	fwrite (&dato,sizeof(dato_t),1,datos);

	fclose(datos);
}
bool existeNombre (dato_t leido,char* nombre){
	int cursor=0;
	while (nombre[cursor]!='\0' && leido.b == 'A'){
		if (leido.nombreyapellido[cursor]!=nombre[cursor]){
			return false;
		}
		cursor++;
	}
	return true;
}

char* separarNombre (char* nombreyapellido){
	for(int i=0;i<strlen(nombreyapellido);i++){
		if (nombreyapellido[i]==','){
			nombreyapellido[i]='\0';
		}
	}
	return nombreyapellido;
}
int buscarNombre (char* nombre){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb");
	FILE* nuevo = fopen (DIR_ARCH_NV,"wb");
	dato_t leido;
	nuevo_t nuevoReg;
	int registrosArchivados =0;
	if (datos == NULL || nuevo== NULL){
		if (nuevo == NULL){
			printf("Error, el archivo %s no se pudo crear \n",DIR_ARCH_NV);
		}
		printf("Error, el archivo %s no se puede abrir \n",DIR_ARCH_DAT);
	}else{
		fread(&leido,sizeof(dato_t),1,datos);
		while (!feof(datos)){
			if(existeNombre(leido,nombre)){
				nuevoReg.id = leido.id;
				strcpy(nuevoReg.nombre,separarNombre (leido.nombreyapellido));
				registrosArchivados += fwrite (&nuevoReg,sizeof(nuevo_t),1,nuevo);
			}
			fread(&leido,sizeof(dato_t),1,datos);
		}

	}
	fclose (datos);
	fclose (nuevo);
	if (registrosArchivados ==0){
		remove(DIR_ARCH_NV);
	}
	return registrosArchivados;
}

void mostrarDatos(){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb");
	dato_t leido;
	if (datos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_DAT);
	}else{
		fread(&leido,sizeof(dato_t),1,datos);
		while (!feof(datos)){
			if (leido.b == 'A')
				printf ("ID: %d 		 Nombre y Apellido: %s		Nota: %f \n",leido.id,leido.nombreyapellido,leido.nota);
			fread(&leido,sizeof(dato_t),1,datos);
		}
	}
	fclose(datos);
}

void mostrarNuevo(){
	FILE* nuevos = fopen (DIR_ARCH_NV,"rb");
	nuevo_t nuevo;
	if (nuevos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_DAT);
	}else{
		fread(&nuevo,sizeof(nuevo_t),1,nuevos);
		while (!feof(nuevos)){
			printf ("ID: %d 		 Nombre: %s\n",nuevo.id,nuevo.nombre);
			fread(&nuevo,sizeof(nuevo_t),1,nuevos);
		}
	}
	fclose(nuevos);
}

void baja(int id){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb+");
	dato_t leido;
	if (datos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_DAT);
	}else{
		fread(&leido,sizeof(dato_t),1,datos);
		while (!feof(datos)){
			if(leido.id == id){
				int pos=ftell(datos)-sizeof(leido);
				fseek(datos,pos,SEEK_SET);
				leido.b = 'B';
				fwrite(&leido,sizeof(dato_t),1,datos);
				fclose(datos);
				printf("La baja se dio de manera correcta \n");
				return;
			}
			fread(&leido,sizeof(dato_t),1,datos);
		}
	}
	fclose(datos);
}

void limpiarBajas(){
	FILE* datos = fopen (DIR_ARCH_DAT,"rb");
	FILE* datosNuevo = fopen ("archivos/clase8/datosAux.dat","wb");
	dato_t leido;
	if (datos == NULL){
		printf("Error, no se pudo abrir el archivo: %s \n",DIR_ARCH_DAT);
	}else if (datosNuevo == NULL){
		printf("Error, no se pudo abrir el archivo: archivos/clase8/datosAux.dat \n");
	}else{
		fread(&leido,sizeof(dato_t),1,datos);
		while (!feof(datos)){
			if(leido.b == 'A')
				fwrite(&leido,sizeof(dato_t),1,datosNuevo);
			fread(&leido,sizeof(dato_t),1,datos);
		}
	}
	fclose(datos);
	fclose (datosNuevo);
	remove ("archivos/clase8/datos.dat");
	rename ("archivos/clase8/datosAux.dat","archivos/clase8/datos.dat");
}
void ejercicio23(){
	char nombre[30];
	int opcion;
	int id;
	do{
		system("CLS");
		printf("1)Cargar dato \n2)Baja dato\n3)Mostrar datos\n4)Buscar nombre\n5)Mostrar nuevos\n6)Limpiar bajas\n");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				cargarDatos();
			break;
			case 2:
				printf("Ingrese el ID de baja: \n");
				scanf("%d",&id);
				baja(id);
			break;
			case 3:
				mostrarDatos();
			break;
			case 4:
				printf("Ingrese el nombre a buscar \n");
				scanf("%s",nombre);
				printf("La cantidad de registros archivados es: %d \n",buscarNombre(nombre));
			break;
			case 5:
				mostrarNuevo();
			break;
			case 6:
				limpiarBajas();
			break;
			default:
				printf("Error menu, ingrese una opcion valida");
			break;
		}
			printf("Desea seguir? (-1)Para terminar \n");
			scanf(" %d",&opcion);
	}while(opcion != -1);

}

