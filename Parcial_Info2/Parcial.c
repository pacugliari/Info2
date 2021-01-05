#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int cl;
	char d[30];
	unsigned int tipo;
	char b;
}dato_t;

typedef struct{
	int cl;
	int pos;
}datoPila_t;

typedef struct{
	datoPila_t dato;
	void* siguiente;
}nodo_t;

typedef struct{
	nodo_t* primero;
}pila_t;

nodo_t* funcion(int clave,nodo_t* primero){
	//EN CASO DE ERROR O NO ENCONTRAR LA CLAVE EN EL ARCHIVO RETORNA EL PUNTERO PASADO POR PARAMETRO
	FILE* archivo = fopen ("datos.dat","rb+");
	dato_t leido;
	pila_t pila;
	pila.primero = primero;
	nodo_t* aux;
	int contador=0;
	if(!archivo){
		printf("Error en la apertura del archivo datos.dat \n");
		return primero;
	}
	fread(&leido,sizeof(leido),1,archivo);
	contador++;
	while(!feof(archivo)){
		if(leido.cl == clave && (leido.tipo & (1<<0)) && leido.b == 'A'){
			aux = (nodo_t*)malloc(sizeof(nodo_t));
			aux->dato.cl = clave;
			aux->dato.pos = contador;
			if(!aux){
				printf("Error al reservar memoria \n");
				return primero;
			}
			if(!pila.primero){//PILA VACIA
				aux->siguiente = NULL;
			}else{
				aux->siguiente = pila.primero;
			}
			pila.primero = aux;
			return pila.primero;
		}
		fread(&leido,sizeof(leido),1,archivo);
		contador++;
	}
	//SI LLEGA A ESTE LUGAR ES QUE EL REGISTRO NO EXISTE Y DEBO CARGARLO
	leido.b = 'A';
	leido.cl = clave;
	printf("Ingrese la descripcion \n");
	gets(leido.d);
	fflush(stdin);
	printf("Ingrese el tipo \n");
	scanf("%d",&leido.tipo);
	fflush(stdin);
	fwrite(&leido,sizeof(leido),1,archivo);
	fclose(archivo);
	return primero;
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);//AGREGADO PARA EVITAR BUG CONSOLA ECLIPSE
	dato_t cargar;
	cargar.b = 'A';
	cargar.cl = 1234;
	cargar.tipo = 1;

	FILE* archivo = fopen ("datos.dat","wb");
	if(!archivo){
		printf("error en la creacion del archivo \n");
		return 0;
	}
	fwrite(&cargar,sizeof(cargar),1,archivo);
	cargar.b = 'A';
	cargar.cl = 123456;
	cargar.tipo = 1;
	fwrite(&cargar,sizeof(cargar),1,archivo);
	cargar.b = 'A';
	cargar.cl = 1234567;
	cargar.tipo = 1;
	fwrite(&cargar,sizeof(cargar),1,archivo);
	fclose (archivo);

	//LLAMADA A PILA Y FUNCION
	nodo_t* primero= NULL;
	nodo_t* aux;
	primero = funcion(1234,primero);
	primero = funcion(12345,primero);
	primero = funcion(123456,primero);
	primero = funcion(1234567,primero);

	//RECORRO EL ARCHIVO
	archivo = fopen ("datos.dat","rb");
	if(!archivo){
		printf("Error en la apertura del archivo \n");
		return 0;
	}
	fread(&cargar,sizeof(cargar),1,archivo);
	while(!feof(archivo)){
		printf("Clave: %d Descripcion: %s \n",cargar.cl,cargar.d);
		fread(&cargar,sizeof(cargar),1,archivo);
	}

	fclose(archivo);

	//RECORRO PILA PARA VER SI FUNCIONA
	int contador =0;
	aux = primero;
	while(aux){
		printf("Clave: %d Posicion %d \n",aux->dato.cl,aux->dato.pos);
		aux = aux->siguiente;
		contador++;
	}
	//VEO SI SE LIBERO LA MEMORIA
	printf("Liberado %d \n",contador);

	//LIBERO MEMORIA
	while(primero){
		aux = primero;
		primero = primero->siguiente;
		free(aux);
	}
	return EXIT_SUCCESS;
}
