/*
	BACHARELADO EM ENGENHARIA DE SOFTWARE 2021
	ATIVIDADE 3 - ALGORITMOS E LÓGICA DE PROGRAMAÇÃO 2
	DISCENTE: CARLOS GIOVANO CUNHA MENDONÇA
	RA: 21054660-5
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>	//inclui a biblioteca stdbool para trabalhar com booleanos, necessária a depender da versão do compilador.

int main() {
	int quantidade_cartelas;
	bool duplicado;	// chave de verificação para valores duplicados
	
	printf("Digite a quantidade de cartelas: ");
	scanf("%i", &quantidade_cartelas);

	int numeros_cartela[quantidade_cartelas][10];	//cria uma matriz com a quantidade de cartelas desejadas com 10 elementos cada.
	
	srand(time(NULL));
	
	for (int i = 0; i < quantidade_cartelas; i++) {
		int j = 0;
		while (j < 10) {
			duplicado = false;
			int numero_aleatorio = rand() % 99;
			
			/*Percorre a matriz na linha i e verifica se o número aleatório gerado é igual ao elemento j da linha.
			  Caso seja igual, significa que é duplicado e então interrompemos o loop e continuamos com a operação.*/
			for (int k = 0; k < j; k++) {
				if (numero_aleatorio == numeros_cartela[i][k]) {
					duplicado = true;
					break;
				}
			}
			
			/*Caso o número aleatório gerado não seja duplicado, atribuimos esse valor ao elemento j da linha i da 
			matriz, em seguida passamos para o próximo elemento j.*/
			if (!duplicado) {
				numeros_cartela[i][j] = numero_aleatorio;
				j++;
			}
		}
	}
	
	// imprime os valores da matriz
	for (int i = 0; i < quantidade_cartelas; i++) {
		printf("cartela %i: ", i+1);
		for (int j = 0; j < 10; j++) {
			printf("%d\t", numeros_cartela[i][j]);
		}
		printf("\n\n");
	}

	return(0);
}
	
	                               