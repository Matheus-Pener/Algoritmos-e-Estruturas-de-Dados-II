#include <stdio.h>
 
#include <string.h>
 
 
 
struct CodonAmino {
 
    char codon[4];
 
    char amino;
 
};
 
 
 
int main() {
 
    int N, M;
 
    scanf("%d", &N);
 
 
 
    struct CodonAmino dicionario[N];
 
    
 
    for (int i = 0; i < N; i++) {
 
        scanf("%s %c", dicionario[i].codon, &dicionario[i].amino);
 
    }
 
 
 
    scanf("%d", &M);
 
 
 
 
 
    for (int i = 0; i < M; i++) {
 
        char rna[10001];
 
        scanf("%s", rna);
 
 
 
        int len = strlen(rna);
 
        char amino_sequence[10001];
 
        int amino_index = 0;
 
 
 
        for (int j = 0; j < len; j += 3) {
 
            char codon[4];
 
            strncpy(codon, rna + j, 3);
 
            codon[3] = '\0';
 
 
 
            char amino = '*';
 
            for (int k = 0; k < N; k++) {
 
                if (strcmp(codon, dicionario[k].codon) == 0) {
 
                    amino = dicionario[k].amino;
 
                    break;
 
                }
 
            }
 
 
 
            amino_sequence[amino_index] = amino;
 
            amino_index++;
 
        }
 
 
 
        amino_sequence[amino_index] = '\0';
 
        printf("%s\n", amino_sequence);
 
    }
 
 
 
    return 0;
 
}
