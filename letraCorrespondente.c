#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

char letra_correspondente(mpz_t index){
    //Caracteres definidos
    char caracteres[95] = {
        ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
        '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
        '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'
    };
    
    long int intIndex = mpz_get_si(index);

    //Caso caracter estiver fora do nosso escopo
    if(intIndex -32 > 94 || intIndex < 0 ){
        return 'Ø';
    } 
   
    return caracteres[intIndex - 32];
}
