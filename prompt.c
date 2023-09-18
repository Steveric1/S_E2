#include "main.h"
#include "headerfile.h"

int main() {
    const char *inputString = "apple,banana,cherry,grape";
    char delimiter = ',';
    
    path_helper help;
    help.path = inputString;
    help.delim = delimiter;

    // Call path_to_list to split the inputString
    directory_n *resultList = path_to_list(NULL, help);

    if (resultList) {
        // Print the resulting list
        directory_n *current = resultList;
        while (current) {
            printf("%s\n", current->path);
            current = current->link;
        }

        // Free the memory allocated for the list (assuming you have a free_dir function)
        free_dir(&resultList);
    }

    return 0;
}