//gcc RL1Q2.c -o q2 && ./q2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen, strcpy

#define MAX_SIZE_LINE 10000

typedef struct Stack {
  char **S;
  long top;
  long size;
} Stack;

char *custom_strstr(const char *string1, const char *string2) {
  long len1 = strlen(string1);
  long j = 0;
  for (long i = 0; i < len1; i++) {
    if (string1[i] == string2[j]) {
      j++;
    } 
    else {
      j = 0;
    }
    if (string2[j] == '\0') {
      return (char *)string1 + i - (j - 1);
    }
  }
  return NULL;
}

// O ultimo token não é retornado caso a string não finalize no delim, mas fica
// salvo no cursor "1 12 123 A Abc" -> retorna a cada chamada 1, 12, 123, A. No
//final ABC fica salvo em **cursor
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

long count_occurrency(char *string, char *substring) {
  long count = 0;
  while ((string = custom_strstr(string, substring)) != NULL) {
    count++;
    string += strlen(substring);
  }
  return count;
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

Stack *create_stack(long max_size) {
  Stack *stack = malloc(sizeof(Stack));
  stack->S = malloc(max_size * sizeof(char*));
  stack->size = max_size;
  stack->top = -1;
  return stack;
}

void delete_stack(Stack *stack) {
  if (stack != NULL) {
    if (stack->S != NULL) {
      for (int i = 0; i <= stack->top; i++) {
        free(stack->S[i]);
      }
      free(stack->S);
    }
    free(stack);
  }
}

bool is_full(Stack *stack) { return stack->top == stack->size - 1; }

bool is_empty(Stack *stack) { return stack->top == -1; }

bool push(Stack *stack, char *word) {
  if (!is_full(stack)) {
    stack->S[++stack->top] = word;
    return true;
  } else {
    // printf("Cannot push, since stack is full");
    return false;
  }
}

char *pop(Stack *stack) {
  if (!is_empty(stack)) {
    return stack->S[stack->top--];
  } else {
    // printf("Cannot pop since the stack is empty");
    return NULL;
  }
}

char *seek(Stack *stack) {
  if (!is_empty(stack)) {
    return stack->S[stack->top];
  } else {
    return NULL;
  }
}

int main() {
  FILE *read_file = fopen("L1Q2.in", "r");
  FILE *save_file = fopen("L1Q2.out", "w");
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
    //Para nao adicionar o \n na ultima linha
    bool is_last_line = false;
    
    // Troca o '\n' do final por um ' ', para lidar com o ultimo token. Caso não
    // tenha empurra o \0 para frente e e adiciona um ' '
    if(has_char(line, '\n')){
      line[strlen(line) - 1] = ' ';
    }
    else{
      long size = strlen(line);
      line[size] = ' ';
      line[size + 1] = '\0';
      is_last_line = true;
    }

    // Criação das estruturas
    long n_words = count_occurrency(line, " ");
    Stack *main_stack = create_stack(n_words);
    Stack *aux_stack = create_stack(n_words);

    //Loop que trata o token
    while ((token = custom_strsep(&c, ' ')) != NULL) {
      long size = strlen(token);
      char *word = malloc(size * sizeof(char) + 1);
      strcpy(word, token);

      if (is_empty(main_stack)) {
        push(main_stack, word);
        // Isso serve para primeira operação
        if (token == line) {
          fprintf(save_file, "push-%s", word);
        } 
        else{
          fprintf(save_file, " push-%s", word);
        }
      }
      else {
        while (!is_empty(main_stack) && custom_strcmp(seek(main_stack), word) > 0) {
          char *top_word = pop(main_stack);
          push(aux_stack, top_word);
        }
        if(!is_empty(aux_stack)){
          fprintf(save_file, " %ldx-pop", aux_stack->top + 1);
        }
        
        push(main_stack, word);
        fprintf(save_file, " push-%s", word);
        while(!is_empty(aux_stack)){
          char *top_word = pop(aux_stack);
          push(main_stack, top_word);
          fprintf(save_file, " push-%s", top_word);
        }
      }
    }
    if(!is_last_line){
      fprintf(save_file, "\n");
    }

    //Destruicao das estruturas
    delete_stack(main_stack);
    delete_stack(aux_stack);
  }

  // printf("Fim do arquivo!\n");
  fclose(read_file);
  fclose(save_file);
  return 0;
}
