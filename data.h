/***********************************************************
Name: Diana Lozano
Assignment: 05
Purpose: This is the data header file.
***********************************************************/

#ifndef DATA_H
#define DATA_H

#include <string>
using std::string;

struct Data {
    int id;
    string information;
};

struct DataNode {
    Data data;
    DataNode *left, *right;
};

#endif /* DATA_H */
