
#include "ArvoreBST.h"

int ArvoreBST::contarFolhas(No* atual){
    if(atual == NULL)
        return 0;
    else {
        if(atual->getEsq() == NULL && atual->getDir() == NULL)
            return 1;
        else{
            return (contarFolhas(atual->getEsq()) + contarFolhas(atual->getDir()));
        }
    }
}



