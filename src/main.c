#include <stdio.h>

void clear_screen() {
    printf("\e[1;1H\e[2J");
}

int main() {
    char* selected_date;

    set_path();
}
