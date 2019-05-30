#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>
void showErrors(int cod){
	char c;
	switch (cod){
		case 1:
			printf("A linha inicial n�o est� na forma correta \n");
		break;
		case 2:
			printf("A coluna inicial n�o est� na forma correta \n");
		break;
		case 3:
			printf("A linha destino n�o est� na forma correta \n");
		break;
		case 4:
			printf("A coluna inicial n�o est� na forma correta \n");
		break;
		case 5:
			printf("Esse espa�o � vazio n�o pode ser movido \n");
		break;
		case 6:
			printf("Movimento Inv�lido  \n");
		break;
		case 7:
			printf("N�o � permitido andar para tr�s \n");
		break;
		case 8:
			printf("Voc� est� jogando com as pe�as erradas \n");
		break;
		case 9:
			printf("Voc� s� pode ir em um espa�o em branco \n");
		break;
		case 10:
			printf("Para realizar essa jogada precisa ter uma pe�a adversaria no meio \n");
			break;
		default:
			printf("Jogada efetuada! \n");	
	}
}
int validaDiagonalRainha(int initLin,int initCol,int destCol,int destLin,int matrizTabuleiro[9][9],int aux){
		if(initLin!=destLin && initCol!=destCol){		
			if(initLin>destLin && initCol<destCol){
				if(matrizTabuleiro[initLin-1][initCol+1]==99){
					validaDiagonalRainha(initLin-1,initCol+1,destCol,destLin,matrizTabuleiro,aux);
				}else if((aux==15 && matrizTabuleiro[initLin-1][initCol+1]==11 && initLin-2==destLin && initCol+2==destCol && matrizTabuleiro[destLin][destCol]==99)|| (aux==16 && matrizTabuleiro[initLin-1][initCol+1]==10  && initLin-2==destLin && destCol+2==destCol && matrizTabuleiro[destLin][destCol]==99)){
					return 1;
				}else{
					return 0;
				}
			}else if(initLin<destLin && initCol>destCol){
				if(matrizTabuleiro[initLin+1][initCol-1]==99){
					validaDiagonalRainha(initLin+1,initCol-1,destCol,destLin,matrizTabuleiro,aux);
				}else if((aux==15 && matrizTabuleiro[initLin+1][initCol-1]==11 && initLin+2==destLin && initCol-2==destCol && matrizTabuleiro[destLin][destCol]==99)|| (aux==16 && matrizTabuleiro[initLin+1][initCol-1]==10  && initLin+2==destLin && destCol-2==destCol && matrizTabuleiro[destLin][destCol]==99)){
					return 1;
				}else{
					return 0;
				}
			}else if(initLin<destLin && initCol<destCol){
				if(matrizTabuleiro[initLin+1][initCol+1]==99){
					validaDiagonalRainha(initLin+1,initCol+1,destCol,destLin,matrizTabuleiro,aux);
				}else if((aux==15 && matrizTabuleiro[initLin+1][initCol+1]==11 && initLin+2==destLin && initCol+2==destCol && matrizTabuleiro[destLin][destCol]==99)||(aux==16 && matrizTabuleiro[initLin+1][initCol+1]==10  && initLin+2==destLin && destCol+2==destCol && matrizTabuleiro[destLin][destCol]==99)){
					return 1;
				}else{
					return 0;
				}
			}else if(initLin>destLin && initCol>destCol){
				if(matrizTabuleiro[initLin-1][initCol-1]==99){
					validaDiagonalRainha(initLin-1,initCol-1,destCol,destLin,matrizTabuleiro,aux);
				}else if((aux==15 && matrizTabuleiro[initLin-1][initCol-1]==11 && initLin-2==destLin && initCol-2==destCol && matrizTabuleiro[destLin][destCol]==99)|| (aux==16 && matrizTabuleiro[initLin-1][initCol-1]==10  && initLin-2==destLin && destCol-2==destCol && matrizTabuleiro[destLin][destCol]==99)){
					return 1;
				}else{
					return 0;
				}
			}
		}else if(matrizTabuleiro[destLin][destCol]==99){
			return 1;
		}else{
			return 0;
		}
}

