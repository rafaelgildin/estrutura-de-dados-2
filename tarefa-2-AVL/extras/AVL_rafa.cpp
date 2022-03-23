#include <iostream>
using namespace std;

class No
{
    private:
	No *esq, *dir;
	int chave;
	int FB;

    public:
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
	No *raiz;
	int testaFB;

    public:
	Arvore()
	{
		raiz = NULL;
	}

	void inserir(int chave)
	{
        raiz = inserir(raiz, chave);
	}
    // insere recursivamente um novo no
	No * inserir(No *no, int chave)
	{
		if( no == NULL ){
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
};

// para visualizar a execucao acesse
// https://pythontutor.com/cpp.html#mode=edit
int main(int argc, char *argv[])
{
	Arvore arv;

	// insere as chaves
	arv.inserir(8);
    arv.inserir(15);
    arv.inserir(18);
    arv.inserir(25);
    arv.inserir(19);


	// percorre em ordem iniciando da raiz
	cout << "\nPercorrendo em ordem crescrente...\n";
	arv.emOrdem();
    cout << "\nDenhando a arvore deitada...\n";
    arv.DesenhaArvore();
	return 0;
}