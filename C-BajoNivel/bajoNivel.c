/*
 * bajoNivel.c
 *
 *  Created on: 13 sep. 2020
 *      Author: PACugliari
 */

#include "../headers/bajoNivel.h"

//OPERACIONES ESCRITAS COMO MACROS
#define toggleBit(var,bit) var=var^(1<<bit)
#define clearBit(var,bit) var=var&~(1<<bit)
#define setBit(var,bit) var=var|(1<<bit)

//CAMPO DE BITS

typedef struct{
	unsigned char campo1:3;//3 bits
	unsigned char campo2:1;//1 bit
	unsigned char campo3:4;//4 bits
}campo_t;

void bajoNivel(void){

	char numero = 0b00001010; //NUMERO 10 EN DECIMAL ESCRITO EN BINARIO
	printf ("Cargo numero %d en notacion binaria : %d \n",numero,numero);

	numero = 0xB;//NUMERO 11 EN DECIMAL ESCRITO EN HEXADECIMAL

	printf ("Cargo numero %d en notacion hexadecimal %d \n",numero,numero);

	printf("----------------------------------------------------------\n");
	campo_t numero2;

	//CARGO NUMEROS
	numero2.campo1 = 0b101;//0 a 7
	numero2.campo2 = 0b1;//0 o 1
	numero2.campo3 = 0b1101;//0 a 15
	printf ("El valor del campo 1 es %d \n",numero2.campo1);
	printf ("El valor del campo 2 es %d \n",numero2.campo2);
	printf ("El valor del campo 3 es %d \n",numero2.campo3);

	printf ("Campo de bits con operaciones \n");

	clearBit(numero2.campo1,0);//ESTABA EL VALOR 5, QUEDA EL VALOR 4
	printf ("El valor del campo 1 es %d \n",numero2.campo1);
	toggleBit(numero2.campo2,0);//CAMBIO EL VALOR DE 1 A 0
	printf ("El valor del campo 2 es %d \n",numero2.campo2);
	setBit(numero2.campo3,1);//ESTABA EL VALOR 13 ACTIVO EL BIT 1, QUEDA EL VALOR 15
	printf ("El valor del campo 3 es %d \n",numero2.campo3);

	printf("----------------------------------------------------------\n");

	//DESPLAZAMIENTO

	printf("Desplazamiento del valor %d \n",numero);

	numero = numero << 3; //MULTIPLICA NUMERO*2^3

	printf("Desplazamiento de n bits a izquierda(multiplicacion) %d \n",numero);

	numero = numero >> 2; //DIVIDE NUMERO/2^2

	printf("Desplazamiento de n bits a derecha (division)%d \n",numero);

	printf("----------------------------------------------------------\n");

	//OPERACIONES
	numero=0;

	setBit(numero,3);//PRENDE EL BIT 3, NUMERO DECIMAL 8

	printf("Prendo un bit %d \n",numero);

	toggleBit(numero,2); //CAMBIA 0 A 1 EL BIT 2, NUMERO DECIMAL 12

	printf("Cambio un bit %d \n",numero);

	clearBit(numero,3); //APAGA EL BIT 3, NUMERO DECIMAL 4

	printf("Apago un bit %d \n",numero);

	printf("----------------------------------------------------------\n");

}
