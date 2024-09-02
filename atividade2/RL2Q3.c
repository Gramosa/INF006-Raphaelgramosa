//gcc RL2Q3.c -o q3 && ./q3
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

Node* get_min_node(Node *n){
  Node *p = NULL;
  while(n != NULL){
    p = n;
    n = n->l;
  }

  return p;
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

Node* search_node(Node* n, int key){
  if(n == NULL || n->key == key){
    return n;
  }

  if(key < n->key){
    return search_node(n->l, key);
  }
  else{
    return search_node(n->r, key);
  }
}

// Função auxiliar para atualizar a altura de um nó
void update_height(Node *node) {
  if (node) {
    // Atualiza a altura com base na altura do pai
    node->height = (node->p) ? node->p->height + 1 : 0;
  }
}

// Função para remover um nó dado um ponteiro para a estrutura Tree e o nó a ser removido
void remove_node(Tree *tree, Node *node_to_remove) {
  if (node_to_remove == NULL) {
    return;
  }

  Node *parent = node_to_remove->p;

  // Caso 1: O nó a ser removido não tem filho esquerdo
  if (node_to_remove->l == NULL) {
    Node *temp = node_to_remove->r;
    if (parent) {
      if (parent->l == node_to_remove) {
        parent->l = temp;
      } else {
        parent->r = temp;
      }
    } else {
      // Atualize a raiz se o nó a ser removido for a raiz
      tree->root = temp;
    }
    if (temp) {
      temp->p = parent;
      // Atualiza a altura do nó substituto
      update_height(temp);
    }
    free(node_to_remove);
  }
  // Caso 2: O nó a ser removido não tem filho direito
  else if (node_to_remove->r == NULL) {
    Node *temp = node_to_remove->l;
    if (parent) {
      if (parent->l == node_to_remove) {
        parent->l = temp;
      } else {
        parent->r = temp;
      }
    } else {
      // Atualize a raiz se o nó a ser removido for a raiz
      tree->root = temp;
    }
    if (temp) {
      temp->p = parent;
      // Atualiza a altura do nó substituto
      update_height(temp);
    }
    free(node_to_remove);
  }
  // Caso 3: O nó a ser removido tem dois filhos
  else {
    // Encontre o sucessor (o menor nó na subárvore direita)
    Node *successor = get_min_node(node_to_remove->r);

    // Copie os dados do sucessor para o nó a ser removido
    node_to_remove->key = successor->key;

    // Remova o sucessor
    remove_node(tree, successor);
  }

  // Atualize as alturas dos nós ancestrais a partir do nó pai
  Node *current = parent;
  while (current) {
    update_height(current);
    current = current->p;
  }
}

void write_tree_in_order(Node *n, Node *min_node, FILE *save_file){
  if(n == NULL){
    return;
  }

  write_tree_in_order(n->l, min_node, save_file);

  if(n == min_node){
    fprintf(save_file, "%d (%d)", n->key, n->height);
  }
  else{
    fprintf(save_file, " %d (%d)", n->key, n->height);
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
  FILE* read_file = fopen("L2Q3.in", "r");
  FILE* save_file = fopen("L2Q3.out", "w");
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

    //flag de token
    bool is_add = true;
    while ((token = custom_strsep(&c, ' ')) != NULL) {
      if(*token == 'a'){
        is_add = true;
      }
      else if(*token == 'r'){
        is_add = false;
      }
      else{
        int value = strtol(token, NULL, 10);

        if(is_add){
          //printf("valor adicionado normal: %d\n", value);
          add(t, create_node(value));
        }
        else{
          Node *n = search_node(t->root, value);
          if(n != NULL){
            //printf("valor removido: %d\n", value);
            remove_node(t, n);
          }
          else{
            //printf("valor adicionado por r: %d\n", value);
            add(t, create_node(value));
          }
        }
      }
    }
    //printf("\n");
    //Salvamento no arquivo
    write_tree_in_order(t->root, get_min_node(t->root), save_file);

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