#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

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
    //Converte os dados em String//EXCLUIR DPS , DESNECESSÁRIO!!!
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


int preCodificar(char letra){
    //Declarando nossa referência da ACSII | Intervalo : 32-126
    char caracteres[95] = {
        ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
        '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
        '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'
    };

    for (int i = 0; i < 95; i++)
    {
        if(letra == caracteres[i]){
            return i + 32;
        } 
    }
    //RESOLVER PROBLEMA PQ TA PASSANDO O FOR NO ULTIMO CARACTER QUE NAO DEVERIA EXISTIR
    //printf("Caracter %c é inválido!\n", letra);
    //return -1;
}

void encriptar(char mensagem[255], char n_string[255], char  e_string[255]){
        //Declarando e Inicializando variáveis arbitrariamentre grandes 
        mpz_t n, e, base;
        mpz_inits(n, e, base, NULL);

        //Convertendo a string lida para inteiro gmp
        mpz_init_set_str(n, n_string, 10);
        mpz_init_set_str(e, e_string, 10);
        
        //Pré-Codificar
        int i = 0, array_pre_codificado[255];
        while (mensagem[i] != '\0')
        {   
            array_pre_codificado[i] = preCodificar(mensagem[i]);
            i++;
        }
        
        //Codificar 
        mpz_t array_codificado[i];


        for (int k = 0; k < i - 1; k++)
        {   mpz_init(array_codificado[k]);
            mpz_set_ui(base, array_pre_codificado[k]);

            // Calcula (base^exponent) % modulus
            mpz_powm(array_codificado[k], base, e, n);
        }
        

        
        
        //Cria um txt com os dados 
        FILE *file;
        file = fopen("mensagem-encriptada.txt", "w");

        for (int k = 0; k < i -1; k++)
        {   
            gmp_fprintf(file, "%Zd ",array_codificado[k]);
        }

        fclose(file);
       

        
        


       
        

        
        
        
    
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
        getchar();
        switch(escolha) {
        case 1:
            //Lendo a entrada como string
            char p_string[100], q_string[100], e_string[100];
            printf("Digite os valores de p q e:\n");
            scanf(" %s %s %s", p_string, q_string, e_string);

            chavePublica(p_string, q_string,e_string);
            break;
        case 2:
            unsigned char mensagem[255];
            printf("Digite a mensagem a ser encriptada:\n");
            fgets(mensagem, sizeof(mensagem), stdin);

            unsigned char n_str[255], e_str[255];
            printf("Digite o valor a chave publica (n,e)\n");
            scanf(" %s %s", n_str, e_str);
            
            encriptar(mensagem, n_str, e_str);
            

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