#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    for(int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i){
        nodes[i] = new Node(0,0,0);
    }
    length = 0;
}

NodeList::~NodeList(){
    // DELETE EACH NODE
    for(int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i){
        delete nodes[i];
    }
}

NodeList::NodeList(NodeList& other){
    // DEEP COPY
    for(int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i){
        nodes[i] = new Node(other.nodes[i]->getRow(), other.nodes[i]->getCol(), other.nodes[i]->getDistanceTraveled());
    }
}

int NodeList::getLength(){
    return this->length;
}

void NodeList::addElement(Node* newPos){
    nodes[length] = newPos;
    ++length;
}

Node* NodeList::getNode(int i){
    return nodes[i];
}