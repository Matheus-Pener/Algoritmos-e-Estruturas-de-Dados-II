#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 999999        // Tamanho estipulado da hash para um pior caso
#define MAX_STRING_SIZE 13 // Tamanho máximo da string

// Estrutura para os nós da tabela de hash
typedef struct Node
{
    char data[MAX_STRING_SIZE];
    struct Node *next;
    int str_len; // Armazena o comprimento da string para otimizar as comparações
} Node;

/* Função para obter o valor numérico correspondente a um caractere ('A', 'C', 'G', 'T') com finalidade
de diminuir as colisões transformando os input em base 4, podendo reduzir colisões*/
int base4_char_value(char c)
{
    switch (c)
    {
    case 'A':
        return 0;
    case 'C':
        return 1;
    case 'G':
        return 2;
    case 'T':
        return 3;
    default:
        return -1; // Caracteres inválidos
    }
}

// Função de hash que converte uma string em um índice na tabela de hash
int hash(const char *str)
{
    int hash = 0, factor = 1;
    int str_len = strlen(str);
    for (int i = str_len - 1; i >= 0; i--)
    {
        hash += base4_char_value(str[i]) * factor;
        factor *= 4;
        hash %= SIZE; // Garante que o valor do hash esteja dentro dos limites da tabela
    }
    return hash;
}

// Função para inserir uma nova string na tabela de hash
void insert(Node *hashTable[], const char *str)
{
    int index = hash(str);
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "Erro de alocação de memória na linha %d\n", __LINE__); // fprint -> utilizado para impressão de erro em arquivo
        exit(EXIT_FAILURE);                                                     // Caso haja falha encerra o programa
    }

    // Copia a string para o novo nó
    strcpy(newNode->data, str);
    newNode->str_len = strlen(str);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Função para procurar uma string na tabela de hash
int find(Node *hashTable[], const char *str)
{
    int index = hash(str);
    int str_len = strlen(str);

    Node *current = hashTable[index];
    while (current != NULL)
    {
        // Compara comprimento e conteúdo da string
        if (current->str_len == str_len && strcmp(current->data, str) == 0)
        {
            return 1; // Encontrou a string na tabela
        }
        current = current->next;
    }

    return 0; // String não encontrada
}

// Função principal
int main()
{
    Node *hashTable[SIZE] = {NULL}; // Inicializa a tabela de hash com ponteiros nulos
    int n;

    // Leitura do número de operações
    if (scanf("%d", &n) != 1)
    {
        perror("Erro na leitura do número de operações");
        exit(EXIT_FAILURE);
    }

    // Loop para processar as operações
    for (int i = 0; i < n; i++)
    {
        char operation[10];
        char str[MAX_STRING_SIZE];

        // Leitura da operação e da string
        if (scanf("%9s", operation) != 1 || scanf(" %12[^\n]", str) != 1)
        {
            perror("Erro na leitura da operação e da string");
            exit(EXIT_FAILURE);
        }

        // Remoção do caractere de nova linha, se presente
        str[strcspn(str, "\n")] = '\0';

        // Execução da operação correspondente
        if (strcmp(operation, "insert") == 0)
        {
            insert(hashTable, str);
        }
        else if (strcmp(operation, "find") == 0)
        {
            // Impressão do resultado da busca
            if (find(hashTable, str))
            {
                printf("yes\n");
            }
            else
            {
                printf("no\n");
            }
        }
    }

    // Liberação de memória alocada para os nós da tabela de hash
    for (int i = 0; i < SIZE; i++)
    {
        Node *current = hashTable[i];
        while (current != NULL)
        {
            Node *next = current->next;
            free(current);
            current = next;
        }
    }
    return 0;
}
