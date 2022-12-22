#include <list>
#include <iostream>
#include <limits>
#include "RBTree.hpp"
#define WHITE 1
#define GRAY 2
#define BLACK 3

using namespace std;

template<class T> class Node{
    private:
        Node<T> *parent; //puntatore al precedente
        unsigned short int color;
        unsigned int dTime; 
        T data;
        //list<Node<T> *> *adjacentList;
        RBTree<Node<T> *> *TreeRBList;  //Albero RB come se fosse una lista di adiacenza
        public:
        Node(T data) { //costruttore
            this->data = data;
            color = WHITE;
            parent = nullptr;
            dTime = numeric_limits<int>::max(); //pongo dtime a infinito
            //adjacentList = new list<Node<T> *>; //creo una nuova lista di adiacenza
            TreeRBList = new RBTree<Node<T> *>; //Albero RB come se fosse una lista di adiacenza
        };
        T getData(){return data;};
        void addEdge(unsigned int key, Node<T> *newEdge);
        //list<Node<T> *> * getAdjacentList(){return adjacentList;};
        RBTree<Node<T> *> * getRBList(){return this->TreeRBList; };
        void setColor(unsigned short int newColor);
        unsigned short int getColor() {return color;}
        void setParent(Node<T> *newParent);
        Node<T> *getParent(){return parent;}
        void set_dTime(unsigned int new_dTime);
        unsigned int get_dTime(){return dTime;}
        void Remove_edge(unsigned int key);
        void resetNode();
};

template <class T> void Node<T>::addEdge(unsigned int  key, Node <T> *newEdge){  
    this->TreeRBList->insertNodeRB(key,newEdge); //richiamo l'insert dell'albero RB per aggiungere alla lista di adiacenza
}

template <class T> void Node<T>::Remove_edge(unsigned int  key){
    this->TreeRBList->RB_delete(key); //richiamo il delete dell'albero RB per rimuovere dalla lista di adiacenza
}

template <class T> void Node<T>::setColor(unsigned short int newColor){
    color=newColor;
}

template <class T> void Node<T>::setParent(Node * newParent) 
{
    parent = newParent;
}

template <class T> void Node<T>::set_dTime(unsigned int new_dTime) 
{
    dTime = new_dTime;
}

template <class T> void Node<T>::resetNode() 
{
    setColor(WHITE);
    setParent(nullptr);
    set_dTime(numeric_limits< unsigned int>::max());
}