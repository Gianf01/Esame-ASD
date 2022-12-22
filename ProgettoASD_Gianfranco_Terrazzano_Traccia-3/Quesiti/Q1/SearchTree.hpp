#include "NodeRB.hpp"
template <typename T>
class BinarySearchTree
{
    private:
        NodeRB<T> *root;
        void Transplant(NodeRB<T> *u,NodeRB<T> *v);
        NodeRB<T> *NilT= new NodeRB<T>();   
    public:
        BinarySearchTree(){       
        setRoot(getNil());
        };   
        void DestroyRecursive(NodeRB<T> *NodeRB){
            if(NodeRB !=NilT){
                DestroyRecursive(NodeRB->getLeft());
                DestroyRecursive(NodeRB->getRight());
                delete NodeRB;
            }
        };
         virtual ~BinarySearchTree(){
            DestroyRecursive(root);
        };
        NodeRB<T> *getRoot(){return root;}
        void setRoot(NodeRB <T> *newRoot);
        void insertNode(int key, T data);
        void delNode(int key); 
        void inorder(NodeRB<T> *x);
        void preorder(NodeRB<T> *x);
        NodeRB<T> *getNil(){return NilT;}
        void postorder(NodeRB<T> *x);
        NodeRB<T> *minimum(NodeRB<T> *x);
        NodeRB<T> *maximum(NodeRB<T> *x);
        NodeRB<T> *searchNode(NodeRB<T> *x, int key); 
        NodeRB<T> *predecessor(NodeRB<T> *x);
        NodeRB<T> *successor(NodeRB<T> *x);
        vector<T> * VectorRB();
        vector<T> * InorderRB(NodeRB<T> * x, vector<T> * Vector);
};

template <class T> void BinarySearchTree<T>::setRoot(NodeRB <T> *newRoot) {
    this->root = newRoot;
}

template<typename T> NodeRB<T> *BinarySearchTree<T>::searchNode(NodeRB <T> *x, int key){
    if (x == NilT || key== x->getKey()){
        return x;
    }
    if (key<x->getKey())
        return searchNode(x->getLeft(),key);
    else
        return searchNode(x->getRight(),key);
}

template<typename T> void BinarySearchTree<T>::Transplant(NodeRB <T> *u, NodeRB <T> *v){
    if (u->getParent==NilT){
       setRoot(v);
    }else if(u==u->getParent()->getLeft){
            u->getParent()->setLeft(v);
    }else  u->getParent()->setRight(v);
    if (v!=NilT){
         v->setParent(u->getParent());
    }
}

template<typename T> NodeRB<T> *BinarySearchTree<T>::minimum(NodeRB <T> *x){
    while(x->getLeft() != NilT){
        x=x->getLeft();
    }
    return x;
}

template<typename T> NodeRB<T> *BinarySearchTree<T>::maximum(NodeRB <T> *x){
    while(x->getRight() != NilT){
        x=x->getRight();
    }
    return x;
}

template<typename T> NodeRB<T> *BinarySearchTree<T>::predecessor(NodeRB <T> *x){
    if (x->getLeft() != NilT){
        return maximum(x->getLeft());
    }
    NodeRB<T> *y= x->getParent();
    while(y != NilT && x==y->getLeft()){
        x=y;
        y=y->getParent();
    }
    return y;
}

template<typename T> NodeRB<T> *BinarySearchTree<T>::successor(NodeRB <T> *x){
    if (x->getRight() != NilT){
        return minimum(x->getRight());
    }
    NodeRB<T> *y= x->getParent();
    while(y != NilT && x==y->getRight()){
        x=y;
        y=y->getParent();
    }
    return y;
}

 template<typename T> void BinarySearchTree<T>::insertNode(int key, T data){    
    NodeRB<T> *y = NilT;
    NodeRB<T> *x = root;
    NodeRB<T> *z = new NodeRB<T>(key,data);
    z->setRight(NilT);
    z->setLeft(NilT);
    z->setParent(NilT);
    while (x!=NilT){
        y=x;
        if (z->getKey() < x->getKey()){
            x= x->getLeft();
        }else x= x->getRight();
    }
    z->setParent(y);
    if (y==NilT){
        setRoot(z);
    }else if(z->getKey() < y->getKey()){
        y->setLeft(z);
    }else y->setRight(z);
 }

template<typename T> void BinarySearchTree<T>::delNode(int key){
    NodeRB<T> *Nodo = searchNode(root, key);
    if (Nodo->getLeft()==NilT){
        Transplant(Nodo, Nodo->getRight());
    } else if(Nodo->getRight()==NilT) 
        Transplant(Nodo, Nodo->getLeft());
    else{
        NodeRB<T> *min = minimum(Nodo->getRight());
        if (min->getParent()!= Nodo){
            Transplant(min, min->getRight());
            min->setRight(Nodo->getRight());
            min->getRight()->setParent(min);
        }
        Transplant(Nodo,min);
        min->setLeft(Nodo->getLeft());
        min->getLeft->setParent(min);
    }
 }

 template<typename T> void BinarySearchTree<T> :: inorder(NodeRB<T> *x)
{
    if(x == NilT)
        return;
    inorder(x->getLeft());
    cout<<x->getData()<<" ";
    inorder(x->getRight());
}

template<typename T> void BinarySearchTree<T> :: preorder(NodeRB<T> *x)
{
    if(x == NilT)
        return;
    cout<<x->getData()<<" ";
    preorder(x->getLeft());
    preorder(x->getRight());
}

template<typename T> void BinarySearchTree<T> :: postorder(NodeRB<T> *x)
{
    if(x == NilT)
        return;
    postorder(x->getLeft());
    postorder(x->getRight());
    cout<<x->getData()<<" ";
}

template <class T>  vector<T> * BinarySearchTree<T>::InorderRB(NodeRB<T> * x, vector<T> * Vector) {
    if (x != NilT) {
        InorderRB(x->getLeft(), Vector);
        Vector->push_back(x->getData());
        InorderRB(x->getRight(), Vector);
    }
    return Vector;
}

template <class T> vector<T> * BinarySearchTree<T>::VectorRB() {
    vector<T> * VectorRB= new vector<T>;
    InorderRB(this->getRoot(), VectorRB);
    return VectorRB;
}



