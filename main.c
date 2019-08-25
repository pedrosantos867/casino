#include <stdio.h>
#include <stdlib.h>
#include <time.h> //seed para o srand
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "debug.h"
#include "memory.h"
#include <sys/types.h>

int menuPrincipal();
int playSlotMachine();
int showScores();
int menuPlayAgain();
int guardarResultado();

int score = 0;

int * generateNumbers(int min, int max); //gerar numeros dando min e max
//char * pontucao(int numerosEntrada[2]);


int main (int argc, char *argv[])
{
	(void)argc; (void)argv; //Ignora parametros de entrada 
	printf("\n\nBem vindo ao Casino do Estoril\n\n");
	
	menuPrincipal();
}


int playSlotMachine(){
	int *numerosGerados;
	srand(time(NULL));

	printf("\n\nA gerar numeros ...\n");
	sleep(3);

	numerosGerados = generateNumbers(1,5);

	//Geração dos numeros 
	printf("\n\t\tSairam os numeros:\t\t\n");
	printf("\n+-----------------------------------------------+\n|");
	for(int i = 0; i < 3; i++){
		
		printf( "\t%d\t|", numerosGerados[i]);
	}
	printf("\n+-----------------------------------------------+\n");

	//Pontuação
	if(numerosGerados[0] == numerosGerados[1] & numerosGerados[0] == numerosGerados[2]){
		printf("Parabens, ganhou %d€\n", numerosGerados[0]*10);

	}else{
		printf("Que azar, melhor sorte para a próxima\n\n");
	}

	menuPlayAgain();
	return 1;
	
}


int * generateNumbers(int min, int max){
	static int numerosSaida[2];
	for(int i = 0; i < 3; i++){
		numerosSaida[i] = (rand()% (max-min+1))+min;
	}
	return numerosSaida;
}

int menuPrincipal(){
	printf("\nEscolha uma opção: \n1- Jogar Slot Machine\t\t2- Iniciar sessão\t\t3- Mostrar ultimos resultados\t\t4- Guardar resultado e sair\t\t99- Sair\n\n");
	
	int option;
	scanf("%d", &option);

	switch(option){
		case 1:
			playSlotMachine();
			break;
		case 2: 
			printf("\nPor implementar\n");
			printf("A voltar ao menu principal\n\n");
			sleep(2);
			printf("\e[1;1H\e[2J"); 
			menuPrincipal();
			break;
		case 3:
			showScores();
			menuPrincipal();
			break;
		case 4:
			guardarResultado();
			break;
		case 99:
			printf("\nA sair ...\n");
			sleep(3);
			break;
		default:
			printf("\nOpção invalida\n");
	}
	return option;
}

int guardarResultado(){
	char name[100];
	FILE *fptr;
	score += 10;
	printf("Introduza o seu nome\n");
	scanf("%s", &name);

	if((fptr = fopen("scores.txt", "a")) == NULL){
		printf("Error! Opening file\n");
		exit(1);
	}

	fprintf(fptr, "Nome: %s -- Score: %d\n\n", name, score);
	fclose(fptr);

	menuPrincipal();
	return 1;
}


int showScores(){
	FILE *fptr;

	char c;
	
	if((fptr = fopen("scores.txt", "r")) == NULL){
		printf("Error! Opening file\n");
		exit(1);
	}

	c = fgetc(fptr);
	while(c != EOF){
		printf("%c",c);
		c = fgetc(fptr);
	}

	fclose(fptr);
	return 1;
}

int menuPlayAgain(){
	printf("Do you want to play again?\n1- Yes\t2- Go to main menu\n");

	int option;
	scanf("%d", &option);

	switch(option){
		case 1:
			playSlotMachine();
			break;
		case 2: 
			menuPrincipal();
		default:
			printf("Opção invalida\n");
	}
	return option;
}


/* ----------------- UTILITARIOS -----------------

	for(int i = 0; i < 3; i++){
		printf( "numerosFinais[%d] = %d\n", i, numerosFinais[i]);
	}
	
	system("echo asd"); //chamar comando da SHELL 
	printf("\e[1;1H\e[2J"); //Limpar ecran 
*/