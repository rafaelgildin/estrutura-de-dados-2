// Rafael Avraham Gildin Acherboim 31940242
// GUSTAVO ANDRADE DE PAULA 42081327
//https://www.cplusplus.com/reference/list/list/
//list documentation

#include <iostream>
#include <list>

using namespace std;

class HashTable{
private:
  list<int> *table;

public:
  // Constructor to create a hash table with 'n' indices:
  int colisoes = 0;
  int total_elements;
  float total_numeros = 0;
  // Hash function to calculate hash for a value:
  // o resto de key com a quantidade de elementos
  int  getHash(int key){
    return key % total_elements;
  }

  HashTable(int n){
    total_elements = n;
    table = new list<int>[total_elements];
  }

  // Insert data in the hash table:
  void insertElement(int key){
    int hash = getHash(key);
    // tamanho da lista
    // cout << "hash = " << hash << "tamanho lista = " << table[hash].size() << endl;
    // se a lista tiver tamanho >= 1, colisao++
    if(table[hash].size() >= 1){
      colisoes+=1;
      // cout << "colisoes = " << colisoes << endl;
    }
    total_numeros++;
    table[hash].push_back(key); //Add element at the end
  }

  // Remove data from the hash table:
  void removeElement(int key){
    int x = getHash(key);

    list<int>::iterator i; 
    for (i = table[x].begin(); i != table[x].end(); i++) { 
      // Check if the iterator points to the required item:
      if (*i == key) 
        break;
    }

    // If the item was found in the list, then delete it:
    if (i != table[x].end()) {
      table[x].erase(i); //Erase elements
      total_numeros--;
    }
      
  }

  void printAll(){
    // Traverse each index:
    for(int i = 0; i < total_elements; i++){
      cout << "Index " << i << ": ";
      // Traverse the list at current index:
      for(int j : table[i])
        cout << j << " => ";

      cout << endl;
    }
  }

  float calculaMedia(){
    return total_numeros/total_elements;
  }
};

int main() {
  int tamanho_tabela_hash = 21;
  // Create a hash table with x indices:
  HashTable ht(tamanho_tabela_hash);

  // Declare the data to be stored in the hash table:
  int array[] = {2, 4, 6, 8, 10, 1, 21, 13, 15, 9, 12, 30, 7, 17, 24, 45, 41, 32, 38, 39, 35, 26, 27, 50, 55, 52};

  // Insert the whole data into the hash table:
  for(int i = 0; i < sizeof(array)/sizeof(array[0]); i++)
    ht.insertElement(array[i]);

  // falar a quantidade de colisoes
  cout << "Tamanho tabela hash = " << tamanho_tabela_hash << endl;
  cout << "Total de colisoes = " << ht.colisoes << endl;
  cout << "Tamanho medio das listas = " << ht.calculaMedia(); 

  cout << "\n\n..:: Hash Table ::.." << endl;
  ht.printAll();
  cout << "\n\n" << endl;

  // cout << "total de numero = " << ht.total_numeros << endl;
  // ht.removeElement(1);
  // cout << "total de numero = " << ht.total_numeros << endl;
  // cout << endl << "..:: After deleting element 1 ::.." << endl;
  // ht.printAll();

  return 0;
}