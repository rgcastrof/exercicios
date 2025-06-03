#include "vector.h"

int main() {
    vector* v = new_vector(sizeof(int), INT);
    for (int i = 1; i <= 10; i += 2) {
        v->push_back(v, &i);
    }
    int b = 99;
    v->push_front(v, &b);
    v->show(v, INT);
    free_vet(v);
    return 0;
}
