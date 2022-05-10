#include <iostream>
#include <utility>
#include <vector>
#include <algorithm> 
#include <fstream>
#include <cstdlib>

using namespace std;

class No
{
    private:
    public:
	No *esq, *dir;
	std::string chave;
	int FB;
	vector<pair<string, float>> dados;
	No(std::string chave, vector<pair<string, float>> dados)
	{
		this->chave = std::move(chave);
		this->dados = std::move(dados);
		esq = nullptr;
		dir = NULL;
		FB=0;
	}

    std::string getChave() const
	{
		return chave;

	}

    float procurarDado(const string& coluna){
        for (auto & dado : dados){
            if (coluna == dado.first){
                return dado.second;
            }
        }
        cout << "Coluna não encontrada!" << endl;
    }

	const vector<pair<std::string, float>>& getDados() const{
		return dados;
	}

	// funcoes getters e setters
	No* getEsq() const
	{
		return esq;
	}
	No* getDir() const
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
	int getFB() const{
	    return FB;
	}

	//FatorB = R - L
    void setFB(int FatorB){
	    this->FB = FatorB;
	}
};

class Arvore
{
    private:
    public:
    No *raiz;
    No *selecionado = nullptr;
    No *noDesbalanceado;
	int testaFB{};
	Arvore()
	{
		raiz = nullptr;
        noDesbalanceado = nullptr;
	}

    //ok
    int contarNos(No* atual){
    if(atual == nullptr)  return 0;
    else return ( 1 + contarNos(atual->getEsq()) + contarNos(atual->getDir()));
    }
    //ok
    int CalcularFB(No * no)
    {
        if(no == nullptr)
            return 0;
        return altura(no->dir) - altura(no->esq);
    }
    //ok
    int altura(No* atual)
    {
        if(atual == nullptr)
            return -1;
        else
        {
            if(atual->getEsq() == nullptr && atual->getDir() == nullptr)
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
    //ok
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
                nosPtr[q] = no;
                q+=1;
                // cout << "no = " << no->chave << endl;
                getVetorAvr(no->getDir(),nosPtr, q);

            }
        }

    No* PesquisarPai(const std::string& dado, No* no) const{ // ok
  	/*
		retorna o pai de um nó.
		OBS: colocar apenas nó com pai
  	*/
    if (raiz == nullptr) return nullptr; //arvore vazia
    if (no->getChave() == dado) return nullptr; //arvore com 1 folha, sem pai
    No* atual = no;  // cria ptr aux (atual) e comeca a procurar
    No* noFilhoDir = nullptr;
    No* noFilhoEsq = nullptr;
    while (true) {
	  if(atual->getDir() != nullptr)// verificar se tem chave na direita
			if(atual->getDir()->getChave() == dado) //verifica se é o dado
				return atual;
	  if(atual->getEsq() != nullptr)// verificar se tem chave na esquerda
			if(atual->getEsq()->getChave() == dado) //verifica se é o dado
				return atual;
      if(dado < atual->getChave() )
	  	atual = atual->getEsq(); // caminha para esquerda
      else
	  	atual = atual->getDir(); // caminha para direita
      if (atual == nullptr)
	  	return nullptr; // encontrou uma folha e nao encontrou a chave
    }
    return atual; //encontrou o dado
  }

