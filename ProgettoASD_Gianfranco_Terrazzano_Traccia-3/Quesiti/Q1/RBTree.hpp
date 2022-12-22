#include "SearchTree.hpp"
#include <queue>
//Classe albero RB

template <class T> class RBTree : public BinarySearchTree<T>{
    private:
        void leftRotate(NodeRB<T> * current);
        void rightRotate(NodeRB<T> * current);
        void RB_Transplant(NodeRB<T> *u, NodeRB<T> *v);
    public:
    RBTree() {
        BinarySearchTree<T>();
    }
    ~RBTree() { }
    void insertNodeRB(int key, T data);
    void RB_delete(int key);
    void RB_Delete_Fixup(NodeRB <T> *x);
};

template <class T> void RBTree<T> :: leftRotate(NodeRB<T> *x){
NodeRB<T> *y= x->getRight();
if (y == this->getNil()) return;
x->setRight(y->getLeft());
    if (y->getLeft() != this->getNil())
        y->getLeft()->setParent(x);
    y->setParent(x->getParent());
    if (x->getParent() == this->getNil()){
        this->setRoot(y);
    }
    else if (x==x->getParent()->getLeft())
        x->getParent()->setLeft(y);
    else
        x->getParent()->setRight(y);
    y->setLeft(x);
    x->setParent(y);
}

template <class T> void RBTree<T>::rightRotate(NodeRB<T> * x) {
 NodeRB<T> * y = x->getLeft();
    
    if (y == this->getNil()) return;
    x->setLeft(y->getRight());
    
    if (y->getRight() != this->getNil()) {
        (y->getRight())->setParent(x);
    }
    
    y->setParent(x->getParent());
    
    if (x->getParent() == this->getNil()) {
        this->setRoot(y);
    } else if (x == (x->getParent()->getRight())) {
        (x->getParent())->setRight(y);
    } else {
        (x->getParent())->setLeft(y);
    }
    
    y->setRight(x);
    x->setParent(y);   
}

template <class T> void RBTree<T> :: insertNodeRB(int key,T data){     
this->insertNode(key, data);
NodeRB<T> * x = this->searchNode(this->getRoot(),key);
x->setColor("red");
    while (this->getRoot() != x && (x->getParent())->getColor() == "red"){ //controllo non violi la seconda proprietà
        if(x->getParent()==((x->getParent())->getParent())->getLeft()){
            NodeRB<T> *y= ((x->getParent())->getParent())->getRight();

            if (y!= this->getNil() && y->getColor()=="red"){ //risolvo il caso 1
                (x->getParent())->setColor("black");
                y->setColor("black");
                ((x->getParent())->getParent())->setColor("red");
                x = (x->getParent())->getParent();
            }else{
                if(x= (x->getParent())->getRight()){ //sono nel caso 2 e passo al caso 3
                    x = x->getParent();
                    leftRotate(x);
                }
                //Caso 3
                (x->getParent())->setColor("black"); //il padre di x diventa "black" e il ciclo non verrà ri-eseguito
                ((x->getParent())->getParent())->setColor("red");
                rightRotate(((x->getParent())->getParent()));
            }
        }else{ //analogo al ramo then con RIGHT and LEFT scambiati
            NodeRB<T> * y = ((x->getParent())->getParent())->getLeft();
        
            if (y != this->getNil() && y->getColor() == "red") {
                (x->getParent())->setColor("black");
                y->setColor("black");
                ((x->getParent())->getParent())->setColor("red");
                x = ((x->getParent())->getParent());
            } else {
                if (x == (x->getParent())->getLeft()) {
                    x = x->getParent();
                    rightRotate(x);
                }
                
                (x->getParent())->setColor("black");
                ((x->getParent())->getParent())->setColor("red");
                leftRotate(((x->getParent())->getParent()));
            }
        } 
    }
    (this->getRoot())->setColor("black");
}


template <typename T> void RBTree<T> :: RB_Transplant(NodeRB<T> *u, NodeRB<T> *v){
    if (u->getParent()==this->getNil())
        this->setRoot(v);
    else if (u == u->getParent()->getLeft()){
        u->getParent()->setLeft(v);
    }
    else  u->getParent()->setRight(v);
    
    if (v != this->getNil()) 
        v->setParent(u->getParent());
}


template <typename T> void RBTree<T> :: RB_delete(int key){
    NodeRB<T> *z= this->searchNode(this->getRoot(), key);
    NodeRB<T> *y = z;
    NodeRB<T> *x;
    string Origcol= y->getColor();
    if (z->getLeft()==this->getNil()){
        x=z->getRight();
        RB_Transplant(z, z->getRight());
    }else if (z->getRight()==this->getNil()){
        x=z->getLeft();
        RB_Transplant(z, z->getLeft());
    }else{
        y=this->minimum(z->getRight());
        Origcol=y->getColor();
        x=y->getRight();
        if (y->getParent()==z){
            x->setParent(y); // se x==NILL[T]
        }else{
            RB_Transplant(y, y->getRight());
            y->setRight(z->getRight());
            y->getRight()->setParent(y);
        }
        RB_Transplant(z,y);
        y->setLeft(z->getLeft());
        y->getLeft()->setParent(y);
        y->setColor(z->getColor()); //y prende il colore di z
    }
    if (Origcol=="black"){
        if (x!=this->getNil()){
            RB_Delete_Fixup(x);
        }
    }
} 


template<typename T> void RBTree<T>::RB_Delete_Fixup(NodeRB <T> *x){
    while(x != this->getRoot()&& x->getColor()=="black"){
        NodeRB <T> *px=x->getParent();
        if(x==px->getLeft()){
            NodeRB <T> *w=px->getRight();
            if(w->getColor()=="red"){
                w->setColor("black");
                px->setColor("red");
                leftRotate(px);
                w=px->getRight();
            }
            if(w->getLeft()->getColor()=="black" && w->getRight()->getColor()=="black"){
                w->setColor("red");
                x=px;
            }else{
                if(w->getRight()->getColor()=="black"){
                    w->getLeft()->setColor("black");
                    w->setColor("red");
                    rightRotate(w);
                    w=px->getRight();
                }
                w->setColor(px->getColor());
                px->setColor("black");
                w->getRight()->setColor("black");
                leftRotate(px);
                x=this->getRoot();
            }
        }else{
            NodeRB <T> *w=px->getLeft();
            if(w->getColor()=="red"){
                w->setColor("black");
                px->setColor("red");
                rightRotate(px);
                w=px->getLeft();
            }
            if(w->getLeft()->getColor()=="black" && w->getRight()->getColor()=="black"){
                w->setColor("red");
                x=px;
            }else{
                if(w->getLeft()->getColor()=="black"){
                    w->getRight()->setColor("black");
                    w->setColor("red");
                    leftRotate(w);
                    w=px->getLeft();
                }
                w->setColor(px->getColor());
                px->setColor("black");
                w->getLeft()->setColor("black");
                rightRotate(px);
                x=this->getRoot();
            }
        }
    }
    x->setColor("black");
}





