//
// Created by Denozi on 07/07/2021.
//
#include <stdbool.h>

typedef struct {
    int *array;
    size_t used;
    size_t size;
} Array;
char round_cipher(Array *cipher, int shift);
bool is_lowercase(char letter);
bool is_uppercase(char letter);
void initArray(Array *a, size_t initialSize);
void freeArray(Array *a);
void insertArray(Array *a, char *element);
void printArray(Array *a);

