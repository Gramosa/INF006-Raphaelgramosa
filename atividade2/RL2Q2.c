//gcc RL2Q2.c -o q2 && ./q2
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen, strtol
#include <stdbool.h>

#define MAX_SIZE_LINE 10000

typedef struct Node{
  int key;
  struct Node *p; //parent
  struct Node *l; //left
  struct Node *r; //right
} Node;

typedef struct Tree{
  Node *root;
} Tree;

Node* create_node(int key){
  Node* n = malloc(sizeof(Node));
  n->key = key;
  n->p = NULL;
  n->l = NULL;
  n->r = NULL;

  return n;
}

void destroy_node(Node *n){
  if(n == NULL){
    return;
  }

  destroy_node(n->l);
  destroy_node(n->r);
  free(n);
}

Tree* create_tree(){
  Tree* t = malloc(sizeof(Tree));
  t->root = NULL;

  return t;
}

void destroy_tree(Tree *t){
  if(t == NULL){
    return;
  }
  destroy_node(t->root);
  free(t);
}

void add_node(Node *p, Node *n){
  if(n->key < p->key){
    if(p->l == NULL){
      n->p = p;
      p->l = n;
    }
    else{
      add_node(p->l, n);
    }
  }
  else if(n->key > p->key){
    if(p->r == NULL){
      n->p = p;
      p->r = n;
    }
    else{
      add_node(p->r, n);
    }
  }
  else{
    destroy_node(n);
  }
}

void add(Tree *t, Node *n){
  if(t == NULL && n == NULL){
    return;
  }
  if(t->root == NULL){
    t->root = n;
  }
  else{
    add_node(t->root, n);
  }
}

Node* get_min_node(Tree *t){
  if(t == NULL && t->root == NULL){
    return NULL;
  }
  Node *p = NULL;
  Node *n = t->root;
  while(n != NULL){
    p = n;
    n = n->l;
  }

  return p;
}

int sum_tree(Node *n){
  if(n == NULL){
    return 0;
  }

  return sum_tree(n->l) + sum_tree(n->r) + n->key;
}

void write_tree_in_order(Node *n, Node* min_node, FILE *save_file){
  if(n == NULL){
    return;
  }

  write_tree_in_order(n->l, min_node, save_file);

  int diff = sum_tree(n->r) - sum_tree(n->l);
  if(n == min_node){
    fprintf(save_file, "%d (%d)", n->key, diff);
  }
  else{
    fprintf(save_file, " %d (%d)", n->key, diff);
  }
  
  write_tree_in_order(n->r, min_node, save_file);
}

// O ultimo token não é retornado caso a string não finalize no delim, mas fica
// salvo no cursor "1 12 123 A Abc" -> retorna a cada chamada 1, 12, 123, A. No
// final Abc fica salvo em **cursor
char *custom_strsep(char **cursor, char delim) {
  if (cursor == NULL || *cursor == NULL) {
    printf("Bug, ponteiro NULL ou apontando para NULL");
    return NULL;
  }

  char *begin = *cursor;
  while (**cursor != '\0') {
    if (**cursor == delim) {
      **cursor = '\0';
      (*cursor)++; // Move para uma posicao depois do delimitador
      return begin;
    }
    (*cursor)++;
  }

  return NULL;
}

bool has_char(const char *str, const char target) {
  while (*str != '\0') {
    if (*str == target) {
      return true;
    }
    str++;
  }

  return false;
}

int main() {
  FILE* read_file = fopen("L2Q2.in", "r");
  FILE* save_file = fopen("L2Q2.out", "w");
  if(read_file == NULL){
    printf("Erro ao ler o arquivo de leitura\n");
    return 1;
  }
  if(save_file == NULL){
    printf("Erro ao ler o arquivo de salvamento\n");
    return 1;
  }

  char line[MAX_SIZE_LINE];

  while(fgets(line, MAX_SIZE_LINE, read_file) != NULL){
    //Variavel para agir como cursor da linha
    char *c = line;
    //Variavel para receber o item
    char *token = NULL;
    //Para nao adicionar o \n na ultima linha
    bool is_last_line = false;

    //Troca o '\n' do final por um ' ', para lidar com o ultimo token. Caso não tenha empurra o \0 para frente e e adiciona um ' '
    if(has_char(line, '\n')){
      line[strlen(line) - 1] = ' ';
    }
    else{
      long size = strlen(line);
      line[size] = ' ';
      line[size + 1] = '\0';
      is_last_line = true;
    }

    //Criação das estruturas, unicas para cada linha do arquivo
    Tree *t = create_tree();

    while ((token = custom_strsep(&c, ' ')) != NULL) {
      int value = strtol(token, NULL, 10);

      add(t, create_node(value));
    }
    //Salvamento no arquivo
    //Supondo que não havera arvores vazias...
    write_tree_in_order(t->root, get_min_node(t), save_file);

    if(!is_last_line){
      fprintf(save_file, "\n");
    }

    //Destruicao das estruturas
    destroy_tree(t);
  }
  fclose(read_file);
  fclose(save_file);
  return 0;
}