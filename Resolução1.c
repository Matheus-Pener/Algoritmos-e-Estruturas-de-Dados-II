#include <stdio.h>
#include <stdlib.h>
 
int cmp(const void *a, const void *b) {
    int elemento1 = *(int *)a;
    int elemento2 = *(int *)b;
 
    if (elemento1 < elemento2) {
        return -1;  
    } else if (elemento1 > elemento2) {
        return 1; 
    } else {
        return 0;  
    }
}
 
int main() {
    int n, s2;
    
    scanf("%d %d", &n, &s2);
    
    int *S = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &S[i]);
    }
    
    qsort(S, n, sizeof(int), cmp);
    
    int count = 0;
    
    int left = 0, right = n - 1;
    while (left < right) {
        int sum = S[left] + S[right];
        if (sum == s2) {
            count++;
            left++;
            right--;
        } else if (sum < s2) {
            left++;
        } else {
            right--;
        }
    }
    printf("%d\n", count);
    free(S);
    
    return 0;
}
