#include <stdio.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int isWordCharacter(char c) {
    return isalpha(c) || c == '\''; // Consider apostrophes as part of words (e.g., "it's")
}

int main() {
    char fileName[BUFFER_SIZE];
    char input;
    FILE *file;
    char buffer[BUFFER_SIZE];
    int lines = 0;
    int words = 0;
    int inWord = 0;

    while(1) {
        printf("\nEnter f for entering file name, q to quit: ");
        scanf(" %c", &input);

        if (input == 'f') {
            printf("Enter file name: ");
            scanf("%s", fileName);

            file = fopen(fileName, "r");
            if (!file) {
                printf("%s cannot be opened\n", fileName);
            } else {
                lines = words = inWord = 0;

                while (fgets(buffer, BUFFER_SIZE, file)) {
                    lines++;
                    for (int i = 0; buffer[i]; i++) {
                        if (isWordCharacter(buffer[i])) {
                            if (!inWord) {
                                words++;
                                inWord = 1;
                            }
                        } else {
                            inWord = 0;
                        }
                    }
                    // Reset inWord at the end of each line
                    inWord = 0;
                }
                fclose(file);

                // Re-open and output the content of the file
                file = fopen(fileName, "r");
                printf("\nContent of %s:\n", fileName);
                while (fgets(buffer, BUFFER_SIZE, file)) {
                    printf("%s", buffer);
                }
                fclose(file);

                // Output the statistics
                printf("\nNumber of lines of file: %d\n", lines);
                printf("Number of words of file: %d\n", words);
                printf("Average number of words per line of file: %.2f\n", lines > 0 ? (float)words / lines : 0);
            }
        } else if (input == 'q') {
            printf("Good bye\n");
            break;
        } else {
            printf("Invalid command\n");
        }
    }
    return 0;
}
