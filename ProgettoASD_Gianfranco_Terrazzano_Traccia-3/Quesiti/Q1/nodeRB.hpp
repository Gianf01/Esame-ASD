#include<iostream>
#include<string>
using namespace std;

template <typename T>
class NodeRB{
    private:
        int key;
        NodeRB *parent;
        NodeRB *left;
        NodeRB *right;
        T data;
        string color;
    public:
        NodeRB() : key(-1), data(NULL), parent(nullptr), left(nullptr), right(nullptr), color("black") {}
        NodeRB(int key, T data):parent{nullptr}, left{nullptr},right{nullptr} {this->key=key;this->data=data; this->color="black";};
        int getKey(){return key;};
        void setParent(NodeRB *p){parent=p;};
        NodeRB *getParent(){return parent;};
        void setLeft(NodeRB *l){left=l;};
        NodeRB *getLeft(){return left;};
        void setRight(NodeRB *r){right=r;};
        NodeRB *getRight(){return right;};
        string getColor(){return color;};
        void setColor(string c){color = c;};
        T getData(){return data;};
        virtual ~NodeRB(){
            delete left;
            delete right;
            delete parent;
        };
};