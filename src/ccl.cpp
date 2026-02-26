#include "../include/ccl.h"

using namespace std;

//################################################################################################################################
// FUNCIONES AUXILIARES PRIVADAS


int CompactChainList::countSubsequencesFrom(vector<Element>& expanded, vector<Element>& subsequence, int posExpanded, int posSubseq) {
    int ans = 0;

    if (posSubseq == subsequence.size()) {
        ans = 1;
    } else {
        if (posExpanded >= expanded.size()) {
            ans = 0;
        } else {
            for (int i = posExpanded; i < expanded.size(); i++) {
                if (expanded[i] == subsequence[posSubseq]) 
                    ans += countSubsequencesFrom(expanded, subsequence, i + 1, posSubseq + 1);
            }
        }
    }
    return ans;
}

int CompactChainList::blockCount() {
    int ans = 0;       
    bool avanzar = true;
    Node* current = first;

    if (first != NULL) {
        while (avanzar) {
            ans++;
            current = current->getNext();
            if (current == first) 
                avanzar = false;
        }
    }
    return ans;
}

void CompactChainList::insertBlock(Element v, int count) {
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

void CompactChainList::appendRemainingBlocks(Node* current, Node* startNode, CompactChainList& result) {
    if (current != NULL) {
        bool seguir = true;
        
        while (seguir) {
            result.push_back(current->getVal(), current->getLength());
            current = current->getNext();
            
            if (current == startNode) {
                seguir = false;
            }
        }
    }
}

Node* CompactChainList::findNodeAtPosition(int position, int& localPos) {
    Node* result = NULL;
    
    if (first != NULL && position >= 0 && position < listSize) {
        Node* current = first;
        int accumulatedPos = 0;
        bool found = false;
        
        do {
            int blockEnd = accumulatedPos + current->getLength();
            
            if (position < blockEnd && !found) {
                localPos = position - accumulatedPos;
                result = current;
                found = true;
            } else {
                accumulatedPos = blockEnd;
                current = current->getNext();
            }
        } while (current != first && !found);
    }
    return result;
}


//#################################################################################################################################
// OPERACIONES CONSTRUCTORAS

CompactChainList::CompactChainList() {
    first = NULL;
    listSize = 0;
}

CompactChainList::CompactChainList(vector<Element>& sequence) {
    first = NULL;
    listSize = 0;
    
    if (!sequence.empty()) {
        Element currentValue = sequence[0];
        int count = 1;
        
        for (int i = 1; i < sequence.size(); i++) {
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

CompactChainList::CompactChainList(const CompactChainList& other) {
    first = NULL;
    listSize = 0;
    
    if (other.first != NULL) {

        Node* current = other.first;
        
        do {
            Node* newNode = new Node(current->getVal(), current->getLength(), NULL, NULL);
            
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
            
            listSize += current->getLength();
            current = current->getNext();
            
        } while (current != other.first);
    }
}
//#################################################################################################################################
// OPERACIONES MODIFICADORAS

void CompactChainList::push_back(Element e, int count) {
    Node *newNode = new Node(e, count, NULL, NULL);
    
    if (first == NULL) {

        first = newNode;
        newNode->setNext(newNode);
        newNode->setPrev(newNode);
        listSize = count;
    } else {
        
        Node* last = first->getPrev();
        
        if (last->getVal() == e) {
            
            last->setLength(last->getLength() + count);
            listSize += count;
            delete newNode;
        } else {
            
            last->setNext(newNode);
            newNode->setPrev(last);
            newNode->setNext(first);
            first->setPrev(newNode);
            listSize += count;
        }
    }
}

void CompactChainList::push_front(Element e, int count){
    Node *newNode = new Node(e, count, NULL, NULL);

    if (first == NULL){

        first = newNode;
        newNode->setNext(newNode);
        newNode->setPrev(newNode);
        listSize = count;

    }
    else if (first->getVal() == e){

        first->setLength(first->getLength() + count );
        listSize += count;
        delete newNode;
    }
    else {

        Node *last = first->getPrev();

        newNode->setNext(first);
        newNode->setPrev(last);

        last->setNext(newNode);
        first->setPrev(newNode);

        first = newNode;
        listSize += count;

    }
}

void CompactChainList::removeFirstOcurrence(Element e){

    if (first != NULL){

        Node *current = first;
        int accumulatedpos = 0;
        bool flag = false;

        do {
            if (current->getVal() == e && !flag) {
                flag = true;

                if (current->getLength() == 1){

                    Node* prevNode = current->getPrev();
                    Node* nextNode = current->getNext();
                    
                    if (current == nextNode){
                        first = NULL;
                        delete current;
                        listSize = 0;                        
                    }
                    else {
                        prevNode->setNext(nextNode);
                        nextNode->setPrev(prevNode);

                        if (current == first)
                            first = nextNode;

                        delete current;
                        listSize -= 1;
                    } 
                } else {
                    current->setLength(current->getLength() - 1);
                    listSize -= 1;
                }
            } else { 
                current = current->getNext();
            }
        } while ( current != first && !flag);
    }
}

void CompactChainList::removeAllOcurrences(Element e){
    if (first != NULL){
        Node* current = first;
        Node* startNode = first;
        bool flag = true;
        
        while (flag){
            Node* nextNode = current->getNext();
            
            if (current->getVal() == e){
                Node* prevNode = current->getPrev();
                
                if (current == nextNode){
                    delete current;
                    first = NULL;
                    listSize = 0;
                    flag = false;
                }
                else {
                    prevNode->setNext(nextNode);
                    nextNode->setPrev(prevNode);
                    
                    if (current == first){
                        first = nextNode;
                        startNode = nextNode;
                    }
                    
                    listSize -= current->getLength();
                    delete current;
                    current = nextNode;
                    
                    if (current == startNode){
                        flag = false;
                    }
                }
            }
            else {
                current = nextNode;
                
                if (current == startNode){
                    flag = false;
                }
            }
        }
    }
}

void CompactChainList::removeBlockPosition(int p){

    if (first != NULL){
        Node* current = first;
        int accumulatedPos = 0;
        bool found = false;
        
        do {
            int blockEnd = accumulatedPos + current->getLength();
            
            if (p < blockEnd && !found){
                found = true;
                
                Node* prevNode = current->getPrev();
                Node* nextNode = current->getNext();
                
                if (current == nextNode){
                    delete current;
                    first = NULL;
                    listSize = 0;
                }
                else {
                    prevNode->setNext(nextNode);
                    nextNode->setPrev(prevNode);
                    
                    if (current == first){
                        first = nextNode;
                    }
                    
                    listSize -= current->getLength();
                    delete current;
                }
            }
            else {
                accumulatedPos = blockEnd;
                current = current->getNext();
            }
        } while (current != first && !found);
    }
}

void CompactChainList::modifyAllOcurrences(Element old_e, Element new_e) {
    if (first != NULL && old_e != new_e) {
        Node* current = first;
        Node* startNode = first;
        bool continuar = true;
        
        while (continuar) {
            Node* nextNode = current->getNext();
            
            if (current->getVal() == old_e) {
                current->setVal(new_e);
                
                Node* prevNode = current->getPrev();
                if (prevNode != current && prevNode->getVal() == new_e) {
                    prevNode->setLength(prevNode->getLength() + current->getLength());
                    prevNode->setNext(nextNode);
                    nextNode->setPrev(prevNode);
                    
                    if (current == first) {
                        first = prevNode;
                        startNode = prevNode;
                    }
                    
                    Node* toDelete = current;
                    current = prevNode;
                    delete toDelete;
                    nextNode = current->getNext();
                }

                if (nextNode != current && nextNode->getVal() == new_e) {
                    current->setLength(current->getLength() + nextNode->getLength());
                    Node* nextNextNode = nextNode->getNext();
                    current->setNext(nextNextNode);
                    nextNextNode->setPrev(current);
                    
                    if (nextNode == startNode) {
                        startNode = current;
                    }
                    delete nextNode;
                    nextNode = current->getNext();
                }
            }
            current = nextNode;
            if (current == startNode) 
                continuar = false;
        }
    }
}

// INSERT ELEMENT __________________________________________________________________________________________________________________

void CompactChainList::insertElement(int position, Element e) {
    if (position >= 0 && position <= listSize) {
        if (position == listSize) {
            push_back(e, 1);
        } else if (position == 0) {
            push_front(e, 1);
        } else {
            int localPos;
            Node* node = findNodeAtPosition(position, localPos);
            
            if (node != NULL) {
                if (node->getVal() == e) {
                    node->setLength(node->getLength() + 1);
                    listSize++;
                } else {
                    if (localPos == 0) {
                        Node* prevNode = node->getPrev();
                        
                        if (prevNode->getVal() == e) {
                            prevNode->setLength(prevNode->getLength() + 1);
                        } else {
                            Node* newNode = new Node(e, 1, node, prevNode);
                            prevNode->setNext(newNode);
                            node->setPrev(newNode);
                        }
                        listSize++;
                    } else {
                        int leftLength = localPos;
                        int rightLength = node->getLength() - localPos;
                        Element originalVal = node->getVal();
                        
                        node->setLength(leftLength);
                        
                        Node* nextNode = node->getNext();
                        
                        Node* newNode = new Node(e, 1, NULL, node);
                        node->setNext(newNode);
                        
                        Node* rightNode = new Node(originalVal, rightLength, nextNode, newNode);
                        newNode->setNext(rightNode);
                        nextNode->setPrev(rightNode);
                        listSize++;
                    }
                }
            }
        }
    }
}

// SET____________________________________________________________________________________________________________________________

void CompactChainList::set(int position, Element e) {
    bool flag = true;

    if (!(position >= 0 && position < listSize)) {
        flag = false;
    }

    Node* node = NULL;
    int localPos = 0;

    if (flag) {
        node = findNodeAtPosition(position, localPos);
        if (node == NULL) {
            flag = false;
        }
    }

    if (flag) {
        if (node->getVal() == e) {
            flag = false;
        }
    }

    if (flag) {
        if (node->getLength() == 1) {
            node->setVal(e);
            Node* prevNode = node->getPrev();
            Node* nextNode = node->getNext();

            if (prevNode != node && prevNode->getVal() == e) {
                prevNode->setLength(prevNode->getLength() + 1);
                prevNode->setNext(nextNode);
                nextNode->setPrev(prevNode);
                if (node == first) {
                    first = prevNode;
                }
                Node* toDelete = node;
                node = prevNode;
                delete toDelete;
                nextNode = node->getNext();
            }

            if (nextNode != node && nextNode->getVal() == e) {
                node->setLength(node->getLength() + nextNode->getLength());
                Node* nextNextNode = nextNode->getNext();
                node->setNext(nextNextNode);
                nextNextNode->setPrev(node);
                delete nextNode;
            }

        } else {
            if (localPos == 0) {
                node->setLength(node->getLength() - 1);
                Node* prevNode = node->getPrev();

                if (prevNode != node && prevNode->getVal() == e) {
                    prevNode->setLength(prevNode->getLength() + 1);
                } else {
                    Node* newNode = new Node(e, 1, node, prevNode);
                    prevNode->setNext(newNode);
                    node->setPrev(newNode);
                    if (node == first) {
                        first = newNode;
                    }
                }

            } else if (localPos == node->getLength() - 1) {
                node->setLength(node->getLength() - 1);
                Node* nextNode = node->getNext();

                if (nextNode != node && nextNode->getVal() == e) {
                    nextNode->setLength(nextNode->getLength() + 1);
                } else {
                    Node* newNode = new Node(e, 1, nextNode, node);
                    node->setNext(newNode);
                    nextNode->setPrev(newNode);
                }

            } else {
                int leftLength = localPos;
                int rightLength = node->getLength() - localPos - 1;
                Element originalVal = node->getVal();

                node->setLength(leftLength);

                Node* nextNode = node->getNext();

                Node* newNode = new Node(e, 1, NULL, node);
                node->setNext(newNode);

                Node* rightNode = new Node(originalVal, rightLength, nextNode, newNode);
                newNode->setNext(rightNode);
                nextNode->setPrev(rightNode);
            }
        }
    }
    return;
}


//#################################################################################################################################
// OPERACIONES ANALIZADORAS


void CompactChainList::print() {
    cout << "Size = " << listSize << ", Blocks = " << blockCount() << "\n";
    cout << "[";

    bool firstPrint = true;
    if (first != NULL) {
        Node* current = first;
        bool continuar = true;

        while (continuar) {
            if (!firstPrint) cout << ",";
            cout << "{" << current->getVal() << ", " << current->getLength() << "}";
            firstPrint = false;

            current = current->getNext();
            if (current == first) continuar = false;
        }
    }
    cout << "]\n";
}

int CompactChainList::searchElement(Element e) {
    int res = -1;
    
    if (first != NULL) {
        Node* current = first;
        int accumulatedPos = 0;
        bool flag = false;
        
        do {
            if (current->getVal() == e) {
                flag = true;
                res = accumulatedPos;
            } else {
                accumulatedPos += current->getLength();
                current = current->getNext();
            }
        } while (current != first && !flag);
    }
    
    return res;
}

int CompactChainList::size() {        //Complejidad constante, listSize guarda cuántos elementos totales hay en la lista
    return listSize;
}

CompactChainList CompactChainList::getLexicographicFusion(CompactChainList& other) {
    CompactChainList result;
    
    if (first != NULL && other.first != NULL) {
        Node* current1 = first;
        Node* current2 = other.first;
        bool list1Complete = false;
        bool list2Complete = false;
        
        while (!list1Complete || !list2Complete) {
            if (list1Complete) {
                result.push_back(current2->getVal(), current2->getLength());
                current2 = current2->getNext();
                if (current2 == other.first) {
                    list2Complete = true;
                }
            } else if (list2Complete) {
                result.push_back(current1->getVal(), current1->getLength());
                current1 = current1->getNext();
                if (current1 == first) {
                    list1Complete = true;
                }
            } else {
                Element val1 = current1->getVal();
                Element val2 = current2->getVal();
                
                if (val1 < val2) {
                    result.push_back(val1, current1->getLength());
                    current1 = current1->getNext();
                    if (current1 == first) {
                        list1Complete = true;
                    }
                } else if (val1 > val2) {
                    result.push_back(val2, current2->getLength());
                    current2 = current2->getNext();
                    if (current2 == other.first) {
                        list2Complete = true;
                    }
                } else {
                    int totalLength = current1->getLength() + current2->getLength();
                    result.push_back(val1, totalLength);
                    
                    current1 = current1->getNext();
                    current2 = current2->getNext();
                    
                    if (current1 == first) 
                        list1Complete = true;
                    if (current2 == other.first) 
                        list2Complete = true;
                }
            }
        }
    } else if (first != NULL) {
        appendRemainingBlocks(first, first, result);
    } else if (other.first != NULL) {
        appendRemainingBlocks(other.first, other.first, result);
    }
    return result;
}

int CompactChainList::getConsecutiveOcurrences(vector<Element>& subsequence) {
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

int CompactChainList::getOcurrences(vector<Element>& subsequence) {
    int count = 0;
    
    if (first != NULL && !subsequence.empty()) {
        list<Element> expandedList = expand();
        vector<Element> expanded(expandedList.begin(), expandedList.end());
        
        int seqSize = subsequence.size();
        int expandedSize = expanded.size();
        
        count = countSubsequencesFrom(expanded, subsequence, 0, 0);
    }
    return count;
}

int CompactChainList::getIndexFirstConsecutiveOcurrence(vector<Element>& subsequence) {
    int index = -1;
    
    if (first != NULL && !subsequence.empty()) {
        list<Element> expandedList = expand();
        vector<Element> expanded(expandedList.begin(), expandedList.end());
        
        int seqSize = subsequence.size();
        int expandedSize = expanded.size();
        bool found = false;
        
        for (int i = 0; i <= expandedSize - seqSize && !found; i++) {
            bool match = true;
            
            for (int j = 0; j < seqSize && match; j++) {
                if (expanded[i + j] != subsequence[j]) {
                    match = false;
                }
            }
            
            if (match) {
                index = i;
                found = true;
            }
        }
    }
    return index;
}

int CompactChainList::getIndexFirstOcurrence(vector<Element>& subsequence) {
    int index = -1;
    
    if (first != NULL && !subsequence.empty()) {
        list<Element> expandedList = expand();
        vector<Element> expanded(expandedList.begin(), expandedList.end());
        
        int seqSize = subsequence.size();
        int expandedSize = expanded.size();
        bool found = false;
        
        for (int i = 0; i < expandedSize && !found; i++) {
            if (expanded[i] == subsequence[0]) {
                int seqIndex = 1;
                
                for (int j = i + 1; j < expandedSize && seqIndex < seqSize; j++) {
                    if (expanded[j] == subsequence[seqIndex]) {
                        seqIndex++;
                    }
                }
                if (seqIndex == seqSize) {
                    index = i;
                    found = true;
                }
            }
        }
    }
    return index;
}


list<Element> CompactChainList::expand() {
    list<Element> result;
    
    if (first != NULL) {
        Node* current = first;
        bool continuar = true;
        
        while (continuar) {
            int length = current->getLength();
            Element val = current->getVal();
            
            for (int i = 0; i < length; i++) {
                result.push_back(val);
            }
            
            current = current->getNext();
            
            if (current == first) {
                continuar = false;
            }
        }
    }
    return result;
}

//#################################################################################################################################
// SOBRECARGA DE OPERADORES

CompactChainList CompactChainList::operator+(CompactChainList& other) {
    CompactChainList result = getLexicographicFusion(other);
    return result;
}

Element CompactChainList::operator[](int index) {
    Element result = Element();
    
    if (first != NULL && index >= 0 && index < listSize) {
        Node* current = first;
        int accumulatedPos = 0;
        bool found = false;
        
        do {
            int blockEnd = accumulatedPos + current->getLength();
            
            if (index < blockEnd && !found) {
                found = true;
                result = current->getVal();
            } else {
                accumulatedPos = blockEnd;
                current = current->getNext();
            }
        } while (current != first && !found);
    }
    return result;
}

bool CompactChainList::operator<(CompactChainList& other) {
    bool result = false;
    
    if (first == NULL && other.first != NULL) {
        result = true;
    } else if (first != NULL && other.first != NULL) {
        Node* current1 = first;
        Node* current2 = other.first;
        int pos1 = 0, pos2 = 0;
        bool continuar = true;
        bool encontradoDiferencia = false;
        
        while (continuar && !encontradoDiferencia) {
            Element val1 = current1->getVal();
            Element val2 = current2->getVal();
            
            if (val1 < val2) {
                result = true;
                encontradoDiferencia = true;
            } else if (val1 > val2) {
                result = false;
                encontradoDiferencia = true;
            } else {
                pos1++;
                pos2++;
                
                if (pos1 >= current1->getLength()) {
                    current1 = current1->getNext();
                    pos1 = 0;
                    
                    if (current1 == first) {
                        if (pos2 < current2->getLength() || current2->getNext() != other.first) {
                            result = true;
                        }
                        continuar = false;
                    }
                }
                if (pos2 >= current2->getLength() && continuar) {
                    current2 = current2->getNext();
                    pos2 = 0;
                    
                    if (current2 == other.first) 
                        continuar = false;
                }
            }
        }
    }
    return result;
}

bool CompactChainList::operator==(CompactChainList& other) {
    bool result = false;
    
    if (listSize == other.listSize) {
        if (first == NULL && other.first == NULL) {
            result = true;
        } else if (first != NULL && other.first != NULL) {
            Node* current1 = first;
            Node* current2 = other.first;
            int pos1 = 0, pos2 = 0;
            int totalChecked = 0;
            bool iguales = true;
            
            while (totalChecked < listSize && iguales) {
                if (current1->getVal() != current2->getVal()) {
                    iguales = false;
                } else {
                    pos1++;
                    pos2++;
                    totalChecked++;
                    
                    if (pos1 >= current1->getLength()) {
                        current1 = current1->getNext();
                        pos1 = 0;
                    }
                    
                    if (pos2 >= current2->getLength()) {
                        current2 = current2->getNext();
                        pos2 = 0;
                    }
                }
            }
            result = iguales;
        }
    }
    return result;
}
//#################################################################################################################################

void CompactChainList::sortVectorCCL(vector<CompactChainList>& v) {
    sort(v.begin(), v.end());
}

//##################################################################################################################################

// OPERACIÓN ADICIONAL

map<Element, vector<int>> CompactChainList::summary() {
    map<Element, vector<int>> ans;
    
    if (first != NULL) {
        Node* current = first;
        bool continuar = true;
        
        while (continuar) {
            Element val = current->getVal();
            int length = current->getLength();
            
            if (ans.find(val) != ans.end()) {
                ans[val].push_back(length);
            } else {
                vector<int> lengths;
                lengths.push_back(length);
                ans[val] = lengths;
            }
            
            current = current->getNext();
            
            if (current == first) 
                continuar = false;
        }
    }
    return ans;
}
