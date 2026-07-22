#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct non_zero_value {
    size_t row;
    size_t col;
    int value;
};

struct non_zero_value *populate_non_zero(struct non_zero_value *non_zero, size_t *p_nnz);
void non_zero_swap(struct non_zero_value *non_zerov1, struct non_zero_value *non_zerov2);
void insertion_sort_non_zero(struct non_zero_value non_zero[], const size_t nnz);
void print_matrix(const size_t nrows, const size_t ncols, const struct non_zero_value non_zero[], const size_t nnz);
void print_stage_header(const size_t stage);
void print_delimiter(void);
int char_to_int(char character);

int main (void) {
    
    enum { MATRIX_DIM_FORMAT = 3 };

    char dim_buffer[MATRIX_DIM_FORMAT + 1 + 1]; // leave space for newline and terminating character so that it doesn't sit in stdin

    fgets(dim_buffer, sizeof(dim_buffer), stdin);

    const size_t nrows = char_to_int(dim_buffer[0]), ncols = char_to_int(dim_buffer[2]);

    struct non_zero_value *non_zeros_initial = malloc(0), *non_zero_target = malloc(0);

    size_t nnz_i = 0, nnz_t = 0;

    non_zeros_initial = populate_non_zero(non_zeros_initial, &nnz_i);

    non_zero_target = populate_non_zero(non_zero_target, &nnz_t);

    print_stage_header(0);

    printf("Initial matrix: %.*s, nnz=%zu\n", MATRIX_DIM_FORMAT, dim_buffer, nnz_i);

    insertion_sort_non_zero(non_zeros_initial, nnz_i);

    print_matrix(nrows, ncols, non_zeros_initial, nnz_i);

    print_delimiter();

    printf("Target matrix: %.*s, nnz=%zu\n", MATRIX_DIM_FORMAT ,dim_buffer, nnz_t);

    insertion_sort_non_zero(non_zero_target, nnz_t);

    print_matrix(nrows, ncols, non_zero_target, nnz_t);

    return 0;
}

/* 
populates an initially null dynamically allocated array with all of the non-zero values in row, col, value form
as structs for each array element. Also tracks how many non-zero values there are provided an external variable.

parameters:
    non_zero which is a pointer to the first element of initially null dynamically allocated array.
    p_nnz is a pointer to the number of non-zero values in encapsulating scope.

returns:
    same pointer to dynamically allocated array to which it was initially passed.
*/
struct non_zero_value *populate_non_zero(struct non_zero_value *non_zero, size_t *p_nnz) {

    enum { NON_ZERO_VALUE_FORMAT = 5 };

    char nz_buffer_str[NON_ZERO_VALUE_FORMAT + 1 + 1]; // need one extra character for the newline and terminating character

    for (;;) {
        fgets(nz_buffer_str, sizeof(nz_buffer_str), stdin);
        
        if (nz_buffer_str[0] == '#') {
            break;
        }

        (*p_nnz)++;

        struct non_zero_value nz_buffer_int = {
            .row = char_to_int(nz_buffer_str[0]),
            .col = char_to_int(nz_buffer_str[2]),
            .value = char_to_int(nz_buffer_str[4])
        };

        struct non_zero_value *temp = realloc(non_zero, sizeof(nz_buffer_int) * (*p_nnz));

        if (temp == NULL) { // check for proper allocation of memory
            free(non_zero);
            printf("Memory allocation failed.\n");
            return NULL;
        } else {
            non_zero = temp;
        }

        *(non_zero + *p_nnz - 1) = nz_buffer_int;
    }

    return non_zero; // pointer to pointer here might be better, although this still works
}

/* 
sorts an array of non-zero values fron lowest to highest row and then columns number in row major order using
insertion sort.

parameters:
    non_zero which is the array containing the non-zero values.
    nnz which is the length of the array containing non-zero values.
*/
void insertion_sort_non_zero(struct non_zero_value non_zero[], const size_t nnz) {
    for (size_t element_ind = 0; element_ind < nnz; element_ind++) { // sort through through each element of the array
        for (size_t left_ind = element_ind;
             left_ind >= 0 && left_ind <= nnz - 1 - 1 &&
              non_zero[left_ind].row >= non_zero[left_ind + 1].row;
               left_ind--) { // for each element, look at all of the elements to the left of the target element to be sorted
                if (non_zero[left_ind].row > non_zero[left_ind + 1].row) {
                    non_zero_swap(&non_zero[left_ind], &non_zero[left_ind + 1]); // swap in case of rows out of order
                } else if (non_zero[left_ind].row == non_zero[left_ind + 1].row){
                    if (non_zero[left_ind].col > non_zero[left_ind + 1].col) { // swap in case of cols out of order given the rows are the same
                        non_zero_swap(&non_zero[left_ind], &non_zero[left_ind + 1]);
                    }
                }
               }
    }
}

/* 
swaps the values of two non-zero values within an array of non-zero values in which they are both stored.

parameters:
    non_zerov1 the address of the first value to be swapped.
    non_zerov2 the address of the second value to be swapped.
*/
void non_zero_swap(struct non_zero_value *non_zerov1, struct non_zero_value *non_zerov2) {
    struct non_zero_value non_zero_buffer = *non_zerov1;
    *non_zerov1 = *non_zerov2;
    *non_zerov2 = non_zero_buffer;
}

void print_matrix(const size_t nrows, const size_t ncols, const struct non_zero_value non_zero[], const size_t nnz) {
    size_t non_zero_ind = 0;

    for (size_t row = 0; row < nrows; row++) {
        printf("[");

        for (size_t col = 0; col < ncols; col++) {
            if (non_zero_ind <= nnz &&
                row == non_zero[non_zero_ind].row &&
                col == non_zero[non_zero_ind].col
            ) {
                printf("%d", non_zero[non_zero_ind].value);
                non_zero_ind++;
            } else {
                printf(" ");
            }
        }

        printf("]\n");
    }
}

/* 
prints the header for each stage given the level as an int.
*/
void print_stage_header(const size_t stage) {
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

/* 
turns a singular char represented integer into its corresponding int represented integer.
*/
int char_to_int(char character) {
    return character - '0';
}
