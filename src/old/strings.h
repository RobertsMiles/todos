typedef struct Letter {
    char self;
    struct Letter* next;
} Letter;

// Returns a newly initialized head character.
Letter* new_string();

// Frees every letter of the string.
void free_string(Letter* head);

// Reads stdin into a given linked list of characters.
void read_string(Letter* head);

// Prints a given linked list of characters to stdout.
void print_string(Letter* head);