#include <stdio.h>
#define valor_final 10

//PEDIR PARA O USUÁRIO UM VALOR INICIAL
//PEDIR PARA O USUÁRIO UMA RAZÃO.
//RAZÃO = DE QUANTO EM QUANTO PULA
//TERMINA EM 10
//COMEÇA ONDE O USUÁRIO QUISER E DEVE SER > 10

int main(int argc, char ** argv) {
    int i, r, v, f;
    printf("Digite um valor incial da sequência: ");
    scanf(" %d", &v);
    printf("Digite a razão dessa sequência: ");
    scanf(" %d", &r);

    
    
        for(i=v; i<=valor_final ; i+=r) {
    

        printf("%d ", i);
        }
return 0;
}
    
