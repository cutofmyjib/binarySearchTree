/***********************************************************
Name: Diana Lozano
Assignment: 05
Purpose: This is where all the binary search tree functions are defined.
■ isEmpty(): boolean -- Return true or false depending on count
■ getCount(): integer -- Return a count of the nodes
■ getRootData(Data*): boolean -- If the root exists, fill the Data struct with the root data, return
true. If the root doesn’t exist, fill the Data struct with -1 and an empty string and return false
■ clear(): void -- Empties the tree. 
■ addNode(int id, string data): boolean -- Add a node in-order based on id
■ removeNode(int targetId): boolean -- Removes a node and re-orders the tree
■ getNode(Data*, int): boolean -- Fill the data to the Data struct if the node exists and
return true. If it does not exist, place -1 and an empty string in the Data struct and return false.
■ contains(int): bool -- Return true or false if a node exists or not.
■ getHeight(): integer -- Return the height of the tree
***********************************************************/
#include "bintree.h"
#include "data.h"

//CONSTRUCTOR
BinTree::BinTree()
{
    count = 0;
    rootPtr = nullptr;
}

//DESTRUCTOR
BinTree::~BinTree()
{
    // clear();
    // height = -1
}

//PUBLIC FUNCTIONS
bool BinTree::getRootData(Data *rootData)
{
    if (rootPtr == NULL)
    {
        rootData->id = -1;
        rootData->information = "";
        return false;
    }

    rootData->id = rootPtr->data.id;
    rootData->information = rootPtr->data.information;
    return true;
}

bool BinTree::isEmpty()
{
    return count ? true : false;
}

int BinTree::getCount()
{
    return count;
}



