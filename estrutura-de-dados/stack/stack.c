#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Stack*
stack_new(int initial_capacity)
{
    Stack* s = malloc(sizeof(Stack));
    if (!s) {
        fprintf(stderr, "failed to malloc Stack\n");
        exit(1);
    }
    s->data = malloc(initial_capacity * sizeof(int));
    if (!s->data) {
        fprintf(stderr, "failed to malloc data\n");
        free(s);
        exit(1);
    }
    s->top = -1;
    s->capacity = initial_capacity;
    return s;
}

int
is_empty(Stack* s)
{
    return s->top == -1;
}

int
is_full(Stack* s)
{
    return s->top == s->capacity - 1;
}

void
resize(Stack* s)
{
    s->capacity *= 2;
    s->data = realloc(s->data, s->capacity * sizeof(int));
    if (!s->data) {
        fprintf(stderr, "failed to realloc data\n");
        exit(1);
    }
}

void
push(Stack* s, int value)
{
    if (is_full(s)) {
        resize(s);
    }
    
    s->data[++s->top] = value;
}

int
pop(Stack* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    return s->data[s->top--];
}

int
top(Stack* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    return s->data[s->top];
}

void
stack_free(Stack* s)
{
    free(s->data);
    free(s);
}
