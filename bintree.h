/***********************************************************
Name: Diana Lozano
Assignment: 04
Purpose: This is the BinTree header file.
***********************************************************/
#include <iostream>     /* cout, endl */
#include "data.h"

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

using namespace std;

class BinTree {
private:
    DataNode *rootPtr;
    int count;
    int height;
    int getCountHelper();
    int getHeightHelper(DataNode *subtreePtr);
    bool addNodeHelper(int, string);
    bool getRootDataHelper(Data*);
    bool isEmptyHelper();
    void displayPreOrderHelper(DataNode *subtreePtr);

public:
    BinTree();
    ~BinTree();
    bool addNode(int, string);
    bool contains(int);
    bool getNode(Data*, int);
    bool getRootData(Data*);
    bool isEmpty();
    bool removeNode(int);
    int getCount();
    int getHeight();
    void clear();
    void displayInOrder();    
    void displayPostOrder();
    void displayPreOrder();
    void displayTree();
};

#endif /* BINARY_TREE_H */
