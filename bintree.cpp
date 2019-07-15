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

//CONSTRUCTOR
BinTree::BinTree()
{
    count = 0;
    rootPtr = nullptr;
}

//DESTRUCTOR
BinTree::~BinTree()
{
    clearHelper(rootPtr);
}

//PRIVATE FUNCTIONS
bool BinTree::addNodeHelper(DataNode *subtreePtr, int nodeId, string nodeInfo)
{
    bool isAdded = false;
    if (subtreePtr->data.id > nodeId) {
        if (!subtreePtr->left) {
            subtreePtr->left = new DataNode;
            subtreePtr->left->data.id = nodeId;
            subtreePtr->left->data.information = nodeInfo;
            subtreePtr->left->left = nullptr;
            subtreePtr->left->right = nullptr;

            count += 1;

            isAdded = true;
        } else {
            addNodeHelper(subtreePtr->left, nodeId, nodeInfo);
        }
    } else {
        if (!subtreePtr->right) {
            subtreePtr->right = new DataNode;
            subtreePtr->right->data.id = nodeId;
            subtreePtr->right->data.information = nodeInfo;
            subtreePtr->right->left = nullptr;
            subtreePtr->right->right = nullptr;

            count += 1;

            isAdded = true;
        } else {
            addNodeHelper(subtreePtr->right, nodeId, nodeInfo);
        }
    }
    return isAdded;
}

bool BinTree::containsHelper(DataNode *subtreePtr, int targetId)
{
    bool treeContains = false;

    if (subtreePtr == nullptr) {
        treeContains = false;
    } else if (subtreePtr->data.id == targetId){
        treeContains = true;
    } else if (targetId > subtreePtr->data.id) {
        return containsHelper(subtreePtr->right, targetId);
    } else if (targetId < subtreePtr->data.id) {
        return containsHelper(subtreePtr->left, targetId);
    } else {
        treeContains = false;
    }

    return treeContains;
}

bool BinTree::findMin(DataNode *subtreePtr, Data *returnNode)
{
    bool minFound = false;
    //find minimum by traversing to the left of given subtree
    if (subtreePtr == nullptr){
        returnNode->id = -1;
        returnNode->information = "";
        minFound = false;
    } else if (subtreePtr->left == nullptr) {
        returnNode->id = subtreePtr->data.id;
        returnNode->information = subtreePtr->data.information;
        minFound = true;
    } else {
        findMin(subtreePtr->left, returnNode);
    }
    return minFound;
}

bool BinTree::getNodeHelper(DataNode *subtreePtr, Data *returnNode, int targetId)
{
    bool nodeFound = false;
    
    if (subtreePtr == nullptr){
        returnNode->id = -1;
        returnNode->information = "";
        nodeFound = false;
    } else if (targetId > subtreePtr->data.id) {
        return getNodeHelper(subtreePtr->right, returnNode, targetId);
    } else if (targetId < subtreePtr->data.id) {
        return getNodeHelper(subtreePtr->left, returnNode, targetId);
    } else if (targetId == subtreePtr->data.id) {
        returnNode->id = subtreePtr->data.id;
        returnNode->information = subtreePtr->data.information;
        nodeFound = true;
    } else {
        nodeFound = false;
    }
    return nodeFound;
}

bool BinTree::getRootDataHelper(Data *rootData)
{
    if (rootPtr == nullptr)
    {
        rootData->id = -1;
        rootData->information = "";
        return false;
    }
    
    rootData->id = rootPtr->data.id;
    rootData->information = rootPtr->data.information;
    
    return true;
}

bool BinTree::isEmptyHelper()
{
    return count ? false : true;
}

