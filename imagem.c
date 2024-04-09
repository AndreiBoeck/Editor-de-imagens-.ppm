#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int R;
    int G;
    int B;
} RGB;

typedef struct{
    int coluna;
    int linha;
    int valor;
} TAMANHO;

int inverte(int pixel){
    int pixel_invertido;



    return pixel_invertido;
}


int main(void){
    FILE *fp;
    fp = fopen("UwU.ppm","r");

    char formato[3];
    fscanf(fp, "%s", formato); 	// lê o tipo de imagem P3 (color), P2 (P&B)
    printf("%s\n", formato);

    TAMANHO tamanho;
    tamanho.coluna = 0;
    tamanho.linha = 0;
    fscanf(fp, "%d %d", &tamanho.coluna, &tamanho.linha); 	// lê o tamanho da matriz
    printf("%d %d\n", tamanho.coluna, tamanho.linha);

    fscanf(fp, "%d", &tamanho.valor); 	// lê o valor máximo.
    printf("%d\n", tamanho.valor);

    int pixel[tamanho.coluna][tamanho.linha];

    int i, j;
    RGB rgb;
    for(j=0; j<tamanho.linha; j++)
    {
        for(i=0; i<tamanho.coluna; i++)
        {
            fscanf(fp, "%d %d %d", &rgb.R, &rgb.G,&rgb.B);
            printf("%d %d %d\n", rgb.R, rgb.G,rgb.B);
        }
    }


}