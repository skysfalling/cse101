// Filename: linkedlist.h
// 
// Header file for the class LinkedList that represents a linked list
//
// Added ADV Operations to header file
// -- Node logs prev node now to make operations easier
//
//
//
//
// Sky Casey. 2022 CSE 101
//


 

#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

// node struct to hold data

struct Node
{
	int data;
	Node *next;
};

class LinkedList
{
	public:

		Node *head; // Stores head of linked list
		
		// << delete specific node >>
		void deleteNode(Node*);
		void deleteNode(Node*, Node*, Node*);

		// << delete specific occurence of value >>
		void deleteOccurrence(int, int); // wrapper
		void deleteOccurrence(int, int, Node*); // recursive function
        void deleteLastOccurrence(int, Node*, Node*); // recursive function

        // << reverse the linked list >>
        Node* reverse(int);
        Node* reverse(int, Node*, Node*);

        // << get node at index >>
        Node* getListIndex(int);

        // << delete extra occurrences >>
        void deleteExtraOccurrences(int);
        void deleteExtraOccurrences(int, int, Node*);
    
		LinkedList(); // Default constructor sets head to null
	        void insert(int); // insert int into list 
        	Node* find(int); // find int in list, and return pointer to node with that int. If there are multiple copies, this only finds one copy
        	Node* find(int, Node*); // recursive find 
        	Node* deleteNode(int); // remove a node with int (if it exists), and return pointer to deleted node. This does not delete all nodes with the value.
        	Node* deleteNode(int, Node*, Node*); // recursive remove
		void deleteList(); // deletes every node to prevent memory leaks, and frees memory
		void deleteList(Node*); // recursive delete 
		string print(); // Construct string with data of list in order 
		string print(Node*); // recursive construct string
		int length(); // Returns the length of the linked list
		int length(Node*); // recursive length computation
};

#endif
