#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

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
		dir = nullptr;
		FB=0;
	}

    std::string getChave()
	{
		return chave;

	}

    float procurarDado(const string& coluna){
        for (int i=0;i<dados.size();i++){
            if (coluna == dados[i].first){
                return dados[i].second;
            }
        }
        cout << "Coluna não encontrada!" << endl;
    }

	const vector<pair<std::string, float>>& getDados(){
		return dados;
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
	int testaFB;
	Arvore()
	{
		raiz = nullptr;
	}

    //------------------------------------------------------------------ testes
    
    bool remover(std::string alimento_informado)
    {
        No *atual = raiz;
        No *pai = raiz;
        bool filho_esq = true;
        // ****** Buscando o valor **********
        while (atual->getChave() != alimento_informado)   // enquanto nao encontrar o alimento
        {
            pai = atual;
            if(alimento_informado < atual->getChave() )   // caminha para esquerda
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
        cout << "\natual = " << atual->chave << endl;
        cout << "pai = " << pai->chave << endl;
        cout << "filho_esq = " << filho_esq << endl;


        // // Se eh uma folha, basta elimina-lo e fazer o ptr do pai receber NULL
        // if (atual->getEsq() == NULL && atual->getDir() == NULL)
        // {
        //     if (atual == raiz ) raiz = NULL; // se raiz
        //     else if (filho_esq)
        //         pai->setEsq(NULL); // se for filho a esquerda do pai
        //     else
        //         pai->setDir(NULL); // se for filho a direita do pai
        //     //apaga o no
        // }
        // // Se eh pai e nao possui um filho a direita, substitui pela subarvore a esquerda
        // else if (atual->getDir() == NULL)
        // {
        //     if (atual == raiz) raiz = atual->getEsq(); // se raiz
        //     else if (filho_esq) pai->setEsq(atual->getEsq()); // se for filho a esquerda do pai
        //     else pai->setDir(atual->getEsq()); // se for filho a direita do pai
        // }
        // // Se eh pai e nao possui um filho a esquerda, substitui pela subarvore a direita
        // else if (atual->getEsq() == NULL)
        // {
        //     if (atual == raiz) raiz = atual->getDir(); // se raiz
        //     else if (filho_esq) pai->setEsq(atual->getDir()); // se for filho a esquerda do pai
        //     else pai->setDir(atual->getDir()); // se for  filho a direita do pai
        // }
        // // Se possui filhos a esq e dir
        // else
        // {
        //     No *sucessor = no_sucessor(atual);
        //     // Usando o metodo sucessor para encontrar o no mais a esquerda da subarvore a direita (menor dos maiores)
        //     if (atual == raiz) raiz = sucessor; // se eh raiz
        //     else if(filho_esq) pai->setEsq(sucessor); // se for filho a esquerda do pai
        //     else pai->setDir(sucessor); // se for filho a direita do pai
        //     sucessor->setEsq(atual->getEsq()); // acertando os ponteiros esquerda e direita do sucessor
        // }
        // //delete atual;
        // return true;
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
        // *********************************************************************************          continuar
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


    // void remover(){
    //     // ---------------------------------------------continuar 
    //     cout << raiz->getFB() << endl;
    //     cout << "implementando remover" << endl;
    //     /*
    //     - OK recebe chave, encontrar no, caso contário retorna mensagem
    //     - OK 4 tipos de rotacao
    //     - remover no, com:
    //         - 0 filhos
    //         - 1 filho
    //         - 2 filhos
    //     - verificar fator de balanceamento de todos os nos
    //     - balancear arvore
    //     */
    // }

    // No * removerRec(No * no, std::string chave){
    //     No * p;
	// 	if( no == nullptr ){
    //         return NULL;
	// 	}
	// 	// se for menor, entao deleta a esquerda
	// 	if(chave < no->getChave())
	// 	{
    //         //percorre recursivamente a subarvore da esquerda
    //         no->setEsq(removerRec(no->getEsq(), chave));
    //         // ----------------continuar
	// 	}
    //     // se for maior, entao deleta a direita
	// 	else if(chave > no->getChave()){

    //         //percorre recursivamente a subarvore da direita
    //         no->setDir(removerRec(no->getDir(), chave));
    //         // ----------------continuar
	// 	}
    //     else{//encontrou o no que deve ser removido
    //         if(no->getDir() != nullptr){//no com filho na direita
    //             p = no->getDir();

    //             while(p->getEsq() != nullptr)//busca o menor no dos maiores (sub-arvore direita)
    //                 p = p->getEsq();

    //             no->chave = p->chave;
    //             no->dir = removerRec(no->dir, p->chave);
    //         }
    //         else
    //             return no->esq;
    //     }
    // }




    int CalcularFB(No * no)
    {
        //verificar se esta ok
        int altEsq,altDir;
        if( no == NULL)
            return(0);
        if(no -> esq == NULL)
            altEsq = 0;
        else
            altEsq = 1 + no->esq->FB;
        if(no -> dir == NULL)
            altDir = 0;
        else
            altDir = 1 + no -> dir -> FB;
        return(altDir-altEsq);
    }


	void inserir(const std::string& chave, const vector<pair<string, float>>& dados)
	{
        raiz = inserir(raiz, chave, dados);
	}
    // insere recursivamente um novo no
	No * inserir(No *no, const std::string& chave, const vector<pair<string, float>>& dados)
	{
		if( no == nullptr ){
            //insere o novo no
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
                RotacaoSimplesDireita(p, u);                
                // p->setEsq(u->getDir());
                // u->setDir(p);
                // // ajusta o novo balanceamento de p
                // // pois ele passa ser uma T1 - T2 = 0
                // p->setFB(0);
                // p = u; // p passa ser o u
                // cout <<" => realizada uma rotacao simples a direita \n";
            }
            // inseriu na subarvore direita de u
            // fazer uma rotacao dupla a direita
            else{
                RotacaoDuplaDireita(p, u, v);
                // v = u->getDir();           // aqui poderia ser o q caso T2 e T3 sejam nulos
                // u->setDir(v->getEsq());
                // p->setEsq(v->getDir());
                // v->setEsq(u);
                // v->setDir(p);
                // if( v->getFB() == -1 ){ // se inseriu na subarvore esquerda de v
                //     p->setFB(1);
                //     u->setFB(0);
                // }
                // else if( v->getFB() == 1 ){ // se inseriu na subarvore direita de v
                //     p->setFB(0);
                //     u->setFB(-1);
                // }
                // else{ // v = q
                //     p->setFB(0);
                //     u->setFB(0);
                // }
                // p = v; // p passa ser o v
                // cout << " => realizada uma rotacao dupla a direita \n";
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
            RotacaoSimplesEsquerda(p, z);
            // p->setDir(z->getEsq());
            // z->setEsq(p);
            // // ajusta o novo balanceamento de p
            // // pois ele passa ser uma T1 - T2 = 0
            // p->setFB(0);
            // p = z;
            // cout << " => realizada uma rotacao simples a esquerda \n";
        }
        // inseriu na subarvore direita de z
        // fazer uma rotacao dupla a esquerda
        else{
            RotacaoDuplaEsquerda(p, z, y);
            // y = z->getEsq();
            // z->setEsq(y->getDir());
            // p->setDir(y->getEsq());
            // y->setEsq(p);
            // y->setDir(z);

            // if( y->getFB() == 1 ){ // se inseriu na subarvore direita y
            //         p->setFB(-1);
            //         z->setFB(0);
            // }
            // else if( y->getFB() == -1 ){ // se inseriu na subarvore esquerda de y
            //         p->setFB(0);
            //         z->setFB(1);
            // }
            // else{ // y == q
            //         z->setFB(0);
            //         p->setFB(0);
            // }
            // p = y;
            // cout << " => realizada uma rotacao dupla a esquerda \n";
        }
        p->setFB(0);
        return p;
    }

    //------------------------ rotacoes --------------------------

    void RotacaoSimplesDireita(No*& p, No*& u){//passar ponteiro por referencia
        p->setEsq(u->getDir());
        u->setDir(p);
        // ajusta o novo balanceamento de p
        // pois ele passa ser uma T1 - T2 = 0
        p->setFB(0);
        p = u; // p passa ser o u
        cout <<" => realizada uma rotacao simples a direita \n";
    }

    void RotacaoDuplaDireita(No*& p, No*& u, No*& v){
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
        p = v; // p passa ser o v
        cout << " => realizada uma rotacao dupla a direita \n";
    }
    
    void RotacaoSimplesEsquerda(No*& p, No*& z){
        p->setDir(z->getEsq());
        z->setEsq(p);
        // ajusta o novo balanceamento de p
        // pois ele passa ser uma T1 - T2 = 0
        p->setFB(0);
        p = z;
        cout << " => realizada uma rotacao simples a esquerda \n";
    }

    void RotacaoDuplaEsquerda(No*& p, No*& z, No*& y){
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
        // coloca palavra em letra maiuscula
        int cont = 0;
        transform(str.begin(),str.end(),str.begin(), ::tolower);
        for (int i = 0; i < str.size(); i++){
            if(cont == 0){
                str[i] = toupper(str[i]);
                cont++;
                }else if(str[i]==' '){
                    cont = 0;
                }

        }
        return str;
    }  


};

