//compilacao: gcc uni_list.c -o uni_list && ./uni_list

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
	int key;
	struct Node* next;
} Node;

typedef struct UniList{
	Node* head;
	int size;
} UniList;

Node* create_node(int value){
	Node* node = malloc(sizeof(Node));
	node->key = value;
	node->next = NULL;
	return node;
}

UniList* create_list(){
	UniList* list = malloc(sizeof(UniList));
	list->head = NULL;
	list->size = 0;
	return list;
}

void destroy_list(UniList* list){
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

bool add(UniList* list, Node* n, int index){
	if(list == NULL || n == NULL){
		return false;
	}
  //Corrige o indice negativo, contando do final da lista
	if(index < 0){
		index = (list->size + 1) + index;
    if(index < 0){
      return false;
    }
	}
	if(index > list->size){
		return false;
	}
	if(index == 0){
		n->next = list->head;
		list->head = n;
	}
	else{
		Node* temp_n = list->head;
		//index-1 para pegar o node anterior a posicao que sera adicionada
		for(int i = 0; i < index-1; i++){
			temp_n = temp_n->next;
		}
		n->next = temp_n->next;
		temp_n->next = n;
	}
	
	list->size++;
	return true;
}

bool delete(UniList *list, int key){
  if(list == NULL || list->head == NULL){
    return false;
  }
  Node* prev = NULL;
  Node* n = list->head;
  while(n != NULL){
    if(n->key == key){
      if(prev == NULL){
        list->head = n->next;
      }
      else{
        prev->next = n->next;
      }
      free(n);
      list->size--;
      return true;
    }

    prev = n;
    n = n->next;
  }

  return false;
}

Node* search(UniList* list, int key){
	Node* n = list->head;
	while(n != NULL && n->key != key){
		n = n->next;
	}
	return n;
}



void show_list(UniList* list){
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
	UniList* list = create_list();
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