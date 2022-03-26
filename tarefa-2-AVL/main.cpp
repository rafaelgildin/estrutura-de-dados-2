#include "AVL.cpp"
#include "LeitorCSV.h"
#include <vector>
#include <list>
#include <algorithm>
#include <tuple>

// int main(int argc, char *argv[])
// {
//     ArvoreBST arv;
//     int opcao, x;
//     cout << ("\nTestando o TAD BST (Elementos do tipo int)\n");

//     do
//     {
//         cout << "\n\n";
//         cout << "\n***********************************";
//         cout << "\n\tMenu - Arvore BST\n";
//         cout << "\nEntre com a opcao:";
//         cout << "\n ----1: Inserir";
//         cout << "\n ----2: Excluir";
//         cout << "\n ----3: Pesquisar";
//         cout << "\n ----4: Imprimir em ordem";
//         cout << "\n ----5: Qde de nos";
//         cout << "\n ----6: Altura";
//         cout << "\n ----7: Remover";
//         cout << "\n ----8: Informacoes";
//         cout << "\n ----9: Sair do programa\n";
//         cout << "\n***********************************";
//         cout << "\n-> ";
//         cin >> opcao;
//         switch(opcao)
//         {
//         case 1:
//         {
//             cout << "\n Informe o valor (int) -> ";
//             cin >> x;
//             arv.inserir(x);
//             break;
//         }
//         case 2:
//         {
//             cout << "\n Ainda nao implementado! ";

//             break;
//         }
//         case 3:
//         {
//             cout << "\n Informe o valor da chave (int) -> ";
//             cin >> x;
//             //No *ret = arv.Pesquisar(x,arv.getRaiz());
//             No *ret = arv.PesquisarRec(arv.getRaiz(),x);
//             if (ret == NULL)
//             {
//                 cout << "\n Chave nao encontrada! ";
//             }
//             else
//             {
//                 cout << "\n Chave encontrada! ";
//             }
//             break;
//         }
//         case 4:
//         {
//             cout << "Percorrendo em ordem...\n";
//             arv.emOrdem(arv.getRaiz());
//             break;
//         }
//         case 5:
//         {
//             cout << "Qde de nos: " << arv.contarNos(arv.getRaiz());
//             break;
//         }
//         case 6:
//         {
//             cout << "Altura da Arvore: " << arv.altura(arv.getRaiz());
//             break;
//         }
//         case 7:
//         {
//             cout << "\n Informe o valor (int) a ser removido -> ";
//             cin >> x;
//             bool resp = arv.remover(x);
//             if (resp)
//                 cout << "\n No removido!";
//             else
//                 cout << "\n No nao encontrado!";
//             break;
//         }
//         case 8:
//         {
//             arv.infs();
//             break;
//         }
//         default:
//             if (opcao != 9)
//                 cout << "\n Opcao invalida! \n\n\n";
//         } // fim switch
//     }
//     while(opcao != 9);

//     return 0;
// }



tuple < Arvore,vector<vector<string>>,vector<pair<string, float>>,vector<string>,vector<string> > inserirDadosArv(Arvore arv, 
vector<vector<string>> tabela, vector<pair<string, float>> dados, vector<string> colunas, vector<string> alimentos){

    lerCSV("dados/dados_finais.csv", tabela);
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
    return make_tuple(arv, tabela, dados, colunas, alimentos);
}



void imprimeAlimentos(vector<vector<string>> tabela, Arvore arv, vector<string> colunas,vector<string> alimentos){
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

    for(string alimento_informado : lista_alimentos){ //Percorrer a lista de alimentos e procurar um a um na árvore
                arv.selecionarNo(alimento_informado);
                cout << "\n" << "informacoes nutricionais da(o): " << arv.getSelecionado()->getChave() << "\n" << endl;
                for(int j=0;j<(tabela[0].size())-1;j++){ //percorrer as colunas
                    cout << tabela[0][j+1] << ": " << arv.getSelecionado()->procurarDado(colunas[j]) << "\n" << endl;
                }
            }

    for(int j=0;j<(tabela[0].size())-1;j++){
            float contador = 0;
            cout << "\n" << "Relacao Nutricional Completa: " << endl;
            for(string alimento_informado : lista_alimentos){ //percorrer as colunas
                arv.selecionarNo(alimento_informado);
                contador = contador + arv.getSelecionado()->procurarDado(colunas[j]);
            }
            cout << tabela[0][j+1] << ": " << contador << "\n" << endl;
    }
    //Selecionar nó com esse nome -> Todos nomes estão no vetor alimentos
    //arv.selecionarNo(alimentos[0]);

    //Printar chave do nó
    //cout << arv.getSelecionado()->getChave() << endl;

    //Procurar algum dado do alimento -> Todos dados disponíveis estão no vetor colunas
    //cout << arv.getSelecionado()->procurarDado(colunas[22]) << endl;

}






int main(int argc, char *argv[])
{
    Arvore arv;
    vector<vector<string>> tabela;
    vector<pair<string, float>> dados;
    vector<string> colunas, alimentos;
    tie(arv, tabela, dados, colunas, alimentos) = inserirDadosArv(arv, tabela, dados, colunas, alimentos);
    imprimeAlimentos( tabela, arv, colunas, alimentos);


    // percorre em ordem iniciando da raiz
    // cout << "\nPercorrendo em ordem crescrente...\n";
    // arv.emOrdem();
    // cout << "\nDenhando a arvore deitada...\n";
    // arv.DesenhaArvore();







    return 0;
}
