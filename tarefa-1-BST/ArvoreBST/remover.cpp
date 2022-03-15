
#include "ArvoreBST.h"

void ArvoreBST::getVetorAvr(No* no, int nosChaves[], No *nosPtr[], int &q){
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

  
No* ArvoreBST::PesquisarPai(int dado, No* no){
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

int ArvoreBST::RemoverNo(No* atual, int dado){
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
