
#include "ArvoreBST.h"

int ArvoreBST::encontrarMax(No* no)
    {
        // Caso nulo
        if (no == NULL)
            return -2147483648;

        // Retorno de 3 valores: Chave da raiz, maximo na sub arvore da direita, e maximo na sub arvore da esquerda
        int res = no->getChave();
        int dirRes = encontrarMax(no->getEsq());
        int esqRes = encontrarMax(no->getDir());
        if (esqRes > res)
            res = esqRes;
        if (dirRes > res)
            res = dirRes;
        return res;
    }

int ArvoreBST::encontrarMin(No* no)
    {
        // Caso nulo
        if (no == nullptr)
            return 2147483647; //Valor maximo do int

        // Retorno de 3 valores: Chave da raiz, minimo na sub árvore da direita, e minimo na sub árvore da esquerda
        int res = no->getChave();
        int esqRes = encontrarMin(no->getEsq());
        int dirRes = encontrarMin(no->getDir());
        if (esqRes < res)
            res = esqRes;
        if (dirRes < res)
            res = dirRes;
        return res;
    }


int ArvoreBST::encontrarMax2(No* no)
    {  
        No* atual  = no;
        
        while (atual->getDir() != NULL){
          atual = atual->getDir();
        }

        cout << "Valor Maximo: " << atual->getChave();

        free(atual);
    }

int ArvoreBST::encontrarMin2(No* no)
    {  
        No* atual  = no;
        
        while (atual->getEsq() != NULL){
          atual = atual->getEsq();
        }

        cout << "Valor Minimo: " << atual->getChave();

        free(atual);
    }
