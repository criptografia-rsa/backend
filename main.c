#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

int escolhaInicial(){
    
    printf("1-Gerar chave pública\n");
    printf("2-Encriptar\n");
    printf("3-Desencriptar.\n");

    int escolha;
    scanf("%d", &escolha);

    if(escolha>3 || escolha < 1){
        system("clear");
        printf("*Digite uma escolha válida*\n\n");
        return escolhaInicial();
    }
    system("clear");
    return escolha;
}

void chavePublica(char p_string[100],char q_string[100], char e_string[100]){

    //Declarando as variáveis mpz
    mpz_t p,q,e,n;
    mpz_inits(p, q,e,n, NULL);

    //Convertendo a entrada para mpz (Inteiro Arbitrariamente Grande)
    mpz_init_set_str(p, p_string, 10);
    mpz_init_set_str(q, q_string, 10);
    mpz_init_set_str(e, e_string, 10);

    //Calcula a Chave Publica 
    mpz_mul(n, p, q);

    //gmp_printf("p: %Zd | q: %Zd | e: %Zd | n: %Zd\n", p, q, e, n);
    printf("TXT ALTERADO!\n");
    //Converte os dados em String//EXCLUIR DPS DESNECESSÁRIO
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
    mpz_clears(p, q, e,n, NULL);
    free(str_p); free(str_q); free(str_e); free(str_n);

    return;
}

void encriptar(){
        printf("Entrou no  encriptar()\n");

    
    return;
}

void  desencriptar(){
    printf("Entrou no  desencriptar()\n");
    
    return;
}


int main(){
    int voltar;
    do{
        system("clear");
        int escolha = escolhaInicial();
        
        switch(escolha) {
        case 1:
            //Lendo a entrada como string
            char p_string[100], q_string[100], e_string[100];
            printf("Digite os valores de p q e:\n");
            scanf(" %s %s %s", p_string, q_string, e_string);

            chavePublica(p_string, q_string,e_string);
            break;
        case 2:
            encriptar();
            

            break;
        case 3:
            desencriptar();
            break;
        }

        printf("Voltar a tela inicial? [1,0] \n");
        scanf("%d", &voltar);

    } while (voltar);
    
    return 0;
}