int validaMovimento(int initLin,int initCol,int destCol,int destLin,int diff, int aux,int destino,int medio,int vez,int queen,int matrizTabuleiro[9][9]){
	if(vez==0 && aux==10 ||vez==0 && aux==15|| vez==1 && aux==11||vez==1 && aux==16){
		if(diff==2 && queen==0 || diff==1 && queen==0 ){
			char descAsc;
			if(aux==99){
				showErrors(5);
				return 0;
			}else if (aux==10){
				descAsc='d';
			}else if(aux==11){
				descAsc='a';
			}
			//TESTE FRENTE-TR�S
			if((descAsc=='a' && destLin<initLin) || (descAsc=='d' && destLin>initLin)|| diff>=2){
				if(diff==1){
					//TESTE DIAGONAL
					if(destCol==initCol-1||destCol==initCol+1){
						//TESTE VAZIO
						if(destino!=99){
							showErrors(9);
							return 0;
						}
						return 1;
					}else{
						showErrors(6);
						return 0;
					}
				}else if(diff==2){
					if(destCol==initCol-2||destCol==initCol+2){
						if(destino!=99){
							showErrors(9);
							return 0;
						}
						if(descAsc=='d' && (medio!=11 && medio!=16)){
							showErrors(10);
							return 0;
						}
						if(descAsc=='a' && (medio!=10 && medio!=15)){
							showErrors(10);
							return 0;
						}
						return 1;
					}else{
						showErrors(6);
						return 0;
					}		
				}else{
					showErrors(6);
					return 0;
				}
	 		}else{
	 			showErrors(7);
	 			return 0;
	 		}
		}else if(queen){
				if(initLin>destLin && initCol<destCol || initLin<destLin && initCol>destCol || initLin<destLin && initCol<destCol || initLin>destLin && initCol>destCol){
					if(validaDiagonalRainha(initLin,initCol,destCol,destLin,matrizTabuleiro,aux)){
						return 1;
					}else{
						showErrors(6);
						return 0;
					}
				}else{
					showErrors(6);
					return 0;
				}
		}else{
			showErrors(6);
			return 0;
		}
	}else{
   		showErrors(8);
   		return 0;
   	}
}
int validaEntrada(int initLin,int initCol,int destCol,int destLin){
	if(initLin<1||initLin>8){
		showErrors(1);
		return 0;
	}else if(initCol<1||initCol>8){
		showErrors(2);
		return 0;
	}else if(destLin<1||destLin>8){
		showErrors(3);
		return 0;
	}else if(destCol<1||destCol>8){
		showErrors(4);
		return 0;
	}else{
		return 1;
	}
} 
int lePosicoes(int *pinitLin,int *pinitCol,int *pdestLin,int *pdestCol){
	printf("\nDigite a posi��o inicial da pe�a({n�mero linha}{n�mero coluna}):",setlocale(LC_ALL,""));
	scanf("%d",pinitLin);
    printf("\nDigite a posi��o final da pe�a({n�mero linha}{n�mero coluna}):",setlocale(LC_ALL,""));
    scanf("%d",pdestLin);
    *pinitCol=*pinitLin%10;
    *pinitLin=*pinitLin/10;
    *pdestCol=*pdestLin%10;
    *pdestLin=*pdestLin/10;
    return validaEntrada(*pinitLin,*pinitCol,*pdestCol,*pdestLin);
}

void populaDadosvalidacao(int matrizTabuleiro[9][9], int *paux,int *pdestino,int *pmedio,int *pmedLin,int *pmedCol,int *pdiff, int initLin, int destLin,int initCol, int destCol){
	*pdiff = abs(initLin-destLin);
	*paux=matrizTabuleiro[initLin][initCol];
	*pdestino=matrizTabuleiro[destLin][destCol];
	if(*pdiff>=2){
		if(initLin>destLin && initCol>destCol){
			*pmedCol=destCol+1;
			*pmedLin=destLin+1;
		} else if(initLin<destLin && initCol<destCol){
			*pmedCol=destCol-1;
			*pmedLin=destLin-1;
		} else if(initLin>destLin && initCol<destCol){
			*pmedCol=destCol-1;
			*pmedLin=destLin+1;
		}if(initLin<destLin && initCol>destCol){
			*pmedCol=destCol+1;
			*pmedLin=destLin-1;
		}
		*pmedio=matrizTabuleiro[*pmedLin][*pmedCol];
	}
}
int jogada(int matrizTabuleiro[9][9],int vez,int *ppontos,int *pcontnc){
	int initLin,initCol,destLin,destCol,aux,queen,destino,medLin,medCol,medio,diff;
    if(lePosicoes(&initLin,&initCol,&destLin,&destCol)){
    	if(vez==0 && matrizTabuleiro[initLin][initCol]==15 || vez==1 && matrizTabuleiro[initLin][initCol]==16){
    		queen=1; 
    	}else{
    		queen=0;
		}	
		populaDadosvalidacao(matrizTabuleiro,&aux,&destino,&medio,&medLin,&medCol,&diff,initLin,destLin,initCol,destCol);    	
        if(validaMovimento(initLin,initCol,destCol,destLin,diff,aux,destino,medio,vez,queen,matrizTabuleiro)){
        	*pcontnc=*pcontnc+1;
			//troca pe�a
			matrizTabuleiro[initLin][initCol]=99;
    		matrizTabuleiro[destLin][destCol]=aux;
    		//come pe�a
    		if(diff>=2){
    			matrizTabuleiro[medLin][medCol]=99;
				*ppontos=*ppontos+1;
				*pcontnc=0;		
    		}
    		//troca rainha
    		if(vez==0 && destLin==8){
    			matrizTabuleiro[destLin][destCol]=15; 
    		}
    		if(vez==1 && destLin==1){
    			matrizTabuleiro[destLin][destCol]=16; 
    		}
    		return 1;
    	}else{
    		return 0;
		}
    }else{
    	return 0;
	}
}
void mostraTabuleiro (int matrizTabuleiro[9][9]){
	//10-Brancos 11-pretos 15-rainhaBranca 16-rainhaPreta 99-espa�o vazio;
	int i,j;
	printf("\n\n\n______________________________\n");
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			switch(matrizTabuleiro[i][j]){
				case 99: printf("   ");
				    break;
				case 10:
					printf(" %c ",'x');
					break;
				case 11:
					printf(" %c ",'o');
				break;
				case 15:
					printf(" %c ",'r');
				break;
				case 16:
					printf(" %c ",'q');
				break;
				default: printf(" %d ",matrizTabuleiro[i][j]);
						}
		}
		printf("\n______________________________\n");
	}
	printf("______________________________");
