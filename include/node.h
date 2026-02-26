#ifndef NODE_H
#define NODE_H

#include <cstdio>
#include <cstdlib>

typedef int Element;

class Node {
private:
  Element val;
  int length;
  Node *next, *prev;

public:
  Node();
  Node(Element, int, Node *, Node *);
  Element getVal();
  int getLength();
  Node *getNext();
  Node *getPrev();
  void setVal(Element);
  void setLength(int);
  void setNext(Node *);
  void setPrev(Node *);
};

#endif
