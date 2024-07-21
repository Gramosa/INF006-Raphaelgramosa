/*
|
|   Colaboradores: Uitan Macial, Ravena Dafne e Raphael Gramosa
|
|   Devido ao uso do math.h (Para a funcao sqrt), caso a compilação seja feita pelo GCC ou Clang (linux) É NECESSÁRIO
|   adicionar a flag -lm para linkar com com a biblioteca libc. No windows usando o MinGW ou MSVC pode não ser necessário.
|
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE_LINE 1024

typedef struct Point {
    int x;
    int y;
    double dist_origin;
} Point;

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

    p.x = (int)strtod(++str_p, &str_p);
    if(*str_p != ','){
        printf("É esperado uma virgula separando as coordenadas");
        return p;
    }

    p.y = (int)strtod(++str_p, &str_p);
    if(*str_p != ')'){
        printf("Ponto nao termina com ')'");
        return p;
    }
    p.dist_origin = calculate_distance(p, origin);
    *end_ptr = ++str_p;
    return p;
}

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

void sort_points(Point* points, int size){
    for(int i = 0; i < size; i++){
        int lower_pos = i;
        for(int j = i+1; j < size; j++){
            if(points[j].dist_origin < points[lower_pos].dist_origin){
                lower_pos = j;
            }
        }
        Point temp = points[i];
        points[i] = points[lower_pos];
        points[lower_pos] = temp;
    }
}

int main(){
    FILE* read_file = fopen("L0Q1.in", "r");
    FILE* save_file = fopen("L0Q1.out", "w");
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
        Point *points = NULL;
        // aloca dinamicamee a quantidade de pontos necessarios, e lida com com casos sem pontos (numero, numero)
        char *ptr = strchr(line, '(');
        int i = 0;
        if(ptr != NULL){
            points = malloc(count_char(line, '(') * sizeof(Point));

            while(*ptr != '\0'){
                points[i] = parse_point(ptr, &ptr);
                if(*ptr == '\n' || *ptr == ' '){
                    ptr++; //pula o espaço em branco ou \n
                }
                else if(*ptr == '\0'){
                    is_last_line = true;
                }
                i++;
            }
        }
        double short_distance = 0;
        double total_distance = 0;
        if(i > 0){
            short_distance = calculate_distance(points[0], points[i-1]);
            for(int k = 0; k < i - 1; k++){
                total_distance += calculate_distance(points[k], points[k+1]);
            }
        }
        sort_points(points, i);
        fprintf(save_file, "points");
        if(i > 0){
            for(int j = 0; j < i; j++){
                fprintf(save_file," (%d,%d)", points[j].x, points[j].y);
            }
            fprintf(save_file, " distance %.2f shortcut %.2f", total_distance, short_distance);
        }
        if(!is_last_line){
            fprintf(save_file, "\n");
        }
        free(points);
    }

    fclose(read_file);
    fclose(save_file);
    return 0;
}