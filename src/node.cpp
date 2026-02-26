#include "../include/node.h"

Node::Node(){
  length = 0;
}

Node::Node(Element e, int len, Node* n1, Node* n2){
  val = e;
  length = len;
  next = n1;
  prev = n2;
}

Element Node::getVal(){return val;}

int Node::getLength(){return length;}

Node* Node::getNext(){return next;}

Node* Node::getPrev(){return prev;}

void Node::setVal(Element e){val = e;}

void Node::setLength(int len){length = len;}

void Node::setNext(Node* n){next = n;}

void Node::setPrev(Node* n){prev = n;}
