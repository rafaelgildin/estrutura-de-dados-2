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
	int contarFolhas(No* atual) {
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


	//--------------------------------------------Rafael---------------------------------
	void getVetorAvr(No* no, int nosChaves[], No *nosPtr[], int &q)
	{
	/*
	inputs
		no: nó da arvore
		nosChaves: vetor com as chaves dos nós
		nosPtr: vetor com os ponteiros dos nós
		q: quantidade de iterações: idealmente colocar 0
	outputs por parâmetro:
		nosChaves
		nosPtr
	*/
		if(no != NULL)
		{
			getVetorAvr(no->getEsq(), nosChaves,nosPtr, q);
			//cout << "q = " << q << "  | chave = " << no->getChave() <<  endl;
			nosChaves[q] = no->getChave();
			nosPtr[q] = no;
			q+=1;
			getVetorAvr(no->getDir(), nosChaves,nosPtr, q);
		}
	}


  //versao iterativa
  No *PesquisarPai(int dado, No* no) {
  	/*
		retorna o pai de um nó.
		OBS: colocar apenas nó com pai
  	*/
    if (raiz == NULL) return NULL; //arvore vazia
    if (no->getChave() == dado) return NULL; //arvore com 1 folha, sem pai
    No* atual = no;  // cria ptr aux (atual) e comeca a procurar
    No* noFilhoDir = NULL;
    No* noFilhoEsq = NULL;
    while (true) {
	  if(atual->getDir() != NULL)// verificar se tem chave na direita
			if(atual->getDir()->getChave() == dado) //verifica se é o dado
				return atual;
	  if(atual->getEsq() != NULL)// verificar se tem chave na esquerda
			if(atual->getEsq()->getChave() == dado) //verifica se é o dado
				return atual;
      if(dado < atual->getChave() )
	  	atual = atual->getEsq(); // caminha para esquerda
      else
	  	atual = atual->getDir(); // caminha para direita
      if (atual == NULL)
	  	return NULL; // encontrou uma folha e nao encontrou a chave
    }
    return atual; //encontrou o dado
  }

  int RemoverNo(No* atual, int dado) {
  	/*
  	Remover um nó da árvore
  	situações possíveis:
  		(nó não está na árvore)
	  	caso 1: arvore sem nó retorna erro
	  	caso 2: se o nó não estiver na arvore, retornar erro
	  	(nó está na árvore)
	  	caso 3: arvore com 1 no, no folha(sem filho): no pai deve apontar para null e excluir o no.
	  	caso 4: no com 1 filho
		caso 5: no com 2 filhos
  	*/
  	cout << "entra no RemoverNo" << endl;
	No *noRemover = Pesquisar(dado, atual);//pegar o nó que deve ser removido

    if(atual == NULL){//caso 1
     	cout << "Arvore sem no" << endl;
		return -1;
	}
	else if(noRemover == NULL){//caso 2
     	cout << "No nao se encontra na arvore" << endl;
		return -1;
	 }//nó está na arvore caso 3:
	else if( (dado == raiz->getChave()) && (contarNos(atual) == 1)){
     	cout << "arvore com 1 no" << endl;
     	raiz = NULL;
     	cout << "no removido" << endl;
		return -1;
	}
    else //caso 4
	{
	//no com 1 filho:
		cout << "noRemover = " << noRemover->getChave() << " " << endl;
		// pegar alguns dados sobre o nó
	   	No *noPai = PesquisarPai(dado, atual);
		No *noFilhoDir=NULL, *noFilhoEsq = NULL;
		int qFilhos=0, qPai=0;
		if(noPai != NULL){// verificar se tem pai
			cout << "noPai = " << noPai->getChave() << " " << endl;
			qPai++;
		}
		if(noRemover->getDir() != NULL){// verificar se tem chave na direita, se sim a pega
			noFilhoDir = noRemover->getDir();
			cout << "noFilhoDir = " << noFilhoDir->getChave() << " " << endl;
			qFilhos++;
		}
		if(noRemover->getEsq() != NULL){// verificar se tem chave na esquerda, se sim a pega
			noFilhoEsq = noRemover->getEsq();
			cout << "noFilhoEsq = " << noFilhoEsq->getChave() << " " << endl;
			qFilhos++;
		}
		//no com 1 filho e sem pai (no = raiz)
		if(qFilhos == 1 && qPai == 0){
			cout << "no com 1 filho e sem pai" << endl;
			//pegar o filho
			//raiz = filho
			//deletar o no antigo
			if (noFilhoDir != NULL){
				raiz = noFilhoDir;
			}
			if (noFilhoEsq != NULL){
				raiz = noFilhoEsq;
			}
			noRemover = NULL;
			delete noRemover;
		}
		//no sem filho e com pai
		if(qFilhos == 0 && qPai == 1){
			cout << "no sem filho e com pai" << endl;
			//pai aponta para NULL em dir e esq
			//deletar o no antigo
			if (noPai->getDir() == noRemover){
				noPai->setDir(NULL);
			}
			if (noPai->getEsq() == noRemover){
				noPai->setEsq(NULL);
			}
			noRemover = NULL;
			delete noRemover;
		}
		//no com 1 filho e com pai
		if(qFilhos == 1 && qPai == 1){
			cout << "no com 1 filho e com pai" << endl;
			//paiNoRemover aponta para filhoNoRemover
			//deletar NoRemover
			if (noFilhoDir != NULL){
				noPai->setDir(noFilhoDir);
			}
			if (noFilhoEsq != NULL){
				noPai->setEsq(noFilhoEsq);
			}
			noRemover = NULL;
			delete noRemover;
		}
		//no com 2 filhos -> caso 5
		if(qFilhos == 2){
			cout << "no com 2 filhos" << endl;
			int i,valor, qNos = contarNos(noRemover), q=0;
			No *nosPtr[qNos];
			int nosChaves[qNos];
			getVetorAvr(noRemover, nosChaves, nosPtr,q); //criar um vetor com a sub-arvore, com raiz = noRemover -> getVetorAvr()

			//se tiver noPai apontar para NULL no lado do noRemover
			if(noPai != NULL){
				if(noRemover == noPai->getDir())
					noPai->setDir(NULL);
				if(noRemover == noPai->getEsq())
					noPai->setEsq(NULL);
			}
			//colocar noFilhoDir como raiz, se noRemover for raiz
			if(noRemover==raiz){
					raiz = noFilhoDir;
				}
			//inserir os nos na arvore
			for(i=0; i<qNos; i++){
				cout << "i:" << i << "  nosChaves=" << nosChaves[i] << "   nosPtr=" << nosPtr[i] << endl;
				if(nosChaves[i] != noRemover->getChave()){//não inserir o noRemover, quando esse não é raiz
					valor = nosChaves[i];
					inserir(valor);
				}
			}
			//deletar noRemover
			noRemover->setDir(NULL);
			noRemover->setEsq(NULL);
			delete noRemover;
		}
     	cout << "qPai=" << qPai << "  qFilhos=" << qFilhos << endl;
		cout << "Fim fa funcao RemoverNo" << endl;
     	return -1;

    }
  }
  //--------------------------------------------Rafael---------------------------------


    int encontrarMax(No* no)
    {
        // Caso nulo
        if (no == NULL)
            return -2147483648;
        // Retorno de 3 valores: Chave da raiz, maximo na sub arvore da direita, e maximo na sub arvore da esquerda
        int res = no->getChave();
        int dirRes = encontrarMax(no->getEsq());
        int esqRes = encontrarMax(no->getDir());
        if (esqRes > res)
            res = esqRes;
        if (dirRes > res)
            res = dirRes;
        return res;
    }

    int encontrarMin(No* no)
    {
        // Caso nulo
        if (no == NULL)
            return 2147483647; //Valor maximo do int

        // Retorno de 3 valores: Chave da raiz, minimo na sub árvore da direita, e minimo na sub árvore da esquerda
        int res = no->getChave();
        int esqRes = encontrarMin(no->getEsq());
        int dirRes = encontrarMin(no->getDir());
        if (esqRes < res)
            res = esqRes;
        if (dirRes < res)
            res = dirRes;
        return res;
    }
};

