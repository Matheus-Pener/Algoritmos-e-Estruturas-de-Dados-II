#include <stdio.h>
#include <stdlib.h>
 
int main() {
    int V, C;
    scanf("%d %d", &V, &C);
 
    int votos[V][3];
    int votos_primeira_opcao[C + 1];
    for (int i = 0; i <= C; i++) votos_primeira_opcao[i] = 0; // Inicializando contagem de votos
 
    int total_votos_primeira_opcao = 0;
 
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &votos[i][j]);
            if (j == 0 && votos[i][j] >= 1 && votos[i][j] <= C) {
                votos_primeira_opcao[votos[i][j]]++;
                total_votos_primeira_opcao++;
            }
        }
    }
 
    if (total_votos_primeira_opcao == 0) {
        printf("0\n");
        return 0;
    }
 
    int maior1 = -1, posMaior1 = -1, empate = 0;
    for (int i = 1; i <= C; i++) {
        if (votos_primeira_opcao[i] > maior1) {
            maior1 = votos_primeira_opcao[i];
            posMaior1 = i;
            empate = 0;
        } else if (votos_primeira_opcao[i] == maior1) {
            empate = 1;
        }
    }
 
    double porcentagem1 = (double)maior1 / total_votos_primeira_opcao * 100;
    printf("%d %.2lf\n", posMaior1, porcentagem1);
 
    if (!empate && porcentagem1 < 50.00) {
        int votos_segundo_turno[C + 1];
        for (int i = 1; i <= C; i++) votos_segundo_turno[i] = 0;
 
        int segundo_candidato = -1, maior2 = -1, posMaior2 = -1;
        for (int i = 1; i <= C; i++) {
            if (i != posMaior1 && (segundo_candidato == -1 || votos_primeira_opcao[i] > votos_primeira_opcao[segundo_candidato])) {
                segundo_candidato = i;
            }
        }
 
        for (int i = 0; i < V; i++) {
            int voto_contabilizado = 0;
            for (int j = 0; j < 3 && !voto_contabilizado; j++) {
                if (votos[i][j] >= 1 && votos[i][j] <= C) {
                    if (votos[i][j] == posMaior1 || votos[i][j] == segundo_candidato) {
                        votos_segundo_turno[votos[i][j]]++;
                        voto_contabilizado = 1;
                    }
                }
            }
        }
 
        for (int i = 1; i <= C; i++) {
            if (votos_segundo_turno[i] > maior2) {
                maior2 = votos_segundo_turno[i];
                posMaior2 = i;
            }
        }
 
        double porcentagem2 = (double)maior2 / (votos_segundo_turno[posMaior1] + votos_segundo_turno[segundo_candidato]) * 100;
        printf("%d %.2lf\n", posMaior2, porcentagem2);
    }
 
    return 0;
}
