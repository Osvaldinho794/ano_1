#include <stdio.h>

int main() {

int maior_numero_atual = 0, numero, menor_numero_atual = 0;


printf("Digite quantos valores você quiser e descubra o maior e o menor: \n");
scanf(" %d", &numero);//esse scanf me diz o maior número
menor_numero_atual=numero;
maior_numero_atual=numero;
do{
    scanf(" %d", &numero);//esse scanf me diz o menor número
    if(numero>0){//eu também posso fazer: if(numero<menor_numero_atual && numero>0, para que 0 não assuma o menor valor
		
	if(numero>maior_numero_atual){
	    maior_numero_atual=numero;
	    
	}if(numero<menor_numero_atual) {
			menor_numero_atual=numero;
}
}
}while(numero>0);
printf("O maior numero eh: %d\n", maior_numero_atual);
printf("O menor numero eh: %d\n", menor_numero_atual);
return 0;
}
