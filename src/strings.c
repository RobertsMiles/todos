#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"

void set_string(FILE *stream, char* string) {
    string = NULL;
    char *buffer;

    //string = realloc(string, sizeof(char));
    buffer = malloc(sizeof(char));

    if (stream == stdin) fflush(stdin);

    int i = 0;
    while (1) {
        string[i] = getc(stream);
        //scanf("%c", &string[i]);
        if (string[i] == '\n' || string[i] == '\0') break;
        buffer = realloc(buffer, sizeof(char) * (i + 1));
        strcpy(buffer, string);
        string = realloc(string, sizeof(char) * (i + 2));
        strcpy(string, buffer);
        i++;
    }
    string[i] = '\0';

    free(buffer);
}