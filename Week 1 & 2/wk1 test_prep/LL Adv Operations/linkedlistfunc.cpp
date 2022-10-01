// Filename: linkedlist.cpp
// Contains Helper Functions for linkedlist
// ( constructor, insert, find, deleteNode, deleteList, print, length )
// 
// Also contains Test Prep Adv Operations
// -- 

#include "linkedlistfunc.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
using namespace std;


// <<<<<< DELETE SPECIFIC NODE >>>>>>>

// deleteNode(Node* node) : deletes a specific Node and connects that Node's prev and next Nodes 
// Input : Node to delete
// Output : Void , just deletes Node 
void LinkedList :: deleteNode(Node* node)
{
    // base case, node has to be real value
    if (node == NULL)
    	return;
    else
        if (node->prev == NULL) // prev was supposed to be pointer of previous node. Since prev is NULL, curr is the head
            head = head->next; // move head pointer to next value
        else
            node->prev->next = node->next; // delete curr from the list, by "skipping" over curr
        
	node->next = NULL; // set the next pointer to NULL, to prevent dangling references
	delete(node); // delete given node
}



// <<<<<< DELETE Kth OCCURENCE >>>>>>>

// deleteOccurrence(int val, int occ_count) : Deletes a specific occurence of the given value.
// Input: Value to check , Occurrence count to delete
//      -- if input occurrence is "-1", find last occurence
// Output: Void, just deletes Node
// Wrapper for recursive function
void LinkedList :: deleteOccurrence(int val, int occ_count)
{
    // check if occ_count is valid
    if (occ_count == 0)
    {
        throw std::invalid_argument("Cannot delete 0th occurence of a value");
        return;
    }    

    // check if deleteLastOccurrence
    if (occ_count == -1)
        deleteLastOccurrence(val, head, NULL);
    else
        deleteOccurrence(val, occ_count, head); // call recursive function
}

// deleteOccurrence(int val, int occ_count, Node *curr) : Deletes a specific occurence of the given value.
// -- The occurence value will subtract one from itself for every occurence that is found in the Linked List
//    Once the value reaches 0, the function will delete that Node 
// Input: Value to check , Occurrence count to delete, curr node in recursion
// Output: Void, just deletes Node
// Recursive function to find and delete specific occurence of node
void LinkedList :: deleteOccurrence(int val, int occ_count, Node *curr)
{
    if (curr == NULL) // base case, end of list or list is empty
        return;

    if (curr->data == val) // curr node has val
        occ_count -= 1; // subtract one from occurence count
	
	// ** OCCURENCE FOUND **
	if (occ_count == 0){
        deleteNode(curr);
		return;	
	}
    
    deleteOccurrence(val, occ_count, curr->next); // recursive call to list starting from next node
}

// deleteLastOccurence(int val, Node *curr, Node* delNode)
// Input : Value to check, curr node in recursion, node to delete once finished`
// Output : Void , just deletes node
// Recursive Function to delete last occurrence of node

void LinkedList :: deleteLastOccurrence(int val, Node* curr, Node* delNode)
{
    // << CHECK FOR END OF LIST >>
    if (curr == NULL) // end of list or list is empty
    {
        if (delNode != NULL) // if delNode is valid, delete
        {
           deleteNode(delNode); 
        }
        return;
    }

    // << SET delNode IF VALUE IS SAME >>
    if (curr->data == val)
    {
        delNode = curr;
    }

    deleteLastOccurrence(val, curr->next, delNode);
}


// <<<<<<<<<<<<<<<<<< REVERSE LINKED LIST >>>>>>>>>>>>>>>>>>>>>>

// TODO :  fix printing of list, currently printing last node of reversed list

// reverse(Node* head)
// Input : head node to start from, recursively uses this node as curr
// Output : after recursion, returns new head of list

Node* LinkedList :: reverse(Node* curr)
{
    if (curr == NULL || curr->next == NULL)
    {
        cout << "-- reverse : new head" + to_string(curr->data) << endl;
        head = curr; // ** SET LIST HEAD TO CURR **
        return curr;
    }

    /* reverse the rest of the list and put the first element at the end */
    Node* rest = reverse(curr->next);
    curr->next->next = curr;

    //cout << "rest : " + to_string(rest->data) << endl;


    // remove lingering pointer to incorrect node
    // ( just placed node at end of list so currently it doesn't point to anything)
    curr->next = NULL;

    // return the new head node
    return rest;
}






