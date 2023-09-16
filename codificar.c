#include <stdio.h>


int main(){
    //Definindo um array com os caracteres a ACSII 
    char characters[95] = {
        ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
        '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
        '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'
    };



    //Declara e Recebe os textos a serem codificados
    printf("Digite o texto não codificado: \n");
    unsigned char  txtNoCript[255]; 
    fgets(txtNoCript, sizeof(txtNoCript), stdin);
    
    //Declara Array com os valores PRE-CODIFICADOS
    int preCodificados[255];


    //Declara a variavel que vai armazenar o tamanho do texto
    int tam_txt = 0;

    //Pecorre todas os caracteres 
    while (txtNoCript[tam_txt] != '\0')
    {
        //Pecorre todo o array ACSII
        for (int k = 0; k < 95; k++)
        {   
            //Caso caracter for igual ao da tabela...
            if(txtNoCript[tam_txt] == characters[k]){
                //Por que +10? Meus caracteres preCodificados vão de 32 - 126
                preCodificados[tam_txt] = k + 32;
            }
        }
    
        tam_txt++;
    }
    
    for (int i = 0; i < tam_txt -1; i++)
    {
        printf("%d ", preCodificados[i]);
    }
    
    

    return 0;
}