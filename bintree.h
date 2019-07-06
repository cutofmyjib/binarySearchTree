/***********************************************************
Name: Diana Lozano
Assignment: 04
Purpose: This is the BinTree header file.
***********************************************************/
#include "data.h"

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

class BinTree {
private:
    DataNode *rootPtr;
    int count;
    int height;
    bool getRootData(Data*);
    bool isEmpty();
    int getCount();
    void displayTree();

public:
    BinTree();
    ~BinTree();
    bool addNode(int, string);
    bool contains(int);
    bool getNode(Data*, int);
    bool removeNode(int);
    int getHeight();
    void clear();
    void displayPreOrder();
    void displayPostOrder();
    void displayInOrder();    
};

#endif /* BINARY_TREE_H */
