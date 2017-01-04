

#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

/*Prototypes*/
int   push    (node*, void*);
void* pop     (node**, void*);
int   contains(node*, void*);
void  destroy (node*);

/*Implementations*/
node* linked_list_init(void* payload, size_t size, int (*compare)(void*, void*),
		       void (*print)(node*) ){
  //malloc memory for new node
  node* n = (node*) malloc(sizeof(node));
  if(n == NULL) return NULL;
  n -> payload = (void*) malloc(size);
  if(n -> payload == NULL) return NULL;
  //set all members
  memcpy(n->payload, payload, size);
  n -> size     = size;
  n -> next     = NULL;
  n -> push     = push;
  n -> pop      = pop;
  n -> compare  = compare;
  n -> contains = contains;
  n -> print    = print;
  n -> destroy  = destroy;

  return n;
}


int push(node* n, void* p){
  while( n-> next !=NULL) n = n->next;
  n -> next = linked_list_init(p, n-> size, n-> compare, n->print);
  if( n->next == NULL ) return -1; 
  return 1;
}

void* pop(node** n, void* dst){
  memcpy( (*n)->payload, dst, (*n)->size);
  free( (*n) -> payload );
  node* new_head = (*n)-> next;
  free(*n);
  *n = new_head;
  return dst;
}

int contains(node* n, void* p){
  while( n -> next != NULL ){
    if( n->compare(n->payload, p) )return 1;
    n = n -> next;
  }
  return 0;
}

void destroy(node* n){
  while(n != NULL ){
    free( n-> payload );
    node* next_node = n -> next;
    free( n );
    n = next_node;
  }
}
