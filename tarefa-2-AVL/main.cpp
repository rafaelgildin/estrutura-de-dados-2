//
// Created by gustavo on 23/03/2022.
//

#include "AVL.cpp"
#include "LeitorCSV.h"
#include <vector>

int main(int argc, char *argv[])
{
    Arvore arv;

    vector<vector<string> > tabela;
    lerCSV("dados/dados_finais.csv", tabela);

    //Printar tabela
    for (auto & i : tabela){
        for (auto & j : i){
            cout << j << " ";
        }
        cout << endl;
    }

    // insere as chaves
    arv.inserir("Salve");
    arv.inserir("Salve2");
    arv.inserir("Salve3");
    arv.inserir("Salve4");
    arv.inserir("Salve5");


    // percorre em ordem iniciando da raiz
    cout << "\nPercorrendo em ordem crescrente...\n";
    arv.emOrdem();
    cout << "\nDenhando a arvore deitada...\n";
    arv.DesenhaArvore();
    return 0;
}