#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura para armazenar valores de cor de cada pixel
struct Pixel
{
    int R, G, B;
};

// Converte a imagem para tons de cinza, ajustando R, G, B para serem iguais à média dos três
struct Pixel **tCinza(struct Pixel **matriz, int linhas, int colunas){
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matriz[i][j].R /= 3;
            matriz[i][j].G = matriz[i][j].R;
            matriz[i][j].B = matriz[i][j].R;
        }
    }
    return matriz;
}

// Aplica o efeito negativo à imagem, subtraindo os valores de cor do máximo permitido
struct Pixel **negativa(struct Pixel **matriz, int linhas, int colunas, int valor){
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matriz[i][j].R = valor - matriz[i][j].R;
            matriz[i][j].G = valor - matriz[i][j].G;
            matriz[i][j].B = valor - matriz[i][j].B;
        }
    }
    return matriz;
}

// Aumenta o brilho da imagem com base em uma porcentagem fornecida pelo usuário
struct Pixel **aumentaBrilho(struct Pixel **matriz, int linhas, int colunas, int valor) {
    int porcentagem;
    printf("deseja diminuir o brilho em quantos porcento? (0 - 100)");
    scanf("%d", &porcentagem);

    porcentagem += 100;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matriz[i][j].R = (matriz[i][j].R * porcentagem)/100;
            matriz[i][j].G = (matriz[i][j].G * porcentagem)/100;
            matriz[i][j].B = (matriz[i][j].B * porcentagem)/100;

            // Evita que o pixel ultrapasse o limite de 255.
            if(matriz[i][j].R > valor){
                matriz[i][j].R = valor;
            }
            if(matriz[i][j].G > valor){
                matriz[i][j].G = valor;
            }
            if(matriz[i][j].B > valor){
                matriz[i][j].B = valor;
            }
        }
    }
    return matriz;
}

// Diminui o brilho da imagem com base em uma porcentagem fornecida pelo usuário
struct Pixel **diminuiBrilho(struct Pixel **matriz, int linhas, int colunas){
    int porcentagem;
    printf("deseja diminuir o brilho em quantos porcento? (0 - 100)");
    scanf("%d", &porcentagem);

    porcentagem = 100 - porcentagem;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matriz[i][j].R = (matriz[i][j].R * porcentagem)/100;
            matriz[i][j].G = (matriz[i][j].G * porcentagem)/100;
            matriz[i][j].B = (matriz[i][j].B * porcentagem)/100;

            // Evita que o pixel ultrapasse o limite de 0.
            if(matriz[i][j].R < 0){
                matriz[i][j].R = 0;
            }
            if(matriz[i][j].G < 0){
                matriz[i][j].G = 0;
            }
            if(matriz[i][j].B < 0){
                matriz[i][j].B = 0;
            }
        }
    }

    return matriz;
}

// Gira a imagem 90 graus à direita
struct Pixel **gira(struct Pixel **matrix, int linhas, int colunas) {
    // Alocando memória para a nova matriz rotacionada
    struct Pixel **matriz = (struct Pixel **)malloc(colunas * sizeof(struct Pixel *));
    for (int i = 0; i < colunas; i++) {
        matriz[i] = (struct Pixel *)malloc(linhas * sizeof(struct Pixel));
    }

    // Preenchendo a nova matriz com os valores rotacionados
    for (int i = 0; i < colunas; ++i) {
        for (int j = 0; j < linhas; ++j) {
            matriz[i][j].R = matrix[linhas - j - 1][i].R;
            matriz[i][j].G = matrix[linhas - j - 1][i].G;
            matriz[i][j].B = matrix[linhas - j - 1][i].B;
        }
    }
    return matriz;
}

// Aplica um efeito que simula o envelhecimento da imagem
struct Pixel **envelhecer(struct Pixel **matrix, int linhas, int colunas, int valor) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int ogRed = matrix[i][j].R;
            int ogGreen = matrix[i][j].G;
            int ogBlue = matrix[i][j].B;

            int newRed = (int)(0.393 * ogRed + 0.769 * ogGreen + 0.189 * ogBlue);
            int newGreen = (int)(0.349 * ogRed + 0.686 * ogGreen + 0.168 * ogBlue);
            int newBlue = (int)(0.272 * ogRed + 0.534 * ogGreen + 0.131 * ogBlue);

            // Evita que o pixel ultrapasse o limite de 255.
            matrix[i][j].R = newRed > valor ? valor : newRed;
            matrix[i][j].G = newGreen > valor ? valor : newGreen;
            matrix[i][j].B = newBlue > valor ? valor : newBlue;
        }
    }
    return matrix;
}

