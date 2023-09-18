#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

int initialChoose(){
    
    printf("1-Gerar chave pública\n");
    printf("2-Encriptar\n");
    printf("3-Desencriptar.\n");

    int escolha;
    scanf("%d", &escolha);

    if(escolha>3 || escolha < 1){
        system("clear");
        printf("*Digite uma escolha válida*\n\n");
        return initialChoose();
    }
    
    return escolha;
}

int main(){
    int escolha = initialChoose();
    
    switch(escolha) {
    case 1:
        chavePublica();
        break;
    case 2:
        encripitar();
        break;
    case 3:
        desencriptar();
        break;
    }
    return 0;
}