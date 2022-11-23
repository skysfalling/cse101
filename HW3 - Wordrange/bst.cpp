// Filename: bst.cpp
// 
// Contains the class BST that represents a binary search tree. This contains some basic operations, such as insert, delete, find, and printing in various traversal orders
// 
// C. Seshadhri, Jan 2020

#include "bst.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

// Default constructor sets head and tail to null
BST :: BST()
{
	root = NULL;
  range_query = 0;
}

// Insert(int val): Inserts the int val into tree, at the head of the list. Note that there may be multiple copies of val in the list. Just calls the recursive function
// Input: Int to insert into the BST
// Output: Void, just inserts new Node
void BST :: insert(string word)
{
    Node *to_insert = new Node(word); // create a new Node with the value val
    if (root == NULL) // tree is currently empty
    {
        root = to_insert; // make new node the root
    }
    else
    {
        insert(root,to_insert); // make call to recursive insert, starting from root

        //cout << "  ++ parent of insert: " << to_string(to_insert->parent->key) << endl;
    }
}

// insert(Node* start, Node* to_insert): Inserts the Node to_insert into tree rooted at start. We will always call with start being non-null. Note that there may be multiple copies of val in the list. 
// Input: Int to insert into the subtree
// Output: Void, just inserts new Node
void BST :: insert(Node* start, Node* to_insert)
{
    if (start == NULL) // in general, this should not happen. We never call insert from a null tree
        return;
    if (to_insert->word <= start->word) // inserted node has smaller (or equal) key, so go left
    {
        if(start->left == NULL)
        {
            start->left = to_insert; // make this node the left child
            to_insert->parent = start; // set the parent pointer
            return;
        }
        else // need to make recursive call
        {
            insert(start->left, to_insert);
            return;
        }
    }
    else // inserted node has larger key, so go right
    {
        if(start->right == NULL)
        {
            start->right = to_insert; // make this node the right child
            to_insert->parent = start; // set the parent pointer
            return;
        }
        else // need to make recursive call
        {
            insert(start->right, to_insert);
            return;
        }
    }
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void BST :: deleteBST()
{
    deleteBST(root);
}

// Deletes every Node in subtree rooted at startto prevent memory leaks.
// Input: Node* start
// Output: Void, just deletes every Node of the list
void BST :: deleteBST(Node* start)
{
    if(start == NULL) // tree is already empty
        return; 
    deleteBST(start->left); // delete left subtree
    deleteBST(start->right); // delete right subtree
    delete(start); // delete node itself
}
    
// ====================== HW3 ==================

int BST :: rangeCount(string k1, string k2)
{
  //cout << "find range between " << k1 << " , " << k2 << endl;

  range_query = 0;
  recRangeCount(root, k1, k2);

  return range_query;

}

void BST :: recRangeCount(Node* root, string k1, string k2)
{
    /* base case */
    if (root == NULL )
    {
        return;
    }
     
    /* search left subtree */
    if ( k1 < root->word )
    {
        recRangeCount(root->left, k1, k2);
    }
     
    /* if root's data lies in range, then prints root's data */
    if ( k1 <= root->word && k2 >= root->word )
    {
      range_query += 1;

      //cout << "  ++ found " << to_string(root->key);
      //cout << " // range count: " << to_string(range_query) << endl;
    }
     
    /* recursively call the right subtree */
    recRangeCount(root->right, k1, k2);
}

int BST :: rangeCount(int k1, int k2)
{
  //cout << "find range between " << to_string(k1) << " , " << to_string(k2) << endl;

  range_query = 0;
  recRangeCount(root, k1, k2);

  return range_query;

}

void BST :: recRangeCount(Node* root, int k1, int k2)
{
    /* base case */
    if (root == NULL )
    {
        return;
    }
     
    /* search left subtree */
    if ( k1 < root->key )
    {
        recRangeCount(root->left, k1, k2);
    }
     
    /* if root's data lies in range, then prints root's data */
    if ( k1 <= root->key && k2 >= root->key )
    {
      range_query += 1;

      //cout << "  ++ found " << to_string(root->key);
      //cout << " // range count: " << to_string(range_query) << endl;
    }
     
    /* recursively call the right subtree */
    recRangeCount(root->right, k1, k2);
}

