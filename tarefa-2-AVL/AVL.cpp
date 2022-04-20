#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

class No
{
    private:
	No *esq, *dir;
	std::string chave;
	int FB;
	vector<pair<string, float>> dados;

    public:
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
	No *raiz;
    No *selecionado = nullptr;

	int testaFB{};

    public:
	Arvore()
	{
		raiz = nullptr;
	}

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
    }

    string converterPalavra(string str){
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

