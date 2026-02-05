#include <ctype.h>
#include <stdio.h>
#include <string.h>

int is_arg_count_valid(const int argc);
int is_filename_valid(const char* filename);
FILE* open_file(const char* filename);
void read_file(FILE* to_read);

int main(int argc, char *argv[]) {
    /* confirm we have good arguments */
    if (!is_arg_count_valid(argc)) {
        printf("Invalid arguments provided.\n");
        return 1;
    }

    /* make sure filename is good */
    const char* filename = argv[1];
    if (!is_filename_valid(filename)) {
        printf("File %s is not valid.\n", filename);
        return 1;
    }

    /* make sure we can open the file */
    char local_filename[50] = "./";
    strcat(local_filename, filename);
    FILE* to_read = open_file(local_filename);
    if (!to_read) {
        printf("Error reading file %s.\n", filename);
        return 1;
    }

    /* read it! */
    read_file(to_read);
    fclose(to_read);
    return 0;
}

/* confirms we have the proper amount of arguments */
int is_arg_count_valid(const int argc) {
    return argc == 2;
}

/* only allow alphanumeric and periods */
int is_filename_valid(const char* filename) {
    for (int i = 0; filename[i] != EOF && filename[i] != '\0'; i++) {
        const char letter = filename[i];
        if (!isalnum(letter) && letter != '.' && letter != '\n') {
            return 0;
        }
    }
    return 1;
}

/* simple file open */
FILE* open_file(const char* filename) {
    return fopen(filename, "r");
}

/* read a valid file */
void read_file(FILE* to_read) {
    char line[255];

    int line_count = 1;
    while (*fgets(line, 255, to_read) != '\0') {
        printf("Line %d: %s", line_count++, line);
        // line now contained comma-delimited information
        char* split = strtok(line, ",");
        while (split != NULL) {
            printf("Split: %s\n", split);
            split = strtok(NULL, ",");
        }
    }
}

