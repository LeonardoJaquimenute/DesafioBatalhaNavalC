#include <stdio.h>
#include <stdlib.h> // para abs()

#define TAM 10
#define TAM_HAB 5
#define TAM_NAVIO 3

/* ======================================
   Função: inicializarTabuleiro
   Preenche o tabuleiro com 0 (água)
   ====================================== */
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    int i, j;
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

/* ======================================
   Função: exibirTabuleiro
   Mostra o tabuleiro na tela
   ====================================== */
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    int i, j;

    printf("    ");
    for (j = 0; j < TAM; j++) printf("%2d ", j);
    printf("\n");

    for (i = 0; i < TAM; i++) {
        printf("%2d |", i);
        for (j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0)
                printf(" . ");
            else if (tabuleiro[i][j] == 3)
                printf(" N ");
            else if (tabuleiro[i][j] == 5)
                printf(" * ");
            else
                printf(" ? ");
        }
        printf("|\n");
    }
    printf("\n");
}

/* ======================================
   Função: posicionarNavio
   Coloca um navio de tamanho fixo (3)
   ====================================== */
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    int k;
    if (orientacao == 0) { // horizontal
        for (k = 0; k < TAM_NAVIO; k++) {
            if (coluna + k < TAM) tabuleiro[linha][coluna + k] = 3;
        }
    } else { // vertical
        for (k = 0; k < TAM_NAVIO; k++) {
            if (linha + k < TAM) tabuleiro[linha + k][coluna] = 3;
        }
    }
}

/* ======================================
   Função: criarCone
   Cria uma matriz 5x5 em formato de cone
   ====================================== */
void criarCone(int cone[TAM_HAB][TAM_HAB]) {
    int i, j;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i) && i <= TAM_HAB / 2)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

/* ======================================
   Função: criarCruz
   Cria uma matriz 5x5 em formato de cruz
   ====================================== */
void criarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    int i, j, meio = TAM_HAB / 2;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (i == meio || j == meio)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

/* ======================================
   Função: criarOctaedro
   Cria uma matriz 5x5 em formato de losango (octaedro)
   ====================================== */
void criarOctaedro(int octaedro[TAM_HAB][TAM_HAB]) {
    int i, j, meio = TAM_HAB / 2;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

/* ======================================
   Função: aplicarHabilidade
   Sobrepõe a habilidade ao tabuleiro
   ====================================== */
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int linha, int coluna) {
    int i, j;
    int meio = TAM_HAB / 2;
    int posLinha, posColuna;

    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            posLinha = linha - meio + i;
            posColuna = coluna - meio + j;
            if (habilidade[i][j] == 1 && posLinha >= 0 && posLinha < TAM && posColuna >= 0 && posColuna < TAM) {
                if (tabuleiro[posLinha][posColuna] == 0)
                    tabuleiro[posLinha][posColuna] = 5;
            }
        }
    }
}

/* ======================================
   Função principal
   ====================================== */
int main() {
    int tabuleiro[TAM][TAM];
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    inicializarTabuleiro(tabuleiro);

    posicionarNavio(tabuleiro, 2, 2, 0);
    posicionarNavio(tabuleiro, 6, 5, 1);

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, cone, 4, 4);
    aplicarHabilidade(tabuleiro, cruz, 8, 2);
    aplicarHabilidade(tabuleiro, octaedro, 1, 8);

    printf("=== Tabuleiro com Habilidades ===\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
