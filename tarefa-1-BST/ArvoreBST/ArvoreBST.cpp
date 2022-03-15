
#include "ArvoreBST.h"

ArvoreBST::ArvoreBST(){
    raiz = NULL;
};

void ArvoreBST::inserir(int chave){
    if(raiz == NULL) // verifica se a árvore está vazia
        raiz = new No(chave); // cria um novo nó
    else
        inserirAux(raiz, chave);
}

void ArvoreBST::inserirAux(No *no, int chave){
    // se for menor, então insere à esquerda
    if(chave < no->getChave())
    {
        // verifica se a esquerda é nulo
        if(no->getEsq() == NULL)
        {
            No *novo_no = new No(chave);
            no->setEsq(novo_no); // seta o novo_no à esquerda
        }
        else
        {
            // senão, continua percorrendo recursivamente
            inserirAux(no->getEsq(), chave);
        }
    }
        // se for maior, então insere à direita
    else if(chave > no->getChave())
    {
        // verifica se a direita é nulo
        if(no->getDir() == NULL)
        {
            No *novo_no = new No(chave);
            no->setDir(novo_no); // seta o novo_no à direita
        }
        else
        {
            // senão, continua percorrendo recursivamente
            inserirAux(no->getDir(), chave);
        }
    }
    // se for igual, não vai inserir
    // não pode existir 2 chaves iguais
}

No* ArvoreBST::getRaiz(){
    return raiz;
}

void ArvoreBST::preOrdem(No* no){
    if(no != NULL)
    {
        cout << no->getChave() << " ";
        preOrdem(no->getEsq());
        preOrdem(no->getDir());
    }
}

void ArvoreBST::posOrdem(No* no){
    if(no != NULL)
    {
        posOrdem(no->getEsq());
        posOrdem(no->getDir());
        cout << no->getChave() << " ";

    }
}

