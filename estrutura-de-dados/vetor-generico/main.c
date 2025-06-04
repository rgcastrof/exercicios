#include "vector.h"
#include <stdio.h>

int main() {
    vector* v = new_vector(sizeof(int), INT);
    for (int i = 1; i <= 10; i += 2) {
        v->push_back(v, &i);
    }
    int b = 99;
    v->push_front(v, &b);
    // v->clear(v);
    int c = 100;
    printf("antes: ");
    v->show(v, INT);
    printf("%d", v->len(v));
    v->insert(v, 1, &c);
    printf("depois: ");
    v->show(v, INT);
    if (v->empty(v) == true) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    free_vet(v);
    return 0;
}
