#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Constantes do programa
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

// Valores para representação no tabuleiro
#define AGUA 0
#define NAVIO 3
#define EFEITO_HABILIDADE 5

// Estrutura para representar uma posição no tabuleiro
typedef struct {
    int linha;
    int coluna;
} Posicao;

// Estrutura para representar um navio
typedef struct {
    Posicao inicio;
    int direcao; // 0=horizontal, 1=vertical, 2=diagonal-principal, 3=diagonal-secundaria
} NavioInfo;

// Protótipos das funções
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], NavioInfo navio);
bool validarPosicaoNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], NavioInfo navio);
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                      Posicao origem);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    // Declaração do tabuleiro principal
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Matrizes para as habilidades especiais
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    printf("=== BATALHA NAVAL - SIMULADOR COMPLETO ===\n\n");
    
    // ETAPA 1 e 2: Inicializar tabuleiro e posicionar navios
    inicializarTabuleiro(tabuleiro);
    
    // Definição dos quatro navios
    NavioInfo navios[4] = {
        {{2, 1}, 0},  // Navio horizontal na linha 2, coluna 1
        {{0, 5}, 1},  // Navio vertical na linha 0, coluna 5
        {{5, 2}, 2},  // Navio diagonal principal na linha 5, coluna 2
        {{3, 7}, 3}   // Navio diagonal secundária na linha 3, coluna 7
    };
    
    // Posicionar todos os navios no tabuleiro
    printf("Posicionando navios...\n");
    for (int i = 0; i < 4; i++) {
        if (posicionarNavio(tabuleiro, navios[i])) {
            printf("Navio %d posicionado com sucesso!\n", i + 1);
        } else {
            printf("Erro ao posicionar navio %d!\n", i + 1);
        }
    }
    
    printf("\nTabuleiro com navios posicionados:\n");
    exibirTabuleiro(tabuleiro);
    
    // ETAPA 3: Criar e aplicar habilidades especiais
    printf("\n=== DEMONSTRAÇÃO DAS HABILIDADES ESPECIAIS ===\n");
    
    // Criar as matrizes de habilidades
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);
    
    // Demonstrar habilidade Cone
    printf("\n--- Aplicando Habilidade CONE no centro (5,5) ---\n");
    int tabuleiroCone[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    // Copiar tabuleiro original
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiroCone[i][j] = tabuleiro[i][j];
        }
    }
    aplicarHabilidade(tabuleiroCone, habilidadeCone, (Posicao){5, 5});
    exibirTabuleiro(tabuleiroCone);
    
    // Demonstrar habilidade Cruz
    printf("\n--- Aplicando Habilidade CRUZ no centro (4,4) ---\n");
    int tabuleiroCruz[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    // Copiar tabuleiro original
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiroCruz[i][j] = tabuleiro[i][j];
        }
    }
    aplicarHabilidade(tabuleiroCruz, habilidadeCruz, (Posicao){4, 4});
    exibirTabuleiro(tabuleiroCruz);
    
    // Demonstrar habilidade Octaedro
    printf("\n--- Aplicando Habilidade OCTAEDRO no centro (6,6) ---\n");
    int tabuleiroOctaedro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    // Copiar tabuleiro original
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiroOctaedro[i][j] = tabuleiro[i][j];
        }
    }
    aplicarHabilidade(tabuleiroOctaedro, habilidadeOctaedro, (Posicao){6, 6});
    exibirTabuleiro(tabuleiroOctaedro);
    
    printf("\n=== FIM DA SIMULAÇÃO ===\n");
    printf("Legenda: 0=Água, 3=Navio, 5=Área de Efeito\n");
    
    return 0;
}

/**
 * Inicializa o tabuleiro com água (valor 0) em todas as posições
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * Exibe o tabuleiro no console de forma organizada
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    // Cabeçalho com números das colunas
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Valida se um navio pode ser posicionado na posição especificada
 */
