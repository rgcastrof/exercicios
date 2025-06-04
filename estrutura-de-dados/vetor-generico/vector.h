#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b)) // macro que retorna o maior valor dentre os dois elementos

typedef enum {
    INT,
    FLOAT,
    STRING
} Type;

typedef struct vector {
    void *data; // ponteiro genérico para os dados
    int size; // tamanho do vetor
    size_t capacity; // capacidade do vetor
    size_t type_size; // tamanho de cada elemento. vai receber o tamanho do tipo do elemento com sizeof()
    void (*push_back)(struct vector*, void*);
    void (*push_front)(struct vector*, void*);
    void (*insert)(struct vector*, int, void*);
    void (*clear)(struct vector*);
    bool (*empty)(struct vector*);
    Type type;
    void (*show)(struct vector*, Type);
    void *(*at)(struct vector*, int index);
    void *(*front)(struct vector*);
    void *(*back)(struct vector*);
    int (*len)(struct vector*);
    int (*cap)(struct vector*);
} vector;

// Global funtions declarations
vector* new_vector(size_t type_size, Type type);
void free_vet(vector *v);

// Vector methods declarations
void push_back(vector *v, void* value);
void push_front(vector *v, void* value);
void insert(vector* v, int pos, void* value);
void clear(vector *v);
bool empty(vector *v);
void show(vector* v, Type type);
void *at(vector* v, int index);
void *front(vector* v);
void *back(vector* v);
int size(vector* v);
int capacity(vector* v);

#endif
