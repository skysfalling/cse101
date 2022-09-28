
/*
9/26/2022

Given a word w
    1 - Find: if w is already present
	======= RECURSIVE IMPLEMENTATION ======
	Find (val)
		1. check if head -> data is val
		2. if not, recursively find it starting from head -> next


	Node* FIND(int val){
		//return a pointer with data = val
		//return NULL if val is not present
	
		return Find(val, head);
	}

	Node* Find(int val, Node* start){
		
		if (start = null){
			return NULL;
		}
		if (start->data == vall){
			return start;
		}

		return find(val, start->next);
	}

	<< PRINT >>
	void print(){
		while (curr != null){
			printf(curr->data);
			curr = curr->next;
		}
	}	

    2 - Update: frequency of the word
    3 - Indert: if w is not present
    4 - Delete: remove w from the list

LINKED LIST
1. Allocated exactly the right amount of memory
2. We do not need to know this during setup
3. It does not have to use continuous memory

RECURSIVE IMPLEMENTATION
Find (val)
	1. check if head -> data is val
	2. if not, recursively find it starting from head -> next





*/


#include <stdio.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList{
    Node *head;
} LinkedList;

int main(void) {
    // Write C code here
    printf("Hello world\n");

    return 0;
}