    void Balancear(){
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
                FB = CalcularFB(nosPtr[i]);
                nosPtr[i]->FB = FB;
                // cout << "i = " << i << "  | chave = " << nosChaves[i] << "  | FB = " << nosPtr[i]->FB << endl;
                //verificar se modulo eh igual a 2              
                if(abs(FB) == 2){
                    // cout << "no desbalanceado = " << " i = " << i << endl;
                    noDesbalanceado = nosPtr[i];
                    cout << "no desbalanceado = " << noDesbalanceado->chave << endl;
                }
            }          
            if(noDesbalanceado != nullptr){
                No * filhoDir = noDesbalanceado->dir;
                No * filhoEsq = noDesbalanceado->esq;
                No * p = noDesbalanceado;
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
                noDesbalanceado =  nullptr;
            }
            else 
                break;
        }
    }

    bool remover(std::string v)//ok
    {
        if (raiz == nullptr) return false; //arvore esta vazia

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
            if (atual == nullptr) return false; // encontrou uma folha E nao achou a chave -> TERMINA
        }

        // **************************************************************
        // se chegou aqui quer dizer que encontrou a chave v na arvore
        // "atual": contem a referencia ao No a ser eliminado
        // "pai": contem a referencia para o pai do No a ser eliminado
        // "filho_esq": verdadeiro se atual eh filho a esquerda do pai
        // **************************************************************

        // Se eh uma folha, basta elimina-lo e fazer o ptr do pai receber NULL
        if (atual->getEsq() == nullptr && atual->getDir() == nullptr)
        {
            if (atual == raiz ) raiz = nullptr; // se raiz
            else if (filho_esq)
                pai->setEsq(nullptr); // se for filho a esquerda do pai
            else
                pai->setDir(nullptr); // se for filho a direita do pai
            //apaga o no
        }
        // Se eh pai e nao possui um filho a direita, substitui pela subarvore a esquerda
        else if (atual->getDir() == nullptr)
        {
            if (atual == raiz) raiz = atual->getEsq(); // se raiz
            else if (filho_esq) pai->setEsq(atual->getEsq()); // se for filho a esquerda do pai
            else pai->setDir(atual->getEsq()); // se for filho a direita do pai
        }
        // Se eh pai e nao possui um filho a esquerda, substitui pela subarvore a direita
        else if (atual->getEsq() == nullptr)
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
        // atual->dir = nullptr;
        // atual->esq = nullptr;
        delete atual;
        Balancear();
        return true;
    }

    No *no_sucessor(No *apaga)   // O parametro eh a referencia para o No que deseja-se apagar
    {
        No *paidosucessor = apaga;
        No *sucessor = apaga;
        No *atual = apaga->getDir(); // vai para a subarvore a direita

        while (atual != nullptr)   // enquanto nao chegar no no mais a esquerda
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
    //------------------------ rotacoes --------------------------

    void RotacaoSimplesDireita(No*& p, No*& u){//passar ponteiro por referencia
        No * pPai = PesquisarPai(p->chave, raiz);
        bool pFilhoEsq;
        if (pPai != nullptr)
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
            if(pFilhoEsq && pPai != nullptr)
                pPai->esq = u;
            else if (pPai != nullptr)
                pPai->dir = u;
        }
    }

    void RotacaoDuplaDireita(No*& p, No*& u, No*& v){
        No * pPai = PesquisarPai(p->chave, raiz);
        bool pFilhoEsq;
        if (pPai != nullptr)
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
            if(pFilhoEsq && pPai != nullptr)
                pPai->esq = v;
            else if (pPai != nullptr)
                pPai->dir = v;
        }
    }

    void RotacaoSimplesEsquerda(No*& p, No*& z){
        No * pPai = PesquisarPai(p->chave, raiz);
        bool pFilhoEsq;
        if (pPai != nullptr)
            pFilhoEsq = pPai->esq == p; // p eh filho esq?
        // cout << "\n\n\ndesenha arvore " << endl;DesenhaArvore();
        // cout << "p = " << p->chave << "   z = " << z->chave << endl;
        // cout << "pFilhoEsq = " << pFilhoEsq << endl;
        // cout << "z.esq = " << z->getEsq()->chave << "   z.dir = " << z->getDir()->chave << endl;

        p->setDir(z->getEsq());
        z->setEsq(p);
        // ajusta o novo balanceamento de p
        // pois ele passa ser uma T1 - T2 = 0
        p->setFB(0);
        // p = z;//?
        cout << " => realizada uma rotacao simples a esquerda \n";
        if(raiz == p){
            raiz = z;
        }
        else{//p nao eh raiz
            cout << "entra no else" << endl;
            if(pFilhoEsq && pPai != nullptr)
                pPai->esq = z;
            else if (pPai != nullptr)
                pPai->dir = z;
        }
    }

    void RotacaoDuplaEsquerda(No*& p, No*& z, No*& y){
        No * pPai = PesquisarPai(p->chave, raiz);
        bool pFilhoEsq = NULL;
        if(pPai != nullptr)
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
            if(pFilhoEsq && pPai != nullptr)
                pPai->esq = y;
            else if (pPai != nullptr)
                pPai->dir = y;
        }

        // DesenhaArvore();
    }
    //-----------------------------------------------------

	void inserir(const std::string& chave, const vector<pair<string, float>>& dados)
	{
        raiz = inserir(raiz, chave, dados);
	}
    // insere recursivamente um novo no
	No * inserir(No *no, const std::string& chave, const vector<pair<string, float>>& dados)
	{
		if( no == nullptr ){
            //seta que alterou a subarvore e eh para testar o Fator de Balanceamento
            testaFB = 1;
            return new No(chave, dados);
		}
		// se for menor, entao insere a esquerda
		if(chave < no->getChave())
		{
            //percorre recursivamente a subarvore da esquerda
            no->setEsq(inserir(no->getEsq(), chave, dados));

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
            no->setDir(inserir(no->getDir(), chave, dados));
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

    void selecionarNo(const string& chave){
        selecionarNoRec(raiz, chave);
    }

    void selecionarNoRec(No *no, const string& chave){
        if(no != nullptr)
        {
            selecionarNoRec(no->getEsq(), chave);
            if (no->getChave() == chave){
                selecionado = no;
            }
            selecionarNoRec(no->getDir(), chave);
        }
    }

    No * getSelecionado(){
        if(selecionado != nullptr){
         return selecionado;
        }
      return nullptr;
    }

    string converterPalavra(string str){
        int cont = 0;
        transform(str.begin(),str.end(),str.begin(), ::tolower);
        for (char & i : str){
            if(cont == 0){
                i = tolower((char)i);//coloca maiuscula na primeira
                cont++;
                }else if(i==' '){
                    cont = 0;
                }
        }
        return str;
    }

	void escreverCSV(){
		std::ofstream myfile;
		myfile.open ("dados/saida.csv");

		myfile << "food_and_serving";
		myfile << ", ";
		for (auto& i : raiz->getDados()){
				myfile << i.first;
				myfile << ", ";
		}
		myfile << "\n";
		
		percorrer(raiz, myfile);
		myfile.close();

		cout << "Arquivo saida.csv escrito com sucesso." << endl;
    }
    // polimorfismo de sobrecarga
	void percorrer(No* no, std::ofstream& myfile)
	{
		if(no != nullptr)
		{
			percorrer(no->getEsq(), myfile);
			//cout << no->getChave() << " ";
			string chave = no->getChave();

			myfile << chave;
			myfile << ", ";
			
			for (auto& i : no->getDados()){
				myfile << i.second;
				myfile << ", ";
			}

			myfile << "\n";
			
			percorrer(no->getDir(), myfile);
		}
	}

};

