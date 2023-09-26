<h1>Documentação | Criptografia RSA </h1> 


<h3>Código Unicode </h3>D

* Unicode e Caracteres que representão da posição 32-126 ASCII (https://www.ime.usp.br/~pf/algoritmos/apend/ascii.html)

        characters[95] 

        {
            ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
            '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
            'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
            '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
            'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'
        }


<h3>Biblioteca GMP</h3>
*Essa biblioteca tem como objetivo permitir a operação de números arbitrariamente grandes 

<h4>Instalando a Biblioteca GMP </h4>


<strong>Ubuntu/Debian</strong> 

    sudo apt-get update
    sudo apt-get install libgmp-dev

<strong>Fedora/strong> 

    sudo dnf install gmp-devel

<strong>Arch Linux</strong> 

    sudo pacman -S gmp

<strong>macOS - Usando Homebrew</strong> 

    macOS (Usando Homebrew)

<strong>Qualquer Sistema</strong> 

    curl -O https://gmplib.org/download/gmp/gmp-x.y.z.tar.xz

    tar -xvf gmp-x.y.z.tar.xz

    cd gmp-x.y.z

    ./configure
    make
    sudo make install



<h3>Teste | Valores de Entrada</h3>

01 Gerar Chave Publica (n,e)

p: 81071
q: 91397
e: 100417

02 Encritar 



03 Desencriptar