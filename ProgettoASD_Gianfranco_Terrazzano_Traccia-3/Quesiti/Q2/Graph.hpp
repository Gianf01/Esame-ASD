#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <limits.h>
#include <algorithm>
#include "Node.hpp"
#include "DisjointSet.hpp"

using namespace std;

template <class T> class Graph {
private:
    std::vector<Node<T> *> * nodes;
    std::vector<Node<T> *> * getNodes();

    std::vector<std::pair<unsigned int, std::pair<unsigned int, int>>> edges;
    std::vector<std::pair<unsigned int, std::pair<unsigned int, unsigned int> >> MST;
    std::vector<std::pair<unsigned int, std::pair<unsigned int, unsigned int> >> MST2;
    void resetNodesProperties();
    
public:
    Graph() {
        this->nodes = new std::vector<Node<T> *>;
    }
    
    void addNode(Node<T> * nodeToAdd);
    Node<T> * getNodeAtIndex(int index);
    void printAdjacentList();
    void Add_Edge(int u, int v, int w);
    int getID(Node<T> * u);
    int getWeight(int firstIndex, int secondIndex);
    void printMST();
    void printMST2();
    unsigned int kruskalMST();
    unsigned int kruskalMST2();
    bool CheckIfNodeExsist(Node<T>* nodeToCheck);
    int GetEdgeID(unsigned int w, unsigned int u,  unsigned int v);
    bool FindEdge(unsigned int u, unsigned int v, unsigned int w);
};

template <class T> std::vector<Node<T> *> * Graph<T>::getNodes() {
    return this->nodes;
}

template <class T> void Graph<T>::addNode(Node<T> * nodeToAdd) {
     if (!CheckIfNodeExsist(nodeToAdd)){
        nodes->push_back(nodeToAdd);
    }else{
        cout <<"il nodo è già stato inserito"<<endl;
    }
}

