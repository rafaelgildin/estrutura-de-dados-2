// GUSTAVO ANDRADE DE PAULA 42081327
// Gustavo Bernard Schwarz 32141157
// Rafael Avraham Gildin Acherboim 31940242
// Andrea Mindlin Tessler - 42012538

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

    void emOrdem(No* no);
    
    void preOrdem(No* no);

    void posOrdem(No* no);

    //versao iterativa
    No *Pesquisar(int dado, No* no);

    //versao recursiva
    No *PesquisarRec (No* r, int k);

    //versao recursiva
    int contarNos(No* atual);

    int contarFolhas(No* atual);

    //versao recursiva
    int altura(No* atual);

    void getVetorAvr(No* no, int nosChaves[], No *nosPtr[], int &q);
    No *PesquisarPai(int dado, No* no);
    int RemoverNo(No* atual, int dado);

    int encontrarMax(No* no);
    int encontrarMin(No* no);
    int encontrarMax2(No* no);
    int encontrarMin2(No* no);
    
};


#endif //ESTRUTURA_ARVOREBST_H