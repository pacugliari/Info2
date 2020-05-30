#include "../headers/clase6.h"

int factorial (int numero){
	if (numero ==0 || numero==1){
		return 1;
	}
	return numero*factorial(numero-1);
}


void ejecutarFactorial(){
	int numero;
	int factorialNumero;
	printf("Ingrese el valor del numero a calcular el factorial \n");
	scanf("%d",&numero);

	factorialNumero = factorial(numero);

	printf("El factorial de %d! es: %d \n",numero,factorialNumero);
}


