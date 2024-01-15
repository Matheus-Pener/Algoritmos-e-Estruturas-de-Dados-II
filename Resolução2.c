#include <stdio.h>
#include <stdlib.h>
 
// Estrutura para representar a demanda por compra
typedef struct {
    int senha;
    int valor;
} Demanda;
 
// Função de comparação para a fila de prioridade (heap)
int comparaDemanda(const void *a, const void *b) {
    return ((Demanda *)b)->valor - ((Demanda *)a)->valor;
}
 
int main() {
    char operacao;
    int senha = 1;
    Demanda *fila = NULL;
    int tamanhoFila = 0;
 
    while (1) {
        scanf(" %c", &operacao);
        if (operacao == 'f') {
            break;  // Finaliza as negociações
        } else if (operacao == 'c') {
            // Nova demanda por compra
            int valor;
            scanf("%d", &valor);
 
            // Alocar espaço para uma nova demanda
            fila = (Demanda *)realloc(fila, (tamanhoFila + 1) * sizeof(Demanda));
            fila[tamanhoFila].senha = senha;
            fila[tamanhoFila].valor = valor;
            tamanhoFila++;
            senha++;
        } else if (operacao == 'v') {
            // Operação de venda
            if (tamanhoFila > 0) {
                // Usar uma fila de prioridade (heap) para encontrar o comprador com a maior oferta
                qsort(fila, tamanhoFila, sizeof(Demanda), comparaDemanda);
 
                // Imprimir a senha do comprador com a maior oferta
                printf("%d\n", fila[0].senha);
 
                // Remover o comprador com a maior oferta (no topo da fila)
                for (int i = 1; i < tamanhoFila; i++) {
                    fila[i - 1] = fila[i];
                }
                tamanhoFila--;
            } else {
                // Não há compradores na fila
                printf("0\n");
            }
        }
    }
 
    // Liberar a memória alocada para a fila
    free(fila);
 
    return 0;
}
