// TAD AVL
// Rafael Avraham Gildin Acherboim 31940242
// Andrea Mindlin Tessler - 42012538
// GUSTAVO ANDRADE DE PAULA 42081327
// Gustavo Bernard Schwarz 32141157

#include "AVL.cpp"
#include "LeitorCSV.h"
#include <vector>
#include <list>
#include <algorithm>
#include <tuple>

tuple < Arvore,vector<vector<string>>,vector<pair<string, float>>,vector<string>,vector<string> > inserirDadosArv(Arvore arv, 
vector<vector<string>> tabela, vector<pair<string, float>> dados, vector<string> colunas, vector<string> alimentos){

    lerCSV("dados/com-pai/dados_finais_RDD.csv", tabela);
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

void imprime1Alimento(vector<vector<string>> tabela, Arvore arv, vector<string> colunas,vector<string> alimentos){
    std::string alimento_informado;
    list<string> lista_alimentos;
    while(true){   //Pegar a String informada, e colocar em uma lista
        cout << "Insira o alimento consumido: ";
        cin >> alimento_informado;
        alimento_informado = arv.converterPalavra(alimento_informado);
        arv.selecionarNo(alimento_informado);
        if(arv.getSelecionado() != nullptr){
            lista_alimentos.push_back(alimento_informado);
            cout << "Alimento registrado" << endl;
            break;
        }else{
            cout << "Alimento nao presente na tabela, tente novamente" << endl;
        }
    }
    for(string alimento_informado : lista_alimentos){ //Percorrer a lista de alimentos e procurar um a um na árvore
                arv.selecionarNo(alimento_informado);
                cout << "\n" << "informacoes nutricionais da(o): " << arv.getSelecionado()->getChave() << "\n" << endl;
                for(int j=0;j<(tabela[0].size())-1;j++){ //percorrer as colunas
                    cout << tabela[0][j+1] << ": " << arv.getSelecionado()->procurarDado(colunas[j]) << endl;
                }
            }
            // arv.selecionado = nullptr;
}

void imprimeAlimentos(vector<vector<string>> tabela, Arvore arv, vector<string> colunas,vector<string> alimentos){
    std::string alimento_informado;
    list<string> lista_alimentos;
    while(true){   //Pegar a String informada, e colocar em uma lista
        cout << "Insira o alimento consumido (Digite Sair quando tiver finalizado): ";
        cin >> alimento_informado;
        // std::getline (std::cin, alimento_informado);
        alimento_informado = arv.converterPalavra(alimento_informado);
        arv.selecionarNo(alimento_informado);
        if(arv.getSelecionado() != nullptr && alimento_informado != "sair"){
            lista_alimentos.push_back(alimento_informado);
            cout << "Alimento registrado" << endl;
        }else if(alimento_informado != "sair"){
            cout << "Alimento nao presente na tabela, tente novamente" << endl;
        }else{
            break;
        }
        }

    cout << "\n" << "Relacao Nutricional Completa: " << endl;
    for(int j=0;j<(tabela[0].size())-1;j++){
            float contador = 0;
            
            for(string alimento_informado : lista_alimentos){ //percorrer as colunas
                arv.selecionarNo(alimento_informado);
                contador = contador + arv.getSelecionado()->procurarDado(colunas[j]);
            }
            cout << tabela[0][j+1] << ": " << contador << endl;
    }
    // arv.selecionado = nullptr;
    //Selecionar nó com esse nome -> Todos nomes estão no vetor alimentos
    //arv.selecionarNo(alimentos[0]);
    //Printar chave do nó
    //cout << arv.getSelecionado()->getChave() << endl;
    //Procurar algum dado do alimento -> Todos dados disponíveis estão no vetor colunas
    //cout << arv.getSelecionado()->procurarDado(colunas[22]) << endl;
}

void remove1Alimento(Arvore &arv){
    std::string alimento_informado;
    while(true){
        cout << "Insira o alimento a ser removido: ";
        cin >> alimento_informado;
        alimento_informado = arv.converterPalavra(alimento_informado);
        arv.selecionarNo(alimento_informado);
        if(arv.getSelecionado() != nullptr){
            cout << "Alimento encontrado = " << arv.getSelecionado()->getChave() << endl;
            break;
        }else{
            cout << "Alimento nao presente na tabela, tente novamente" << endl;
        }
    }
    // remover o alimento
    arv.remover(alimento_informado);
    cout << "\nAlimento " << alimento_informado << " removido com sucesso" << endl;
    // arv.DesenhaArvore();
    // cout << "raiz = " << arv.raiz->chave << endl;
}

int main(int argc, char *argv[])
{
    Arvore arv;
    vector<vector<string>> tabela;
    vector<pair<string, float>> dados;
    vector<string> colunas, alimentos;
    tie(arv, tabela, dados, colunas, alimentos) = inserirDadosArv(arv, tabela, dados, colunas, alimentos);
    int opcao, x;
    cout << ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nTestando o TAD AVL\n");
    do
    {
        cout << "\n\n";
        cout << "\n***********************************";
        cout << "\n\tMenu - Arvore AVL\n";
        cout << "\nEntre com a opcao:";
        cout << "\n ----1: Pesquisar Alimento Consumido";
        cout << "\n ----2: Pesquisar Alimentos Consumidos";
        cout << "\n ----3: Percorrer em Ordem Crescente";
        cout << "\n ----4: Desenhar a arvore deitada";
        cout << "\n ----5: Remover Alimento";
		cout << "\n ----6: Salvar arvore em arquivo";
		cout << "\n ----7: Imprime altura e quantidade de nos";
        cout << "\n ----8: Sair do programa\n";
        cout << "\n***********************************";
        cout << "\n-> ";
        cin >> opcao;
        switch(opcao)
        {
        case 1:
        {
            imprime1Alimento( tabela, arv, colunas, alimentos);
            break;
        }
        case 2:
        {
            imprimeAlimentos( tabela, arv, colunas, alimentos);
            break;
        }
        case 3:
        {
            //percorre em ordem iniciando da raiz
            cout << "\nPercorrendo em ordem crescrente...\n";
            arv.emOrdem();
            break;
        }
        case 4:
        {
            cout << "\nDenhando a arvore deitada...\n";
            arv.DesenhaArvore();
            break;
        }
        case 5:
        {
            remove1Alimento(arv);
            // arv.DesenhaArvore();
            // cout << "raiz = " << arv.raiz->chave << endl;
            break;
        }
		case 6:
        {
            arv.escreverCSV();
            break;
        }
		case 7:
        {
            int altura = arv.altura(arv.raiz);
            int qNos = arv.contarNos(arv.raiz);
            cout << "altura = " << altura << " |   qNos = " << qNos << endl;
            break;
        }
        default:
            if (opcao != 8)
                cout << "\n Opcao invalida! \n\n\n";
        } // fim switch
    }
    while(opcao != 8);
    return 0;
}
