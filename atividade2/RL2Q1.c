//gcc RL2Q1.c -o q1 && ./q1
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
  int height;
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
  n->height = 0;

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
  n->height++;
  
  if(n->key < p->key){
    if(p->l == NULL){
      n->p = p;
      p->l = n;
    }
    else{
      add_node(p->l, n);
    }
  }
  else{
    if(p->r == NULL){
      n->p = p;
      p->r = n;
    }
    else{
      add_node(p->r, n);
    }
  }
}

void add(Tree *t, Node *n, FILE *save_file){
  if(t == NULL && n == NULL){
    return;
  }
  if(t->root == NULL){
    t->root = n;
    fprintf(save_file, "%d", 0);
  }
  else{
    add_node(t->root, n);
    fprintf(save_file, " %d", n->height);
  }
}

Node* get_max_node(Tree *t){
  if(t == NULL && t->root == NULL){
    return NULL;
  }
  Node *p = NULL;
  Node *n = t->root;
  while(n != NULL){
    p = n;
    n = n->r;
  }

  return p;
}

Node* get_parent(Node *n){
  if(n == NULL){
    return NULL;
  }

  return n->p;
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
  FILE* read_file = fopen("L2Q1.in", "r");
  FILE* save_file = fopen("L2Q1.out", "w");
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

      add(t, create_node(value), save_file);
    }
    //Salvamento no arquivo
    Node* max_node = get_max_node(t);
    fprintf(save_file, " max %d alt %d", max_node->key, max_node->height);

    Node* parent = get_parent(max_node);
    fprintf(save_file, " pred");
    if(parent == NULL){
      fprintf(save_file, " NaN");
    }
    else{
      fprintf(save_file, " %d", parent->key);
    }

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