printf("\n");
}
void trocaVez(int sucess,int *pvez){
	if(sucess){
			if(*pvez==0){
				*pvez=1;
			}else if(*pvez==1){
				*pvez=0;
			}
		}
}
void contaPecas(int matrizTabuleiro[9][9],int *ppb,int *ppp,int *pdb,int *pdp){
	int i,j; 
	for(i=1;i<9;i++){
		for(j=1;j<9;j++){
			switch(matrizTabuleiro[i][j]){
				case 10:*ppb=*ppb+1;
				break;
				case 11:*ppp=*ppp+1;
				break;
				case 15:*pdb=*pdb+1;
				break;
				case 16:*pdp=*pdp+1;
				break;
			}
		}
	}
}
int fimDeJogo(int matrizTabuleiro[9][9],int pcontnc,int *pganhador){
	int ppb=0,ppp=0,pdb=0,pdp=0;
	contaPecas(matrizTabuleiro,&ppb,&ppp,&pdb,&pdp);
	if(pcontnc>20||(ppp==0&&ppb==0&&pdb==2&&pdp==2)||(ppp==0&&ppb==0&&pdb==2&&pdp==1)||(ppp==0&&ppb==0&&pdb==1&&pdp==2)||(ppp==0&&ppb==1&&pdb==1&&pdp==2)||(ppp==1&&ppb==0&&pdb==2&&pdp==1)||(ppp==0&&ppb==0&&pdb==1&&pdp==1)||(ppp==0&&ppb==1&&pdb==1&&pdp==1)||(ppp==1&&ppb==0&&pdb==1&&pdp==1)){
		*pganhador=0;
		return 1;
	}else if((ppp==0&&pdp==0&&(ppb!=0||pdb!=0))||(ppb==0&&pdb==0&&(ppp!=0||pdp!=0))){
		*pganhador=1;
		return 1;
	}else if(ppb!=0||ppp!=0||pdb!=0||pdp!=0){
		return 0;
	}
}
void lerNomes(char pj1[50],char pj2[50]){
	printf("\nDigite o nome do primeiro jogador(m�ximo de 50 caracteres):",setlocale(LC_ALL,""));
	scanf("%s",pj1);
	printf("\nDigite o nome do segundo jogador(m�ximo de 50 caracteres):",setlocale(LC_ALL,""));
	scanf("%s",pj2);
}
void instrucoes(char pj1[50],char pj2[50]){
	int opcao;
	printf("|--------------------------------------------------|\n");
	printf("|                INSTRU��ES                        |\n",setlocale(LC_ALL,""));
	printf("| PE�AS:                                           |\n",setlocale(LC_ALL,""));
	printf("| AS PEDRAS VERMELHAS S�O REPRESENTADAS POR UM X   |\n",setlocale(LC_ALL,""));
	printf("| AS DAMAS VERMELHAS S�O REPRESENTADAS POR UM r    |\n",setlocale(LC_ALL,""));
    printf("| AS PEDRAS BRANCAS S�O REPRESENTADAS POR UM o     |\n",setlocale(LC_ALL,""));
	printf("| AS DAMAS BRANCAS S�O REPRESENTADAS POR UM q      |\n",setlocale(LC_ALL,""));
	printf("| COMO JOGAR:                                      |\n",setlocale(LC_ALL,""));
	printf("| 1.O JOGADOR 1(PE�AS VERMELHAS) COME�AR� A PARTIDA|\n",setlocale(LC_ALL,""));
	printf("| 2.PARA MOVIMENTAR AS PE�AS DIGITE O N�MERO DA LI-|\n",setlocale(LC_ALL,""));
	printf("| NHA INICIAL SEGUIDO DO N�MERO DA COLUNA INICIAL. |\n",setlocale(LC_ALL,""));
    printf("| EXEMPLO: 34 (LINHA 3 COLUNA 4). LOGO AP�S DIGITE |\n",setlocale(LC_ALL,""));
	printf("| O N�MERO DA LINHA DESTINO SEGUIDO DO N�MERO DA   |\n",setlocale(LC_ALL,""));
	printf("| COLUNA DESTINO.EXEMPLO 45(LINHA 4 COLUNA 5).     |\n",setlocale(LC_ALL,""));
	printf("|--------------------------------------------------|\n",setlocale(LC_ALL,""));
	printf("| PARA JOGAR TECLE 1                               |\n",setlocale(LC_ALL,""));
	printf("|--------------------------------------------------|\n",setlocale(LC_ALL,""));
    printf("Digite a op��o:",setlocale(LC_ALL,""));
	scanf("%d",&opcao);
	switch(opcao){
		case 1:lerNomes(pj1,pj2);
		break;
		default:printf("Op��o inexistente: \n");
		instrucoes(pj1,pj2);
	}
}
void criaMenu(char pj1[50],char pj2[50]){
	int opcao;
	printf("|--------------------------------------------------|\n");
	printf("|                Bem Vindo a Damas 1.0             |\n");
	printf("|                1-JOGAR                           |\n");
	printf("|                2-INTRU��ES                       |\n",setlocale(LC_ALL,""));
	printf("|--------------------------------------------------|\n");
	printf("Digite a op��o:",setlocale(LC_ALL,""));
	scanf("%d",&opcao);
	switch(opcao){
		case 1:lerNomes(pj1,pj2);
		break;
		case 2:instrucoes(pj1,pj2);
		break;
		default:printf("Op��o inexistente: \n",setlocale(LC_ALL,""));
		criaMenu(pj1,pj2);
	}
}