template <class T> Node<T> * Graph<T>::getNodeAtIndex(int index) { //ritorna un nodo dall'indice
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

template <class T> int Graph<T>::GetEdgeID(unsigned int w, unsigned int u,  unsigned int v){ //Ritorna l'indice di un arco
int i=0;
    for ( auto it = edges.begin(); it != edges.end(); it++){
        i++;
        if (it->first== w && it->second.first == u && it->second.second == v){
            return i;
        }
    }
    cout<<"l'arco non esiste"<<endl;
    abort();
}

template <class T> void Graph<T>::printAdjacentList() {
    for(auto singleNode: *(getNodes())) {
        std::cout << "Adj(" << singleNode->getData() << "): ";
        
        for (auto adjacentNode: *(singleNode->getAdjacentList())) std::cout << "  " << adjacentNode->getData();
        std::cout << std::endl;
    }
}

template <class T> bool Graph<T>::FindEdge(unsigned int u, unsigned int v, unsigned int w){ //Cerca un arco nel vettore edge
    for ( const auto& edge: edges){
        if (edge.first == w && edge.second.first == u && edge.second.first == v){
            cout <<"Arco trovato"<<endl;
            return true;
        }
    } 
    cout<<"Arco non trovato"<<endl;
    return false; 
}

template <class T> void Graph<T>::Add_Edge(int u, int v, int w){
    if (!(FindEdge(u,v,w))){
    edges.push_back({ w, { u, v } });
    getNodeAtIndex(u)->addEdge(this->getNodeAtIndex(v));
    cout << "arco inserito correttamente!"<<endl;
    }else{ cout<<"l'arco già esiste!"<<endl;}
}



template <class T> void Graph<T>::resetNodesProperties() {
    for (auto & node: *(getNodes())) node->resetNode();
}

template <class T> int Graph<T>::getID(Node<T>* u){ //ritorna l'indice di un nodo
    int i;
    for (i=0; i< nodes->size(); i++){
        if (u->getData()==getNodeAtIndex(i)->getData())
            return i;
    } 
    cout <<"il nodo non esiste" <<endl;
    abort();
}

template <class T> int Graph<T>::getWeight(int firstIndex, int secondIndex) {
    for (auto it = edges.begin(); it != edges.end(); it++) {
        if (it->second.first == firstIndex && it->second.second == secondIndex) {
            return it->first;
        }
    }
     cout <<"l'arco non esiste" <<endl;
    abort();
}

template <class T> unsigned int Graph<T>::kruskalMST() {
    unsigned int MSTWeight = 0;
    std::sort(edges.begin(),edges.end());
    //per ogni u in G_v
    //    MAKE-SET(u)
    DisjointSet disjointSet((unsigned int) this->nodes->size());

    //std::vector<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>>::iterator it;
    
    for (auto it = edges.begin(); it != edges.end(); it++){
        unsigned int u = it->second.first; //indice nodo sorgente dell'arco
        unsigned int v = it->second.second; //indice nodo destinazione dell'arco
        unsigned int setU = disjointSet.findSet(u);
        unsigned int setV = disjointSet.findSet(v);
        if (setU != setV){
            unsigned int w = it->first;  //peso dell'arco
            MST.push_back({w, {u, v}});
            MSTWeight += it->first;
            disjointSet.unionSet(setU, setV);
        }
    }
    return MSTWeight;
}

template <class T> unsigned int Graph<T>::kruskalMST2() {
    //dichiaro un cammino minimo tmp
    std::vector<std::pair<unsigned int, std::pair<unsigned int, unsigned int> >> MSTtmp;
    //Dichiaro una variabile che memorizzerà il peso del secondo cammino minimo
    unsigned int SecondBest=std::numeric_limits<int>:: max();
    //Faccio un doppio ciclo for che rimuove uno alla volta gli archi dell'MST
    for (auto st = MST.begin(); st != MST.end(); st++){
        for (auto st2 =edges.begin(); st2 != edges.end(); st2++){
            if (st->first==st2->first && st->second.first == st2->second.first && st->second.second == st2->second.second){
                int tmp= GetEdgeID(st->first,st->second.first,st->second.second); 
                edges.erase(edges.begin()+tmp-1); //rimuovo l'arco uguale all'arco dell'MST 
            }
        }
        //Ricalcolo kruskal senza l'arco dell'MST rimosso 
        unsigned int MSTWeight2 = 0;
        MSTtmp.clear();
        std::sort(edges.begin(),edges.end());
            //per ogni u in G_v
            //    MAKE-SET(u)
        DisjointSet disjointSet2((unsigned int) this->nodes->size());
            
        for (auto it = edges.begin(); it != edges.end(); it++){
            unsigned int u = it->second.first; //indice nodo sorgente dell'arco
            unsigned int v = it->second.second; //indice nodo destinazione dell'arco
            unsigned int setU = disjointSet2.findSet(u);
            unsigned int setV = disjointSet2.findSet(v);
            if (setU != setV){
                unsigned int w = it->first;  //peso dell'arco
                MSTtmp.push_back({w, {u, v}});
                MSTWeight2 += it->first;
                disjointSet2.unionSet(setU, setV);
            }
        }
        if (SecondBest > MSTWeight2){
            MST2.clear();
            SecondBest= MSTWeight2; //Aggiorno la variabile del secondo peso minimo migliore 
            MST2.insert(MST2.end(), MSTtmp.begin(),MSTtmp.end()); //inserisco l'MST tmp dentro L'MST2
        }
        edges.push_back({ st->first, { st->second.first, st->second.second } }); //Riaggiungo l'arco che avevo rimosso e passo al successivo
    }
    return SecondBest;   
}


template <class T> void Graph<T>::printMST() {
    cout << "Stampo il minimum spanning tree: \n" << endl;

    for (auto it = MST.begin(); it != MST.end(); it++){
        std::cout << getNodeAtIndex(it->second.first)->getData() << " - " << getNodeAtIndex(it->second.second)->getData() << "->"<< it->first << "\n";
    }
}

template <class T> void Graph<T>::printMST2() {
    cout << "Stampo il second minimum spanning tree: \n" << endl;

    for (auto it = MST2.begin(); it != MST2.end(); it++){
        std::cout << getNodeAtIndex(it->second.first)->getData() << " - " << getNodeAtIndex(it->second.second)->getData() << "->"<< it->first << "\n";
    }
}
#endif 