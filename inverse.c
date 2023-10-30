#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

void inverso_modular(mpz_t d, mpz_t e_temp, mpz_t k_temp){
    //Declarando os vetores necessários
    mpz_t resto[100000],  quociente[100000] , m[100000], n[100000], aux, mod_k;

    //Inicialização dos dois primeiros elementos de resto[], m[] e n[]
    mpz_inits(resto[0], resto[1],  m[0], m[1],   n[0], n[1], aux, mod_k, NULL);
    mpz_inits(quociente[0], quociente[1], NULL);

    //Atribuindo os valores conhecidos para o funcionamento da solução 
    mpz_set(resto[0], e_temp); mpz_set(resto[1], k_temp);
    mpz_set_ui(m[0], 1); mpz_set_ui(m[1], 0);
    mpz_set_ui(n[0], 0); mpz_set_ui(n[1], 1);
    mpz_set(mod_k, k_temp);

    //Calcular a mod b
    mpz_mod(aux, e_temp, k_temp);

    int tam = 0;
    while (mpz_cmp_ui(aux, 0) != 0)
    {   
        //Inicializando os novos elementos
        mpz_inits(resto[tam + 2], quociente[tam+2], m[tam+2], n[tam+2], NULL);

        //Calcula o novo quociente do array quociente[]
        mpz_tdiv_q(quociente[tam+2], resto[tam], resto[tam+1]);

        //Calcula o  novo resto do array resto[]
        mpz_mod(resto[tam + 2], resto[tam], resto[tam+1]);

        //Calculando o produto mq e nq
        mpz_t produto_mq,produto_nq;
        mpz_inits(produto_mq, produto_nq, NULL);

        mpz_mul(produto_mq, m[tam+1], quociente[tam+2]);
        mpz_mul(produto_nq, n[tam+1], quociente[tam+2]);

        //Calcula o novo m do array m[]
        mpz_sub(m[tam+2], m[tam], produto_mq );
        mpz_sub(n[tam+2], n[tam], produto_nq );

        mpz_set(e_temp, k_temp);
        mpz_set(k_temp, resto[tam+2]);
    
        //Calcular a mod b
        mpz_mod(aux, e_temp, k_temp);
        tam++;
    }

    // Verificar se m[index+1] é negativo
    while (mpz_cmp_ui(m[tam + 1], 0) < 0) {
        // Adicionar mod_k a m[index+1]
        mpz_add(m[tam + 1], m[tam + 1], mod_k);
    }

    mpz_set(d, m[tam+1]);
    
    return;
}
