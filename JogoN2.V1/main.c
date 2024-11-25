#include <stdlib.h>
#include <locale.h>
#include "quiz.h"


int main() {
    // Configuração inicial
    system("color b0"); // Configura a cor do terminal
    setlocale(LC_ALL, "Portuguese"); // Define localização para o idioma português

    // Inicia o menu principal
    menuPrincipal();
    return 0;
}

