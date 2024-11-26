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
char* get_date(char* choice) {
    char command_in[64] = {'\0'}; // TODO replace strcat() with dynamic alternative to avoid potential buffer overflows
    strcat(command_in, "date --date='");
    strcat(command_in, choice);
    strcat(command_in, "' +%F");
    FILE* command_out = popen(command_in, "r");
    //fgets(date, 16, command_out);
    printf("get_string(command_out)");
    char* date = get_string(command_out);
    if (pclose(command_out)) return NULL;
    return date;
}

char *choose_date() {
    char *date = NULL;
    while (date == NULL) {
        printf("Date: ");
        //fflush(stdin);
        while ((getchar()) != '\n');
        char *choice = get_string(stdin);
        date = get_date(choice);
    }
    return date;
}

char* evaluate_choice(char choice) {
    switch (choice) {
        case 'c': return choose_date();
        //case 'a': add_task(date); break;
        //case 'e': edit_task(date); break;
        //case 'r': remove_date(date); break;
        default: return get_date("today");
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
    char* path = get_string(stdin);

    char command_in[2048] = {'\0'}; // TODO replace strcat() with dynamic alternative to avoid potential buffer overflows
    strcat(command_in, "echo '");
    strcat(command_in, path);
    strcat(command_in, "' > ~/.config/todos/directory.conf");

    system("mkdir -p ~/.config/todos");
    system(command_in);
}

char* get_path() {
    FILE* path_stream = fopen("~/.config/todos/directory.conf", "r");
    //if (path_stream == NULL) set_path();
    return get_string(path_stream);
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
    char *date, choice = '\0';
    //char* path = get_path();
    //printf("%s\n", path);

    date = get_date("today");

    while (choice != 'q') {
        //clear_screen();
        printf("%s\n\n", date);//print_dates();
        print_options();
        //choice = get_char(stdin);
        choice = getc(stdin);
        //fflush(stdin);
        date = evaluate_choice(choice);
    }

    clear_screen();

    return 0;
}