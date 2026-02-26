#ifndef CCL_H
#define CCL_H

#include "node.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

class CompactChainList {
private:
  Node *first;
  int listSize;

  // función auxiliar para agregar un bloque, utilizada en constructor con
  // vector
  void insertBlock(Element v, int count);

  // función auxiliar para agregar los bloques restantes en la fusión
  // lexicográfica
  static void appendRemainingBlocks(Node *current, Node *startNode,
                                    CompactChainList &result);

  // función auxiliar para encontrar el nodo y la posición local correspondiente
  // a la p global, para operación de set e insertElement
  Node *findNodeAtPosition(int position, int &localPos);

  // función auxiliar para contar el número de bloques para el print CCL
  int blockCount();

  // función auxiliar para contar subsecuencias de forma recursiva en
  // getOcurrences
  int countSubsequencesFrom(vector<Element> &expanded,
                            vector<Element> &subsequence, int posExpanded,
                            int posSubseq);

public:
  // OPERACIONES CONSTRUCTORAS
  CompactChainList();
  CompactChainList(vector<Element> &sequence);
  CompactChainList(const CompactChainList &other);

  // OPERACIONES MODIFICADORAS
  void set(int position, Element e);
  void insertElement(int position, Element e);
  void modifyAllOcurrences(Element old_e, Element new_e);
  void push_front(Element e, int count);
  void push_back(Element e, int count);
  void removeFirstOcurrence(Element e);
  void removeAllOcurrences(Element e);
  void removeBlockPosition(int p);

  // OPERACIONES ANALIZADORAS
  int searchElement(Element e);
  int getIndexFirstConsecutiveOcurrence(vector<Element> &subsequence);
  int getIndexFirstOcurrence(vector<Element> &subsequence);
  int getConsecutiveOcurrences(vector<Element> &subsequence);
  int getOcurrences(vector<Element> &subsequence);
  int size();
  list<Element> expand();
  void print();
  CompactChainList getLexicographicFusion(CompactChainList &other);

  // SOBRECARGA DE OPERADORES
  CompactChainList operator+(CompactChainList &other);
  Element operator[](int index);
  bool operator<(const CompactChainList &other) const;
  bool operator==(const CompactChainList &other) const;

  // METODO ESTATICO
  static void sortVectorCCL(vector<CompactChainList> &v);

  // OPERACIÓN ADICIONAL
  map<Element, vector<int>> summary();
};

#endif
