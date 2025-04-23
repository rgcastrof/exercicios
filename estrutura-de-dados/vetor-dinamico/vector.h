#ifndef VECTOR_H
#define VECTOR_H

// struct
typedef struct vector {
    int *data;
    int size;
    int capacity;
    void (*push_back)(struct vector*, int);
    void (*push_front)(struct vector*, int);
    void (*erase)(struct vector*, int);
    int (*begin)(struct vector*);
    int (*end)(struct vector*);
} vector;

// functions declarations
struct vector *new_vector(int);
void push_back(struct vector*, int);
void push_front(struct vector*, int);
void erase(struct vector*, int);
int begin(struct vector*);
int end(struct vector*);

#endif
