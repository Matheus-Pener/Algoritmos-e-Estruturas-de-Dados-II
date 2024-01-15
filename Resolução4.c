#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Projeto {
    int project;
    struct Projeto* prox;
} Projeto;
 
typedef struct Node {
    char name[16];
    int height;
    Projeto* projetos;
    struct Node* esq;
    struct Node* dir;
} Node;
 
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
 
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}
 
int getBalanceFactor(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->esq) - height(node->dir);
}
 
Node* createNode(char* name, int project) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->height = 1;
    newNode->projetos = NULL;
    Projeto* projectNode = (Projeto*)malloc(sizeof(Projeto));
    projectNode->project = project;
    projectNode->prox = NULL;
    newNode->projetos = projectNode;
    newNode->esq = NULL;
    newNode->dir = NULL;
    return newNode;
}
 
Node* rightRotate(Node* y) {
    Node* x = y->esq;
    Node* T2 = x->dir;
 
    x->dir = y;
    y->esq = T2;
 
    y->height = max(height(y->esq), height(y->dir)) + 1;
    x->height = max(height(x->esq), height(x->dir)) + 1;
 
    return x;
}
 
Node* leftRotate(Node* x) {
    Node* y = x->dir;
    Node* T2 = y->esq;
 
    y->esq = x;
    x->dir = T2;
 
    x->height = max(height(x->esq), height(x->dir)) + 1;
    y->height = max(height(y->esq), height(y->dir)) + 1;
 
    return y;
}
 
int balanceFactor(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->esq) - height(node->dir);
}
 
Node* insere(Node* root, char* name, int project) {
    if (root == NULL)
        return createNode(name, project);
 
    if (strcmp(name, root->name) < 0)
        root->esq = insere(root->esq, name, project);
    else if (strcmp(name, root->name) > 0)
        root->dir = insere(root->dir, name, project);
    else {
        Projeto* projectNode = (Projeto*)malloc(sizeof(Projeto));
        projectNode->project = project;
        projectNode->prox = root->projetos;
        root->projetos = projectNode;
    }
 
    root->height = 1 + max(height(root->esq), height(root->dir));
 
    int diferenca = balanceFactor(root);
 
    if (diferenca > 1 && strcmp(name, root->esq->name) < 0)
        return rightRotate(root);
 
    if (diferenca < -1 && strcmp(name, root->dir->name) > 0)
        return leftRotate(root);
 
    if (diferenca > 1 && strcmp(name, root->esq->name) > 0) {
        root->esq = leftRotate(root->esq);
        return rightRotate(root);
    }
 
    if (diferenca < -1 && strcmp(name, root->dir->name) < 0) {
        root->dir = rightRotate(root->dir);
        return leftRotate(root);
    }
 
    return root;
}
 
Node* procura(Node* root, char* name) {
    if (root == NULL)
        return NULL;
 
    if (strcmp(name, root->name) < 0)
        return procura(root->esq, name);
    else if (strcmp(name, root->name) > 0)
        return procura(root->dir, name);
    else
        return root;
}
 
void printProjects(Projeto* projectNode) {
    if (projectNode != NULL) {
        printProjects(projectNode->prox);
        printf("%d ", projectNode->project);
    }
}
 
void freeProjects(Projeto* projectNode) {
    if (projectNode != NULL) {
        freeProjects(projectNode->prox);
        free(projectNode);
    }
}
 
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->esq);
        freeTree(root->dir);
        freeProjects(root->projetos);
        free(root);
    }
}
 
int main() {
    Node* root = NULL;
    int entrada;
 
    do {
        scanf("%d", &entrada);
        if (entrada == 1) {
            char name[16];
            int project;
            scanf("%s %d", name, &project);
            root = insere(root, name, project);
        } else if (entrada == 2) {
            char name[16];
            scanf("%s", name);
            Node* result = procura(root, name);
            if (result != NULL) {
                printf("%d ", result->height);
                printProjects(result->projetos);
                printf("\n");
            } else {
                printf("0\n");
            }
        }
    } while (entrada != 0);
    freeTree(root);
    return 0;
}
