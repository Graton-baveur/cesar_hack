#include <stdio.h>
#include "cesar_function.h"
#include <stdbool.h>
#include <stdlib.h>

const int SIZE_ASCII_LOWERCASE = 25;
const int SIZE_ASCII_UPPERCASE = 25;

const char ASCII_LOWERCASE[26] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z'};
const char ASCII_UPPERCASE[26] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
        'W', 'X', 'Y', 'Z'};


void initArray(Array *a, size_t initialSize) {
    /**
    * Create a new dynamic array.
    * @param a is the structure that contain the array of character.
    * @param initialSize is the size of array .
    * @return void
    */
    a->array = malloc(initialSize * sizeof(char));
    a->used = 0;
    a->size = initialSize;
}

void freeArray(Array *a) {
    /**
    * Erase the content of the given array
    * @param a is the structure that contain the array of character.
    * @return void
    */
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

void insertArray(Array *a, char *element) {
    /**
     * Allow to insert an element in the array and automatically reallocate size. Allow to emulate dynamic array.
     * @param a is the structure that contain the array of character.
     * @param element is the character to insert in the array
     * @return void
     */
    if (a->used == a->size) {
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(char));
    }
    a->array[a->used++] = element;
}

void printArray(Array *a) {
     /**
     * Print each element of the array
     * @param a is the structure that contain the array of character
     * @return void
     */
    for (int i = 0; i < a->used; i++) {
        printf("%c", a->array[i]);
    }
    printf("\n");

}


bool is_lowercase(char letter) {
     /**
     * Return true if the character given is in lowercase.
     * @param letter character to test
     * @return true if the test is a succeed
     */

    for (int i = 0; i < SIZE_ASCII_LOWERCASE ;
    i++) {
        if (letter == ASCII_LOWERCASE[i]) {
            return true;
        }
    }
    return false;
}

bool is_uppercase(char letter) {
    /**
    * Return true if the character given is in uppercase.
    * @param letter character to test
    * @return true if the test is a succeed
    */

    for (int i = 0; i < SIZE_ASCII_UPPERCASE ;
    i++) {
        if (letter == ASCII_UPPERCASE[i]) {
            return true;
        }
    }
    return false;
}

void round_uppercase(char *letter, int shift ) {
    /**
    * Shift the given uppercase character with shift value.
    * @param letter character to test
    * @param value used to shift.
    * @return void
    */
    int index = 0;
    for (int i = 0; i < SIZE_ASCII_UPPERCASE ;
    i++) {
        if (*letter == ASCII_UPPERCASE[i]) {
            index = i;
        }
    }
    index = index + shift;

    if (index <= SIZE_ASCII_LOWERCASE) {
        *letter = ASCII_UPPERCASE[index];
    }
    if (index > SIZE_ASCII_LOWERCASE) {
        index = index - SIZE_ASCII_LOWERCASE;
        *letter = ASCII_UPPERCASE[index];
    }
}

void round_lowercase(char *letter, int shift) {
    /**
    * Shift the given lowercase character with shift value.
    * @param letter character to test
    * @param value used to shift.
    * @return void
    */
    int index = 0;
    for (int i = 0; i < SIZE_ASCII_LOWERCASE ;
    i++) {
        if (*letter == ASCII_LOWERCASE[i]) {
            index = i;
        }
    }
    index = index + shift;

    if (index <= SIZE_ASCII_UPPERCASE) {
        *letter = ASCII_LOWERCASE[index];
    }
    if (index > SIZE_ASCII_UPPERCASE) {
        index = index - SIZE_ASCII_UPPERCASE;
        *letter = ASCII_LOWERCASE[index];
    }
}

char round_cipher(Array *cipher, int shift) {
    /**
    * Shift all the character of the array with the shift value given
    * @param letter character to test
    * @param value used to shift.
    * @return void
    */
    for (int i = 0; i < cipher->size; i++) {
        if (is_lowercase(cipher->array[i]) == true) {
            round_lowercase(&cipher->array[i], shift);
            continue;
        }
        if (is_uppercase(cipher->array[i]) == true) {
            round_uppercase(&cipher->array[i], shift);
            continue;
        } else {
            continue;
        }
    }
    return cipher;
}

int main(int argc, char **argv) {
    int round = strtol(argv[2], NULL, 10);;
    int count = 0;
    while (argv[++count] != NULL);
    if (count != 3) {
        printf("Wrong args passed \n");
        printf("Should be ./cesar cipher round \n");
    } else {
        printf("----------CESAR HACK START ------------------");
        /// Initialize dynamic array with Array struct
        Array cipher;
        int size_of_cipher = 0;
        while (argv[1][size_of_cipher] != NULL) {
            size_of_cipher++;
        };

        initArray(&cipher, size_of_cipher);

        printf("\nCipher text: \n");
        /// Fill in the array with arg passed in argument
        char *p;
        for (p = *(argv + 1); *p; p++) {
            printf("%c", *p);
            insertArray(&cipher, *p);
        }
        printf("\n");

        /// decode the ciphertext
        round_cipher(&cipher, round);

        printf("Plaintext: \n");
        printArray(&cipher);
    }
    return 0;
}
