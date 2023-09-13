#include "main.h"
#include "getline.h"
#include "strtok.h"

int main() {
    char cmd[] = "This is 'a; test' with\\n escape; sequences";
    size_t count = cmd_to_split(cmd), i;
    char *token = cmd;

    printf("Number of tokens: %lu\n", count);

    /*Print each token*/
    for (i = 0; i < count; i++) {
        printf("Token %lu: '%s'\n", i + 1, token);
        /*Move to the next token (if any)*/
        token += _strlen(token) + 1;
    }

    return 0;
}