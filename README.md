# damas

Trabalho de implementação da disciplina Sistemas Operacionais

Prof. Andre Luis Martinotto

Testes realizados no Ubuntu 19.04

Criar dispositivo caracter:

* sudo mknod /dev/damas c 60 0
* sudo chmod 666 /dev/damas

Compilar e instalar (na pasta driver):

* make
* sudo insmod driver.ko

Para rodar o jogo:

* gcc -o damas Damas.c
* ./damas (abrir primeira instância)
* ./damas (abrir segunda instância)
