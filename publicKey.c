#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

char *chavePublica(char *p_string,char *q_string, char *e_string){

    //Declarando as variáveis mpz
    mpz_t p,q,e,n;
    mpz_inits(p, q,e,n, NULL);

    //Convertendo a entrada para mpz (Inteiro Arbitrariamente Grande)
    mpz_init_set_str(p, p_string, 10);
    mpz_init_set_str(q, q_string, 10);
    mpz_init_set_str(e, e_string, 10);

    //Calcula a Chave Publica 
    mpz_mul(n, p, q);

    //Converte os dados em String
    char *str_n, *str_e;
    str_n =  mpz_get_str(NULL, 10, n);
    str_e =  mpz_get_str(NULL, 10, e);

    //Concatenando as strings 
    int tam_string = strlen(str_n) + strlen(str_e) + 2;
    char *response = (char *)malloc(tam_string * sizeof(char));

    snprintf(response, tam_string, "%s %s", str_n, str_e);

    //Cria um txt com os dados 
    FILE *file;
    file = fopen("chave-publica.txt", "w");
    fprintf(file, "%s",response);
    fclose(file);
    
    //Limpa memória alocada
    mpz_clears(p, q, e,n, NULL);
    free(str_e); free(str_n);

    return response;
}
