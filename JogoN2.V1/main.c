#include <stdlib.h>
#include <locale.h>
#include "quiz.h"


int main() {
    // Configura��o inicial
    system("color b0"); // Configura a cor do terminal
    setlocale(LC_ALL, "Portuguese"); // Define localiza��o para o idioma portugu�s

    // Inicia o menu principal
    menuPrincipal();
    return 0;
}