bool BinTree::removeNodeHelper(DataNode *parent, DataNode *subtreePtr, int targetId)
{
    bool isRemoved = false;
    
    if (subtreePtr == nullptr) {
        isRemoved = false;
        return isRemoved;
    } 
    
    if (targetId < subtreePtr->data.id) {
        isRemoved = removeNodeHelper(subtreePtr, subtreePtr->left, targetId);
    } else if (targetId > subtreePtr->data.id) {
        isRemoved = removeNodeHelper(subtreePtr, subtreePtr->right, targetId);
    } else {
        //node is found
        if (subtreePtr->left == nullptr || subtreePtr->right == nullptr){
            
            //if current node has no child or one child
            //set the current node's only child to a tempNode pointer
            DataNode *tempNode;
            tempNode = subtreePtr->left;
            if (subtreePtr->right) {
                tempNode = subtreePtr->right;
            }

            if (parent) {
                if (parent->left == subtreePtr) {
                    parent->left = tempNode;
                } else {
                    parent->right = tempNode;
                }
            } else {
                rootPtr = tempNode;
            }
            delete subtreePtr;
            subtreePtr = nullptr;
            count--;
            isRemoved = true;
        } else {
            //if node has 2 children
            //find the minimum in right subtree, save id and information
            Data *temp;
            temp = new Data;
            findMin(subtreePtr->right, temp);
            
            //to delete the current node, set the value to minimum node data
            subtreePtr->data.id = temp->id;
            subtreePtr->data.information = temp->information;

            //delete the original duplicate of minimum node, call remove function recursively
            isRemoved = removeNodeHelper(subtreePtr, subtreePtr->right, temp->id);
        }
    }
    return isRemoved;

}

int BinTree::getCountHelper()
{
    return count;
}

int BinTree::getHeightHelper(DataNode *subtreePtr)
{
    int height = 0;
    if (subtreePtr == nullptr) {
        return height;
    } 
    else {
        height = (1 + std::max(getHeightHelper(subtreePtr->left), getHeightHelper(subtreePtr->right)));
    }

    return height;
}

void BinTree::clearHelper(DataNode *subtreePtr)
{
    DataNode *garbage;
    garbage = subtreePtr;
    
    if (garbage) {
        if (garbage->left)
            removeNodeHelper(nullptr, garbage->left, garbage->left->data.id);
        
        if (garbage->right)
            removeNodeHelper(nullptr, garbage->right, garbage->right->data.id);
        
    }

    delete rootPtr;
    rootPtr = nullptr;
    count = 0;
}

void BinTree::displayInOrderHelper(DataNode *subtreePtr)
{
    if (subtreePtr == nullptr)
        return;

    displayInOrderHelper(subtreePtr->left);
    cout << subtreePtr->data.id << " " << subtreePtr->data.information << endl;
    displayInOrderHelper(subtreePtr->right);
}

void BinTree::displayPostOrderHelper(DataNode *subtreePtr)
{
    if (subtreePtr == nullptr)
        return;

    displayPostOrderHelper(subtreePtr->left);
    displayPostOrderHelper(subtreePtr->right);
    cout << subtreePtr->data.id << " " << subtreePtr->data.information << endl;
}

void BinTree::displayPreOrderHelper(DataNode *subtreePtr)
{
    if (subtreePtr == nullptr)
        return;

    cout << subtreePtr->data.id << " " << subtreePtr->data.information << endl;
    displayPreOrderHelper(subtreePtr->left);
    displayPreOrderHelper(subtreePtr->right);
}


//PUBLIC FUNCTIONS
bool BinTree::contains(int targetId){
    return containsHelper(rootPtr, targetId);
}

bool BinTree::addNode(int nodeId, string nodeInfo)
{
    bool isAdded = false;
    if (rootPtr != nullptr)
    {
        isAdded = addNodeHelper(rootPtr, nodeId, nodeInfo);
    }
    else 
    {
        rootPtr = new DataNode;
        rootPtr->data.id = nodeId;
        rootPtr->data.information = nodeInfo;
        rootPtr->left = nullptr;
        rootPtr->right = nullptr;

        count++;

        return true;
    }
    return isAdded;
}

bool BinTree::isEmpty()
{
    return isEmptyHelper();
}

bool BinTree::getNode(Data *returnNode, int targetId)
{
    return getNodeHelper(rootPtr, returnNode, targetId);
}

bool BinTree::getRootData(Data *rootData)
{
    return getRootDataHelper(rootData);
}

bool BinTree::removeNode(int targetId)
{
    return removeNodeHelper(nullptr, rootPtr, targetId);
}

int BinTree::getCount()
{
    return getCountHelper();
}

int BinTree::getHeight()
{
    return getHeightHelper(rootPtr);
}

void BinTree::displayInOrder()
{
    displayInOrderHelper(rootPtr);
}

void BinTree::displayPostOrder()
{
    displayPostOrderHelper(rootPtr);
}

void BinTree::clear()
{
    clearHelper(rootPtr);
}

void BinTree::displayPreOrder()
{
    displayPreOrderHelper(rootPtr);
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
    displayInOrder();
    cout << "Post-Order Traversal" << endl;
    displayPostOrder();
}
