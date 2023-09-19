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
    system("clear");
    return escolha;
}

void chavePublica(){
    //Declara e inicializa as variáveis 
    mpz_t p, q, e, n; 
    mpz_inits(p, q, e, n, NULL);

    //Recebe os valores  
    printf("Digite os valores p, q, e, respectivamente.\n");
    gmp_scanf("%Zd %Zd %Zd", p, q, e);    

    //### COLOCAR UMA FUNÇÃO QUE VERIFICA SE  P, Q É COMPRIMO A (P-1)(Q-1) ###

    //Calcula a Chave Publica 
    mpz_mul(n, p, q);

    gmp_printf("p: %Zd | q: %Zd | e: %Zd | n: %Zd\n", p, q, e, n);

    //Converte os dados em String
    char *str_q, *str_p, *str_n, *str_e;
    str_p =  mpz_get_str(NULL, 10, p);
    str_q =  mpz_get_str(NULL, 10, q);
    str_n =  mpz_get_str(NULL, 10, n);
    str_e =  mpz_get_str(NULL, 10, e);

    //Cria um txt com os dados 
    FILE *file;
    file = fopen("chave-publica.txt", "w");
    fprintf(file, "p: %s\nq: %s\nn: %s\ne: %s\n",str_p,str_q, str_n, str_e);
    fclose(file);
    
    //Limpa memória alocada
    mpz_clears(p, q, e, n, NULL);
    free(str_p); free(str_q); free(str_e); free(str_n);

    return;
}

void encripitar(){
    

    return;
}
int main(){
    int voltar;
    do{
    system("clear");
    int escolha = initialChoose();
    
    switch(escolha) {
    case 1:
        chavePublica();
        printf("Voltar a tela inicial? [1,0] \n");
        scanf("%d", &voltar);
        break;
    case 2:
        encripitar();
        break;
    case 3:
        //desencriptar();
        break;
    }

    } while (voltar);
    
    
    
    return 0;
}