int main(int argc, char *argv[])
{
	ArvoreBST arv;
    int opcao, x;
    cout << ("\nTestando o TAD BST (Elementos do tipo int)\n");
//	arv.inserir(20);arv.inserir(10);arv.inserir(30); // inserir dados
//	arv.inserir(5);arv.inserir(15);
	do {
    	cout << "\n";
        cout << "\n***********************************";
        cout << "\n\tMenu - Arvore BST\n";
        cout << "\nEntre com a opcao:";
		cout << "\n ----1: Inserir";
		cout << "\n ----2: Excluir";
		cout << "\n ----3: Pesquisar";
		cout << "\n ----4: Imprimir em ordem";
		cout << "\n ----5: Qde de nos";
		cout << "\n ----6: Qde de folhas";
		cout << "\n ----7: Altura";
        cout << "\n ----8: Valor maximo";
        cout << "\n ----9: Valor minimo";
		cout << "\n ----10: Sair do programa";
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
				cout << "Qde de folhas: " << arv.contarFolhas(arv.getRaiz());
				break;
			}
			case 7:{
				cout << "Altura da Arvore: " << arv.altura(arv.getRaiz());
                break;
			}
            case 8:{
            	int max = arv.encontrarMax(arv.getRaiz());
            	if(max == -2147483648){
            		cout << "arvore sem no" << endl;
            		break;
				}
                cout << "Valor maximo: " << max;
                break;
            }
            case 9:{
            	int min = arv.encontrarMin(arv.getRaiz());
            	if(min == 2147483647){
            		cout << "arvore sem no" << endl;
            		break;
				}
                cout << "Valor minimo: " << min;
                break;
            }
			default:
                cout << "\n Opcao invalida! \n";
        } // fim switch
    } while(opcao != 10);
	return 0;
}
