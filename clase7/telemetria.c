#include "../headers/clase7.h"

/*
Ejercicio 5: En un sistema de telemetría, se tiene un bus de datos serial con 4 dispositivos.
Cada uno de ellos tendrá una dirección conocida. Se pide diseñar una estructura de datos que contenga, direccion,
comando y dato cada uno de ellos de 8 bits. Para simularlo el usuario ingresará los tres valores y el
programa le imprimirá en pantalla la respuesta del dispositivo.

Ejercicio 18: Usando la función init_sensors del ejercicio de Telemetría con Pasaje por Referencia,
crear un archivo de datos que contenga a la información de los 4 sensores guardados.
 */

#define CANT_SENS 4
#define CANT_COM 3
#define DIR1 25
#define DIR2 50
#define DIR3 75
#define DIR4 100
#define DIR_ARCHIVO "archivos/clase7/mediciones.dat"

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

enum{
	true = 1,
	false = 0,
	errorSeguir = -1,
	errorComando = -2
};

void guardarSensores(sensor_t* sensores){
	FILE* guardarSensores = fopen (DIR_ARCHIVO,"wb");
	if(guardarSensores == NULL){
		printf("No se pudo crear el archivo \n");
	}else{
		int sensoresGuardados=0;
		for(int i=0;i<CANT_SENS;i++){
			sensoresGuardados+=fwrite(&sensores[i],sizeof(sensor_t),1,guardarSensores);
		}
		printf("Se guardaron los datos de %d sensores",sensoresGuardados);
		fclose(guardarSensores);
	}

	free(sensores);
}

sensor_t* iniciarSensores_archivo(){

	sensor_t* sensores = calloc(CANT_SENS,sizeof(sensor_t ));
	FILE* mediciones = fopen(DIR_ARCHIVO,"rb");

	if(mediciones == NULL){
		uint8_t direcciones []={DIR1,DIR2,DIR3,DIR4};
		int agregarComando;

		for(int i=0;i<CANT_SENS;i++){
			sensores[i].comunicacion.direccion=direcciones[i];
			printf("Ingrese el valor iniciar del sensor cuya direccion es %d \n",direcciones[i]);
			scanf(" %3d",&(sensores[i].medicion));
			printf("Valor agregado correctamente \n");
			printf("Ingrese maximo 2 comandos,los comandos que puede tener son:\n1)GET\n2)SET\n3)NADA \n");
			sensores[i].comandos[0]='h';
			for(int j=1;j<CANT_COM;j++){
				printf("Agrege el %dº comando \n",j);
				do{
					scanf(" %1d",&agregarComando);
					switch(agregarComando){
						case 1:
							sensores[i].comandos[j]='g';
						break;
						case 2:
							sensores[i].comandos[j]='s';
						break;
						case 3:
							sensores[i].comandos[j]=' ';
						break;
						default:
							printf("Comando invalido vuelva a probar");
							agregarComando = errorComando;
						break;
					}
				}while(agregarComando==errorComando);
				printf("Comando agregador correctamente \n");
			}
		}

	}else{
		rewind(mediciones);
		int cursor=1;
		fread(&sensores[0],sizeof(sensor_t),1,mediciones);
		while (!feof(mediciones)){
			fread(&sensores[cursor],sizeof(sensor_t),1,mediciones);
			cursor++;
		}
		fclose(mediciones);
	}

	printf("Lista de sensores: \n");
	for(int i=0;i<CANT_SENS;i++){
		printf("Direccion: %d Medicion %d \n",(int)sensores[i].comunicacion.direccion,sensores[i].medicion);
	}
	return sensores;
}

int existeComando(sensor_t sensor,char comando){
	for(int i=0;i<CANT_COM;i++){
		if(sensor.comandos[i]==comando){
			return true;
		}
	}
	return false;
}

void get_archivo(sensor_t sensores[CANT_SENS],uint8_t direccion){
	for(int i=0;i<CANT_SENS;i++){
		if(sensores[i].comunicacion.direccion==direccion){
			if(existeComando(sensores[i],'g') ){
				printf("Valor medido: %d \n",sensores[i].medicion);
			}else{
				printf("Comando no encontrado \n");
			}
			return;
		}
	}
	printf("Error,sensor no encontrado \n");
}

void set_archivo (sensor_t sensores[CANT_SENS],uint8_t direccion,uint8_t dato){
	for(int i=0;i<CANT_SENS;i++){
		if(sensores[i].comunicacion.direccion==direccion){
			if (existeComando(sensores[i],'s')){
				sensores[i].medicion=dato;
				printf("Valor seteado \n");
			}else{
				printf("Comando no encontrado \n");
			}
			return;
		}
	}
	printf("Error,sensor no encontrado \n");
}

void help_archivo(sensor_t sensores[CANT_SENS],uint8_t direccion){
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

void telemetria_archivo(){

	sensor_t* sensores=iniciarSensores_archivo();//sensores,direcciones,comandos

	int direccionI;
	int datoI;
	comunicacion_t comunicacion;
	int seguir=false;

	do{
		printf("Ingrese direccion, comando y dato: \n");
		scanf(" %3d",&direccionI);
		scanf(" %1c",&(comunicacion.comando));
		scanf(" %3d",&datoI);
		comunicacion.direccion = (char)direccionI;
		comunicacion.dato = (char)datoI;

		switch (comunicacion.comando){
			case 'g':
				get_archivo(sensores,comunicacion.direccion);
			break;
			case 's':
				set_archivo(sensores,comunicacion.direccion,comunicacion.dato);
			break;
			case 'h':
				help_archivo(sensores,comunicacion.direccion);
			break;
			default:
				printf("Comando invalido \n");
			break;
		}

		do{
			printf("Desea seguir? 1) SI 2) NO \n");
			scanf("  %1d",&seguir);
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

	guardarSensores(sensores);
}


