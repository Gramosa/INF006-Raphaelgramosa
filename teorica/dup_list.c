//compilacao: gcc dup_list.c -o dup_list && ./dup_list

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
  int key;
  struct Node* next;
  struct Node* prev;
} Node;

typedef struct DupList{
  Node* head;
  Node* tail;
  int size;
} DupList;

Node* create_node(int value){
  Node* node = malloc(sizeof(Node));
  node->key = value;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

DupList* create_list(){
  DupList* list = malloc(sizeof(DupList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void destroy_list(DupList* list){
  if(list == NULL){
    return;
  }
  Node* n = list->head;
  while(n != NULL){
    Node* temp = n;
    n = n->next;
    free(temp);
  }
  free(list);
}

bool add(DupList* list, Node* n){
  if(list == NULL || n == NULL){
    return false;
  }
  if(list->head == NULL){
    list->head = n;
  }
  else{
    n->next = list->head;
    list->head->prev = n;
    list->head = n;
  }

  list->size++;
  return true;
}

bool delete(DupList *list, int key){
  if(list == NULL || list->head == NULL){
    return false;
  }
  Node* n = list->head;
  while(n != NULL){
    if(n->key == key){
      if(n->prev == NULL){
        list->head = n->next;
      }
      else{
        n->prev->next = n->next;
      }
      
      free(n);
      list->size--;
      return true;
    }
    
    n = n->next;
  }

  return false;
}

Node* search(DupList* list, int key){
  Node* n = list->head;
  while(n != NULL && n->key != key){
    n = n->next;
  }
  return n;
}

void show_list(DupList* list){
  if(list == NULL){
    return;
  }
  printf("[");
  Node* n = list->head;
  while(n != NULL){
    printf(" %d", n->key);
    n = n->next;
  }
  printf(" ]\n");
}

int main(int argc, char *argv[]){
  DupList* list = create_list();
  for(int i = 0; i < 10; i++){
    add(list, create_node(i));
  }
  printf("Lista inicialemente: ");
  show_list(list);

  if(add(list, create_node(-1))){
    printf("Numero -1 adicionado na lista\n");
    show_list(list);
  }
  if(search(list, -1) != NULL){
    printf("Numero -1 esta presente na lista\n");
    show_list(list);
  }
  if(delete(list, -1)){
    printf("Numero -1 deletado da lista\n");
    show_list(list);
  }

  //error handling tests
  if(!search(list, 999)){
    printf("Numero 999 nao encontrado na lista\n");
    show_list(list);
  }
  if(!delete(list, 999)){
    printf("Erro ao deletar o numero 999 na lista\n");
    show_list(list);
  }

  printf("Situacao final da lista: ");
  show_list(list);

  destroy_list(list);
}