#ifndef __LINKED_LIST_GUARD_
#define __LINKED_LIST_GUARD_
#include<stdlib.h>

//FIFO implementation
typedef struct node_t{
  //basically anything right
  void*  payload;
  //size of payload datatype
  size_t size;
  struct node_t* next;
  //pushes new node in head position
  int   (*push) (struct node_t*, void*);
  //pops head node
  void* (*pop)  (struct node_t**, void*);
  //supplied to the init function
  //expects 1 for equal, 0 for not equal
  //TODO - should this be renamed "equals"?
  int   (*compare)  (void*, void*);
  //returns 1 for contains, 0 for not
  int   (*contains) (struct node_t*, void*);
  //supplied to the init function
  void  (*print)    (struct node_t*);
  //free's all memory allocated for list
  //note: supply head node, else leak is imminent
  void  (*destroy)  (struct node_t*);
}node;

//equivalent of constructor 
node* linked_list_init(void* payload, size_t size, int (*compare)(void*, void*),
			 void (*print)(node*));

#endif
