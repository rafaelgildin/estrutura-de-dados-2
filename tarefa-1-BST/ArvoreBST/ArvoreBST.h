
#ifndef ESTRUTURA_ARVOREBST_H
#define ESTRUTURA_ARVOREBST_H

#include "No.h"
#include <iostream>
using namespace std;

class ArvoreBST
{
private:
    No *raiz;

public:
    ArvoreBST();
    void inserir(int chave);

    void inserirAux(No *no, int chave);

    No* getRaiz();

    void preOrdem(No* no);

    void posOrdem(No* no);

    //versao iterativa
    No *Pesquisar(int dado, No* no);

    //versao recursiva
    No *PesquisarRec (No* r, int k);

    //versao recursiva
    int contarNos(No* atual);

    //versao recursiva
    int contarFolhas(No* atual);

    //versao recursiva
    int altura(No* atual);

    //--------------------------------------------Rafael---------------------------------
    void getVetorAvr(No* no, int nosChaves[], No *nosPtr[], int &q);
};


#endif //ESTRUTURA_ARVOREBST_H
