//
// Created by gustavo on 23/03/2022.
//

#include "AVL.cpp"
#include "LeitorCSV.h"
#include <vector>
#include <list>
#include <algorithm>

int main(int argc, char *argv[])
{
    Arvore arv;

    vector<vector<string> > tabela;
    lerCSV("dados/dados_finais.csv", tabela);

    vector<pair<string, float>> dados;
    vector<string> colunas, alimentos;

    for(int j=1;j<tabela[0].size();j++)
    {
        //Pegar colunas disponíveis
        colunas.emplace_back(tabela[0][j]);
    }

    //Inserir na árvore
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
        alimentos.emplace_back(tabela[i][0]);
        cout<<"\n";
    }

    // percorre em ordem iniciando da raiz
    cout << "\nPercorrendo em ordem crescrente...\n";
    arv.emOrdem();
    cout << "\nDenhando a arvore deitada...\n";
    arv.DesenhaArvore();



    std::string alimento_informado;
    list<string> lista_alimentos;

    while(true){   //Pegar a String informada, e colocar em uma lista
        cout << "Insira o alimento consumido (Digite Sair quando tiver finalizado): ";
        std::getline (std::cin, alimento_informado);
        alimento_informado = arv.converterPalavra(alimento_informado);
        if(std::count(alimentos.begin(),alimentos.end(),alimento_informado)){
            lista_alimentos.push_back(alimento_informado);
            cout << "Alimento registrado" << endl;
        }else if(alimento_informado != "Sair"){
            cout << "Alimento nao presente na tabela, tente novamente" << endl;
        }else{
            break;
        }

        }

    for(string alimento_informado : lista_alimentos){ //Percorrer a lista de alimentos e procurar um a um na árvorez
                arv.selecionarNo(alimento_informado);
                cout << "\n" << "informacoes nutricionais da(o): " << arv.getSelecionado()->getChave() << "\n" << endl;
                for(int j=0;j<(tabela[0].size())-1;j++){ //percorrer as colunas
                    cout << tabela[0][j+1] << ": " << arv.getSelecionado()->procurarDado(colunas[j]) << "\n" << endl;
                }
            }
    //Selecionar nó com esse nome -> Todos nomes estão no vetor alimentos
    //arv.selecionarNo(alimentos[0]);

    //Printar chave do nó
    //cout << arv.getSelecionado()->getChave() << endl;

    //Procurar algum dado do alimento -> Todos dados disponíveis estão no vetor colunas
    //cout << arv.getSelecionado()->procurarDado(colunas[22]) << endl;
    return 0;
}
