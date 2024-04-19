#include <stdio.h>

int main() {

int maior_numero_atual = 0, numero, menor_numero_atual = 0;

menor_numero_atual=numero;
maior_numero_atual=numero;

printf("Digite quantos valores você quiser e descubra o maior e o menor: \n");
//faz com que o valor deixe de ser 0
scanf(" %d", &numero);

//para encerrar o programa devo digitar 0
while(numero!=0) {


		if(numero>maior_numero_atual) 
	{
			maior_numero_atual=numero;

	}	if(numero<menor_numero_atual) {
			menor_numero_atual=numero;
}
scanf(" %d", &numero);
}
printf("O maior numero eh: %d\n", maior_numero_atual);
printf("O menor numero eh: %d\n", menor_numero_atual);
return 0;
}