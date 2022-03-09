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
	//versao iterativa ********* refazer
	int PesquisarNoPaiEFilhos(int dado, No* &noAtual,No* &noAtualPai, No* &noAtualFilhoDir, No* &noAtualFilhoEsq) {
		// recebe uma arvore que tem mais de 1 no e com o no desejado.
		No* atual = noAtual;  // cria ptr aux (atual) e comeca a procurar
	    if (raiz == NULL) return NULL; //arvore vazia
	    while ( (atual->getDir()->getChave() != dado)  || (atual->getEsq()->getChave() != dado)){//pegar o noAtualPai
	      if(dado < atual->getChave() ) 
		  	atual = atual->getEsq(); // caminha para esquerda
	      else 
		  	atual = atual->getDir(); // caminha para direita
//	      if (atual == NULL) 
//		  	return NULL; // encontrou uma folha e nao encontrou a chave
	    }
	    noAtualPai = atual;
	    noAtualFilhoDir = atual->getDir();
	    noAtualFilhoEsq = atual->getEsq();
	    return 0; //encontrou o dado
	  }

  int RemoverNo(No* atual, int dado) { //******************** rafa
  	/*
  	(ok)caso 1: arvore sem nó retorna erro
  	(ok)caso 2: se o nó não estiver na arvore, retornar erro
  	- no está na árvore:
  	(ok)caso 3: arvore com 1 no: remove o no
  	caso 4: no folha(sem filho): no pai deve apontar para null e excluir o no. 
  	caso 5: no com 1 filho: no pai do nó escolhido, aponta para o nó filho do nó escolhido. Remove o nó escolhido.
  	caso 6: no com 2 filhos. pior caso : estudar.
  	*/
  	
	No *noRemover = Pesquisar(dado, atual);//pegar o nó que deve ser removido
    if(atual == NULL){
     	cout << "Arvore sem no" << endl;
		return -1;
	}
	else if(noRemover == NULL){
     	cout << "No nao se encontra na arvore" << endl;
		return -1;
	 }
	else if( (dado == raiz->getChave()) && (contarNos(atual) == 0)){
     	cout << "arvore com 1 no" << endl;
     	raiz = NULL;
     	cout << "no removido" << endl;
		return -1;
	}
	 //nó está na arvore
    else {
     	//caso 3
//     	No *noAtualPai, *noAtualFilhoDir, *noAtualFilhoEsq;
//     	PesquisarNoPaiEFilhos(dado,atual,noAtualPai,noAtualFilhoDir,noAtualFilhoEsq);// pegar os nós pai e filho
//     	cout << "atual = " << atual->getChave() << " " << 
//     		    "noAtualPai = " << noAtualPai->getChave() << " " <<
//     		    "noAtualFilhoDir = " << noAtualFilhoDir->getChave() << " " <<
//     		    "noAtualFilhoEsq = " << noAtualFilhoEsq->getChave() << " " << endl;
     	cout << "pior caso - continuar o desenvolvimento" << endl;
     	return -1;
     }
  }
	
	//PROXIMAS ATIVIDADES DE LAB:
	//ContarFolhas()
	//ValorMin()
	//ValorMax()
	

};

int main(int argc, char *argv[])
{
	ArvoreBST arv;
    int opcao, x;
    cout << ("\nTestando o TAD BST (Elementos do tipo int)\n");
	arv.inserir(3);arv.inserir(4);arv.inserir(2); // inserir dados
	
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
			case 2: {//******************** rafa Excluir
				int dado;
				cout << "Digite o valor do no: ";
				cin >> dado;
				arv.RemoverNo(arv.getRaiz(), dado);
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
