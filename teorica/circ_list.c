//compilacao: gcc circ_list.c -o circ_list && ./circ_list
//nao funcional

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
  int key;
  struct Node* next;
} Node;

typedef struct CircList{
  Node* head;
  Node* tail;
  int size;
} CircList;

Node* create_node(int value){
  Node* node = malloc(sizeof(Node));
  node->key = value;
  node->next = node;
  return node;
}

CircList* create_list(){
  CircList* list = malloc(sizeof(CircList));
  list->head = NULL;
  list->size = 0;
  return list;
}

void destroy_list(CircList* list){
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

bool add(CircList* list, Node* n){
  if(list == NULL || n == NULL){
    return false;
  }
  if(list->head == NULL){
    list->head = n;
    list->tail = n;
  }
  else{
    n->next = list->head;
    list->head = n;
    list->tail->next = n;
  }

  list->size++;
  return true;
}

bool delete(CircList* list, Node* n){
  if(list == NULL || n == NULL){
    return false;
  }
  if(list->head == n){
    if(list->head == list->tail){
      list->head = NULL;
      list->tail = NULL;
    } 
    else {
      list->head = n->next;
      list->tail->next = list->head;
    }
  } 
  else {
    Node* temp = list->head;
    while(temp->next!= n){
      temp = temp->next;
    }
    temp->next = n->next;
    if(n == list->tail){
      list->tail = temp;
    }
  }
  free(n);
  list->size--;
  return true;
}

Node* search(CircList* list, int key){
  Node* n = list->head;
  while(n != list->tail && n->key != key){
    n = n->next;
  }
  return n;
}

void show_list(CircList* list){
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
  CircList* list = create_list();
  for(int i = 0; i < 10; i++){
    add(list, create_node(i), -1);
  }
  printf("Lista inicialemente: ");
  show_list(list);

  if(add(list, create_node(-1), 2)){
    printf("Numero -1 adicionado na posicao 2 da lista\n");
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
  if(!add(list, create_node(999), 12)){
    printf("Erro ao adicionar o numero 999 a lista\n");
    show_list(list);
  }
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