#ifndef STACK_H
#define STACK_H

typedef struct {
    int* data;
    int top;
    int capacity;
} Stack;

Stack* stack_new(int initial_capacity);
int is_empty(Stack* s);
int is_full(Stack* s);
void resize(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int top(Stack* s);
void stack_free(Stack* s);

#endif
