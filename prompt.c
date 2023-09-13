#include "main.h"
#include "getline.h"
#include "strtok.h"

int main() {
    char cmd[] = "This is 'a; test' with\\n escape; sequences";
    size_t count = cmd_to_split(cmd);

    printf("Number of tokens: %zu\n", count);

    // Print each token
    char *token = cmd;
    for (size_t i = 0; i < count; i++) {
        printf("Token %zu: '%s'\n", i + 1, token);
        // Move to the next token (if any)
        token += _strlen(token) + 1;
    }

    return 0;
}