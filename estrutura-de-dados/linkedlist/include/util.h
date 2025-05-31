#ifndef UTIL_H
#define UTIL_H

char **strsplt(char *buffer);
int spltsize(char **args);
void freesplt(char **args, int size);

#endif
