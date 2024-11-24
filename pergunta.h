#ifndef PERGUNTA_H
#define PERGUNTA_H

typedef struct{
    char pergunta[200];
    char alternativas[4];
    char respostaCerta[2];
}pergunta_t;

typedef struct {
    int acertos;
    int erros;
    int totalPerguntas;
    int pontuaçãoTotal;
}estatistica;

#endif