// ===================================================================================
// ================================ GIVEN HELPER FUNCTIONS ===========================
// ===================================================================================

// Default constructor sets head and tail to null
LinkedList :: LinkedList()
{
	head = NULL;
}


// <<<<<<<<< INSERT >>>>>>>>>>>

// Insert(int val): Inserts the int val into list, at the head of the list. Note that there may be multiple copies of val in the list.
// Input: Int to insert into the linked list
// Output: Void, just inserts new Node
// Simply calls recursive function
void LinkedList :: insert(int val)
{
    Node *to_add = new Node; // creates new Node
    to_add->data = val; // sets the data to hold input val

    if (head != NULL)
    	head->prev = to_add; // set curr head prev node to new node
	
    to_add->next = head; // make to_add point to existing head
    head = to_add; // set head to to_add

    //cout << "<< TEST : head (" + to_string(head->data) + ") -> next (" + to_string(head->next->data) + ")" << endl; 
    cout << "  >> HEAD : " + to_string(head->data) << endl;

    if (head->next != NULL)
        cout << "  >> NEXT : " + to_string(head->next->data) << endl;
}


// <<<<<<<<<< FIND FIRST VALUE >>>>>>>>>>

// find(int val): Finds a Node with data "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Just a wrapper to recursive function
Node* LinkedList :: find(int val)
{
    return find(val, head); // just call recursive function
}

// find(int val, Node* curr): Finds a Node with data "val", at list starting from curr
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node in the list containing val
Node* LinkedList :: find(int val, Node *curr)
{
    if (curr == NULL) // base case, list is empty
        return NULL;
    if (curr->data == val) // curr node has val
        return curr;
    else
        return find(val, curr->next); // recursive call to list starting from next node
}





// <<<<<<<< DELETE FIRST NODE WITH VALUE >>>>>>>>>

// deleteNode(int val): Delete a Node with data val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node* LinkedList :: deleteNode(int val)
{
    return deleteNode(val, NULL, head); // recursive call. We set prev to NULL, and curr to head
}

// deleteNode(int val, Node* prev, Node* curr): Delete a Node with data val  from the list starting *with* curr. prev stores pointer of previous node, to aid deletion
// Note that we cannot delete curr, so we only look at the list after that. If no node is found, return NULL.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node* LinkedList :: deleteNode(int val, Node *prev, Node* curr)
{
    if (curr == NULL) // base case, val not found, no more list left
        return NULL;
    if (curr->data == val) // val is found! Now for the case analysis
    {
        if (prev == NULL) // prev was supposed to be pointer of previous node. Since prev is NULL, curr is the head
            head = head->next; // delete head
        else
            prev->next = curr->next; // delete curr from the list, by "skipping" over curr
        curr->next = NULL; // set the next pointer to NULL, to prevent dangling references
        return curr; // returning node with val
    }
    return deleteNode(val, curr, curr->next); // proceed one step in the list
}




// <<<<<<<<< DELETE LIST >>>>>>>>>>

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void LinkedList :: deleteList()
{
    deleteList(head);
}


// deleteList(curr): Deletes every Node of list starting from curr to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list starting from curr
void LinkedList :: deleteList(Node *curr)
{
    if (curr == NULL) // base case, empty list
        return; 
    Node *nextNode = curr->next; // store next node
    delete(curr); // delete current node
    deleteList(nextNode); // recursive call
}

// Prints list in order
// Input: None
// Output: string that has all elements of the list in order
string LinkedList :: print()
{
    string to_return = print(head);
    if (to_return.length() > 0) // non-empty string, has extra space at end
        to_return.pop_back(); // delete last character
    return to_return;
}

// print(Node *curr): Prints list in order, starting from curr
// Input: None
// Output: string that has all elements of the list in order
string LinkedList :: print(Node *curr)
{
    if(curr == NULL) // base case, empty list
        return ""; // return empty string
    return to_string(curr->data) + " " + print(curr->next);
}

// Computes the length of the linked list
// Input: None
// Output: Int, length of list
int LinkedList :: length()
{
    return length(head); // recursive call
}

// length(Node *curr): Computes the length of the linked list, starting from curr
// Input: None
// Output: Int, length of list
int LinkedList :: length(Node *curr)
{
    if (curr == NULL) // base case
       return 0;
    return 1+length(curr->next); // recursive call
}
