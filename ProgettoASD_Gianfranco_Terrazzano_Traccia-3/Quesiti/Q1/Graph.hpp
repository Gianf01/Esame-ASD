#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
#include <vector>
#include <iterator>
#include "GraphNode.hpp"

template <class T> class Graph{
    private:
    vector<Node<T> *> *nodes;
    std::vector<std::pair<unsigned int, unsigned int>> edges;
    vector<Node<T> *> *getNodes(){return nodes;};
    int key;
    public:
    Graph() {
            this->nodes = new vector<Node<T> *>;
        }
        void addNode(Node<T> *nodeToAdd);
        Node<T> *getNodeAtIndex(unsigned int index);
        void AddEdge(unsigned int u, unsigned int v);
        bool CheckIfNodeExsist(Node<T>* nodeToCheck);
        bool FindEdge(unsigned int u, unsigned int v);
        void BFS(Node<T> * root);
        void resetNodesProperties();
        void printNode();
        void printEdge();
        int GetID(Node<T>* u);
        void printBFS();
        void RemoveEdge(unsigned int u, unsigned int v);
        int GetEdgeID(unsigned int u, unsigned int v);
};


template <class T> void Graph<T>::addNode(Node<T>* nodeToAdd){ //Aggiunge il nodo al vettore nodes
    if (!CheckIfNodeExsist(nodeToAdd)){
        nodes->push_back(nodeToAdd);
    }else{
        cout <<"il nodo è già stato inserito"<<endl;
    }
    
}

template <class T> Node<T> * Graph<T>::getNodeAtIndex(unsigned int index) { //ritorna un nodo dall'indice
        if ((index>=0) && (index<this->nodes->size()))
            return this->nodes->at(index);
        else 
            return nullptr;
}

template <class T> bool Graph<T>::CheckIfNodeExsist(Node<T>* nodeToCheck){ //controlla se il nodo è già stato inserito
    int i;
    for (i=0; i< nodes->size(); i++){
        if (nodeToCheck->getData()==getNodeAtIndex(i)->getData())
            return true;
    } 
    return false;   
}

template <class T> int Graph<T>::GetID(Node<T>* u){ //ritorna l'indice di un nodo
    int i;
    for (i=0; i< nodes->size(); i++){
        if (u->getData()==getNodeAtIndex(i)->getData())
            return i;
    }
    cout<< "il nodo non esiste"<<endl;
    abort();
}

template <class T> bool Graph<T>::FindEdge(unsigned int u, unsigned int v){ //Cerca un arco nel vettore edge
    for ( const auto& edge: edges){
        if (edge.first == u && edge.second == v){
            cout <<"Arco trovato"<<endl;
            return true;
        }
    } 
    cout<<"Arco non trovato"<<endl;
    return false; 
}

template <class T> int Graph<T>::GetEdgeID(unsigned int u, unsigned int v){ //Ritorna l'indice di un arco
int i=0;
    for ( const auto& edge: edges){
        i++;
        if (edge.first == u && edge.second == v){
            return i;
        }
    } 
     cout<< "l'arco non esiste"<<endl;
    abort();
}

template <class T> void Graph<T>::resetNodesProperties() 
{
    for (auto singleNode:*nodes) singleNode->resetNode();
}

template <class T> void Graph<T>::AddEdge(unsigned int u, unsigned int v){ //Aggiunge un arco
    if ((getNodeAtIndex(u)!=nullptr) && (getNodeAtIndex(v)!=nullptr)){
        if (!FindEdge(u,v)){
            edges.push_back({ u, v });
            cout << "L'arco è stato inserito correttamente"<< endl;
            getNodeAtIndex(u)->addEdge(v ,this->getNodeAtIndex(v)); //aggiorna la lista di adiacenza(Albero RB) di u
        }else cout<<"L'arco già esiste!"<<endl;
    }else cout<<"Il nodo non esiste!"<<endl;  
}


template <class T> void Graph<T>::RemoveEdge(unsigned int u, unsigned int v){ //rimuove un arco 
    if ((getNodeAtIndex(u)!=nullptr) && (getNodeAtIndex(v)!=nullptr)){
        if (FindEdge(u,v)){
            int tmp= GetEdgeID(u,v);
            edges.erase(edges.begin()+tmp-1); 
            getNodeAtIndex(u)->Remove_edge(v); //rimuove v dalla lista d'adiacenza di u
            cout << "L'arco è stato eliminato"<< endl;
        }else cout<<"L'arco non può essere eliminato perchè non esiste!"<<endl;
    }else cout<<"L'arco non esiste!"<<endl;  
}

template <class T> void Graph<T>::BFS(Node<T> * root) { 
    resetNodesProperties(); 
    root->setParent(nullptr);
    root->setColor(GRAY); 
    root->set_dTime(0);
    queue<Node<T> *> queue; 
    queue.push(root); 
    cout << "\n"<< "Nodi raggiungibili con visita BFS:" << "\n" << endl;
    cout << "Indici dei nodi:\n"<<endl;
     while (!queue.empty()) {
        Node<T> *u = queue.front(); 
        queue.pop(); 
        for (auto & adjacentNodeToU: *(u->getRBList()->VectorRB())){  //BFS utilizzando L'RB Tree
            if (adjacentNodeToU->getColor() == WHITE){ 
                adjacentNodeToU->setColor(GRAY); 
                adjacentNodeToU->setParent(u); 
                adjacentNodeToU->set_dTime(u->get_dTime()+1); 
                queue.push(adjacentNodeToU); 
            }
        }
         u->setColor(BLACK);
         cout<< "Nodo: "<< GetID(u) <<"  Distanza dalla sorgente: "<< u->get_dTime()<<endl;
    }

}


template <class T> void Graph<T>::printBFS(){
 cout<< "Nodi raggiungibili dall'origine, BFS:" <<endl;
 
    for (int i=0; i<nodes->size(); i++){
        if (getNodeAtIndex(i)->getColor()==BLACK)
            cout<< i <<" : "<< getNodeAtIndex(i)->getData() <<endl;
    }
}

template <class T> void Graph<T>::printNode(){ //stampo la lista dei nodi
 cout<< "lista nodi:" <<endl;
    for (int i=0; i<nodes->size(); i++){
        cout<<"indice: "<< i <<" - "<<"data: "<< getNodeAtIndex(i)->getData() <<endl;
    }
}

template <class T> void Graph<T>::printEdge(){  //stampo la lista degli archi
int i=1;
 cout<< "lista archi per indice:" <<endl;
   for ( const auto& edge: edges){
        cout<< i <<" : "<< edge.first <<" - " << edge.second<<endl;
        i++;
    }
}
