#include <stdio.h>
#define MAX_W 20
#define MAX_H 20
 
int contCaminhos(char grafo[MAX_H][MAX_W], int x, int y, int w, int h, int visitado[MAX_H][MAX_W]) {
    if (x < 0 || x >= w || y < 0 || y >= h || visitado[y][x] || grafo[y][x] == '#') {
        return 0;
    }
 
    visitado[y][x] = 1;
    int cont = 1;
 
    cont += contCaminhos(grafo, x + 1, y, w, h, visitado);
    cont += contCaminhos(grafo, x - 1, y, w, h, visitado);
    cont += contCaminhos(grafo, x, y + 1, w, h, visitado);
    cont += contCaminhos(grafo, x, y - 1, w, h, visitado);
 
    return cont;
}
 
int main() {
    int w, h;
    scanf("%d %d", &w, &h);
 
    char grafo[MAX_H][MAX_W];
    int visitado[MAX_H][MAX_W] = {{0}}; // inicializando a matriz
 
    int InicioX, InicioY;
 
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            scanf(" %c", &grafo[i][j]);
 
            if (grafo[i][j] == '@') {
                InicioX = j;
                InicioY = i;
            }
        }
    }
 
    int result = contCaminhos(grafo, InicioX, InicioY, w, h, visitado);
 
    printf("%d\n", result);
 
    return 0;
}
