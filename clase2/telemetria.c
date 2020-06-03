#include "../headers/clase2.h"

/*
Ejercicio 5: En un sistema de telemetría, se tiene un bus de datos serial con 4 dispositivos.
Cada uno de ellos tendrá una dirección conocida. Se pide diseñar una estructura de datos que contenga, direccion,
comando y dato cada uno de ellos de 8 bits. Para simularlo el usuario ingresará los tres valores y el
programa le imprimirá en pantalla la respuesta del dispositivo.
 */

#define CANT_SENS 4
#define CANT_COM 3
#define DIR1 25
#define DIR2 50
#define DIR3 75
#define DIR4 100

typedef  unsigned char uint8_t;
/*typedef <Tipo de dato> <nombre nuevo tipo de dato>*/

/* Luego podremos declarar nuestras variables enteras sin signo de 8 bits,
   utilizando nuestro nuevo tipo de datos.*/

typedef struct{
	uint8_t direccion;
	uint8_t comando;
	uint8_t dato;
}comunicacion_t;

typedef struct{
	comunicacion_t comunicacion;
	char comandos[CANT_COM];
	int medicion;
}sensor_t;



sensor_t* iniciarSensores(){


	uint8_t direcciones []={DIR1,DIR2,DIR3,DIR4};
	char comandos[]={'g','s','h'};
	sensor_t* sensores = calloc(CANT_SENS,sizeof(sensor_t ));

	for(int i=0;i<CANT_SENS;i++){
		sensores[i].comunicacion.direccion=direcciones[i];
		sensores[i].medicion=0;
		for(int j=0;j<CANT_COM;j++){
			sensores[i].comandos[j]=comandos[j];
		}
	}

	return sensores;
}

enum{
	true = 1,
	false = 0,
	errorSeguir = -1
};

void get(sensor_t sensores[CANT_SENS],uint8_t direccion){
	for(int i=0;i<CANT_SENS;i++){
		if(sensores[i].comunicacion.direccion==direccion){
			printf("Valor medido: %d \n",sensores[i].medicion);
			return;
		}
	}
	printf("Error,sensor no encontrado \n");
}

void set (sensor_t sensores[CANT_SENS],uint8_t direccion,uint8_t dato){
	for(int i=0;i<CANT_SENS;i++){
		if(sensores[i].comunicacion.direccion==direccion){
			sensores[i].medicion=dato;
			printf("Valor seteado \n");
			return;
		}
	}
	printf("Error,sensor no encontrado \n");
}

void help(sensor_t sensores[CANT_SENS],uint8_t direccion){
	for(int i=0;i<CANT_SENS;i++){
		if(sensores[i].comunicacion.direccion==direccion){
			printf("Comandos: ");
			for (int j=0;j<CANT_COM;j++){
				printf("%c ",sensores[i].comandos[j]);
			}
			printf("\n");
			return;
		}
	}
	printf("Error,sensor no encontrado \n");
}

void telemetria(){

	sensor_t* sensores=iniciarSensores();//sensores,direcciones,comandos

	int direccionI;
	int datoI;
	comunicacion_t comunicacion;
	int seguir=true;

	do{
		printf("Ingrese direccion, comando y dato: \n");
		scanf("%d %c %d",&direccionI,&(comunicacion.comando),&datoI);
		comunicacion.direccion = (char)direccionI;
		comunicacion.dato = (char)datoI;

		switch (comunicacion.comando){
			case 'g':
				get(sensores,comunicacion.direccion);
			break;
			case 's':
				set(sensores,comunicacion.direccion,comunicacion.dato);
			break;
			case 'h':
				help(sensores,comunicacion.direccion);
			break;
			default:
				printf("Comando invalido \n");
			break;
		}

		do{
			printf("Desea seguir? 1) SI 2) NO \n");
			scanf("%d",&seguir);
			switch(seguir){
				case 1:
					seguir=true;
				break;
				case 2:
					seguir=false;
				break;
				default:
					printf("Error respuesta \n");
					seguir=errorSeguir;
				break;
			}
		}while(seguir==errorSeguir);
	}while(seguir==true);


	free(sensores);

}

