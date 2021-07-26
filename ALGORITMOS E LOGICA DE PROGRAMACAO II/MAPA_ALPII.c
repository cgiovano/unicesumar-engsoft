/*
	ENGENHARIA DE SOFTWARE - 2021
	DISCENTE: CARLOS GIOVANO CUNHA MENDONÇA
	RA: 21054660-5
	ALGORITMOS E LOGICA DE PROGRAMAÇÃO I
	ATIVIDADE MAPA
*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

struct qst {
	char pergunta[256];
	int pontos[1];
};

struct paciente {
	char cpf[12];
	char nome[256];
	char sexo[2];
	int idade;
	
	int pts_qst;
	char risco[256];
};

//Questionário de diagnostico do paciente
struct qst qst_diag_pac[] = {
	{ .pergunta = "Tem Febre?: ", .pontos = 5},
	{ .pergunta = "Tem dor de cabeca?: ", .pontos = 1},
	{ .pergunta = "Tem espirro ou secrecao nasal?: ", .pontos = 1},
	{ .pergunta = "Tem irritacao na garganta?: ", .pontos = 1},
	{ .pergunta = "Tem tosse seca?: ", .pontos = 3},
	{ .pergunta = "Tem dificuldade para respirar?: ", .pontos = 10},
	{ .pergunta = "Tem dor no corpo?: ", .pontos = 1},
	{ .pergunta = "Tem diarreia?: ", .pontos = 1},
	{ .pergunta = "Teve contato com pessoas com covid 19 nos ultimos 14 dias?: ", .pontos = 10},
	{ .pergunta = "Esteve em locais com grande aglomeracao?: ", .pontos = 3}
};

//Cadastro dos dados do paciente
void cadastro_paciente(struct paciente *pac) {
	printf("Informe seu CPF: ");
	gets(pac->cpf);
	
	printf("Informe seu nome completo: ");
	gets(pac->nome);
	
	printf("Informe seu sexo | masculino(m | M) - Feminina (f / F): ");
	gets(pac->sexo);
	
	printf("Informe sua idade: ");
	scanf("%i", &pac->idade);
}

// Salva os dados do paciiente dentro de um arquivo ".txt"
void salva_cadastro(struct paciente *pac) {
	FILE *arq;
	char cad[500];
	
	// Cria o arquivo
	arq = fopen("cadastro_paciente.txt", "w");
	
	// Caso não possamos abrir o arquivo desejado, informamos o usuário. Caso tudo corra bem, imprimimos os dados em arquivo.
	if(arq == NULL) {
		printf("Ocorreu um problema o o arquivo nao pode ser aberto!");
	} else {
		fprintf(arq, "----------Cadastro Paciente---------\nCPF: %s\nPaciente: %s\nSexo: %s\nIdade: %i\nPontos: %i\nRisco: %s\nEncaminhamento para a ala de %s risco!", pac->cpf, pac->nome, pac->sexo, pac->idade, pac->pts_qst, pac->risco, pac->risco);
	}
	fclose(arq);
}

/* Validamos a entrada dos valores do questionário do paciente. Caso o valor não corresponda a um valor válido,
   vamos retornar um valor que será utilizado para realizar o tratamento. */
int valida_entrada(char entrada) {
	if (entrada == 's' || entrada == 'S') {
		return(0);
	} else if (entrada == 'n' || entrada == 'N') {
		return(1);
	} else {
		printf("Entrada invalida\n");
		return(-1);
	}
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	struct paciente paciente_teste;
	
	cadastro_paciente(&paciente_teste);
	
	//aplicamos o questionario e solicitamos a entrada do usuário.
	for (int i = 0; i < 10; i++) {
		fflush(stdin);
		char entrada;
		printf("%s", qst_diag_pac[i].pergunta);
		entrada = getchar();
		int res = valida_entrada(entrada);
		
		if (res == -1) {
			i--;	// Caso a entrada seja inválida, decrementamos, assim, repetimos a ultima pergunta.
		}
		if (res == 0) {
			paciente_teste.pts_qst += *qst_diag_pac[i].pontos;	// Caso o valor seja válido, somamos os pontos
		}
	}
	
	//Verificamos qual o risco do paciente, para que possamos direciona-lo para uma ala especifica
	if (paciente_teste.pts_qst >= 0 && paciente_teste.pts_qst <= 9)
		strcpy(paciente_teste.risco, "baixo");
	if (paciente_teste.pts_qst >= 10 && paciente_teste.pts_qst <= 19)
		strcpy(paciente_teste.risco, "medio");
	if (paciente_teste.pts_qst >= 20)
		strcpy(paciente_teste.risco, "alto");
	
	// Imprime os valores na tela
	printf("O paciente %s de CPF %s, de idade %i e sexo %s, somou %i pontos e sera encaminhado para a ala de risco %s", paciente_teste.nome, paciente_teste.cpf, paciente_teste.idade, paciente_teste.sexo, paciente_teste.pts_qst, paciente_teste.risco);
	
	// Salvamos o cadastro do paciente
	salva_cadastro(&paciente_teste);
	
	return(0);
}