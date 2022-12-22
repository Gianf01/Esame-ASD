#ifndef DisjointSet_h
#define DisjointSet_h
#include <vector>

class DisjointSet {
private:
    std::vector<unsigned int> parent;
    std::vector<unsigned int> rank;
    unsigned int size;
    
    void setSize(unsigned int newSize);
    void setRank(std::vector<unsigned int> newRank);
    void setParent(std::vector<unsigned int> newParent);
    
    unsigned int getSize();
    std::vector<unsigned int> getRank();
    std::vector<unsigned int> getParent();
    
    void link(unsigned int x, unsigned int y);

public:
    DisjointSet(unsigned int size) {
        setSize(size);
        setParent(std::vector<unsigned int>(getSize(), 0));
        setRank(std::vector<unsigned int>(getSize(), 0));

        for (unsigned int i = 0; i < getSize(); i++){
            this->rank.at(i) = 0;
            this->parent.at(i) = i;
        }
    }
    
    ~DisjointSet() { }
    
    void makeSet(unsigned int x);
    unsigned int findSet(unsigned int x);
    void unionSet(unsigned int x, unsigned int y);
    bool sameComponent(unsigned int u, unsigned int v); 
};

void DisjointSet::setSize(unsigned int newSize) {
    this->size = newSize;
}

void DisjointSet::setRank(std::vector<unsigned int> newRank) {
    this->rank = newRank;
}

void DisjointSet::setParent(std::vector<unsigned int> newParent) {
    this->parent = newParent;
}

unsigned int DisjointSet::getSize() {
    return this->size;
}

std::vector<unsigned int> DisjointSet::getRank() {
    return this->rank;
}

std::vector<unsigned int> DisjointSet::getParent() {
    return this->parent;
}

void DisjointSet::makeSet(unsigned int x) {
    this->parent.at(x) = x;
    this->rank.at(x) = 0;
}

unsigned int DisjointSet::findSet(unsigned int x) {
    if (x != this->parent.at(x)) {
        this->parent.at(x) = findSet(this->parent.at(x));
    }
    
    return this->parent.at(x);
}

void DisjointSet::unionSet(unsigned int x, unsigned int y) {
    link(findSet(x), findSet(y));
}

void DisjointSet::link(unsigned int x, unsigned int y) {
    if (rank.at(x) > rank.at(y)) {
        this->parent.at(y) = x;
        this->rank.at(x) += rank.at(y);
    } else {
        this->parent.at(x) = y;
        
        if (this->rank.at(x) == this->rank.at(y)) {
            this->rank.at(y) += 1;
        } else {
            this->rank.at(y) += rank.at(x);
        }
    }
}

bool DisjointSet::sameComponent(unsigned int u, unsigned int v) {
    return (findSet(u) == findSet(v));
}
    
#endif