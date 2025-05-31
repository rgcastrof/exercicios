#include "vector.h"
#include <stdio.h>

int main() {
    vector* v = new_vector(sizeof(int), INT);
    for (int i = 1; i <= 10; i += 2) {
        v->push_back(v, &i);
    }
    v->show(v, INT);
    printf("%d\n", *(int*)v->at(v, 3));
    printf("%d\n", *(int*)v->front(v));
    printf("%d\n", *(int*)v->back(v));
    printf("%d\n", v->size-1);
    printf("%d\n", v->len(v));
    printf("%d\n", v->cap(v));
    free_vet(v);
    return 0;
}
