#ifndef QUIZ_H
#define QUIZ_H

// Estruturas
typedef struct {
    char pergunta[256];
    char alternativas[4][128];
    int respostaCorreta; // Índice da resposta correta
} Pergunta;

typedef struct {
    char nomeJogador[50];
    int pontuacao;
} Estatistica;

// Funções principais
void menuPrincipal();
void iniciarJogo();
void exibirEstatisticas();
void carregarPerguntas(char *arquivo, Pergunta **perguntas, int *quantidade);
void salvarEstatistica(Estatistica estat);

#endif // QUIZ_H

