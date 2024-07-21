#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int *Q;
    int tail;
    int head;
    int lenght;
} Queue;

Queue* create_queue(int size){
    Queue* queue = malloc(sizeof(Queue));
    queue->Q = malloc(size * sizeof(int));
    queue->tail = 0;
    queue->head = 0;
    queue->lenght = size;
    return queue;
}

void destroy_queue(Queue *queue){
    if(queue->Q != NULL){
        free(queue->Q);
    }
    free(queue);
}

void show_queue(Queue *queue){
    int i = queue->head;
    printf("[(h)");
    while(i != queue->tail){
        printf(" %d,", queue->Q[i]);
        i = (i + 1) % queue->lenght;
    }
    printf(" (t)]");
}

void enqueue(Queue *queue, int item){
    queue->Q[queue->head] = item
}

int main(){
    Queue *q = create_queue(8);


    destroy_queue(q);
    return 0;
}
