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
    //TODO
    // clear();
    // height = -1
}

//PRIVATE FUNCTIONS
DataNode BinTree::insertInorder(DataNode *subtreePtr, DataNode *newNodePtr)
{
    cout << endl;
    cout << "INSIDE INSERTORDER" << endl;
    if (subtreePtr == nullptr)
    {
        subtreePtr = newNodePtr;
        count += 1;
        return *subtreePtr;
    }
    else if (subtreePtr->data.id > newNodePtr->data.id)
        *subtreePtr->left = insertInorder(subtreePtr->left, newNodePtr);
    else
        *subtreePtr->right = insertInorder(subtreePtr->right, newNodePtr);
    

}

bool BinTree::addNodeHelper(int nodeId, string nodeInfo)
{
    DataNode *newNodePtr = new DataNode();
    newNodePtr->data.id = nodeId;
    newNodePtr->data.information = nodeInfo;
    newNodePtr->left = nullptr;
    newNodePtr->right = nullptr;

    insertInorder(rootPtr, newNodePtr);
    return true;
}

int BinTree::getCountHelper()
{
    return count;
}

int BinTree::getHeightHelper(DataNode *subtreePtr)
{
    if (subtreePtr == nullptr)
    {
        cout << "hello world" << endl;
        return 0;
    } 
    else
        return 1 + std::max(getHeightHelper(subtreePtr->left), getHeightHelper(subtreePtr->right));
}

// bool BinTree::getRootDataHelper(Data *rootData)
// {
    // if (rootPtr == nullptr)
    // {
    //     rootData->id = -1;
    //     rootData->information = "";
    //     return false;
    // }

    // rootData->id = rootPtr->data.id;
    // rootData->information = rootPtr->data.information;
//     return false;
// }

bool BinTree::isEmptyHelper()
{
    return count ? false : true;
}

void BinTree::displayPreOrderHelper(DataNode *subtreePtr)
{
    subtreePtr = rootPtr;
    if (!isEmptyHelper())
    {
        cout << subtreePtr->data.id << " " << subtreePtr->data.information << endl;
        displayPreOrderHelper(subtreePtr->left);
        displayPreOrderHelper(subtreePtr->right);
    }

}



//PUBLIC FUNCTIONS
bool BinTree::isEmpty()
{
    return isEmptyHelper();
}

bool BinTree::addNode(int nodeId, string nodeInfo)
{
    bool isAdded = addNodeHelper(nodeId, nodeInfo);
    return isAdded;
}

int BinTree::getCount()
{
    return getCountHelper();
}

int BinTree::getHeight()
{
    return getHeightHelper(rootPtr);
}

void BinTree::displayPreOrder()
{
    DataNode *subtreePtr;
    displayPreOrderHelper(subtreePtr);
}

void BinTree::displayTree()
{
    string isEmptyTree = isEmpty() ? "Tree is empty" : "Tree is NOT empty";
    
    cout << isEmptyTree << endl;
    cout << "Height " << getHeight() << endl;
    cout << "Node count: " << getCount() << endl;

    cout << "Pre-Order Traversal" << endl;
    displayPreOrder();
    cout << "In-Order Traversal" << endl;
    // displayInOrder();
    cout << "Post-Order Traversal" << endl;
    // displayPostOrder();
}

