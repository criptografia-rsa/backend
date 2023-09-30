#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

char letra_correspondente(mpz_t index){
    char caracteres[95] = {
        ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
        '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
        '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'
    };

    
    long int intIndex = mpz_get_si(index);

    if(intIndex -32 > 94 || intIndex < 0 ){
        printf("Valor recebido: %ld", intIndex -32);
        return '*';
    } 
    //gmp_printf("%c", caracteres[intIndex - 32]);
    return caracteres[intIndex - 32];
    

}


void inverso_modular(mpz_t d, mpz_t e_temp, mpz_t k_temp){
    
    //Declarando os vetores necessários
    mpz_t resto[1000],  quociente[1000] , m[1000], n[1000], aux, mod_k;

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
    //printf("TXT ALTERADO!\n");
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
            //printf("Entrou no letra  == caracter[]i\n");
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

void desencriptar(char p_string[255],char q_string[255], char e_string[255], char *msg_encriptada){
    printf("Entrou em desencriptar()\n");
    //printf("O valor digitado foi: %s\n\n:", msg_encriptada);
    //printf("%s %s %s\n%s", p_string, q_string,e_string, msg_encriptada );

    //Declarando e inicializando as variáveis arbitrariamente grandes 
    mpz_t p, q, e, d, k, p_menos_1, q_menos_1, n;
    mpz_inits(p, q, e, d, k, p_menos_1, q_menos_1, n, NULL);

    //Convertendo as string para variáveis arbitrariamente grandes 
    mpz_init_set_str(p, p_string, 10);
    mpz_init_set_str(q, q_string, 10);      
    mpz_init_set_str(e, e_string, 10);

    //Calculando n 
    mpz_mul(n, p, q);

    //Definindo (p-1)*(q-1) 
    mpz_sub_ui(p_menos_1, p, 1);
    mpz_sub_ui(q_menos_1, q, 1);
    mpz_mul(k, p_menos_1, q_menos_1);

    //Encontrar o inverso modular entre [e] e [k] onde k = (p-1)*(q-1)
    inverso_modular(d, e, k );
    gmp_printf("#######O inverso é : %Zd\n",d);

    //Converter a string msg_encriptada em um array mpz 
    mpz_t valores_encriptado[255];
    

    char *valor_aux_string;
    valor_aux_string = strtok(msg_encriptada, " ");

    //Divide os valores a cada espaço encontrado
    int z = 0;
    while (valor_aux_string != NULL)
    {   
        mpz_init(valores_encriptado[z]);
        mpz_init_set_str(valores_encriptado[z], valor_aux_string, 10);
        //gmp_printf("%Zd\n", valores_encriptado[z]);
        valor_aux_string = strtok(NULL, " ");
        z++;
    }
    
   
    mpz_t msg_desencriptada[255]; char txt_descodificado[255];
    
    
    
    for (int in = 0; in < z  ; in++)
    {   
        mpz_init(msg_desencriptada[in]);
        
        /*#####################################################################################
            USAR EXPONENCIAÇÃO MODULAR RAPIDA (ADD FUNCAO DPS) => (base^exponent) % modulus
        ######################################################################################*/
        mpz_powm(msg_desencriptada[in], valores_encriptado[in], d, n);
        //gmp_printf("Numero passado: %Zd\n", msg_desencriptada[in]);
        txt_descodificado[in] = letra_correspondente(msg_desencriptada[in]);  
        printf("%d: %c\n", in, letra_correspondente(msg_desencriptada[in])); 
    }
    
    //Cria um txt com os dados 
    FILE *file_descodificado;
    file_descodificado = fopen("mensagem-desencriptada.txt", "w");
    fprintf(file_descodificado, "%s", txt_descodificado);
    fclose(file_descodificado);
    
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
            //Lendo os valores de p q e 
            unsigned char p_s[255], q_s[255], e_s[255];
            printf("Digite o valor de p, q, e :\n");
            scanf(" %s %s %s", p_s, q_s, e_s);
            getchar();

            //Memoria alocada dinamicamente
            char *msg_encriptada = NULL;
            size_t buffer_size = 4096; 
            msg_encriptada = (char *)malloc(buffer_size);

            printf("Digite a mensagem encriptada:\n");
            //getchar();
            fgets(msg_encriptada, buffer_size, stdin);
            
           
            desencriptar(p_s, q_s, e_s, msg_encriptada);
            
            break;
        }

        printf("Voltar a tela inicial? [1,0] \n");
        scanf("%d", &voltar);

    } while (voltar);
    
    return 0;
}