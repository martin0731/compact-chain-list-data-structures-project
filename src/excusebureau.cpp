#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
Martín Estrada Agudelo 
Ingeniería de sistemas - 4 semestre
código de estudiante: 9010264
PROYECTO 

execuse burreau
*/ 

typedef char Element;

class Node{
  private:
    Element val;
    int length;
    Node *next, *prev;

  public:
    Node(){
      length = 0;
    }

    Node(Element e, int len, Node* n1, Node* n2){
      val = e;
      length = len;
      next = n1;
      prev = n2;
    }

    Element getVal(){return val;}

    int getLength(){return length;}

    Node* getNext(){return next;}

    Node* getPrev(){return prev;}

    void setNext(Node* n){next = n;}

    void setPrev(Node* n){prev = n;}
};


class CompactChainList {
private:
    Node* first;
    int listSize;

    // función auxuliar 
    void insertBlock(Element v, int count) {
    Node* newNode = new Node(v, count, NULL, NULL);

    if (first == NULL) {
        first = newNode;
        first->setNext(first);
        first->setPrev(first);
    } else {
        Node* last = first->getPrev();
        last->setNext(newNode);
        newNode->setPrev(last);
        newNode->setNext(first);
        first->setPrev(newNode);
    }
    listSize += count;
}

public:

    CompactChainList() {
        first = NULL;
        listSize = 0;
    }
        
    CompactChainList(vector<Element>& sequence) {
        first = NULL;
        listSize = 0;
        
        if (!sequence.empty()) {
            Element currentValue = sequence[0];
            int count = 1;
            
            for (size_t i = 1; i < sequence.size(); i++) {
                if (sequence[i] == currentValue) {
                    count++;
                } else {
                    insertBlock(currentValue, count);
                    currentValue = sequence[i];
                    count = 1;
                }
            }
            insertBlock(currentValue, count);
        }
    }

    
int getConsecutiveOcurrences(vector<Element>& subsequence) {
    int count = 0;
    
    if (first != NULL && !subsequence.empty()) {
        int seqSize = subsequence.size();
        Node* current = first;
        int posInBlock = 0;
        int globalPos = 0;
        bool continuar = true;
        
        while (globalPos <= listSize - seqSize && continuar) {

            Node* tempNode = current;
            int tempPosInBlock = posInBlock;
            int seqIndex = 0;
            bool match = true;
            
            while (seqIndex < seqSize && match) {
                if (tempNode->getVal() != subsequence[seqIndex]) {
                    match = false;
                } else {
                    seqIndex++;
                    tempPosInBlock++;
                    
                    if (tempPosInBlock >= tempNode->getLength()) {
                        tempNode = tempNode->getNext();
                        tempPosInBlock = 0;
                        
                        if (tempNode == first && seqIndex < seqSize) {
                            match = false;
                        }
                    }
                }
            }
            
            if (match) 
                count++;

            globalPos++;
            posInBlock++;
            
            if (posInBlock >= current->getLength()) {
                current = current->getNext();
                posInBlock = 0;
                
                if (current == first) 
                    continuar = false;   
            }
        }
    }
    return count;
}
    
};

//#############################################################################################################################
//  PROBLEMA DE LA ARENA 

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

vector<Element> stringToVectorWithSeparators(const string& str) {
    vector<Element> v;
    v.push_back('^'); 
    for (char c : str) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            v.push_back(toLower(c));
        } else {
            v.push_back('^');
        }
    }
    v.push_back('^'); 
    return v;
}

int main() {
    int K, E;

    while (cin >> K >> E) {
        cin.ignore();

        vector<vector<Element>> conceptos(K);
        for (int i = 0; i < K; i++) {
            string concepto;
            getline(cin, concepto);
            conceptos[i] = stringToVectorWithSeparators(concepto);
        }

        vector<string> reportes(E);
        vector<int> conteos(E, 0);

        for (int i = 0; i < E; i++) {
            getline(cin, reportes[i]);
            vector<Element> vecReporte = stringToVectorWithSeparators(reportes[i]);
            CompactChainList cclReporte(vecReporte);

            int conteo = 0;
            for (int j = 0; j < K; j++) 
                conteo += cclReporte.getConsecutiveOcurrences(conceptos[j]);

            conteos[i] = conteo;
        }

        int maxConteo = 0;
        for (int i = 0; i < E; i++) {
            if (conteos[i] > maxConteo) 
                maxConteo = conteos[i];
        }

        for (int i = 0; i < E; i++) {
            if (conteos[i] == maxConteo && maxConteo > 0) 
                cout << reportes[i] << endl;
        }
        cout << endl;
    }
    return 0;
}