bool validarPosicaoNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], NavioInfo navio) {
    int linha = navio.inicio.linha;
    int coluna = navio.inicio.coluna;
    
    // Verificar cada posição do navio baseada na direção
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int novaLinha = linha;
        int novaColuna = coluna;
        
        switch (navio.direcao) {
            case 0: // Horizontal
                novaColuna += i;
                break;
            case 1: // Vertical
                novaLinha += i;
                break;
            case 2: // Diagonal principal (↘)
                novaLinha += i;
                novaColuna += i;
                break;
            case 3: // Diagonal secundária (↙)
                novaLinha += i;
                novaColuna -= i;
                break;
        }
        
        // Verificar se está dentro dos limites do tabuleiro
        if (novaLinha < 0 || novaLinha >= TAMANHO_TABULEIRO || 
            novaColuna < 0 || novaColuna >= TAMANHO_TABULEIRO) {
            return false;
        }
        
        // Verificar se a posição já está ocupada
        if (tabuleiro[novaLinha][novaColuna] != AGUA) {
            return false;
        }
    }
    
    return true;
}

/**
 * Posiciona um navio no tabuleiro se a posição for válida
 */
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], NavioInfo navio) {
    // Validar se a posição é válida
    if (!validarPosicaoNavio(tabuleiro, navio)) {
        return false;
    }
    
    int linha = navio.inicio.linha;
    int coluna = navio.inicio.coluna;
    
    // Posicionar o navio no tabuleiro
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int novaLinha = linha;
        int novaColuna = coluna;
        
        switch (navio.direcao) {
            case 0: // Horizontal
                novaColuna += i;
                break;
            case 1: // Vertical
                novaLinha += i;
                break;
            case 2: // Diagonal principal (↘)
                novaLinha += i;
                novaColuna += i;
                break;
            case 3: // Diagonal secundária (↙)
                novaLinha += i;
                novaColuna -= i;
                break;
        }
        
        tabuleiro[novaLinha][novaColuna] = NAVIO;
    }
    
    return true;
}

/**
 * Cria a matriz de efeito da habilidade Cone
 * Formato: cone apontando para baixo, expandindo da ponta para a base
 */
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Inicializar toda a matriz com 0
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Criar formato de cone usando condicionais
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Lógica do cone: área de efeito aumenta conforme desce
            if (j >= centro - i && j <= centro + i) {
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * Cria a matriz de efeito da habilidade Cruz
 * Formato: cruz com centro no meio da matriz
 */
void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Inicializar toda a matriz com 0
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Criar formato de cruz usando condicionais
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Lógica da cruz: linha central ou coluna central
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * Cria a matriz de efeito da habilidade Octaedro (formato losango)
 * Formato: losango com centro no meio da matriz
 */
void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Inicializar toda a matriz com 0
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Criar formato de losango (octaedro visto de frente) usando condicionais
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Lógica do losango: distância Manhattan do centro
            int distancia = abs(i - centro) + abs(j - centro);
            if (distancia <= centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * Aplica uma habilidade especial ao tabuleiro na posição de origem especificada
 */
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                      Posicao origem) {
    int centro = TAMANHO_HABILIDADE / 2;
    
    // Aplicar a habilidade ao tabuleiro usando loops aninhados
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcular a posição no tabuleiro correspondente à posição na matriz de habilidade
            int linhaTab = origem.linha - centro + i;
            int colunaTab = origem.coluna - centro + j;
            
            // Verificar se a posição está dentro dos limites do tabuleiro
            if (linhaTab >= 0 && linhaTab < TAMANHO_TABULEIRO && 
                colunaTab >= 0 && colunaTab < TAMANHO_TABULEIRO) {
                
                // Se a habilidade afeta esta posição e não há navio
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colunaTab] != NAVIO) {
                    tabuleiro[linhaTab][colunaTab] = EFEITO_HABILIDADE;
                }
            }
        }
    }
}

/**
 * Função auxiliar para calcular valor absoluto
 */
int abs(int x) {
    return (x < 0) ? -x : x;
}