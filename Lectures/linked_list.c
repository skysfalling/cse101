/*


LINKED LIST IMPLEMENTATION
 >> using code from CSE13 midterm

*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


// A linked list of floating point numbers.
typedef struct LLfloat {
  float val;
  struct LLfloat *next;
} LLfloat;


// << ADD TO LIST >>
LLfloat *add_to_list (LLfloat *top, float val) {
  
  // create new part of list with value and next index
  LLfloat *newfront = calloc(1, sizeof(LLfloat));
  newfront->val = val;
  newfront->next = top;

  return newfront;
}

// << PRINT LINKED LIST >>
void print_list(LLfloat *top){

  // set cur node to top of list
  LLfloat *cur_node = top;

  //cur node item value
  printf(" top value address: %p // value:%f // next: %p\n", (void *)cur_node , cur_node->val,(void*)cur_node->next);
  
  int endofstack = 0; //end of stack = false

  //iterate through stack
  for (int i = 1; endofstack  == 0; i ++)
  {
    // if next node not null
    if (cur_node->next != NULL){
      cur_node = cur_node->next; //set cur node to next
      printf(" index %d // address: %p // value:%f // next: %p\n", i, (void*)cur_node , cur_node->val, (void*)cur_node->next); //cur node item value
    }
    // else kill loop
    else {endofstack = 1; printf("    ** end of list **\n"); }
      
  }
}

int main(void){

  // create top
  LLfloat *top = calloc(1, sizeof(LLfloat));
  top->val = 10;
  top->next = NULL;
  
  // create list from top  
  for (int i = 0; i < 5; i++)
  {
    top = add_to_list(top, top->val + 1); 
  }

  print_list(top);

  return 0;

}






