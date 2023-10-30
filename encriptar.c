#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

char *encriptar( char *mensagem, unsigned char *n_string, unsigned char  *e_string){
    //Declarando e Inicializando variáveis arbitrariamentre grandes 
    mpz_t n, e, base;
    mpz_inits(n, e, base, NULL);

    //Convertendo a string lida para inteiro gmp
    mpz_init_set_str(n, n_string, 10);
    mpz_init_set_str(e, e_string, 10);
    
    //Pré-Codificar
    int *array_pre_codificado = NULL;
    size_t buffer_size_1 = 4096; 
    array_pre_codificado = (int *)malloc(buffer_size_1);

    //Tamanho da String Mensagem
    int tam_max = strlen(mensagem);

    //Armazena as variaveis com valores codificados
    mpz_t array_codificado[tam_max];

    for (int i = 0; i < tam_max - 1; i++)
    {
        array_pre_codificado[i] = preCodificar(mensagem[i]);
        mpz_init(array_codificado[i]);
        mpz_set_ui(base, array_pre_codificado[i]);

        // Calcula (base^exponent) % modulus
        fastExpoMod(base,e,n,array_codificado[i]);
    }
    
    //Cria um txt com os dados 
    FILE *file;
    file = fopen("mensagem-encriptada.txt", "w");

    char *response_encriptado = NULL;
    //size_t buffer_size_r = 4096; 
    response_encriptado = (char *)malloc(buffer_size_1);


    for (int k = 0; k < tam_max -1; k++)
    {   
        gmp_fprintf(file, "%Zd ",array_codificado[k]);

        char *str = mpz_get_str(NULL, 10, array_codificado[k]);
        strcat(response_encriptado, str); 
        strcat(response_encriptado, " "); 
        free(str); 
    }
    fclose(file);

    return response_encriptado;
}
