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
void set_date(char *choice, char *date) {
    char command_in[64] = {'\0'}; // TODO replace strcat() with dynamic alternative to avoid potential buffer overflows
    strcat(command_in, "date --date='");
    strcat(command_in, choice);
    strcat(command_in, "' +%F");
    FILE* command_out = popen(command_in, "r");
    //fgets(date, 16, command_out);
    printf("set_string(command_out)");
    set_string(command_out, date);
    if (pclose(command_out)) date = NULL;
}

void choose_date(char *date) {
    char *choice = NULL;
    while (choice == NULL) {
        printf("Date: ");
        //fflush(stdin);
        while ((getchar()) != '\n');
        set_string(stdin, choice);
        set_date(choice, date);
    }
}

void evaluate_choice(char choice, char *date) {
    switch (choice) {
        case 'c': choose_date(date);
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
void configure_path(char *path) {
    printf("Enter directory to store todos: ");
    set_string(stdin, path);

    char command_in[2048] = {'\0'}; // TODO replace strcat() with dynamic alternative to avoid potential buffer overflows
    strcat(command_in, "echo '");
    strcat(command_in, path);
    strcat(command_in, "' > ~/.config/todos/directory.conf");

    system("mkdir -p ~/.config/todos");
    system(command_in);
}

void set_path(char *path) {
    FILE* path_stream = fopen("~/.config/todos/directory.conf", "r");
    //if (path_stream == NULL) configure_path();
    set_string(path_stream, path);
}

/*
char get_char(FILE *stream) {
    //fprintf(stdin, "bbbsdbsdgbdgbsdgb");
    //while ((getchar()) != '\n');
    return getc(stream);
    fflush(stream);
}
*/

int main() {
    char *date, *path, choice = '\0';
    //set_path(date);
    //printf("%s\n", path);

    set_date("today", date);

    return -1;

    while (choice != 'q') {
        //clear_screen();
        printf("%s\n\n", date);//print_dates();
        print_options();
        //choice = get_char(stdin);
        choice = getc(stdin);
        //fflush(stdin);
        evaluate_choice(choice, date);
    }

    clear_screen();

    return 0;
}