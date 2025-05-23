#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    INT,
    FLOAT,
    STRING,
} type;

typedef struct element {
    void *value;
    struct element *next;
    struct element *prev;
} element;


typedef struct iterator {
    element *current;
    element *end;
    bool (*has_next)(struct iterator*);
    void *(*next)(struct iterator*);
} iterator;

typedef struct list {
    struct element *root;
    type t;
    int len;
    
    element *(*begin)(struct list*);
    element *(*end)(struct list*);
    bool (*empty)(struct list*);
    int (*size)(struct list*);
    void (*push_front)(struct list*, void*, size_t, type);
    void (*push_back)(struct list*, void*, size_t, type);
    void (*pop_front)(struct list*);
    void (*pop_back)(struct list*);
    void (*clear)(struct list*);
    void (*show)(struct list*, type);
    void (*free_list)(struct list*);
    struct iterator *(*new_iterator)(struct list*);
} list;


list *new_list(type t);

// declaração dos métodos
element *begin(list *l);
element *end(list *l);
bool empty(list *l);
int size(list *l);
void push_front(list *l, void *value, size_t data_size, type t);
void push_back(list *l, void *value, size_t data_size, type t);
void pop_front(list *l);
void pop_back(list *l);
void (clear)(struct list *l);
void show(list *l, type);
void free_list(list *l);
iterator *new_iterator(list *l);
bool has_next(struct iterator*);
void *next(struct iterator*);

#endif
