#ifndef _BPLUSTREENODE_H_
#define _BPLUSTREENODE_H_

#define TREE_PREFIX "leaves/leaf_"

#include "FileObject.hpp"

#include <iostream>
#include <sys/types.h>
#include <algorithm>
#include <climits>
#include <cmath> 
#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>


using namespace std;

class TreeNode{
    public:
        static long fileCount;              // Count of all files
        static long lowerBound;
        static long upperBound;
        static long pageSize;

    private:
        long fileIndex;                     // Name of file to store contents
        bool leaf;                          // Type of leaf

    public:
        long parentIndex;
        long nextLeafIndex;
        long previousLeafIndex;
        double keyType;                     // Dummy to indicate container base
        vector<double> keys;
        vector<long> childIndices;          // FileIndices of the children
        vector<long> objectPointers;  
        
    public:
        TreeNode();
        TreeNode(long _fileIndex);              //Given a fileIndex, read it
        bool isLeaf() { return leaf; }          //Check if leaf
        string getFileName() { return TREE_PREFIX + to_string(fileIndex); } //Get the file name
        long getFileIndex() { return fileIndex; } //Get the fileIndex
        void setToInternalNode() { leaf = false; }  //set to internalNode
        long size() { return keys.size(); } //Return the size of keys
        static void initialize(); //Initialize the for the tree
        long getKeyPosition(double key); //Return the position of a key in keys
        void commitToDisk(); //Commit node to disk
        void readFromDisk(); //Read from the disk into memory
        void printNode(); //Print node information
        void serialize(); //Serialize the subtree
        void insertObject(FileObject object); //Insert object into disk
        void insertNode(double key, 
                        long leftChildIndex, 
                        long rightChildIndex); //Insert an internal node into the tree
        void splitLeaf(); //Split the current Leaf Node
        void splitInternal();  //Split the current internal Node
};

#endif _BPLUSTREENODE_H_