// Função principal que gerencia o fluxo do programa, incluindo leitura e escrita de arquivos, e processamento de imagens
int main(void){
    FILE *fp;
    int c;
    char tipoImg[3];
    int i, j, linhas, colunas, valor, r, g, b;
    int escolha = -1;
    char img[100];
    wprintf(L"Qual arquivo deseja usar?\n");
    scanf("%s", img);
    while(escolha != 0) {
        fp = fopen(img, "r");
        if(fp == NULL){
            fprintf(stderr, "Erro ao abrir o arquivo %s.\n", img);
            exit(EXIT_FAILURE);
        }

        // Lê o cabeçalho do arquivo
        fscanf(fp, "%s", tipoImg);                     // lê o tipo de imagem P3
        fscanf(fp, "%d %d", &colunas, &linhas);        // lê o tamanho da matriz
        fscanf(fp, "%d", &valor);                      // lê o valor máximo.

        // Alocação da matriz de pixels RGB
        struct Pixel **matriz = (struct Pixel **) malloc(linhas * sizeof(struct Pixel *));
        for (i = 0; i < linhas; i++) {
            matriz[i] = (struct Pixel *) malloc(colunas * sizeof(struct Pixel));
        }
        // Leitura dos valores de pixel RGB
        for (i = 0; i < linhas; i++) {
            for (j = 0; j < colunas; j++) {
                fscanf(fp, "%d %d %d", &r, &g, &b);
                matriz[i][j].R = r;
                matriz[i][j].G = g;
                matriz[i][j].B = b;
            }
        }

        // Fecha o arquivo após a leitura
        fclose(fp);

        // Interface do usuário para escolha da manipulação de imagem
        wprintf(L"                      Escolha o que deseja:\n"
                "[1] - Gerar imagens tons de cinza      [2] - Gerar imagem negativa\n"
                "[3] - Aumentar brilho                  [4] - Diminuir brilho\n"
                "[5] - Girar 90 graus                   [6] - Envelhecer a imagem\n"
                "                           [0] - Sair\n");
        scanf("%d", &escolha);

        struct Pixel **matriz2;
        switch (escolha) {
            case 0: {
                break;
            }
            case 1: {
                matriz2 = tCinza(matriz, linhas, colunas);
                break;
            }
            case 2: {
                matriz2 = negativa(matriz, linhas, colunas, valor);
                break;
            }
            case 3: {
                matriz2 = aumentaBrilho(matriz, linhas, colunas, valor);
                break;
            }
            case 4: {
                matriz2 = diminuiBrilho(matriz, linhas, colunas);
                break;
            }
            case 5: {
                matriz2 = gira(matriz, linhas, colunas);
                int aux = linhas; // Troca linhas e colunas para a nova orientação
                linhas = colunas;
                colunas = aux;
                break;
            }
            case 6: {
                matriz2 = envelhecer(matriz, linhas, colunas, valor);
                break;
            }
            default:
                fprintf(stderr, "Opção invalida.\n");
        }

        if(escolha == 0){
            break;
        }

        // Cria um novo arquivo para salvar a imagem processada
        FILE *fp_novo = fopen("ImgAlterada.ppm", "w");
        if (fp_novo == NULL) {
            fprintf(stderr, "Erro ao criar o arquivo 'ImgAlterada.ppm'.\n");
            exit(EXIT_FAILURE);
        }
        // Gravação dos valores de pixel RGB
        fprintf(fp_novo, "P3\n%d %d\n255\n", colunas, linhas);
        for (i = 0; i < linhas; i++) {
            for (j = 0; j < colunas; j++) {
                fprintf(fp_novo, "%d %d %d ", matriz2[i][j].R, matriz2[i][j].G, matriz2[i][j].B);
            }
            fprintf(fp_novo, "\n"); // Adiciona uma nova linha após cada linha de pixels.
        }
        fclose(fp_novo);
    }

    // Mensagem final ao encerrar o programa
    printf("-------------------------------FIM-----------------------------\n");
}
