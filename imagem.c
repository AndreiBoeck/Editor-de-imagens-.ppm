#include <stdio.h>
#include <stdlib.h>

struct Pixel
{
    int R, G, B;
};


typedef struct{
    int coluna;
    int linha;
    int valor;
} TAMANHO;

int inverte(int pixel){
    // Subtrair valor RGB da variavel valor no struct TAMANHO
    int pixel_invertido;


    return pixel_invertido;
}

struct Pixel **gira(struct Pixel **matrix, int linhas, int colunas) {
    struct Pixel **matriz = (struct Pixel **)malloc(colunas * sizeof(struct Pixel *));
    for (int i = 0; i < colunas; i++)
    {
        matriz[i] = (struct Pixel *)malloc(linhas * sizeof(struct Pixel));
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matriz[j][i].R = matrix[i][j].R;
            matriz[j][i].G = matrix[i][j].G;
            matriz[j][i].B = matrix[i][j].B;
        }
    }
    return matriz;
}

struct Pixel **envelhecer(struct Pixel **matrix, int linhas, int colunas) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matrix[i][j].R -= 30;
            matrix[i][j].G -= 15;
            matrix[i][j].B -= 15;
        }
    }
    return matrix;
}


//aumentar e diminuir brilho
//acredito que precisa verificar se está cinza
//correção para caso seja maior que valor  

struct Pixel **diminuirBrilho(struct Pixel **matrix, int linhas, int colunas, int valor) {
    /*if () {
        printf("A imagem não está cinza. Voltando ao menu...\n");
        return matrix; //retorna
    }
    */

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matrix[i][j].R -= valor;
            matrix[i][j].G -= valor;
            matrix[i][j].B -= valor;
            //verificar se valores não ultrapassam o limite de 0
            if (matrix[i][j].R < 0) matrix[i][j].R = 0;
            if (matrix[i][j].G < 0) matrix[i][j].G = 0;
            if (matrix[i][j].B < 0) matrix[i][j].B = 0;
        }
    }
    return matrix;
}

struct Pixel **aumentarBrilho(struct Pixel **matrix, int linhas, int colunas, int valor) {
    /*if () {
        printf("A imagem não está cinza. Voltando ao menu...\n");
        return matrix;
    }
    */

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matrix[i][j].R += valor;
            matrix[i][j].G += valor;
            matrix[i][j].B += valor;
            //verificar se os valores não ultrapassam o limite de 255
            if (matrix[i][j].R > 255) matrix[i][j].R = 255;
            if (matrix[i][j].G > 255) matrix[i][j].G = 255;
            if (matrix[i][j].B > 255) matrix[i][j].B = 255;
        }
    }
    return matrix;
}


int main(void){
    FILE *fp;
    int c;
    char tipoImg[3];
    int i, j, linhas, colunas, valor, r, g, b;
    int escolha = -1;
    char img[50];
    wprintf(L"Qual arquivo deseja usar?\n");
        scanf("%s", img);
    while(escolha != 0) {
        printf("%s\n", img);
        fp = fopen(img, "r");
        if(fp == NULL){
            fprintf(stderr, "Erro ao abrir o arquivo %s.\n", img);
            exit(EXIT_FAILURE);
        }

        // Lê o cabeçalho do arquivo
        fscanf(fp, "%s", tipoImg);                    // lê o tipo de imagem P3
        fscanf(fp, "%d %d", &colunas, &linhas);    // lê o tamanho da matriz
        fscanf(fp, "%d", &valor);                   // lê o valor máximo.

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

        // Fecha o arquivo.
        fclose(fp);

        wprintf(L"                      Escolha o que deseja:\n"
                        "[1] - Gerar imagens tons de cinza      [2] - Gerar imagem negativa\n"
                        "[3] - Aumentar brilho                  [4] - Diminuir brilho\n"
                        "[5] - Girar 90 graus                   [6] - Envelhecer a imagem\n"
                        "                           [0] - Sair\n");
        scanf("%d", &escolha);


        struct Pixel **matriz2;
        switch (escolha) {
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                matriz2 = aumentarBrilho(matriz,linhas,colunas, valor)
                break;
            }
            case 4: {
                matriz2 = diminuirBrilho(matriz,linhas,colunas, valor)
                break;
            }
            case 5: {
                matriz2 = gira(matriz, linhas, colunas);
                break;
            }
            case 6: {
                matriz2 = envelhecer(matriz, linhas, colunas);
                break;
            }
            default:
                fprintf(stderr, "Opção invalida.\n");
                exit(EXIT_FAILURE);
        }

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
        fclose(fp);
    }

    // Fecha o arquivo.
    printf("-------------------------------FIM-----------------------------\n");
}

