//
// Created by gustavo on 23/03/2022.
//

#include "AVL.cpp"
int main(int argc, char *argv[])
{
    Arvore arv;
	float f1 = 0.1;
    // insere as chaves
    arv.inserir("Salve", f1);
    arv.inserir("Salve2", f1);
    arv.inserir("Salve3", f1);
    arv.inserir("Salve4", f1);
    arv.inserir("Salve5", f1);
	
	arv.getRaiz();
    // percorre em ordem iniciando da raiz
    cout << "\nPercorrendo em ordem crescrente...\n";
    arv.emOrdem();
    cout << "\nDenhando a arvore deitada...\n";
    arv.DesenhaArvore();
    return 0;
}
