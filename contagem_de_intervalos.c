#include <stdio.h>

int main()
{

int i, numero, primeiro = 0, segundo = 0, terceiro = 0, quarto = 0;;
printf("Digite valores de 0-100 e descubra quantos deles estão em cada intervalo: ");
do{
    scanf(" %d", &numero);
    if(numero>=0 && numero<=25) {
        primeiro++;    
    }if(numero>=26 && numero<=50) {
        segundo++;    
    }if(numero>=51 && numero<=75) {
        terceiro++;    
    }if(numero>=76 && numero<=100) {
        quarto++;    
    }
}while(numero>-1);
printf("Tem %d valores no intervalo de 0-25\n", primeiro);
printf("Tem %d valores no intervalo de 26-50\n", segundo);
printf("Tem %d valores no intervalo de 51-75\n", terceiro);
printf("Tem %d valores no intervalo de 76-100\n", quarto);

return 0;
}
