#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/linkedlist.h"

element *new_element(void* value, size_t data_size) {
    element *new = malloc(sizeof(element));
    new->value = malloc(data_size); // aloca o espaço do tamanho necessário

    // copia o valor (tamanho em bytes) para o espaço recém alocado
    memcpy(new->value, value, data_size);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

element *create_sentinel() {
    element *sentinel = malloc(sizeof(element));
    sentinel->value = NULL;
    sentinel->next = NULL;
    sentinel->prev = NULL;
    return sentinel;
}

list *new_list(type t) {
    list *l = malloc(sizeof(list));
    l->root = create_sentinel();
    l->root->next = l->root;
    l->root->prev = l->root;
    l->t = t;
    l->len = 0;

    l->begin = begin;
    l->end = end;
    l->empty = empty;
    l->size = size;
    l->push_front = push_front;
    l->push_back = push_back;
    l->pop_front = pop_front;
    l->pop_back = pop_back;
    l->clear = clear;
    l->show = show;
    l->free_list = free_list;
    l->new_iterator = new_iterator;
    return l;
}

element *insert(element *at, void *value, size_t data_size) {
    element *e = new_element(value, data_size);
    e->next = at->next;
    e->prev = at;
    at->next->prev = e;
    at->next = e;
    return e;
}

element *begin(list *l) {
    iterator *it = l->new_iterator(l);
    return it->current;
}

element *end(list *l) {
    iterator *it = l->new_iterator(l);
    return it->end;
}

bool empty(list *l) {
    if (l->size(l) == 0) {
        return true;
    }
    return false;
}

int size(list *l) {
    return l->len;
}

void push_front(list *l, void *value, size_t data_size, type t) {
    if (l->t != t) {
        fprintf(stderr, "invalid type\n");
        return;
    }
    insert(l->root, value, data_size);
    l->len++;
}

void push_back(list *l, void *value, size_t data_size, type t) {
    if (l->t != t) {
        fprintf(stderr, "invalid type\n");
        return;
    }
    if (l->size(l) == 0) {
        element *e = new_element(value, data_size);
        e->next = l->end(l);
        e->prev = l->root;
        l->root->next = e;
        l->root->prev = e;
        l->len++;
        return;
    }
    insert(l->end(l)->prev, value, data_size);
    l->len++;
}

void pop_front(list *l) {
    if (l->empty(l)) {
        printf("empty list\n");
        return;
    }
    if (l->size(l) == 1) {
        l->root->next = l->root;
        l->len--;
        return;
    }
    element *temp = l->root->next;
    l->root->next = l->begin(l)->next;
    l->root->next->prev = l->root;
    l->len--;
    free(temp);
}

void pop_back(list *l) {
    if (l->empty(l)) {
        printf("empty list\n");
        return;
    }
    if (l->size(l) == 1) {
        l->root->next = l->root;
        l->len--;
        return;
    }
    element *last = l->root->prev;
    element *prev = last->prev; 
    prev->next = l->root;
    l->root->prev = prev;
    free(last);
    l->len--;
}

void clear(list *l) {
    if (l->empty(l)) {
        printf("empty list\n");
        return;
    }
    if (l->size(l) == 1) {
        element *e = l->begin(l);
        l->root->next = l->root;
        l->root->prev = l->root;
        free(e);
        l->len = 0;
        return;
    }
    iterator *it = l->new_iterator(l);
    element *e;
    element *next;
    while (it->has_next(it)) {
        e = it->current;
        next = e->next;
        free(e->value);
        free(e);
        it->current = next;
    }
    free(it);
    l->root->next = l->root;
    l->root->prev = l->root;
    l->len = 0;
}

void show(list *l, type t) {
    iterator *it = new_iterator(l);
    switch (l->t) {
        case INT:
            printf("[");
            while (it->has_next(it)) {
                if (it->current != it->end->prev) {
                    printf("%d, ", *(int*)it->next(it));
                } else {
                    printf("%d", *(int*)it->next(it));
                }
            }
            printf("]\n");
            break;
        case FLOAT:
            printf("[");
            while (it->has_next(it)) {
                if (it->current != it->end->prev) {
                    printf("%.2f, ", *(float*)it->next(it));
                } else {
                    printf("%.2f", *(float*)it->next(it));
                }
            }
            printf("]\n");
            break;
        case STRING:
            printf("[");
            while (it->has_next(it)) {
                if (it->current != it->end->prev) {
                    printf("%s, ", (char*)it->next(it));
                } else {
                    printf("%s", (char*)it->next(it));
                }
            }
            printf("]\n");
            break;
        default:
            fprintf(stderr, "invalid type");
            break;
    }

    free(it);
}

void free_list(list *l) {
    element *current = l->root->next;
    while (current != l->root) {
        element *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    free(l->root);
    free(l);
}


iterator *new_iterator(list *l) {
    iterator *it = malloc(sizeof(iterator));
    it->current = l->root->next;
    it->end = l->root;
    it->has_next = has_next;
    it->next = next;
    return it;
}

bool has_next(iterator *it) {
    return it->current != it->end;
}

void *next(iterator *it) {
    if (!it->has_next) {
        fprintf(stderr, "panic: no more elements");
        exit(1);
    }
    void *value = it->current->value;
    it->current = it->current->next;
    return value;
}
