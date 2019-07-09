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
    bool addNodeHelper(DataNode *subtreePtr, int nodeId, string nodeInfo);
    bool findMin(DataNode *subtreePtr, Data *returnNode);
    bool getNodeHelper(DataNode *subtreePtr, Data *returnNode, int targetId);
    bool getRootDataHelper(Data*);
    bool isEmptyHelper();
    bool removeNodeHelper(DataNode *parent, DataNode *subtreePtr, int targetId);
    void clearHelper(DataNode *subtreePtr);
    void displayInOrderHelper(DataNode *subtreePtr);
    void displayPostOrderHelper(DataNode *subtreePtr);
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
