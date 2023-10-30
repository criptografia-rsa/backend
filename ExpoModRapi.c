#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

void fastExpoMod(mpz_t base, mpz_t expoente, mpz_t n, mpz_t lastRest ){
    //Declarando expoente temporário
    mpz_t expoente_temp;
    mpz_init(expoente_temp);
    mpz_set(expoente_temp, expoente);

    mpz_t binary_inverse[10000], binary[10000], resto[10000];

    //Transforma o numero para binario (Invertido)
    int i = 0;
    while (mpz_cmp_ui(expoente_temp, 0) > 0)
    {   
        mpz_t expo_mod_2; 
        mpz_inits(expo_mod_2, binary_inverse[i], NULL);

        //Calcula expoente % 2
        mpz_mod_ui(expo_mod_2, expoente_temp, 2);

        //Atribuição
        mpz_set(binary_inverse[i], expo_mod_2);

        //Calcula expoente/2
        mpz_div_ui(expoente_temp, expoente_temp, 2);
        i++;
    }

    mpz_set(resto[0], base);
    
    //Correção do binário & Aplicação da Exponenciação Modular Rápida
    for (int k = 1; k < i; k++)
    {   
        mpz_init(binary[k]);
        mpz_set(binary[k], binary_inverse[i - k - 1]);
        
        //Calculando resto[k] = resto[k - 1]² mod n
        mpz_mul(resto[k], resto[k - 1], resto[k - 1]);
        mpz_mod(resto[k], resto[k], n);

        if(mpz_cmp_ui(binary[k], 1) == 0){
            //resto[k] = (resto[k]*base) % n;
            mpz_mul(resto[k], resto[k], base);
            mpz_mod(resto[k], resto[k], n);
        }
    }
    
    mpz_set(lastRest, resto[i-1]);

    return;
}
