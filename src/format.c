#include "format.h"

#include <stdio.h>
#include <stddef.h>

/* 
prints the header for each stage given the level as an unsinged long.
*/
void print_stage_header(size_t stage) {
    enum { END_HEADER_LENGTH = 28};

    printf("==STAGE %zu", stage);
    for (size_t i = 0; i < END_HEADER_LENGTH; i++) {
        printf("=");
    }
    printf("\n");
}

/* 
prints the delimiter which clearly separates each of the matrices.
*/
void print_delimiter(void) {
    enum { DELIMITER_LENGTH = 37 };
    
    for (size_t i = 0; i < DELIMITER_LENGTH; i++) {
        printf("-");
    }
    printf("\n");
}
