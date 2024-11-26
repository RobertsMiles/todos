#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"

void clear_screen() {
    printf("\e[1;1H\e[2J");
}

/*
typedef struct {
    char date[11];
    int task;
} Selection;
*/

/*
// Writes the current date to the given string.
void set_current_date(char* date) {
    FILE* command = popen("date +%F", "r");
    fgets(date, 11, command);
}
*/

// Formats the user's date selection into yyyy-mm-dd.
// Returns 0 if successful, otherwise non-zero.
int set_date(char* date, char* choice) {
    char command_in[64] = {'\0'}; // TODO replace strcat() with dynamic alternative to avoid potential buffer overflows
    strcat(command_in, "date --date='");
    strcat(command_in, choice);
    strcat(command_in, "' +%F");
    FILE* command_out = popen(command_in, "r");
    fgets(date, 16, command_out);
    return pclose(command_out);
}

void choose_date(char* date) {
    int validity = -1;
    while (validity) {
        printf("Date: ");
        char *choice = get_string();
        validity = set_date(date, choice);
    }
}

void evaluate_choice(char choice, char* date) {
    switch (choice) {
        case 'c': choose_date(date); break;
        //case 'a': add_task(date); break;
        //case 'e': edit_task(date); break;
        //case 'r': remove_date(date); break;
    }
}

void print_options() {
    printf("\033[34m(c)\033[0mhoose date; ");
    printf("\033[34m(a)\033[0mdd task; ");
    printf("\033[34m(e)\033[0mdit task; ");
    printf("\033[34m(r)\033[0memove task; ");
    printf("\033[34m(q)\033[0muit: ");
}

// TODO replace excessive bash
void set_path() {
    printf("Enter directory to store todos: ");
    char* path = get_string();

    char command_in[2048] = {'\0'}; // TODO replace strcat() with dynamic alternative to avoid potential buffer overflows
    strcat(command_in, "echo '");
    strcat(command_in, path);
    strcat(command_in, "' > ~/.config/todos/directory.conf");

    system("mkdir -p ~/.config/todos");
    system(command_in);
}

char* get_path() {
    FILE* path_file = fopen("~/.config/todos/directory.conf", "r");
    if (path_file == NULL) set_path();
    return NULL;
}

int main() {
    char date[16], choice = '\0';
    //char* path = get_path();

    set_date(date, "today");

    while (choice != 'q') {
        clear_screen();
        printf("%s", date);//print_dates();
        print_options();
        choice = getc(stdin);
        //scanf(" %c", NULL); // silly
        evaluate_choice(choice, date);
    }

    clear_screen();

    return 0;
}