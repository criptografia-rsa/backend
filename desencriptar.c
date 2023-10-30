#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

char *desencriptar(char *p_string,char *q_string, char *e_string, char *msg_encriptada){
    //Declarando e inicializando as variáveis arbitrariamente grandes 
    mpz_t p, q, e, d, k, p_menos_1, q_menos_1, n;
    mpz_inits(p, q, e, d, k, p_menos_1, q_menos_1, n, NULL);

    //Convertendo as string para variáveis arbitrariamente grandes 
    mpz_init_set_str(p, p_string, 10);
    mpz_init_set_str(q, q_string, 10);      
    mpz_init_set_str(e, e_string, 10);

    mpz_mul(n, p, q);

    //Definindo (p-1)*(q-1) 
    mpz_sub_ui(p_menos_1, p, 1);
    mpz_sub_ui(q_menos_1, q, 1);
    mpz_mul(k, p_menos_1, q_menos_1);

    //Encontrar o inverso modular entre [e] e [k] onde k = (p-1)*(q-1)
    inverso_modular(d, e, k );

    //Converter a string msg_encriptada em um array mpz 
    mpz_t valores_encriptado[255];
    char *valor_aux_string;

    //Divide os valores a cada espaço encontrado
    valor_aux_string = strtok(msg_encriptada, " ");
    
    int z = 0;
    while (valor_aux_string != NULL)
    {   
        mpz_init(valores_encriptado[z]);
        mpz_init_set_str(valores_encriptado[z], valor_aux_string, 10);

        valor_aux_string = strtok(NULL, " ");
        z++;
    }
    
    mpz_t msg_desencriptada[255]; char *txt_descodificado = NULL;
    size_t buffer_size_0 = 4096; 
    txt_descodificado = (char *)malloc(buffer_size_0);
    
    for (int in = 0; in < z  ; in++)
    {   
        mpz_init(msg_desencriptada[in]);
        
        fastExpoMod(valores_encriptado[in], d, n, msg_desencriptada[in]);
        txt_descodificado[in] = letra_correspondente(msg_desencriptada[in]);  
    }
    
    //Cria um txt com os dados 
    FILE *file_descodificado;
    file_descodificado = fopen("mensagem-desencriptada.txt", "w");
    fprintf(file_descodificado, "%s", txt_descodificado);
    fclose(file_descodificado);
    
    return txt_descodificado;
}
