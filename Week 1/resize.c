#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define PROMPT "Enter the Student IDs for the class list, followed by an empty line:\n"
#define MESSAGE "The IDs for the students in the class are:\n"
#define ID_LEN 8
#define INIT_ARRAY_SIZE 4

int get_id(char *ID);
int print_id(char **list, int i);

int main(int argc, char **argv) {
    
    printf("%s", PROMPT);

    char *id = (char*) malloc(sizeof(char) * (ID_LEN+1));
    char **list = (char**) malloc(sizeof(*id) * INIT_ARRAY_SIZE);
    int size = INIT_ARRAY_SIZE;

    int i = 0;
    while (scanf("%s", id) != EOF) {
        if (i > size) {
            size = 2 * size; 
            list = (char**) realloc(list, sizeof(*id)*size);
        }
        list[i] = malloc(sizeof(char) * (ID_LEN+1));
        strcpy(list[i], id);
        printf("%s\n", id);
        i++;
    }
    print_id(list, i);
    printf("The array contains %d items, and has a capacity of %d.", i, size);

    return 0;
}

int print_id(char **list, int i) {
    printf("\n%s", MESSAGE);
    int j;
    for (j=0; j<i; j++) {
        printf("%s", list[j]);
        if (j != (i-1)) {
            printf(", ");
        }
    }
    printf("\n");
    return 0;
}