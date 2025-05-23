#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/linkedlist.h"
#include "include/util.h"


int main() {
    list *L = new_list(INT);
    char buffer[255];
    char **args = NULL;
    int size;

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        printf("$%s", buffer);
        args = strsplt(buffer);
        size = spltsize(args);
        int value;

        if (strcmp(args[0], "end") == 0) {
            break;
        } else if (strcmp(args[0], "push_front") == 0) {
            for (int i = 1; i < size; i++) {
                value = atoi(args[i]);
                L->push_front(L, &value, sizeof(int), INT);
            }
        } else if (strcmp(args[0], "push_back") == 0) {
            for (int i = 1; i < size; i++) {
                value = atoi(args[i]);
                L->push_back(L, &value, sizeof(int), INT);
            }
        } else if (strcmp(args[0], "show") == 0) {
            L->show(L, INT);
        } else if (strcmp(args[0], "empty") == 0) {
            if (L->empty(L)) {
                printf("true\n");
            } else {
                printf("false\n");
            }
        } else if (strcmp(args[0], "pop_front") == 0) {
            L->pop_front(L);
            
        } else if (strcmp(args[0], "pop_back") == 0) {
            L->pop_back(L);
            
        } else if (strcmp(args[0], "size") == 0) {
            printf("%d\n", L->size(L));
        } else if (strcmp(args[0], "clear") == 0) {
            L->clear(L);
        } else {
            printf("invalid argument\n");
        }
    }

    L->free_list(L);
    freesplt(args, size);
    return 0;
}
