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


class ArvoreBST
{
private:
    No *raiz;

public:
    ArvoreBST()
    {
        raiz = NULL;
    }

    void inserir(int chave)
    {
        if(raiz == NULL) // verifica se a árvore está vazia
            raiz = new No(chave); // cria um novo nó
        else
            inserirAux(raiz, chave);
    }

    void inserirAux(No *no, int chave)
    {
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

    No* getRaiz()
    {
        return raiz;
    }

    void emOrdem(No* no)
    {
        if(no != NULL)
        {
            emOrdem(no->getEsq());
            cout << no->getChave() << " ";
            emOrdem(no->getDir());
        }
    }

    void preOrdem(No* no)
    {
        if(no != NULL)
        {
            cout << no->getChave() << " ";
            preOrdem(no->getEsq());
            preOrdem(no->getDir());
        }
    }

    void posOrdem(No* no)
    {
        if(no != NULL)
        {
            posOrdem(no->getEsq());
            posOrdem(no->getDir());
            cout << no->getChave() << " ";

        }
    }

    //versao iterativa
    No *Pesquisar(int dado, No* no)
    {
        if (raiz == NULL) return NULL; //arvore vazia
        No* atual = no;  // cria ptr aux (atual) e comeca a procurar
        while (atual->getChave() != dado)
        {
            if(dado < atual->getChave() )
                atual = atual->getEsq(); // caminha para esquerda
            else
                atual = atual->getDir(); // caminha para direita
            if (atual == NULL)
                return NULL; // encontrou uma folha e nao encontrou a chave
        }
        return atual; //encontrou o dado
    }

    //versao recursiva
    No *PesquisarRec (No* r, int k)
    {
        if (r == NULL || r->getChave() == k)
            return r;
        if (r->getChave() > k)
            return PesquisarRec(r->getEsq(), k);
        else
            return PesquisarRec(r->getDir(), k);
    }

    //versao recursiva
    int contarNos(No* atual)
    {
        if(atual == NULL)  return 0;
        else return ( 1 + contarNos(atual->getEsq()) + contarNos(atual->getDir()));
    }


    //versao recursiva
    int altura(No* atual)
    {
        if(atual == NULL)
            return -1;
        else
        {
            if(atual->getEsq() == NULL && atual->getDir() == NULL)
                return 0;
            else
            {
                if (altura(atual->getEsq()) > altura(atual->getDir()))
                    return ( 1 + altura(atual->getEsq()) );
                else
                    return ( 1 + altura(atual->getDir()) );
            }
        }
    }


    bool remover(int v)
    {
        if (raiz == NULL) return false; //arvore esta vazia

        No *atual = raiz;
        No *pai = raiz;
        bool filho_esq = true;

        // ****** Buscando o valor **********
        while (atual->getChave() != v)   // enquanto nao encontrar a chave
        {
            pai = atual;
            if(v < atual->getChave() )   // caminha para esquerda
            {
                atual = atual->getEsq();
                filho_esq = true; //filho a esquerda? sim
            }
            else   // caminha para direita
            {
                atual = atual->getDir();
                filho_esq = false; //filho a esquerda? NAO
            }
            if (atual == NULL) return false; // encontrou uma folha E nao achou a chave -> TERMINA
        }

        // **************************************************************
        // se chegou aqui quer dizer que encontrou a chave v na arvore
        // "atual": contem a referencia ao No a ser eliminado
        // "pai": contem a referencia para o pai do No a ser eliminado
        // "filho_esq": verdadeiro se atual eh filho a esquerda do pai
        // **************************************************************

        // Se eh uma folha, basta elimina-lo e fazer o ptr do pai receber NULL
        if (atual->getEsq() == NULL && atual->getDir() == NULL)
        {
            if (atual == raiz ) raiz = NULL; // se raiz
            else if (filho_esq)
                pai->setEsq(NULL); // se for filho a esquerda do pai
            else
                pai->setDir(NULL); // se for filho a direita do pai
            //apaga o no
        }
        // Se eh pai e nao possui um filho a direita, substitui pela subarvore a esquerda
        else if (atual->getDir() == NULL)
        {
            if (atual == raiz) raiz = atual->getEsq(); // se raiz
            else if (filho_esq) pai->setEsq(atual->getEsq()); // se for filho a esquerda do pai
            else pai->setDir(atual->getEsq()); // se for filho a direita do pai
        }
        // Se eh pai e nao possui um filho a esquerda, substitui pela subarvore a direita
        else if (atual->getEsq() == NULL)
        {
            if (atual == raiz) raiz = atual->getDir(); // se raiz
            else if (filho_esq) pai->setEsq(atual->getDir()); // se for filho a esquerda do pai
            else pai->setDir(atual->getDir()); // se for  filho a direita do pai
        }
        // Se possui filhos a esq e dir
        else
        {
            No *sucessor = no_sucessor(atual);
            // Usando o metodo sucessor para encontrar o no mais a esquerda da subarvore a direita (menor dos maiores)
            if (atual == raiz) raiz = sucessor; // se eh raiz
            else if(filho_esq) pai->setEsq(sucessor); // se for filho a esquerda do pai
            else pai->setDir(sucessor); // se for filho a direita do pai
            sucessor->setEsq(atual->getEsq()); // acertando os ponteiros esquerda e direita do sucessor
        }
        //delete atual;
        return true;
    }

    No *no_sucessor(No *apaga)   // O parametro eh a referencia para o No que deseja-se apagar
    {
        No *paidosucessor = apaga;
        No *sucessor = apaga;
        No *atual = apaga->getDir(); // vai para a subarvore a direita

        while (atual != NULL)   // enquanto nao chegar no no mais a esquerda
        {
            paidosucessor = sucessor;
            sucessor = atual;
            atual = atual->getEsq(); // caminha para a esquerda
        }
        // *********************************************************************************
        // quando sair do while "sucessor" sera o no mais a esquerda da subarvore a direita
        // "paidosucessor" sera o pai de sucessor e "apaga" o no que devera ser eliminado
        // *********************************************************************************
        if (sucessor != apaga->getDir())   // se sucessor nao eh o filho a direita do no que devera ser eliminado
        {
            paidosucessor->setEsq(sucessor->getDir()); // pai herda os filhos do sucessor que sempre serao a direita
            // lembrando que o sucessor nunca podera ter filhos a esquerda, pois, ele sempre sera o
            // no mais a esquerda da subarvore a direita do no apaga.
            // lembrando tambem que sucessor sempre sera o filho a esquerda do pai

            sucessor->setDir(apaga->getDir()); // guardando a referencia a direita do sucessor para
            // quando ele assumir a posicao correta na arvore
        }
        return sucessor;
    }


    int folhas(No *atual)
    {
        if(atual == NULL) return 0;
        if(atual->getEsq() == NULL && atual->getDir() == NULL) return 1;
        return folhas(atual->getEsq()) + folhas(atual->getDir());
    }

    int min()
    {
        No *atual = raiz;
        No *anterior = NULL;
        while (atual != NULL)
        {
            anterior = atual;
            atual = atual->getEsq();
        }
        return anterior->getChave();
    }

    int max()
    {
        No *atual = raiz;
        No *anterior = NULL;
        while (atual != NULL)
        {
            anterior = atual;
            atual = atual->getDir();
        }
        return anterior->getChave();
    }

    void infs()
    {
        cout << "\nInformacoes gerais da arvore: \n";
        cout << "\n Altura da arvore: " << altura(raiz);
        cout << "\n Quantidade de folhas: " << folhas(raiz);
        cout << "\n Quantidade de Nos: " << contarNos(raiz);
        if (raiz != NULL )    // se arvore nao esta vazia
        {
            cout << "\n Valor minimo: " << min();
            cout << "\n Valor maximo: " << max() << endl;
        }
    }

    //ATIVIDADES INICIAIS DE LAB:
    //pesquisar()
    //qdeNos()
    //alturaArvore()



    //PROXIMAS ATIVIDADES DE LAB:
    //ContarFolhas()
    //ValorMin()
    //ValorMax()
    //Remover()



};

int main(int argc, char *argv[])
{
    ArvoreBST arv;
    int opcao, x;
    cout << ("\nTestando o TAD BST (Elementos do tipo int)\n");

    do
    {
        cout << "\n\n";
        cout << "\n***********************************";
        cout << "\n\tMenu - Arvore BST\n";
        cout << "\nEntre com a opcao:";
        cout << "\n ----1: Inserir";
        cout << "\n ----2: Excluir";
        cout << "\n ----3: Pesquisar";
        cout << "\n ----4: Imprimir em ordem";
        cout << "\n ----5: Qde de nos";
        cout << "\n ----6: Altura";
        cout << "\n ----7: Remover";
        cout << "\n ----8: Informacoes";
        cout << "\n ----9: Sair do programa\n";
        cout << "\n***********************************";
        cout << "\n-> ";
        cin >> opcao;
        switch(opcao)
        {
        case 1:
        {
            cout << "\n Informe o valor (int) -> ";
            cin >> x;
            arv.inserir(x);
            break;
        }
        case 2:
        {
            cout << "\n Ainda nao implementado! ";

            break;
        }
        case 3:
        {
            cout << "\n Informe o valor da chave (int) -> ";
            cin >> x;
            //No *ret = arv.Pesquisar(x,arv.getRaiz());
            No *ret = arv.PesquisarRec(arv.getRaiz(),x);
            if (ret == NULL)
            {
                cout << "\n Chave nao encontrada! ";
            }
            else
            {
                cout << "\n Chave encontrada! ";
            }
            break;
        }
        case 4:
        {
            cout << "Percorrendo em ordem...\n";
            arv.emOrdem(arv.getRaiz());
            break;
        }
        case 5:
        {
            cout << "Qde de nos: " << arv.contarNos(arv.getRaiz());
            break;
        }
        case 6:
        {
            cout << "Altura da Arvore: " << arv.altura(arv.getRaiz());
            break;
        }
        case 7:
        {
            cout << "\n Informe o valor (int) a ser removido -> ";
            cin >> x;
            bool resp = arv.remover(x);
            if (resp)
                cout << "\n No removido!";
            else
                cout << "\n No nao encontrado!";
            break;
        }
        case 8:
        {
            arv.infs();
            break;
        }
        default:
            if (opcao != 9)
                cout << "\n Opcao invalida! \n\n\n";
        } // fim switch
    }
    while(opcao != 9);

    return 0;
}
