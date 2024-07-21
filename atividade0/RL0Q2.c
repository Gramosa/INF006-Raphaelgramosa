/*
|
|   Colaboradores: Uitan Macial, Ravena Dafne e Raphael Gramosa
|
|   Devido ao uso do math.h (Para a funcao sqrt e pow), caso a compilação seja feita pelo GCC ou Clang (linux), DEVE-SE
|   adicionar a flag -lm para linkar com com a biblioteca libc. No windows usando o MinGW ou MSVC pode não ser necessário.
|
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_SIZE_LINE 1024
#define MAX_DOUBLE_PRECISION 10

typedef struct Point {
    double x;
    double y;
    double dist_origin;
} Point;

int count_char(const char *str, const char target){
  int count = 0;
  while(*str != '\0'){
    if(*str == target){
      count++;
    }
    str++;
  }
  
  return count;
}

int count_char_in_word(const char *str){
  int count = 0;
  while(*str != ' ' && *str != '\0' && *str != '\n'){
    count++;
    str++;
  }
  
  return count;
}

int count_words(const char *str){
  int count = 0;
  bool in_word = false;
  while(*str != '\0'){
    if(!in_word && ((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z'))){
      in_word = true;
      count++;
    }
    else if(in_word && (*str == ' ' || *str == '\n' || *str == '\0')){
      in_word = false;
    }
    str++;
  }
  
  return count;
}

int count_doubles(const char *str){
  int count = 0;
  bool in_point = false;
  while(*str != '\0'){
    if(*str == '('){
      in_point = true;
    }
    else if(*str == ')'){
      in_point = false;
    }

    if(!in_point && *str == '.'){
      count++;
    }
    str++;
  }
  return count;
}

int count_items(const char *str){
  int count = count_char(str, ' ');
  if(*str != '\n'){
    count++;
  }
  return count;
}

int count_integers(int total_items, int points, int words, int doubles){
  return total_items - (points + words + doubles);
}

int get_double_precision(const double value, const int max_decimal_precision){
  double epsilon = 1.0 / pow(10, max_decimal_precision);
  int precision = 0;

  while(precision < max_decimal_precision && fabs(value - round(value * pow(10, precision)) / pow(10, precision)) > epsilon){
    precision++;
  }

  return precision;
}

double calculate_distance(Point p1, Point p2){
  double delta_x = p1.x - p2.x;
  double delta_y = p1.y - p2.y;
  return sqrt(delta_x * delta_x + delta_y * delta_y);
}

Point parse_point(char *str_p, char **end_ptr){
  const Point origin = {.x = 0, .y = 0, .dist_origin = 0};
  Point p = {.x = 0, .y = 0, .dist_origin = -1};

  if(*str_p != '('){
    printf("Ponto nao inicia com '(', encontrado '%c'", *str_p);
    return p;
  }

  p.x = strtod(++str_p, &str_p);
  if(*str_p != ','){
    printf("É esperado uma virgula separando as coordenadas");
    return p;
  }

  p.y = strtod(++str_p, &str_p);
  if(*str_p != ')'){
    printf("Ponto nao termina com ')'");
    return p;
  }
  p.dist_origin = calculate_distance(p, origin);
  *end_ptr = ++str_p;
  return p;
}

char* parse_word(char *str_p, char **end_ptr){
  int word_size = count_char_in_word(str_p);
  char *word = malloc((word_size + 1) * sizeof(char)); 
  int i = 0;
  // while(*str_p != ' ' && *str_p != '\0' && *str_p != '\n'){

  //     word[i] = *str_p;
  //     i++;
  //     str_p++;
  // }
  for(i = 0; i < word_size; i++){
    word[i] = *str_p;
    str_p++;
  }
  word[i] = '\0';
  *end_ptr = str_p;
  return word;
}

int customStrcmp(const char *string1, const char *string2){
  int i = 0;
  while(string1[i] != '\0' && string2[i] != '\0'){
    if(string1[i] != string2[i]){
      return string1[i] - string2[i];
    }
    i++;
  }
  return string1[i] - string2[i];
}

void sort_points(Point* points, int size){
  for(int i = 0; i < size; i++){
    int lower_pos = i;
    for(int j = i+1; j < size; j++){
      if(points[j].dist_origin < points[lower_pos].dist_origin){
        lower_pos = j;
      }
    }
    if(lower_pos != i){
      Point temp = points[i];
      points[i] = points[lower_pos];
      points[lower_pos] = temp;
    }
  }
}

void sort_words(char **words, int size){
  for(int i = 0; i < size; i++){
    int min_pos = i;
    for(int j = i + 1; j < size; j++){
      if(customStrcmp(words[j], words[min_pos]) < 0){
        min_pos = j;
      }
    }
    if(min_pos != i){
      char* temp = words[i];
      words[i] = words[min_pos];
      words[min_pos] = temp;
    }
  }
}

void sort_doubles(double *doubles, int size){
  for(int i = 0; i < size; i++){
    int min_pos = i;
    for(int j = i + 1; j < size; j++){
      if(doubles[j] < doubles[min_pos]){
        min_pos = j;
      }
    }
    if(min_pos != i){
      double temp = doubles[i];
      doubles[i] = doubles[min_pos];
      doubles[min_pos] = temp;
    }
  }
}

void sort_integers(int *integers, int size){
  for(int i = 0; i < size; i++){
    int min_pos = i;
    for(int j = i + 1; j < size; j++){
      if(integers[j] < integers[min_pos]){
        min_pos = j;
      }
    }
    if(min_pos != i){
      int temp = integers[i];
      integers[i] = integers[min_pos];
      integers[min_pos] = temp;
    }
  }
}

int main(){
  FILE* read_file = fopen("L0Q2.in", "r");
  FILE* save_file = fopen("L0Q2.out", "w");
  if(read_file == NULL){
    printf("Erro ao ler o arquivo de leitura");
    return 1;
  }
  if(save_file == NULL){
    printf("Erro ao ler o arquivo de salvamento");
    return 1;
  } 
  char line[MAX_SIZE_LINE];
  bool is_last_line = false;
  while(fgets(line, MAX_SIZE_LINE, read_file) != NULL){
    char *ptr = line;

    int n_points = count_char(line, '(');
    int n_words = count_words(line);
    int n_doubles = count_doubles(line);
    int n_integers = count_integers(count_items(line), n_points, n_words, n_doubles);
    Point *points = malloc(n_points * sizeof(Point));
    char **words = malloc(n_words * sizeof(char*));
    double *doubles = malloc(n_doubles * sizeof(double));
    int *integers = malloc(n_integers * sizeof(int));
    int ip = 0;
    int iw = 0;
    int id = 0;
    int iint = 0;
    while(*ptr != '\0'){
      if(*ptr == '('){
        points[ip] = parse_point(ptr, &ptr);
        ip++;
      }
      else if((*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= 'a' && *ptr <= 'z')){
        words[iw] = parse_word(ptr, &ptr);
        iw++;
      }
      else{
        double value = strtod(ptr, &ptr);
        int precision = get_double_precision(value, MAX_DOUBLE_PRECISION);
        if(precision == 0){
          integers[iint] = (int)value;
          iint++;
        }
        else{
          doubles[id] = value;
          id++;
        }
      }
      if(*ptr != '\0') //ignora ' ' e '\n'
        ptr++;
      else
        is_last_line = true;
    }

    sort_points(points, n_points);
    sort_words(words, n_words);
    sort_doubles(doubles, n_doubles);
    sort_integers(integers, n_integers);

    fprintf(save_file, "str:");
    for(int i = 0; i < n_words; i++){
      if(i == 0){
        fprintf(save_file, "%s", words[i]);
      }
      else{
        fprintf(save_file, " %s", words[i]);
      }
      free(words[i]);
    }

    fprintf(save_file, " int:");
    for(int i = 0; i < n_integers; i++){
      if(i == 0){
        fprintf(save_file, "%d", integers[i]);
      }
      else{
        fprintf(save_file, " %d", integers[i]);
      }
    }

    fprintf(save_file, " float:");
    for(int i = 0; i < n_doubles; i++){
      if(i == 0){
        fprintf(save_file, "%.*f", get_double_precision(doubles[i], MAX_DOUBLE_PRECISION), doubles[i]);
      }
      else{
        fprintf(save_file, " %.*f", get_double_precision(doubles[i], MAX_DOUBLE_PRECISION), doubles[i]);
      }
    }

    fprintf(save_file, " p:");
    for(int i = 0; i < n_points; i++){
      if(i == 0){
        fprintf(save_file, "(%.*f,%.*f)", get_double_precision(points[i].x, MAX_DOUBLE_PRECISION), points[i].x, get_double_precision(points[i].y, MAX_DOUBLE_PRECISION), points[i].y);
      }
      else{
        fprintf(save_file, " (%.*f,%.*f)", get_double_precision(points[i].x, MAX_DOUBLE_PRECISION), points[i].x, get_double_precision(points[i].y, MAX_DOUBLE_PRECISION), points[i].y);
      }
    }
    if(!is_last_line){
      fprintf(save_file, "\n");
    }

    free(points);
    free(words);
    free(doubles);
    free(integers);
  }
  fclose(read_file);
  fclose(save_file);
  return 0;
}
