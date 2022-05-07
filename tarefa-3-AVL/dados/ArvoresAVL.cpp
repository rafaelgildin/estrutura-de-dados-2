// cd /c/Users/rafaa/rafa/git/estrutura-de-dados-2/tarefa-3-AVL/extras/AVL-final/dados
// clear && g++ -o ArvoresAVL.o ArvoresAVL.cpp && ./ArvoresAVL.o
#include <iostream>
#include <cstdlib>
using namespace std;

class No
{
    private:
    public:
	No *esq, *dir;
	int chave;
	int FB;
	No(int chave)
	{
		this->chave = chave;
		esq = NULL;
		dir = NULL;
		FB=0;
	}

	int getChave()
	{
		return chave;
	}

	// funcoes getters e setters
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
	int getFB(){
	    return FB;
	}
	
	//FB = R - L
    void setFB(int FB){ 
	    this->FB = FB;
	}
};

class Arvore
{
    private:
    public:
	No *raiz;
    No *noDesbalanceado;
	int testaFB;
	Arvore()
	{
		raiz = NULL;
        noDesbalanceado = NULL;
	}

    int contarNos(No* atual){
    if(atual == NULL)  return 0;
    else return ( 1 + contarNos(atual->getEsq()) + contarNos(atual->getDir()));
    }
    
