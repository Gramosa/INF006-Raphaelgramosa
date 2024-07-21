#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List{
    Node *head;
    Node *tail;
} List;

Node* create_node(int k){
    Node* n = malloc(sizeof(Node));
    n->key = k;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

List* create_list(){
    List* l = malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

void add(List* l, Node* n){
    if(l->head == NULL){
        l->head = n;
        l->tail = n;
        return;
    }
    n->next = l->head;
    l->head->prev = n;
    l->head = n;
}

void delete(List *l, Node *x){
    if(x->prev != NULL){
        x->prev->next = x->next;
    }
    else{
        l->head = x->next;
    }
    if(x->next != NULL){
        x->next->prev = x->prev;
    }
    else{
        l->tail = x->prev;
    }
    free(x);
}

Node* search(List *l, int key){
    Node *x = l->head;
    while(x != NULL && x )
}

void show_list(List* l){
    printf("[");
    Node* n = l->head;
    while(n != NULL){
        printf(" %d", n->key);
        n = n->next;
    }
    printf(" ]\n");
}

int main()
{
    Node* no = create_node(1);
    List* list = create_list();
    //Da ruim
    //add(list, no);
    //add(list, no);

    for(int i = 1000; i > 0; i--){
      add(list, create_node(i));
    }


    show_list(list);
    printf("teste");
    return 0;
}