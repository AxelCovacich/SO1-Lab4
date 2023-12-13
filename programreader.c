#include <stdio.h>

int main() {
    int c;

    // Read characters from stdin until EOF
    while ((c = getchar()) != EOF) {
        putchar(c);
    }

    // Print a message indicating the end of file
    printf("\nEnd of File (EOF) reached.\n");

    return 0;
}
