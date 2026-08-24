#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char *chave;
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No* criar_no(const char *chave, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        exit(EXIT_FAILURE);
    }
    novo->chave = strdup(chave); 
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No* buscar(No *raiz, const char *chave) {
    if (raiz == NULL) return NULL;
    int comp = strcmp(chave, raiz->chave);
    if (comp == 0) return raiz;
    if (comp < 0) return buscar(raiz->esq, chave);
    return buscar(raiz->dir, chave);
}

No* inserir(No *raiz, const char *chave, int valor) {
    if (raiz == NULL) {
        return criar_no(chave, valor);
    }
    int comp = strcmp(chave, raiz->chave);
    if (comp < 0) {
        raiz->esq = inserir(raiz->esq, chave, valor);
    } else if (comp > 0) {
        raiz->dir = inserir(raiz->dir, chave, valor);
    }
    return raiz;
}

void liberar_arvore(No *raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz->chave);
    free(raiz);
}

int main() {
    int n = 0;
    if (scanf("%d", &n) != 1) return 0;
    No *raiz = NULL;
    char buffer_chave[256];

    for (int i = 0; i < n; i++) {
        scanf("%255s", buffer_chave);
        No *no_encontrado = buscar(raiz, buffer_chave);
        
        if (no_encontrado == NULL) {
            raiz = inserir(raiz, buffer_chave, 0);
            printf("OK\n");
        } else {
            no_encontrado->valor++;
            char novo_nome[280];
            sprintf(novo_nome, "%s%d", buffer_chave, no_encontrado->valor);
            
            printf("%s\n", novo_nome);
            raiz = inserir(raiz, novo_nome, 0);
        }
    }

    liberar_arvore(raiz);
    return 0;
}