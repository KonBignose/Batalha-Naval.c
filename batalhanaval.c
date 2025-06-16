#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define HABILIDADE 5

// Inicializa o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// Posiciona navios fixos no tabuleiro
void posicionarNavios(int tabuleiro[TAM][TAM]) {
    // Horizontal
    for (int j = 2; j < 5; j++)
        tabuleiro[1][j] = NAVIO;

    // Vertical
    for (int i = 5; i < 8; i++)
        tabuleiro[i][3] = NAVIO;

    // Diagonal Principal
    for (int i = 0; i < 3; i++)
        tabuleiro[i + 2][i + 5] = NAVIO;

    // Diagonal Secundária
    for (int i = 0; i < 3; i++)
        tabuleiro[i + 5][7 - i] = NAVIO;
}

// Aplica a matriz de habilidade ao tabuleiro com centro em (cx, cy)
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[5][5], int cx, int cy) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (habilidade[i][j] == 1) {
                int x = cx + i - 2; // centro = linha + deslocamento
                int y = cy + j - 2;
                if (x >= 0 && x < TAM && y >= 0 && y < TAM && tabuleiro[x][y] != NAVIO)
                    tabuleiro[x][y] = HABILIDADE;
            }
        }
    }
}

// Gera matriz em forma de cone (apontando para baixo)
void gerarCone(int cone[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            cone[i][j] = (j >= 2 - i && j <= 2 + i) ? 1 : 0;
}

// Gera matriz em forma de cruz
void gerarCruz(int cruz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            cruz[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

// Gera matriz em forma de octaedro (losango)
void gerarOctaedro(int oct[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            oct[i][j] = (abs(i - 2) + abs(j - 2) <= 2) ? 1 : 0;
}

// Exibe o tabuleiro completo
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ ");
            else if (tabuleiro[i][j] == NAVIO)
                printf("N ");
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("* ");
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[5][5], cruz[5][5], octaedro[5][5];

    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Aplicar as habilidades
    aplicarHabilidade(tabuleiro, cone, 2, 2);      // Cone no topo esquerdo
    aplicarHabilidade(tabuleiro, cruz, 5, 5);      // Cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);  // Octaedro no canto inferior

    exibirTabuleiro(tabuleiro);

    return 0;
}
