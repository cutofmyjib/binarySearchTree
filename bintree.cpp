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
bool BinTree::addNodeHelper(DataNode *subtreePtr, int nodeId, string nodeInfo)
{
    if (subtreePtr->data.id > nodeId) {
        if (!subtreePtr->left) {
            subtreePtr->left = new DataNode;
            subtreePtr->left->data.id = nodeId;
            subtreePtr->left->data.information = nodeInfo;
            subtreePtr->left->left = nullptr;
            subtreePtr->left->right = nullptr;

            count += 1;

            return true;
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

            return true;
        } else {
            addNodeHelper(subtreePtr->right, nodeId, nodeInfo);
        }
    }
}

int BinTree::getCountHelper()
{
    return count;
}

int BinTree::getHeightHelper(DataNode *subtreePtr)
{
    if (subtreePtr == nullptr)
    {
        return 0;
    } 
    else
        return 1 + std::max(getHeightHelper(subtreePtr->left), getHeightHelper(subtreePtr->right));
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

bool BinTree::findMin(DataNode *subtreePtr, Data *returnNode)
{
    bool minFound = false;
    //find minimum by traversing to the left of given subtree
    if (subtreePtr == nullptr){
        returnNode->id = -1;
        returnNode->information = "";
        minFound = false;
    } else if (subtreePtr->left == nullptr) {
        cout << "FIND MIN FUNC, MINIMUM: " << subtreePtr->data.id << endl;
        returnNode->id = subtreePtr->data.id;
        returnNode->information = subtreePtr->data.information;
        minFound = true;
    } else {
        findMin(subtreePtr->left, returnNode);
    }
    return minFound;
}

bool BinTree::removeNodeHelper(DataNode *subtreePtr, int targetId)
{
    bool isRemoved = false;
    
    if (subtreePtr == nullptr) {
        return isRemoved;
    } else if (targetId < subtreePtr->data.id) {
        removeNodeHelper(subtreePtr->left, targetId);
    } else if (targetId > subtreePtr->data.id) {
        removeNodeHelper(subtreePtr->right, targetId);
    } else {
        //node is found
        cout << "NODE to be deleted FOUND " << endl;
        cout << subtreePtr->data.id << endl;
        if (subtreePtr->left == nullptr && subtreePtr->right == nullptr){
            //case 1: node has no child
            cout << "case 1 -1111- no children " << subtreePtr->data.id << endl;
            delete subtreePtr;
            subtreePtr = nullptr;
            
            isRemoved = true;
        } else if (subtreePtr->left == nullptr) {
            cout << "case 2 -2222- no left child" << endl;
            //case 2: node has one child, left child is null
            DataNode *temp = subtreePtr;
            //set parent pointing to right child, delete current node found
            subtreePtr = subtreePtr->right;
            delete subtreePtr;
            subtreePtr = nullptr;
            isRemoved = true;
        } else if (subtreePtr->right == nullptr) {
            cout << "case 2 -2222-- no right child" << endl;
            //case 2: node has one child, right child is null
            DataNode *temp = subtreePtr;
            //set parent pointing to right child, delete current node found
            subtreePtr = subtreePtr->left;
            delete subtreePtr;
            isRemoved = true;
        } else {
            //case 3: node has 2 children
            cout << "case 3 -333333- 2 children" << endl;
            cout << subtreePtr->left->data.id << " <left id" << subtreePtr->right->data.id << " <right id" <<  endl;
            //find the minimum in right subtree, save id and information
            Data *temp;
            temp = new Data;
            findMin(subtreePtr->right, temp);
            
            //to delete the current node, set the value to minimum node data
            subtreePtr->data.id = temp->id;
            subtreePtr->data.information = temp->information;

            cout << "calling removenodehelper to delete minimum node" << endl;
            //delete the original duplicate of minimum node, call remove function recursively
            removeNodeHelper(subtreePtr->right, temp->id);
            cout << "back to case 3, removed ------------" << endl;
            isRemoved = true;
        }
    }
    return isRemoved;

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
bool BinTree::isEmpty()
{
    return isEmptyHelper();
}

bool BinTree::addNode(int nodeId, string nodeInfo)
{
    bool isAdded = false;
    if (rootPtr != nullptr)
    {
        cout << "addNode func rootPTR not nullptr" << endl;
        isAdded = addNodeHelper(rootPtr, nodeId, nodeInfo);
    }
    else 
    {
        rootPtr = new DataNode;
        rootPtr->data.id = nodeId;
        rootPtr->data.information = nodeInfo;
        rootPtr->left = nullptr;
        rootPtr->right = nullptr;

        count += 1;

        return true;
    }
    return isAdded;
}

bool BinTree::getRootData(Data *rootData)
{
    return getRootDataHelper(rootData);
}

bool BinTree::removeNode(int targetId)
{
    return removeNodeHelper(rootPtr, targetId);
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
    displayPreOrderHelper(rootPtr);
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
