#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DEVICE_NAME "/dev/damas"
#define BUF_MSG 6

int numJogador = 0;
char *jogador;
char * buffer;
int cont = 0;

int writeDriver(char word[BUF_MSG])
{
  int file;
  file = open(DEVICE_NAME, O_WRONLY);

  if (file > 0) {
    write(file, word, BUF_MSG);
    close(file);
  }

  return 1;
}

char* readDriver()
{
  int file;
  char *word = (char*) malloc(BUF_MSG);
  file = open(DEVICE_NAME, O_RDONLY);

  if (file > 0) {
    read(file, word, BUF_MSG);
    close(file);
  }

  return word;
}

int initJogo(){
    writeDriver("00000");
    printf("Jogo Iniciado\n");
    writeDriver("10000");
    setJogador(1,"JOGADOR1");
}

//Realiza Jogada
int realizaJogada(){
    if(numJogador == 1){
         writeDriver("13489");
    }else{
         writeDriver("27623");
    }

}

//Pega a movimentação realizada
int getLinCol(){
    int linhaInicial;
    int colunaInicial;
    int linhaFinal;
    int colunaFinal;

    char jogadaArr[BUF_MSG];
    
    strcpy(jogadaArr, readDriver());
    linhaInicial = jogadaArr[1] - '0';
    colunaInicial = jogadaArr[2] - '0';
    linhaFinal = jogadaArr[3] - '0';
    colunaFinal = jogadaArr[4] - '0';

     printf("Linha Inicial %d - %d\n", linhaInicial, numJogador);
     printf("Coluna Inicial %d - %d\n",colunaInicial,numJogador);
     printf("Linha final %d - %d\n",linhaFinal,numJogador);
     printf("Coluna final %d - %d\n",colunaFinal,numJogador);
}
//Vê se é jogada final
int isFinal(){
   
    printf("BUFFER FINAL %s - %d \n",readDriver(),numJogador);
    return strcmp("11111",readDriver())==0;
}


//Pega o jogador da ultima jogada
int getPlayer(){
    char jogadaArr[BUF_MSG];
    char jogadorChar;
    int jogadorInt;
    strcpy(jogadaArr, readDriver());
    jogadorChar = jogadaArr[0];
    jogadorInt =  jogadorChar - '0';
    return jogadorInt ;
}

//Seta o jogador da execução
int setJogador(int num , char * nome){
    numJogador = num;
    jogador = nome;
}

//Espera outro jogador
int wait (){
    
    printf("WAIT BUFFER %s \n",readDriver() );
    while(getPlayer(readDriver()) == numJogador && !isFinal()){
        sleep(1);
       
        printf("WAIT BUFFER %s \n",readDriver() );
    }
}

int main(){
    if(!strcmp("00000",readDriver())==0 && !strcmp("10000",readDriver())==0 && !strcmp("20000",readDriver())==0){
        initJogo();
    }else if(strcmp("10000",readDriver())==0){
        setJogador(2,"JOGADOR2");
        writeDriver("20000");
    }

    while(!isFinal())
    {
        wait();
        if(!isFinal()){
            getLinCol();
            realizaJogada();

            if(numJogador == 1){
                cont++;
                if(cont == 5){
                    writeDriver("11111");
                }
            }
        }
       
    };
    
    printf("Jogador vencedor %d",getPlayer());
    
}