    int CalcularFB(No * no)
    {
        if(no == NULL)
            return 0;
        return altura(no->dir) - altura(no->esq);
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

    void getVetorAvr(No* no, No *nosPtr[], int &q){
        /*
        inputs
            no: nó da arvore
            nosPtr: vetor com os ponteiros dos nós
            q: quantidade de iterações: idealmente colocar 0
        outputs por parâmetro:
            nosPtr
        */
            if(no != NULL)
            {
                getVetorAvr(no->getEsq(),nosPtr, q);
                //cout << "q = " << q << "  | chave = " << no->getChave() <<  endl;
                nosPtr[q] = no;
                q+=1;
                getVetorAvr(no->getDir(),nosPtr, q);

            }
        }

    No* PesquisarPai(int dado, No* no){ // novo
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

    void Balancear(void){
        /* Balancear a arvore
        nosPtr: vetor com os ponteiros da arvore
        nosChaves: vetor com as chaves da arvore
        qNos: quantidade de nos na arvore
        */
        int i,valor, qNos = contarNos(raiz), q=0, FB;
        // cout << "quantidade de nos = " << qNos << endl;

        No *nosPtr[qNos];
        getVetorAvr(raiz, nosPtr,q); //criar um vetor com a arvore, com raiz = raiz -> getVetorAvr()
        // cout << "imprimindo os dados" << endl;
        while(true){
            //iterar sobre os nos da arvore p recalcular o FB dos nos
            for(i = 0; i<qNos; i++){
                FB = CalcularFB(nosPtr[i]); // --------------- recalcular
                nosPtr[i]->FB = FB;
                // cout << "i = " << i << "  | chave = " << nosChaves[i] << "  | FB = " << nosPtr[i]->FB << endl;
                //verificar se modulo eh igual a 2              
                if(abs(FB) == 2){
                    // cout << "no desbalanceado = " << " i = " << i << endl;
                    noDesbalanceado = nosPtr[i];
                    cout << "no desbalanceado = " << noDesbalanceado->chave << endl;
                }
            }
             
            if(noDesbalanceado != NULL){
                No * filhoDir = noDesbalanceado->dir;
                No * filhoEsq = noDesbalanceado->esq;
                No * p = noDesbalanceado;
                // cout << "pai desbalanceado = " << pai->chave << endl;
                
                // cout << "\n\np = " << p->chave << endl;
                // if(filhoDir != NULL)
                //     cout << "filhoDir = " << filhoDir->chave << endl;
                // if(filhoEsq != NULL)
                //     cout << "filhoEsq = " << filhoEsq->chave << endl;
                // balancear
                if(noDesbalanceado->FB == 2){
                    No * z = p->dir;
                    if(filhoDir->FB < 0){
                        No * y = z->esq;
                        RotacaoDuplaEsquerda(p,z,y);
                    }
                    else{
                       
                        // cout << "z = " << z->chave << endl;
                        RotacaoSimplesEsquerda(p,z);
                        // DesenhaArvore(); break; 
                    }
                }
                else if(noDesbalanceado->FB == -2){
                    No * u = filhoEsq;
                    // cout << "u = " << u->chave << endl;
                    if(filhoEsq->FB > 0){
                        No * v = u->dir;
                        RotacaoDuplaDireita(p,u,v);
                    }
                    else{
                        RotacaoSimplesDireita(p,u);
                    }
                }
                
                noDesbalanceado =  NULL;
            }
            else 
                break;
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
        // cout << "pai = " << pai->chave << "atual = " << atual->chave << endl;
        delete atual;
        Balancear();

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

	void inserir(int chave)
	{
        raiz = inserir(raiz, chave);
	}

    // insere recursivamente um novo no
	No * inserir(No *no, int chave)
	{
		if( no == nullptr ){
            //insere o novo no
            //seta que alterou a subarvore e eh para testar o Fator de Balanceamento
            testaFB = 1;
            return new No(chave);
		}
		// se for menor, entao insere a esquerda
		if(chave < no->getChave())
		{
            //percorre recursivamente a subarvore da esquerda
            no->setEsq(inserir(no->getEsq(), chave));

			// testa o fator de  balanceamento apos a insercao na subarvore da esquerda
			if( testaFB ){
                switch( no->getFB() ){
                    case 1: // se o no estava maior para direita e inseriu a esquerda
                        no->setFB(0); // seta que agora ficou balanceado
                        testaFB=0; // tudo ficou normalizado, nao precisa atualizar mais a arvore
                        break;
                    case 0:// se estava balanceado e como adicionou a esquerda
                        no->setFB(-1);
                        break;
                    case -1: //ja estava desbalanceado para esquerda
                        no = Caso1( no );// no=p, vamos ver qual rotacao usar
                        testaFB=0; // tudo ficou normalizado, nao precisa atualizar mais a arvore
                        break;
                }
			}
		}
		// se for maior, entao insere a direita
		else if(chave > no->getChave()){

            //percorre recursivamente a subarvore da direita
            no->setDir(inserir(no->getDir(), chave));
            // testa o fator de  balanceamento apos a insercao na subarvore da esquerda
			if( testaFB ){
                switch( no->getFB() ){
                    case -1: // se o no estava maior para esquerda e inseriu a direita
                        no->setFB(0); // seta que agora ficou balanceado
                        testaFB=0; // tudo ficou normalizado, nao precisa atualizar mais a arvore
                        break;
                    case 0:// se estava balanceado e como adicionou a direita
                        no->setFB(1);
                        break;
                    case 1: //ja estava desbalanceado para direita
                        no = Caso2( no );// no=p, vamos ver qual rotacao usar
                        testaFB=0; // tudo ficou normalizado, nao precisa atualizar mais a arvore
                        break;
                }
			}
		}
		// caso no->chave = chave retorna o proprio no
		// nao pode existir 2 chaves iguais
        // cout << "retorna no " << no->getChave() << endl;
        return no;
	}
    
    //  metodo trata a insercao  na subarvore a esquerda de p
    No * Caso1( No *p )
    {
            No *u, *v;

            // filho a esquerda de p
            u = p->getEsq();
            // inseriu na subarvore esquerda de u
            // fazer uma rotacao simples a direita
            if( u->getFB() == -1 ){
                // RotacaoSimplesDireita(p, u);          
                p->setEsq(u->getDir());
                u->setDir(p);
                // ajusta o novo balanceamento de p
                // pois ele passa ser uma T1 - T2 = 0
                p->setFB(0);
                p = u; // p passa ser o u
                cout <<" => realizada uma rotacao simples a direita \n";
            }
            // inseriu na subarvore direita de u
            // fazer uma rotacao dupla a direita
            else{
                // RotacaoDuplaDireita(p, u, v);
                v = u->getDir();           // aqui poderia ser o q caso T2 e T3 sejam nulos
                u->setDir(v->getEsq());
                p->setEsq(v->getDir());
                v->setEsq(u);
                v->setDir(p);
                if( v->getFB() == -1 ){ // se inseriu na subarvore esquerda de v
                    p->setFB(1);
                    u->setFB(0);
                }
                else if( v->getFB() == 1 ){ // se inseriu na subarvore direita de v
                    p->setFB(0);
                    u->setFB(-1);
                }
                else{ // v = q
                    p->setFB(0);
                    u->setFB(0);
                }
                p = v; // p passa ser o v
                cout << " => realizada uma rotacao dupla a direita \n";
            }
            p->setFB(0);
            return p;
    }

    //  metodo trata a insercao  na subarvore a direita de p
    No * Caso2( No *p )
    {
        No *z, *y;
        // filho a direita de p
        z = p->getDir();
        // inseriu na subarvore direita de z
        // fazer uma rotacao a esquerda
        if( z->getFB() == 1 ){
            // RotacaoSimplesEsquerda(p, z);
            p->setDir(z->getEsq());
            z->setEsq(p);
            // ajusta o novo balanceamento de p
            // pois ele passa ser uma T1 - T2 = 0
            p->setFB(0);
            p = z;
            cout << " => realizada uma rotacao simples a esquerda \n";
        }
        // inseriu na subarvore direita de z
        // fazer uma rotacao dupla a esquerda
        else{
            // RotacaoDuplaEsquerda(p, z, y);
            y = z->getEsq();
            z->setEsq(y->getDir());
            p->setDir(y->getEsq());
            y->setEsq(p);
            y->setDir(z);

            if( y->getFB() == 1 ){ // se inseriu na subarvore direita y
                    p->setFB(-1);
                    z->setFB(0);
            }
            else if( y->getFB() == -1 ){ // se inseriu na subarvore esquerda de y
                    p->setFB(0);
                    z->setFB(1);
            }
            else{ // y == q
                    z->setFB(0);
                    p->setFB(0);
            }
            p = y;
            cout << " => realizada uma rotacao dupla a esquerda \n";
        }
        p->setFB(0);
        return p;
    }

    //------------------------ rotacoes --------------------------

    void RotacaoSimplesDireita(No*& p, No*& u){//passar ponteiro por referencia
        No * pPai = PesquisarPai(p->chave, raiz);
        bool pFilhoEsq;
        if (pPai != NULL)
            pFilhoEsq = pPai->esq == p; // p eh filho esq?
        
        p->setEsq(u->getDir());
        u->setDir(p);
        // ajusta o novo balanceamento de p
        // pois ele passa ser uma T1 - T2 = 0
        p->setFB(0);
        // p = u; // p passa ser o u

        cout <<" => realizada uma rotacao simples a direita \n";
        if(raiz == p)
            raiz = u;
        else{//p nao eh raiz
            if(pFilhoEsq)
                pPai->esq = u;
            else
                pPai->dir = u;
        }
    }

    void RotacaoDuplaDireita(No*& p, No*& u, No*& v){
        No * pPai = PesquisarPai(p->chave, raiz);
        bool pFilhoEsq;
        if (pPai != NULL)
            pFilhoEsq = pPai->esq == p; // p eh filho esq?
        
        v = u->getDir(); // aqui poderia ser o q caso T2 e T3 sejam nulos
        u->setDir(v->getEsq());
        p->setEsq(v->getDir());
        v->setEsq(u);
        v->setDir(p);
        if( v->getFB() == -1 ){ // se inseriu na subarvore esquerda de v
            p->setFB(1);
            u->setFB(0);
        }
        else if( v->getFB() == 1 ){ // se inseriu na subarvore direita de v
            p->setFB(0);
            u->setFB(-1);
        }
        else{ // v = q
            p->setFB(0);
            u->setFB(0);
        }
        cout << " => realizada uma rotacao dupla a direita \n";
        // p = v; // p passa ser o v
        if(raiz == p)
            raiz = v;
        else{//p nao eh raiz
            if(pFilhoEsq)
                pPai->esq = v;
            else
                pPai->dir = v;
        }
    }

    void RotacaoSimplesEsquerda(No*& p, No*& z){
        No * pPai = PesquisarPai(p->chave, raiz);
        bool pFilhoEsq;
        if (pPai != NULL)
            pFilhoEsq = pPai->esq == p; // p eh filho esq?
        
        // cout << "\n\n\ndesenha arvore " << endl;DesenhaArvore();
        // cout << "p = " << p->chave << "   z = " << z->chave << endl;
        // cout << "z.esq = " << z->getEsq()->chave << "   z.dir = " << z->getDir()->chave << endl;

        p->setDir(z->getEsq());
        z->setEsq(p);
        // ajusta o novo balanceamento de p
        // pois ele passa ser uma T1 - T2 = 0
        p->setFB(0);
        // p = z;//?
        cout << " => realizada uma rotacao simples a esquerda \n";
        if(raiz == p)
            raiz = z;
        else{//p nao eh raiz
            if(pFilhoEsq)
                pPai->esq = z;
            else
                pPai->dir = z;
        }
    }

    void RotacaoDuplaEsquerda(No*& p, No*& z, No*& y){
        No * pPai = PesquisarPai(p->chave, raiz);
        bool pFilhoEsq = NULL;
        if(pPai != NULL)
            pFilhoEsq = pPai->esq == p; // p eh filho esq?           

        // y = z->getEsq();
        z->setEsq(y->getDir());
        p->setDir(y->getEsq());
        y->setEsq(p);
        y->setDir(z);

        if( y->getFB() == 1 ){ // se inseriu na subarvore direita y
                p->setFB(-1);
                z->setFB(0);
        }
        else if( y->getFB() == -1 ){ // se inseriu na subarvore esquerda de y
                p->setFB(0);
                z->setFB(1);
        }
        else{ // y == q
                z->setFB(0);
                p->setFB(0);
        }
        
        cout << " => realizada uma rotacao dupla a esquerda \n";
        // p = y;
        if(raiz == p)
            raiz = y;
        else{//p nao eh raiz
            if(pFilhoEsq)
                pPai->esq = y;
            else
                pPai->dir = y;
        }

        // DesenhaArvore();
    }
    //-----------------------------------------------------
	// polimorfismo de sobrecarga
    void emOrdem(){
        emOrdem(raiz);
    }
    // polimorfismo de sobrecarga
	void emOrdem(No* no)
	{
		if(no != NULL)
		{
			emOrdem(no->getEsq());
			cout << no->getChave() << " ";
			emOrdem(no->getDir());
		}
	}
	void DesenhaArvore(){
        DesenhaArvore(raiz,0);
	}
	void DesenhaArvore(No* no, int espacos )
    {
        if(no != NULL)
		{
            DesenhaArvore(no->getDir(), espacos + 4 );

            for(int i = 0 ; i < espacos; i++ )
                cout << " ";

            cout << no->getChave() << "[" << no->getFB()<< "]\n";

            DesenhaArvore(no->getEsq(), espacos + 4 );
        }
    }
};

int main(int argc, char *argv[])
{
	Arvore arv;
	// TESTES do remover sem pai
    // 1) RSE ok
    arv.inserir(50); arv.inserir(40); arv.inserir(60);arv.inserir(55);arv.inserir(70);
    cout << "apos inserir" << endl; arv.DesenhaArvore();
    arv.remover(40);
    cout << "\n\n\n\nDenhando a arvore deitada depois de balancear...\n"; arv.DesenhaArvore();

    // 2) RDE ok
    //  arv.inserir(50); arv.inserir(40); arv.inserir(60);arv.inserir(55);arv.remover(40); 
    // 3) RSD ok
    //  arv.inserir(60); arv.inserir(50); arv.inserir(70);arv.inserir(40);arv.remover(70); 
    // 4) RDD ok
    //  arv.inserir(60); arv.inserir(50); arv.inserir(70);arv.inserir(55);arv.remover(70);


	// TESTES do remover com pai
    
    /**********************************
    1) RSE -> remove(55) ok
               50
         40          60
      30           55      70
                        65    80

               50
         40            70
      30           60      80
                     65

    arv.inserir(50); arv.inserir(40); arv.inserir(60);arv.inserir(30);arv.inserir(55);
    arv.inserir(70);arv.inserir(65);arv.inserir(80); 
    cout << "apos inserir" << endl; arv.DesenhaArvore();
    arv.remover(55);
    cout << "\n\n\n\nDenhando a arvore deitada depois de balancear...\n"; arv.DesenhaArvore();
    */


    /**********************************
    2) RDE ok -> remove(55)
               50
         40          60
      30           55      70
                         65    

               50
         40            65
      30           60      70
                     

    arv.inserir(50); arv.inserir(40); arv.inserir(60);arv.inserir(30);arv.inserir(55);
    arv.inserir(70);arv.inserir(65);
    cout << "apos inserir" << endl; arv.DesenhaArvore();
    arv.remover(55);
    cout << "\n\n\n\nDenhando a arvore deitada depois de balancear...\n"; arv.DesenhaArvore();
    */

    /*3) RSD -> remove(45)
               50
         40          60
      30   45              70
    20                         

               50
         30          60
      20   40            70
         
                     

    arv.inserir(50); arv.inserir(40); arv.inserir(60);arv.inserir(30);arv.inserir(45);
    arv.inserir(70);arv.inserir(20);
    cout << "apos inserir" << endl; arv.DesenhaArvore();
    arv.remover(45);
    cout << "\n\n\n\nDenhando a arvore deitada depois de balancear...\n"; arv.DesenhaArvore();
    */

    /*4) RDD -> remove(45)
               50
         40          60
     30     45              70
       35                         

               50
         35          60
     30     40              70
           
         
                     

    arv.inserir(50); arv.inserir(40); arv.inserir(60);arv.inserir(30);arv.inserir(45);
    arv.inserir(70);arv.inserir(35);
    cout << "apos inserir" << endl; arv.DesenhaArvore();
    arv.remover(45);
    cout << "\n\n\n\nDenhando a arvore deitada depois de balancear...\n"; arv.DesenhaArvore();
    */
	return 0;
}