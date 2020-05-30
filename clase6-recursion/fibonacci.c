#include "../headers/clase6.h"

int fibonacci (int numero){
   if (numero ==0){
		return 0;
	}else if(numero==1){
		return 1;
	}

	return fibonacci(numero-1)+fibonacci(numero-2);
}


void ejecutarFibonacci(){
	int numero;
	printf("Ingrese el valor del numero a calcular la sucesion de fibonacci \n");
	scanf("%d",&numero);

	printf ("Valor de fibonacci es: %d \n",fibonacci(numero));

	printf ("Mostrar serie de %d es: ",numero);
	for (int i=0;i<=numero;i++){
		printf("%d,",fibonacci(i));
	}

}


