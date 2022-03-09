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
	No *Pesquisar(int dado, No* no) {
    if (raiz == NULL) return NULL; //arvore vazia
    No* atual = no;  // cria ptr aux (atual) e comeca a procurar
    while (atual->getChave() != dado) {
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
  No *PesquisarRec (No* r, int k) {
    if (r == NULL || r->getChave() == k)
       return r;
    if (r->getChave() > k)
       return PesquisarRec(r->getEsq(), k);
    else
       return PesquisarRec(r->getDir(), k);
  }
  
  //versao recursiva
  int contarNos(No* atual) {
   if(atual == NULL)  return 0;
   else return ( 1 + contarNos(atual->getEsq()) + contarNos(atual->getDir()));
  }
  

  //versao recursiva
  int altura(No* atual) {
     if(atual == NULL)
       return -1;
     else {
     	if(atual->getEsq() == NULL && atual->getDir() == NULL)
       		return 0;
     	else{		 
   			if (altura(atual->getEsq()) > altura(atual->getDir()))
   	   			return ( 1 + altura(atual->getEsq()) );
   			else
	   			return ( 1 + altura(atual->getDir()) );
	   }
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

	do {
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
		cout << "\n ----7: Sair do programa\n";
		cout << "\n***********************************";
		cout << "\n-> ";
		cin >> opcao;
		switch(opcao) {
	 		case 1: {
		       cout << "\n Informe o valor (int) -> ";
		       cin >> x;
		       arv.inserir(x);
		       break;
			}
			case 2: {
		       cout << "\n Ainda nao implementado! ";

		       break;
			}
			case 3: {		       
		       cout << "\n Informe o valor da chave (int) -> ";
		       cin >> x;
		       //No *ret = arv.Pesquisar(x,arv.getRaiz());
		       No *ret = arv.PesquisarRec(arv.getRaiz(),x);
		       if (ret == NULL){
		       	cout << "\n Chave nao encontrada! ";
			   }else{
			   	cout << "\n Chave encontrada! ";			   	
			   }      			    	
		       break;
			}
			case 4: {
                cout << "Percorrendo em ordem...\n";
                arv.emOrdem(arv.getRaiz());
                break;
			}
			case 5:{
				cout << "Qde de nos: " << arv.contarNos(arv.getRaiz());
                break;
			}
			case 6:{
				cout << "Altura da Arvore: " << arv.altura(arv.getRaiz());
                break;
			}			
			default:
				if (opcao != 7)
					cout << "\n Opcao invalida! \n\n\n";
        } // fim switch
    } while(opcao != 7);

	return 0;
}
