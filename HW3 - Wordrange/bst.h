// Filename: bst.h
// 
// Header file for the class BST that represents a binary search tree
// 
// C. Seshadhri, Jan 2020

#ifndef BST_H
#define BST_H

#include <string>

using namespace std;

// node struct to hold data
class Node
{
	public:
      int key;
      string word;
	    Node *left, *right, *parent;

        Node() // default constructor
        {
            left = right = parent = NULL; // setting everything to NULL
        }

        Node(int val) // constructor that sets key to val
        {
            key = val;
            left = right = parent = NULL; // setting everything to NULL
        }

        Node(string str) // constructor that sets key to val
        {
            word = str;
            left = right = parent = NULL; // setting everything to NULL
        }
};

class BST
{
	private:
		Node *root; // Stores root of tree
    int range_query;
	public:
		BST(); // Default constructor sets root to null
        void insert(int); // insert int into list 
        void insert(string);
        void insert(Node*, Node*); // recursive version that inserts a node
        Node* find(int); // find int in tree, and return pointer to node with that int. If there are multiple copies, this only finds one copy
        Node* find(Node*, int); // recursive version that finds in a rooted subtree
        Node* minNode(Node*); // gets minimum node in rooted subtree
        Node* maxNode(Node*); // gets maximum node in rooted subtree
        Node* deleteKey(int); // remove a node with int (if it exists), and return pointer to deleted node. This does not delete all nodes with the value.
        Node* deleteNode(Node*); // try to delete node pointed by argument. This also returns the node, isolated from the tree.
		void deleteBST(); // deletes every node to prevent memory leaks, and frees memory
        void deleteBST(Node* start); // deletes every Node in subtree rooted at startto prevent memory leaks.
		string printInOrder(); // Construct string with tree printed InOrder
		string printInOrder(Node* start); // Construct string with rooted subtree printed InOrder
		string printPreOrder(); // Construct string with tree printed PreOrder
		string printPreOrder(Node* start); // Construct string with rooted subtree printed PreOrder
		string printPostOrder(); // Construct string with tree printed PostOrder
		string printPostOrder(Node* start); // Construct string with rooted subtree printed PostOrder

    int rangeCount(int, int);
    void recRangeCount(Node*, int, int);

    int rangeCount(string, string);
    void recRangeCount(Node*, string, string);
};

#endif
