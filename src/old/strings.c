#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

Letter* new_string() {
    return malloc(sizeof(Letter));
}

void free_string(Letter* head) {
    Letter* current = head;
    while (current->self != '\n') {
        Letter* next = head->next;
        free(current);
    }
    free(current);
}



void read_string(Letter* head) {
    Letter* current = head;
    while (1) {
        scanf("%c", &current->self);
        if (current->self == '\n') return;
        current->next = malloc(sizeof(Letter));
        current = current->next;
    }
}

void print_string(Letter* head) {
    Letter* current = head;
    while (current->self != '\n') {
        printf("%c", current->self);
        current = current->next;
    }
}