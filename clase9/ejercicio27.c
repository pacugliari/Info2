#include "../headers/clase9.h"

/*
Ejercicio 27: Partiendo del Ejercicio 22 modificar los datos del Dibujo de Caracteres para que sean representados a nivel de bits, en lugar de bytes.

El Original planteaba hacerlo con bytes guardando 0 y 1 para prendido o apagado. Aquí se pretende hacerlo de a bit. Si el dibujo es de 8x5 debería
guardarse en 5 bytes.
 */






#define COL 5
#define FIL 8
#define DIR_ARCH "archivos/clase9/letras.dat"
#define CANT_LETRAS 30

typedef struct{
	int indice;
	unsigned char forma [5];
}letras_t;

typedef enum{
	errorMenu = -1,
	true = 1,
	false = 0
}bool;

int leeArchivo27(letras_t letras[CANT_LETRAS]){
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

void mostrarLetras27(letras_t letras[CANT_LETRAS],int cantidadLetras){
	if(cantidadLetras > 0){
		for(int i=0;i<cantidadLetras;i++){
			printf("Indice: %d \n",letras[i].indice);
			for(int j=0;j<5;j++)
				printf("%d \n",letras[i].forma[j]);
		}
	}else{
		printf("No hay letras cargadas \n");
	}
}

void borrarLetras27(letras_t letras[CANT_LETRAS],int* cantidadLetras){

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

void cargarBits (letras_t* letraNueva,char bits[8][5]){
	int byteActual=0;
	int bitActual = 7;
	for (int i=0;i<8;i++){
		for(int j=0;j<5;j++){
			if (bits[i][j]=='1'){
				(letraNueva->forma[byteActual]) = (letraNueva->forma[byteActual]) | (1 << bitActual);
			}else{
				(letraNueva->forma[byteActual]) = (letraNueva->forma[byteActual]) & ~(1 << bitActual);
			}
			if (bitActual == 0){
				bitActual = 8;
				byteActual ++;
			}
			bitActual--;
		}
	}
}

void agregarLetras27(letras_t letras[CANT_LETRAS],int* cantidadLetras){
	if(*cantidadLetras <= CANT_LETRAS){
		letras_t letraNueva;
		char bits [8][5];
		int validacion=0;
		printf("Ingrese el caracter: \n");
			for(int i=0;i<8;i++){
				for(int j=0;j<5;j++){
					do{
						scanf(" %c",&bits[i][j]);
						switch(bits[i][j]){
						case '1':
							validacion=true;
						break;
						case '0':
							validacion=true;
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
		cargarBits(&letraNueva,bits);
		letras[(*cantidadLetras)-1]=letraNueva;
	}else{
		printf("Se alcanzo el maximo cantidad de letras (%d letras)\n",CANT_LETRAS);
	}
}

void guardarArchivo27(letras_t letras[CANT_LETRAS],int cantidadLetras){
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


void mostrarPalabra27 (letras_t letras[CANT_LETRAS],int posicionIndices [],int tamanio){
	for(int i=0;i<tamanio;i++){
		for(int j=0;j<5;j++)
			printf("%d \n",letras[posicionIndices[i]-1].forma[j]);
	}
}

void armarPalabra27(letras_t letras[CANT_LETRAS],int cantidadLetras){
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
	}while(menu==true );

	mostrarPalabra27(letras,posicionIndices,tamanio);
}

void ejercicio27(){
	letras_t letras[CANT_LETRAS];

	int cantidadLetras=leeArchivo27(letras);
	int menu;

	do{
		do{
			printf("Cantidad letras almacenadas: %d \n",cantidadLetras);
			printf("1)Mostrar letra(s) guardada(s)\n2)Borrar letra\n3)Agregar letra\n4)Armar palabra con indices\n");
			scanf(" %d",&menu);
			switch(menu){
				case 1:
					mostrarLetras27(letras,cantidadLetras);
				break;
				case 2:
					borrarLetras27(letras,&cantidadLetras);
				break;
				case 3:
					agregarLetras27(letras,&cantidadLetras);
				break;
				case 4:
					armarPalabra27(letras,cantidadLetras);
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

	guardarArchivo27(letras,cantidadLetras);
}
