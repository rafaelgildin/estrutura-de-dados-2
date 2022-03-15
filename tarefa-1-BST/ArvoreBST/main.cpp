#include <iostream>
#include "No.h"
#include "ArvoreBST.h"

using namespace std;

int main(int argc, char *argv[])
{
	ArvoreBST arv;
  int opcao, x;
  cout << ("\nTestando o TAD BST (Elementos do tipo int)\n");
	arv.inserir(20);arv.inserir(10);arv.inserir(30); // inserir dados
//	arv.inserir(5);arv.inserir(15);
	do {
    cout << "\n***********************************";
    cout << "\nMenu - Arvore BST\n";
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
		      No *ret = 
