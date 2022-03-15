#ifndef ESTRUTURA_NO_H
#define ESTRUTURA_NO_H
#include <iostream>
using namespace std;

class No
{
private:
    No *esq, *dir;
    int chave;

public:
    No(int chave)
    {
        this->chave = chave;
        esq = NULL;
        dir = NULL;
    }

    // funções getters e setters
    int getChave()
    {
        return chave;
    }

    No* getEsq()
    {
        return esq;
    }

    No* getDir()
    {
        return dir;
    }

    void setEsq(No *no)
    {
        esq = no;
    }

    void setDir(No *no)
    {
        dir = no;
    }
};


#endif //ESTRUTURA_NO_H

