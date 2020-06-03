#include "../headers/clase2.h"

/*
Ejericio 19: Guardar en un archivo la estructura creada para el ejemplo de dibujo de caracteres.

Ejericio 20: Leer el archivo creado en el Ejercicio 19 y dibujar el caracter en pantalla.
 */
/*
El siguiente emula a un display matríz de punto (Ver Imagen).
Se pide al usuario cargar el caracter y dibujarlo con "1" los puntos encendidos y con "0" los puntos apagados. Una vez finalizada la carga,
imprimir en pantalla.

https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSfVx7kUdm2-5uv-wYOi1rbN0wKV9p4YE2newLwzw0hYS3TJ2Qe&s

 */
#define FIL 8
#define COL 8
#define CANT_PUNT FIL*COL

typedef enum{
	true = 1,
	false = 0
}bool;
void display(){
	char caracter[CANT_PUNT];
	bool esValido = true;

	printf("Ingrese la cadena de caracteres: \n");
	//LEER ENTRADA USUARIO

	do{
		scanf(" %s",caracter);
		for(int i=0;i<CANT_PUNT;i++){
			switch (caracter[i]){
			case '1':
			break;
			case '0':
			break;
			default:
				printf("Caracter invalido, ingrese una cadena unicamente con solo 1 o 0 \n");
				esValido = false;
			break;
			}
		}
	}while(esValido == false);

	//IMPRIMIR CARACTER
	for(int i=0;i<FIL;i++){
		for(int j=0;j<COL;j++){
			printf("%c",caracter[i]);
		}
		printf("\n");
	}
}

