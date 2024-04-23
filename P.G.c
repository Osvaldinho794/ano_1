#include <stdio.h>
#define valor_final 10

int main(int argc, char ** argv) {
    int i, r, v, f;
    printf("Digite um valor incial da sequência: ");
    scanf(" %d", &v);
    printf("Digite a razão dessa sequência: ");
    scanf(" %d", &r);

    
    
        for(i=v; i<=valor_final ; i*=r) {
    

        printf("%d ", i);
        }
return 0;
}
  
