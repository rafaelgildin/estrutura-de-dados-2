// GUSTAVO ANDRADE DE PAULA 42081327
// Gustavo Bernard Schwarz 32141157
// Rafael Avraham Gildin Acherboim 31940242
// Andrea Mindlin Tessler - 42012538
// clear; g++ -o main.exe *.cpp;  .\main.exe


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
	arv.inserir(5);arv.inserir(15);
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
            // arv.emOrdem(arv.getRaiz());
            arv.preOrdem(arv.getRaiz());
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
          cout;
          int max = arv.encontrarMax(arv.getRaiz());
          if(max == -2147483648){
                  cout << "arvore sem no" << endl;
                  break;
          }
          cout << "Valor maximo: " << max;
          break;
      }
      case 9:{
          cout;
          int min = arv.encontrarMin(arv.getRaiz());
          if(min == 2147483647){
                  cout << "arvore sem no" << endl;
                  break;
          }
          cout << "Valor minimo: " << min;
          break;
      }
      case 10: {
          break;
      }
			default:
                cout << "\n Opcao invalida! \n";
        } // fim switch
    } while(opcao != 10);
	return 0;
}
