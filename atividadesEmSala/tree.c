#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
  int key;
  struct Node *p; //parent
  struct Node *l; //left
  struct Node *r; //right
} Node;

typedef struct Tree{
  Node* root;
} Tree;

Node* create_node(int key){
  Node *n = malloc(sizeof(Node));
  n->key = key;
  n->p = NULL;
  n->l = NULL;
  n->r = NULL;
  return n;
}

Tree* create_tree(Node *root){
  Tree *t = malloc(sizeof(Tree));
  t->root = root;
  return t;
}

bool insert(Tree *t, Node *node){
  if(t == NULL || node == NULL){
    return false;
  }
  if(t->root == NULL){
    t->root = node;
  }
  else{
    Node *previous = NULL;
    Node *current = t->root;
    while(current != NULL){
      previous = current;
      if(current->key > node->key){
        current = current->l;
      }
      else{
        current = current->r;
      }
    }
    if(previous->key > node->key){
      previous->l = node;
    }
    else{
      previous->r = node;
    }
    node->p = previous;
  }

  return true;
}

Node* get_sucessor(Node *n){
  return NULL;
}

bool delete(Tree *t, Node *n){
  if(t == NULL || n == NULL){
    return false;
  }
  // if(n->p != NULL){
  //   Node *p = n->p;
  //   if(n->key < p->key){
  //     p->l = n;
  //   }
  //   else{
  //     p->r = n;
  //   }
    
  // }
  if(n->l != NULL){
    n->l->p = n->p;
    n->l->r = n->r;
  }
  else if(n->r != NULL){
    Node *prev = NULL;
    Node *temp = n->r;
    while(temp != NULL){
      prev = n;
      temp = temp->l;
    }
    prev->p = n->p;
    prev->l = n->l;
    
  }
  return true;
}

int main(){
  Tree *tree = create_tree(create_node(5));

  
  
  return 0;
}