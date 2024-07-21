//cd ~/INF006-Raphaelgramosa/atividade1 && gcc RL1Q3.c -o q3 && ./q3

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen, strtol, strtod

#define MAX_SIZE_LINE 10000

// typedef struct DoubleString{
//   double value;
//   char *str_repr; //string representation
// } DoubleString;

//Node usado na lista circular
typedef struct CircNode{
  double value;
  struct CircNode *next;
} CircNode;

//Lista simplesmente ligada circular
typedef struct CircList{
  CircNode *head;
  CircNode *tail;
  long size;
} CircList;

//Node usado na lista duplamente ligada, alem do valor, tem tambem um pointeiro para uma lista duplamente circular
typedef struct DupNode{
  long value;
  CircList *circ_list;
  struct DupNode *next;
  struct DupNode *prev;
} DupNode;

//Lista duplamente ligada
typedef struct DupList{
  DupNode *head;
  DupNode *tail;
  long size;
} DupList;
 
////
// Funcoes relacionadas a lista circular simplesmente ligada
////
CircNode* create_circ_node(double value){
  CircNode* node = malloc(sizeof(CircNode));
  node->value = value;
  node->next = node;
  return node;
}

CircList* create_circ_list(){
  CircList* list = malloc(sizeof(CircList));
  list->head = NULL;
  list->size = 0L;
  return list;
}

bool add_circ_sorted(CircList *list, CircNode *node){
  if(list == NULL || node == NULL) return false;

  if(list->head == NULL){
    list->head = node;
    list->tail = node;
    list->size = 1;
    return true;
  }

  // Quebra temporariamente a ciclicidade da lista
  list->tail->next = NULL;
  
  CircNode *current = list->head;
  CircNode *previous = NULL;
  while(current != NULL && current->value < node->value){
    previous = current;
    current = current->next;
  }
  if(previous == NULL){
    node->next = list->head;
    list->head = node;
  }
  else if(current == NULL){
    previous->next = node;
    list->tail = node;
  }
  else{
    previous->next = node;
    node->next = current;
  }

  // Transforma a lista em circular novamente
  list->tail->next = list->head;
  list->size++;
  
  return true;
}

void destroy_circ_list(CircList* list){
  if(list == NULL){
    return;
  }

  list->tail->next = NULL;
  CircNode *n = list->head;
  while(n != NULL){
    CircNode* temp = n;
    n = n->next;
    free(temp);
  }
  free(list);
}

////
// Funcoes relacionadas a lista duplamente ligada
////
DupNode* create_dup_node(long value){
  DupNode* node = malloc(sizeof(DupNode));
  node->value = value;
  node->circ_list = create_circ_list();
  node->next = NULL;
  node->prev = NULL;
  return node;
}

DupList* create_dup_list(){
  DupList* list = malloc(sizeof(DupList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0L;
  return list;
}

// Adiciona na posicao ja ordenada
bool add_dup_sorted(DupList *list, DupNode* node){
  if(list == NULL || node == NULL) return false;

  if(list->head == NULL){
    list->head = node;
    list->tail = node;
    return true;
  }
  
  DupNode *current = list->head;
  DupNode *previous = NULL;
  while(current != NULL && current->value < node->value){
    previous = current;
    current = current->next;
  }
  
  if(previous == NULL){
    node->next = list->head;
    current->prev = node;
    list->head = node;
  }
  else if(current == NULL){
    node->prev = list->tail;
    previous->next = node;
    list->tail = node;
  }
  else{
    node->prev = previous;
    node->next = current;
    previous->next = node;
    current->prev = node;
  }
  
  return true;
}

void destroy_dup_list(DupList* list){
  if(list == NULL){
    return;
  }
  DupNode* n = list->head;
  while(n != NULL){
    DupNode* temp = n;
    n = n->next;
    free(temp->circ_list);
    free(temp);
  }
  free(list);
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

long custom_strcmp(const char *string1, const char *string2) {
  long i = 0;
  while (string1[i] != '\0' && string2[i] != '\0') {
    if (string1[i] != string2[i]) {
      return string1[i] - string2[i];
    }
    i++;
  }
  return string1[i] - string2[i];
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

double custom_fabs(double value){
  if(value < 0){
    value *= -1;
  }

  return value;
}

int main(){
  FILE *read_file = fopen("L1Q3.in", "r");
  FILE *save_file = fopen("L1Q3.out", "w");
  if (read_file == NULL) {
    printf("Erro ao ler o arquivo de leitura\n");
    return 1;
  }
  if (save_file == NULL) {
    printf("Erro ao ler o arquivo de salvamento\n");
    return 1;
  }

  char line[MAX_SIZE_LINE];

  while (fgets(line, MAX_SIZE_LINE, read_file) != NULL) {
    // Variavel para agir como cursor da linha
    char *c = line;
    // Variavel para receber o item
    char *token = NULL;
    //Flags 
    //Para nao adicionar o \n na ultima linha
    bool is_last_line = false;
    //Para saber quando comeca os valores das listas duplamente ligadas
    bool is_double = false;

    // Troca o '\n' do final por um ' ', para lidar com o ultimo token. Caso não
    // tenha empurra o \0 para frente e e adiciona um ' '
    // Rotina especifica
    if(has_char(line, '\n')){
      line[strlen(line) - 1] = ' ';
    }
    else{
      long size = strlen(line);
      line[size] = ' ';
      line[size + 1] = '\0';
      is_last_line = true;
    }

    //Criacao das estruturas
    DupList *dup_list = create_dup_list();

    
    //Loop que trata o token
    while ((token = custom_strsep(&c, ' ')) != NULL) {
      if(custom_strcmp(token, "LE") == 0){
        is_double = false;
      }
      else if(custom_strcmp(token, "LI") == 0){
        is_double = true;
      }
      else{
        if(!is_double){
          long value = strtol(token, NULL, 10);
          DupNode *node = create_dup_node(value);
          add_dup_sorted(dup_list, node);
        }
        else{
          //Flags do token
          bool was_added = false;
          
          double value = strtod(token, NULL);
          CircNode *node = create_circ_node(value);

          //Loop para encontrar em qual lista circular adicionar o node
          DupNode *current = dup_list->head;
          while(current != NULL){
            //0.00000001 devido ao problema de flutuacao com numeros double
            if(custom_fabs(current->value - value) <= 0.99 + 0.00000001){
              add_circ_sorted(current->circ_list, node);
              was_added = true;
              break;
            }
            current = current->next;
          }

          if(!was_added){
            free(node);
          }
        }
      }
    }

    //Salvamento no arquivo
    fprintf(save_file, "[");
    DupNode *current = dup_list->head;
    while(current != NULL){
      fprintf(save_file, "%ld(", current->value);
      
      CircList *current_circ = current->circ_list;
      long circ_size = current_circ->size;
      CircNode *node = current_circ->head;
      while(circ_size > 0){
        fprintf(save_file, "%.15g", node->value);
        if(circ_size != 1){
          fprintf(save_file, "->");
        }

        node = node->next;
        circ_size--;
      }
      
      fprintf(save_file, ")");
      if(current->next != NULL){
        fprintf(save_file, "->");
      }
      current = current->next;
    }
    fprintf(save_file, "]");
    
    if(!is_last_line){
      fprintf(save_file, "\n");
    }

    //Destruicao das estruturas
    destroy_dup_list(dup_list);
  }

  fclose(read_file);
  fclose(save_file);
  return 0;
}