#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"

char *get_string() {
    char *string, *buffer;

    string = malloc(sizeof(char));
    buffer = malloc(sizeof(char));

    // C moment
    scanf(" %c", NULL);

    int i = 0;
    while (1) {
        string[i] = getc(stdin);
        //scanf("%c", &string[i]);
        if (string[i] == '\n') break;
        buffer = realloc(buffer, sizeof(char) * (i + 1));
        strcpy(buffer, string);
        string = realloc(string, sizeof(char) * (i + 2));
        strcpy(string, buffer);
        i++;
    }
    string[i] = '\0';

    free(buffer);

    return string;
}