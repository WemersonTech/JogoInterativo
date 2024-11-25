#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "quiz.h"

// Função para embaralhar alternativas
void embaralharAlternativas(Pergunta *pergunta) {
    int i, j;
    char temp[128];
    int tempResposta;

    // Embaralha as alternativas usando o algoritmo de Fisher-Yates
    for (i = 0; i < 4; i++) {
        j = rand() % 4; // Gera um índice aleatório entre 0 e 3

        // Troca as alternativas
        strcpy(temp, pergunta->alternativas[i]);
        strcpy(pergunta->alternativas[i], pergunta->alternativas[j]);
        strcpy(pergunta->alternativas[j], temp);

        // Troca a posição da resposta correta se necessário
        if (i == pergunta->respostaCorreta) {
            pergunta->respostaCorreta = j;
        } else if (j == pergunta->respostaCorreta) {
            pergunta->respostaCorreta = i;
        }
    }
}

void menuPrincipal() {
    int opcao;
    do {
        printf("\n=== Quiz em C ===\n");
        printf("1. Iniciar Jogo\n");
        printf("2. Estatísticas\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                iniciarJogo();
                break;
            case 2:
                exibirEstatisticas();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);
}

void iniciarJogo() {
    Pergunta *perguntas = NULL;
    int quantidade = 0, pontos = 0;

    Estatistica estat;
    printf("Digite seu nome: ");
    scanf("%s", estat.nomeJogador);

    // Carregar fases do jogo
    for (int fase = 1; fase <= 5; fase++) {
        char arquivo[20];
        snprintf(arquivo, sizeof(arquivo), "fase%d.txt", fase);

        carregarPerguntas(arquivo, &perguntas, &quantidade);

        printf("\n--- Fase %d ---\n", fase);
        for (int i = 0; i < quantidade; i++) {
            printf("\n%s\n", perguntas[i].pergunta);

            // Embaralha as alternativas antes de exibir
            embaralharAlternativas(&perguntas[i]);

            // Exibe as alternativas embaralhadas
            for (int j = 0; j < 4; j++) {
                printf("%d. %s\n", j + 1, perguntas[i].alternativas[j]);
            }

            int resposta;
            printf("Sua resposta: ");
            scanf("%d", &resposta);

            if (resposta - 1 == perguntas[i].respostaCorreta) {
                printf("Correto!\n");
                pontos += 10;
            } else {
                printf("Errado! A resposta correta era: %s\n",
                       perguntas[i].alternativas[perguntas[i].respostaCorreta]);
                free(perguntas);
                goto fim;
            }
        }

        free(perguntas);
    }

fim:
    printf("\nFim do jogo! Sua pontuação: %d\n", pontos);
    estat.pontuacao = pontos;
    salvarEstatistica(estat);
}

void exibirEstatisticas() {
    FILE *arquivo = fopen("estatisticas.bin", "rb");
    if (!arquivo) {
        printf("Nenhuma estatística encontrada.\n");
        return;
    }

    Estatistica estat;
    printf("\n=== Estatísticas ===\n");
    while (fread(&estat, sizeof(Estatistica), 1, arquivo)) {
        printf("%s - %d pontos\n", estat.nomeJogador, estat.pontuacao);
    }

    fclose(arquivo);
}

void carregarPerguntas(char *arquivo, Pergunta **perguntas, int *quantidade) {
    FILE *arq = fopen(arquivo, "r");
    if (!arq) {
        printf("Erro ao carregar o arquivo: %s\n", arquivo);
        exit(1);
    }

    fscanf(arq, "%d\n", quantidade);
    *perguntas = malloc(*quantidade * sizeof(Pergunta));

    for (int i = 0; i < *quantidade; i++) {
        fgets((*perguntas)[i].pergunta, sizeof((*perguntas)[i].pergunta), arq);
        (*perguntas)[i].pergunta[strcspn((*perguntas)[i].pergunta, "\n")] = '\0';

        for (int j = 0; j < 4; j++) {
            fgets((*perguntas)[i].alternativas[j], sizeof((*perguntas)[i].alternativas[j]), arq);
            (*perguntas)[i].alternativas[j][strcspn((*perguntas)[i].alternativas[j], "\n")] = '\0';
        }
        fscanf(arq, "%d\n", &(*perguntas)[i].respostaCorreta);
    }

    fclose(arq);
}

void salvarEstatistica(Estatistica estat) {
    FILE *arquivo = fopen("estatisticas.bin", "ab");
    if (!arquivo) {
        printf("Erro ao salvar estatísticas.\n");
        return;
    }

    fwrite(&estat, sizeof(Estatistica), 1, arquivo);
    fclose(arquivo);
}

