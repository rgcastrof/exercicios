#include <stdlib.h>
#include <string.h>
#include "vector.h"

// function implementations
vector
*new_vector(int initial_capacity)
{
    vector *v = malloc(sizeof(vector));
    v->data = malloc(sizeof(int) * initial_capacity);
    v->size = 0;
    v->capacity = initial_capacity;
    v->push_back = push_back;
    v->push_front = push_front;
    v->begin = begin;
    v->end = end;
    v->erase = erase;
    return v;
}

void
push_back(vector *v, int value)
{
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof(int) * v->capacity);
    }
    v->data[v->size++] = value;
}

void
push_front(vector *v, int value)
{
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof(int) * v->capacity);
    }
    
    memmove(&v->data[1], v->data, sizeof(int) * v->size);
    v->data[0] = value;
    v->size++;
}

void
erase(vector *v, int index)
{
    if (index > 0 && index < v->size) {
        memmove(&v->data[index], &v->data[index+1], sizeof(int) * (v->size - index - 1));
        v->size--;
    }
}
int
begin(vector *v)
{
    return v->data[0];
}

int
end(vector *v)
{
    return v->data[v->size-1];
}
