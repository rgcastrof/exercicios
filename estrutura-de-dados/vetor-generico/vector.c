#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

vector*
new_vector(size_t type_size, Type type)
{
    vector* v = malloc(sizeof(vector));
    v->size = 0;
    v->capacity = 0;
    v->type_size = type_size;
    v->type = type;
    /* aloca o bloco de memória do vetor, a capacidade multiplica-se
    com o tamanho em bytes do tipo pois o vetor armazenará elementos deste tipo */
    v->data = malloc(v->capacity * type_size);
    v->push_back = push_back;
    v->push_front = push_front;
    v->insert = insert;
    v->clear = clear;
    v->empty = empty;
    v->show = show;
    v->at = at;
    v->front = front;
    v->back = back;
    v->len = size;
    v->cap = capacity;
    return v;
}

void
reserve(vector* v, size_t newcap) {
    if (newcap < v->size) {
        return;
    }

    // a nova capacidade do vetor será newcap multiplicado pelo tamanho do tipo
    void* temp = realloc(v->data, newcap*v->type_size);

    /* verifica se a realocação foi bem sucedida e atualiza
    o bloco de memória do array para o novo tamanho */
    if (temp == NULL) {
        fprintf(stderr, "fail to realloc");
        return;
    }
    v->data = temp;
    v->capacity = newcap;
}

void*
at(vector* v, int index)
{
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "fail: index out of bounds\n");
        return NULL;
    }
    return (char*)v->data + index * v->type_size;
}

void *front(vector* v) {
    if (v->size == 0) {
        fprintf(stderr, "fail: empty vector");
        return NULL;
    }
    return (char*)v->data;
}

void *back(vector* v) {
    if (v->size == 0) {
        fprintf(stderr, "fail: empty vector");
        return NULL;
    }
    return (char*)v->data + (v->size-1) * v->type_size;
}

int size(vector *v) {
    if (v->size == 0) {
        return 0;
    }
    int count = 0;
    for (size_t i = 0; i < v->size; i++) {
        count++;
    }
    return count;
}

bool
empty(vector* v)
{
    if (v->len(v) == 0) {
        return true;
    }
    return false;
}

int capacity(vector *v) {
    return v->capacity;
}

void
push_back(vector *v, void* value)
{
    if (v->size == v->capacity) {
        reserve(v, MAX(1, v->capacity*2));
    }
    /* o primeiro parâmetro faz um casting para poder usar arimética de ponteiros,
     * que funciona em bytes. O casting foi para char pois único tipo de ponteiro
     * em C onde cada incremento é de 1 byte. Após o casting, soma-se este com o
     * tamanho multiplicado pelo tamanho em bytes do tipo do vetor, encontrando
     * assim o espaço para onde será copiado o elemento que se quer adicionar.
     * Neste caso, será no fim do vetor. O segundo parâmetro é o próprio elemento
     * e o terceiro parâmetro é o tamanho em bytes do que se quer copiar, como
     * é um ponteiro genérico, o tamanho será o tamanho do tipo do vetor*/
    memcpy((char*)v->data + v->size * v->type_size, value, v->type_size);
    v->size++;
}

void
push_front(vector *v, void *value)
{
    if (v->size == v->capacity) {
        reserve(v, MAX(1, v->capacity*2));
    }
    /* Incrementa o tamanho do vetor em um e usa a função memmove para copiar
     * o bloco de memória do vetor uma posição pra frente, depois copia o elemento
     * a ser inserido para a primeira posição. */
    v->size++;
    memmove((char*)v->data + v->type_size, v->data, v->size * v->type_size);
    memcpy(v->data, value, v->type_size);
}

void
insert(vector* v, int pos, void* value)
{
    if (pos < 0 || pos > v->len(v)) {
        fprintf(stderr, "fail: invalid insert position");
        return;
    }
    if (v->size == v->capacity) {
        reserve(v, MAX(1, v->capacity*2));
    }

    v->size++;
    memmove((char*)v->data + ((pos+1) * v->type_size), (char*)v->data + ((pos) * v->type_size), (v->size - pos) * v->type_size);
    memcpy((char*)v->data + (pos * v->type_size), value, v->type_size);
}

void
clear(vector *v)
{
    free(v->data);
    v->size = 0;
}

void
show(vector* v, Type type)
{
    printf("[ ");
    switch (type) {
        case INT:
            for (size_t i = 0; i < v->size; i++) {
                if (i < v->size-1) {
                    printf("%d, ", *(int*)((char*)v->data + i * v->type_size));
                } else {
                    printf("%d ", *(int*)((char*)v->data + i * v->type_size));
                }
            }
            break;
        case FLOAT:
            for (size_t i = 0; i < v->size; i++) {
                if (i < v->size-1) {
                    printf("%.2f, ", *(float*)((char*)v->data + i * v->type_size));
                } else {
                    printf("%.2f ", *(float*)((char*)v->data + i * v->type_size));
                }
            }
            break;
        case STRING:
            for (size_t i = 0; i < v->size; i++) {
                if (i < v->size-1) {
                    printf("%s, ", *(char**)((char*)v->data + i * v->type_size));
                } else {
                    printf("%s ", *(char**)((char*)v->data + i * v->type_size));
                }
            }
            break;
    }
    printf("]\n");
}

void
free_vet(vector *v) {
    free(v->data);
    free(v);
}
