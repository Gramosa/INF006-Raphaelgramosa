//gcc RL1Q1.c -o q1 && ./q1

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen, strtol
#include <stdbool.h>

#define MAX_SIZE_LINE 10000

typedef struct Node {
  long data;
  struct Node *next;
} Node;

typedef struct UniList {
  Node *head;
  long long sum_data;
} UniList;

char* custom_strstr(const char *string1, const char *string2){
  long len1 = strlen(string1);
  long j = 0;
  for(long i = 0; i < len1; i++){
    if(string1[i] == string2[j]){
      j++;
    }
    else{
      j = 0;
    }
    if(string2[j] == '\0'){
      return (char*)string1 + i - (j - 1);
    }
  }
  return NULL;
}

//O ultimo token não é retornado caso a string não finalize no delim, mas fica salvo no cursor
//"1 12 123 A Abc" -> retorna a cada chamada 1, 12, 123, A. No final ABC fica salvo em **cursor
char* custom_strsep(char **cursor, char delim){
  if(cursor == NULL || *cursor == NULL){
    printf("Bug, ponteiro NULL ou apontando para NULL");
    return NULL;
  }

  char *begin = *cursor;
  while(**cursor != '\0'){
    if(**cursor == delim){
      **cursor = '\0';
      (*cursor)++; // Move para uma posicao depois do delimitador
      return begin;
    }
    (*cursor)++;
  }

  return NULL;
}

int custom_strcmp(const char *string1, const char *string2){
  int i = 0;
  while(string1[i] != '\0' && string2[i] != '\0'){
    if(string1[i] != string2[i]){
      return string1[i] - string2[i];
    }
    i++;
  }
  return string1[i] - string2[i];
}

// Rotina para ser usada especificamente para corrigir uma string de modo que possa ser usada por custom_strsep
// A string tera o delim no final dela ao fim da interacao
void correct_line_for_strsep(char* line, char delim){
  // Fazer caso necessario
}

long count_occurrency(char *string, char *substring){
  long count = 0;
  while((string = custom_strstr(string, substring)) != NULL){
    count++;
    string += strlen(substring);
  }
  return count;
}

bool has_char(const char *str, const char target){
  while(*str != '\0'){
    if(*str == target){
      return true;
    }
    str++;
  }

  return false;
}

Node* create_node(long data){
  Node *new_node = malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

UniList* create_list(){
  UniList *list = malloc(sizeof(UniList));
  list->head = NULL;
  list->sum_data = 0;
  return list;
}

bool destroy_list(UniList *list){
  if(list == NULL) return false;
  Node *current = list->head;
  while(current != NULL){
    Node *temp = current;
    current = current->next;
    free(temp);
  }
  free(list);
  return true;
}

// Adiciona na posicao ja ordenada
bool add_sorted(UniList *list, Node* node){
  if(list == NULL || node == NULL) return false;

  if(list->head == NULL){
    list->head = node;
    return true;
  }
  Node *current = list->head;
  Node *previous = NULL;
  while(current != NULL && current->data < node->data){
    previous = current;
    current = current->next;
  }
  if(previous == NULL){
    node->next = list->head;
    list->head = node;
  }
  else{
    previous->next = node;
    node->next = current;
  }
  
  return true;
}

int main() {
  FILE* read_file = fopen("L1Q1.in", "r");
  FILE* save_file = fopen("L1Q1.out", "w");
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
    long n_lists = count_occurrency(line, "start");
    UniList **all_lists = malloc(sizeof(UniList*) * n_lists);
    
    for(long i = 0; i < n_lists; i++){
      all_lists[i] = create_list();
    }

    long i = -1; //-1 Porque o incremento ja acontece no inicio da interacao
    while((token = custom_strsep(&c, ' ')) != NULL){
      //significa que as duas iguais
      if(custom_strcmp(token, "start") == 0){
        i++;
      }
      else{
        //Partindo do pressuposto que havera apenas numeros alem da palavra "start"
        long value = strtol(token, NULL, 10);
        add_sorted(all_lists[i], create_node(value));
        all_lists[i]->sum_data += value;
      }
    }
    //Ordernar as listas entre si, simples bubble sort
    for(long i = 0; i < n_lists; i++){
      for(long j = i + 1; j < n_lists; j++){
        if(all_lists[i]->sum_data >= all_lists[j]->sum_data){
          UniList *temp = all_lists[i];
          all_lists[i] = all_lists[j];
          all_lists[j] = temp;
          
          if(all_lists[i]->sum_data == all_lists[j]->sum_data){
            free(temp);
            for(int k = j + 1; k < n_lists; k++){
              all_lists[k-1] = all_lists[k];
            }
            j--;
            n_lists--;
          }
        }
      }
    }
    
    //Salvamento no arquivo e Destruição das estruturas
    for(long i = 0; i < n_lists; i++){
      if(i != 0){
        fprintf(save_file, " ");
      }
      fprintf(save_file, "start");
      Node *n = all_lists[i]->head;
      while(n != NULL){
        fprintf(save_file, " %ld", n->data);
        n = n->next;
      }
      
      destroy_list(all_lists[i]);
    }
    if(!is_last_line){
      fprintf(save_file, "\n");
    }
    free(all_lists);
  }
  
  //printf("Fim do arquivo!\n");
  fclose(read_file);
  fclose(save_file);
  
  return 0;
}
