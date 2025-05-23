#include <stdlib.h>
#include <string.h>

#include "../include/util.h"

char **strsplt(char *buffer) {
    char **args = NULL;
    int str_qtd = 0;
    buffer[strcspn(buffer, "\n")] = '\0';
    char *token = strtok(buffer, " ");
    while (token != NULL) {
        args = realloc(args, (str_qtd + 1) * sizeof(char*));
        args[str_qtd] = strdup(token);
        str_qtd++;
        token = strtok(NULL, " ");
    }
    args = realloc(args, (str_qtd + 1) * sizeof(char*));
    args[str_qtd] = NULL;
    return args;
}

int spltsize(char **args) {
    int count = 0;
    while (args[count] != NULL) {
        count++;
    }
    return count;
}

void freesplt(char **args, int size) {
    for (int i = 0; i < size; i++) {
        free(args[i]);
    }
    free(args);
}