int main(){
	//jogador1 -> vez=0 -> X //jogador2 ->vez1 ->O
	int vez=0,joga=0,sucess,pj1=0,pj2=0,contnc=0,ganhador,teste;
	char jogador1[50],jogador2[50];
	int matrizTabuleiro[9][9]={{99,1,2,3,4,5,6,7,8},
		                         {1,99,10,99,10,99,10,99,10},
		                         {2,10,99,10,99,10,99,10,99},
		                         {3,99,10,99,10,99,10,99,10},
		                         {4,99,99,99,99,99,99,99,99},
		                         {5,99,99,99,99,99,99,99,99},
		                         {6,11,99,11,99,11,99,11,99},
		                         {7,99,11,99,11,99,11,99,11},
		                         {8,11,99,11,99,11,99,11,99}};
	criaMenu(jogador1,jogador2);
	while(joga==0){
		switch(vez){
			case 0: printf("Sua vez %s (PE�AS x)\n",jogador1,setlocale(LC_ALL,""));
			break;
			case 1: printf("Sua vez %s (PE�AS o)\n",jogador2,setlocale(LC_ALL,""));
		}
		printf("Pontua��o %s : %d \n",jogador1,pj1,setlocale(LC_ALL,""));
		printf("Pontua��o %s : %d \n",jogador2,pj2,setlocale(LC_ALL,""));
		mostraTabuleiro(matrizTabuleiro);
		switch(vez){
			case 0: trocaVez(jogada(matrizTabuleiro,vez,&pj1,&contnc),&vez);
			break;
			case 1: trocaVez(jogada(matrizTabuleiro,vez,&pj2,&contnc),&vez);;
		}
		system("cls");
		joga=fimDeJogo(matrizTabuleiro,contnc,&ganhador);
		if(joga==1){
			if(ganhador==0){
				printf("Que pena!O jogo terminou empatado!!");
			}else if(ganhador==1){
				if(pj1>pj2){
					printf("O %s ganhou!",jogador1,setlocale(LC_ALL,""));
				}else if(pj2>pj1){
					printf("O %s ganhou!",jogador2,setlocale(LC_ALL,""));
				}
			}
		}
	}
}