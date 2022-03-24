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

    vector<pair<string, float>> dados;
    for(int i=1;i<tabela.size();i++)
    {
        //Carregando dados da linha no vetor
        dados.clear();
        for(int j=1;j<tabela[i].size();j++)
        {
            //dados.push_back(pair())
            //tabela[0][j] -> Nome da coluna
            //tabela[i][j] -> Dado da linha correspondente à coluna
            dados.emplace_back(tabela[0][j], stof(tabela[i][j]));
        }
        arv.inserir(tabela[i][0], dados); //tabela[i] -> Coluna 0 (nome do alimento -> chave do nó)
        cout<<"\n";
    }

    // percorre em ordem iniciando da raiz
    cout << "\nPercorrendo em ordem crescrente...\n\n";
    arv.emOrdem();
    // cout << "\nDenhando a arvore deitada...\n";
    // arv.DesenhaArvore();

    return 0;
}