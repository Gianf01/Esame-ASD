#ifndef Node_hpp
#define Node_hpp

#include <list>
#include <limits>

#define WHITE 1
#define GRAY  2
#define BLACK 3

template <class T> class Node {
    template<class U> friend class Graph; //permette a graph di accedere ai membri privati e protetti di Node
private:
    Node<T> * parent; //ptr al padre
    unsigned short int color;
    T data;
    std::list <Node <T> *> * adjacentList;


public:
    Node(T data) {
        this->data = data;
        this->color = 0;
        this->parent = nullptr;
        this->adjacentList = new std::list<Node<T> *>;
    }
    void addEdge(Node * newEdge);
    std::list<Node<T> *> * getAdjacentList();
    T getData();
    void setColor(unsigned short int newColor);
    unsigned short int getColor();
    void setParent(Node * newParent);
    Node<T> * getParent();
    void resetNode();
};

template <class T> void Node<T>::addEdge(Node * newEdge) {
    this->adjacentList->push_back(newEdge);
    
}

template <class T> std::list<Node <T> *> * Node<T>::getAdjacentList() {
    return this->adjacentList;
}

template <class T> T Node<T>::getData() {
    return this->data;
}

template <class T> void Node<T>::setColor(unsigned short int newColor) {
    this->color = newColor;
}

template <class T> unsigned short int Node<T>::getColor() {
    return this->color;
}

template <class T> void Node<T>::setParent(Node * newParent) {
    this->parent = newParent;
}

template <class T> Node<T> * Node<T>::getParent() {
    return this->parent;
}



template <class T> void Node<T>::resetNode() {
    setColor(WHITE);
    setParent(nullptr);
}


#endif 