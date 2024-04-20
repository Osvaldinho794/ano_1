#include <stdio.h>

int main()
{

int i, numero=0, negativos, positivos, contador, soma_contadores;
float media, percentual_negativo, percentual_positivo;

printf("Digite um número de termos e veja a média, quantos negativos, quantos positivos e o percentual de positivos: ");
scanf(" %d", &numero);
for(i=1; i<=numero; i++) {
    
scanf(" %d", &contador);
soma_contadores+=contador;
media=soma_contadores/numero;
if(contador<0){
    negativos++;
}if(contador>0){
    positivos++;
}
}
printf("A media dos valores eh: %.2f\n", media);
printf("O número de negativos eh: %d\n", negativos);
printf("O número de positivos eh: %d\n", positivos);
percentual_positivo=(positivos*100)/numero;
percentual_negativo=(negativos*100)/numero;
printf("O percentual de números negativos é %.2f\n", percentual_negativo);
printf("O percentual de números positivos é %.2f\n", percentual_positivo);
return 0;
}
