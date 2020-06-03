#include "../headers/clase7.h"



/*
El siguiente emula a un display matríz de punto (Ver Imagen).
Se pide al usuario cargar el caracter y dibujarlo con "1" los puntos encendidos y con "0" los puntos apagados. Una vez finalizada la carga,
imprimir en pantalla.

Ejericio 19: Guardar en un archivo la estructura creada para el ejemplo de dibujo de caracteres.

Ejericio 20: Leer el archivo creado en el Ejercicio 19 y dibujar el caracter en pantalla.

Ejericio 21: Guardar en el archivo del Ejercicio 19 todos los caracteres necesarios para imprimir el nombre "COSME" y
 una vez guardado usarlos para dibujarlo en pantalla.

https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSfVx7kUdm2-5uv-wYOi1rbN0wKV9p4YE2newLwzw0hYS3TJ2Qe&s

 */

#define COL 8
#define FIL 8
#define DIR_ARCH "archivos/clase7/letras.dat"
#define CANT_LETRAS 30

typedef struct{
	int indice;
	char forma[FIL][COL];
}letras_t;

typedef enum{
	errorMenu = -1,
	true = 1,
	false = 0
}bool;

int leeArchivo(letras_t letras[CANT_LETRAS]){
	FILE* archivo = fopen(DIR_ARCH,"rb");
	int cursor=0;
	if (archivo != NULL){
		do{
			fread(&letras[cursor],sizeof(letras_t),1,archivo);
			cursor++;
		}while (!feof(archivo));
	}
	fclose(archivo);
	if (cursor==0)
		return 0;
	return cursor-1;
}

void mostrarLetras(letras_t letras[CANT_LETRAS],int cantidadLetras){
	if(cantidadLetras > 0){
		for(int i=0;i<cantidadLetras;i++){
			printf("Indice: %d \n",letras[i].indice);
			for(int j=0;j<FIL;j++){
				for(int k=0;k<COL;k++){
					printf("%c",letras[i].forma[j][k]);
				}
				printf("\n");
			}
			printf("\n");
		}
	}else{
		printf("No hay letras cargadas \n");
	}
}

void borrarLetras(letras_t letras[CANT_LETRAS],int* cantidadLetras){

	letras_t letrasAux [CANT_LETRAS];
	int indice;
	int cursor=0;
	bool letraEncontrada=false;
	printf("Ingrese el indice de la letra a borrar \n");
	scanf(" %d",&indice);
	for(int i=0;i<(*cantidadLetras);i++){
		if (letras[i].indice != indice){
			letrasAux[cursor]= letras[i];
			cursor++;
		}else{
			letraEncontrada=true;
		}
	}
	if(letraEncontrada){
		printf("Letra borrada de manera correcta \n");
		(*cantidadLetras)--;
	}else{
		printf("Letra no encontrada \n");
	}
	for(int i=0;i<(*cantidadLetras);i++){
		letras[i]=letrasAux[i];
	}

}

void agregarLetras(letras_t letras[CANT_LETRAS],int* cantidadLetras){
	if(*cantidadLetras <= CANT_LETRAS){
		letras_t letraNueva;
		int validacion=0;
		printf("Ingrese el caracter: \n");
			for(int i=0;i<FIL;i++){
				for(int j=0;j<COL;j++){
					do{
						scanf(" %c",&letraNueva.forma[i][j]);
						switch(letraNueva.forma[i][j]){
						case '1':
						break;
						case '0':
						break;
						default:
							printf("Error, solamente ingresar 1 y 0 \n");
							validacion=errorMenu;
						break;
						}
					}while (validacion==errorMenu);
				}
			}
		(*cantidadLetras)++;
		letraNueva.indice=(*cantidadLetras);
		letras[(*cantidadLetras)-1]=letraNueva;
	}else{
		printf("Se alcanzo el maximo cantidad de letras (%d letras)\n",CANT_LETRAS);
	}
}

void guardarArchivo(letras_t letras[CANT_LETRAS],int cantidadLetras){
	FILE* archivo= fopen (DIR_ARCH,"wb");
	fflush(archivo);
	if(archivo==NULL){
		printf("Error el archivo no se pudo guardar \n");
	}else{
		if(cantidadLetras == 0){
			fclose(archivo);
			remove(DIR_ARCH);
		}else{
			for(int i=0;i<cantidadLetras;i++){
				fwrite(&(letras[i]),sizeof(letras_t),1,archivo);
			}
		}
	}
	fflush(archivo);
	fclose(archivo);
}

void mostrarPalabra (letras_t letras[CANT_LETRAS],int posicionIndices [],int tamanio){
	for(int i=0;i<tamanio;i++){
		for(int j=0;j<FIL;j++){
			for(int k=0;k<COL;k++){
					printf("%c",letras[posicionIndices[i]-1].forma[j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
void armarPalabra(letras_t letras[CANT_LETRAS],int cantidadLetras){
	int posicionIndices [cantidadLetras];
	int indice;
	int tamanio=0;
	int menu;
	do{
		do{
			printf("Ingrese a continuacion la secuencia de indices para armar la palabra \n");
			scanf("%d",&indice);
			if(indice > cantidadLetras || indice<=0){
				printf("Ingrese un indice valido \n");
			}
		}while(indice > cantidadLetras || indice<=0);
		posicionIndices[tamanio]=indice;
		tamanio++;
		do{
			printf("Ingresar otra letra ? 1) SI 2)NO \n");
			scanf("%d",&menu);
			switch(menu){
			case 1:
				menu=true;
			break;
			case 2:
				menu=false;
			break;
			default:
				printf("Error, ingrese 1 o 2 \n");
				menu=errorMenu;
			break;
			}
		}while(menu==errorMenu);
	}while(menu==true && tamanio<cantidadLetras);

	mostrarPalabra(letras,posicionIndices,tamanio);
}

void display_archivo(){
	letras_t letras[CANT_LETRAS];

	int cantidadLetras=leeArchivo(letras);
	int menu;

	do{
		do{
			printf("Cantidad letras almacenadas: %d \n",cantidadLetras);
			printf("1)Mostrar letra(s) guardada(s)\n2)Borrar letra\n3)Agregar letra\n4)Armar palabra con indices\n");
			scanf(" %d",&menu);
			switch(menu){
				case 1:
					mostrarLetras(letras,cantidadLetras);
				break;
				case 2:
					borrarLetras(letras,&cantidadLetras);
				break;
				case 3:
					agregarLetras(letras,&cantidadLetras);
				break;
				case 4:
					armarPalabra(letras,cantidadLetras);
				break;
				default:
					printf("Respuesta invalida \n");
					menu= errorMenu;
				break;
			}
		}while(menu==errorMenu);

		do{
			printf("Desea seguir? 1)SI 2)NO \n");
			scanf(" %d",&menu);
			switch(menu){
			case 1:
				menu=true;
			break;
			case 2:
				menu=false;
			break;
			default:
				printf("Error menu, debe marcar opcion 1 o 2 \n");
				menu=errorMenu;
			break;
			}
		}while(menu==errorMenu);
	}while(menu==true);

	guardarArchivo(letras,cantidadLetras);
}
