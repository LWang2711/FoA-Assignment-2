#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct non_zero_value {
    size_t row;
    size_t col;
    long value;
};

void read_dim(size_t *nrow, size_t *ncol);
struct non_zero_value *populate_non_zero(struct non_zero_value *non_zero, size_t *p_nnz);
bool read_nz_line(size_t *prow_num, size_t *pcol_num, long *pval);
void non_zero_swap(struct non_zero_value *non_zerov1, struct non_zero_value *non_zerov2);
void insertion_sort_non_zero(struct non_zero_value non_zero[], const size_t nnz);
void print_matrix(const size_t nrows, const size_t ncols, const struct non_zero_value non_zero[], const size_t nnz);
void print_stage_header(const size_t stage);
void print_delimiter(void);
int char_to_int(char character);
bool is_valid_value(int value);

int main (void) {
    size_t nrows, ncols;

    read_dim(&nrows, &ncols);

    struct non_zero_value *non_zeros_initial = malloc(0), *non_zero_target = malloc(0);

    size_t nnz_i = 0, nnz_t = 0;

    non_zeros_initial = populate_non_zero(non_zeros_initial, &nnz_i);

    non_zero_target = populate_non_zero(non_zero_target, &nnz_t);

    print_stage_header(0);

    printf("Initial matrix: %zux%zu, nnz=%zu\n", nrows, ncols, nnz_i);

    insertion_sort_non_zero(non_zeros_initial, nnz_i);

    print_matrix(nrows, ncols, non_zeros_initial, nnz_i);

    print_delimiter();

    printf("Target matrix: %zux%zu, nnz=%zu\n", nrows, ncols, nnz_t);

    insertion_sort_non_zero(non_zero_target, nnz_t);

    print_matrix(nrows, ncols, non_zero_target, nnz_t);

    print_stage_header(1);



    return 0;
}

/* 
reads and parses the string input of matrix dimensions from stdin into unsigned long form and
stores it into number of rows and columns.

parameters:
    nrow and ncol are pointers to the size_t number of rows and columns of a matrix.
*/
void read_dim(size_t *nrow, size_t *ncol) {
    int curr_char; // if using getchar(), must use int since need to return EOF code just in case

    *nrow = 0, *ncol = 0;

    while ((curr_char = getchar()) != EOF) {

        if (curr_char == 'x') {
            break;
        }

        *nrow = *nrow * 10 + curr_char - '0'; // tallying up via individual digits formula
    }

    while ((curr_char = getchar()) != EOF) {

        if (curr_char == '\n') {
            break;; // although we don't want the newline nor the terminating character, we want to read it so that it is not in the stdin buffer
        }

        *ncol = *ncol * 10 + curr_char - '0';
    }
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
struct non_zero_value *populate_non_zero(struct non_zero_value *non_zero, size_t *p_nnz) {;

    for (;;) {
        size_t row_num = 0, col_num = 0;
        long value = 0;

        if (!read_nz_line(&row_num, &col_num, &value)) {
            break;
        }

        (*p_nnz)++;

        struct non_zero_value nz_buffer_int = { // cast just in case of compiler conversion
            .row = (size_t) row_num,
            .col = (size_t) col_num,
            .value = (long) value
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
reads a standard line in the format of r,c,v for non-zero values into the value of whatever addresses are provided

parameters:
    prow_num and pcol_num are pointers to the row and column respectively at which the non-zero value is located
    in the matrix.
    pval is a pointer to the value of the non-zero entry in the matrix.
*/
bool read_nz_line(size_t *prow_num, size_t *pcol_num, long *pval) {
    int curr_char;

    bool value_is_neg = false;

    while ((curr_char = getchar()) != EOF) { // read the row number
        if (curr_char == '#') {
            getchar(); // get rid of the terminating character at the end of line for next matrix reading
            return false;
        }

        if (curr_char == ',') {
            break;
        }
            
        *prow_num = *prow_num * 10 + curr_char - '0';
    }

    while ((curr_char = getchar()) != EOF) { // read the column number
            
        if (curr_char == ',') {
            break;
        }
            
        *pcol_num = *pcol_num * 10 + curr_char - '0';
        }

    while ((curr_char = getchar()) != EOF) { // read the value
            
        if (curr_char == '\n') {
            if (value_is_neg) {
                *pval = -*pval;
            }
            return true;
        }

        if (curr_char == '-') {
            value_is_neg = true;
            continue; // in case of running into negative sign, save info but skip the rest of the loop
        }
            
        *pval = *pval * 10 + curr_char - '0';
    }

    return false;
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

    enum { MAX_DIM = 35 };

    bool has_valid_values = true;

    for (size_t nz_ind = 0; nz_ind < nnz; nz_ind++) {
        if (!is_valid_value(non_zero[nz_ind].value)) {
            has_valid_values = false; 
        }
    }

    if (nrows <= MAX_DIM && ncols <= MAX_DIM && has_valid_values) { // if within the allowed matrix size and all values are allowed
        for (size_t row = 0; row < nrows; row++) {
            printf("[");

            for (size_t col = 0; col < ncols; col++) {
                if (non_zero_ind <= nnz &&
                    row == non_zero[non_zero_ind].row &&
                    col == non_zero[non_zero_ind].col
                ) { if (non_zero[non_zero_ind].value == 0) { // in case the user enters 0 as a non-zero value
                    printf(" ");
                } else {
                    printf("%ld", non_zero[non_zero_ind].value);
                }
                non_zero_ind++;
                 } else {
                    printf(" ");
                }
            }

            printf("]\n");
        }
    } else { // if the matrix is too large or if there exists a non-allowed value
        for (size_t nz_ind = 0; nz_ind < nnz; nz_ind++) {
            printf("(%zu, %zu)=%ld\n", non_zero[nz_ind].row, non_zero[nz_ind].col, non_zero[nz_ind].value);
        }
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

/* 
check whether a non-zero value's int value is within the valid allowed value bounds
*/
bool is_valid_value(int value) {
    int valid_values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    size_t nvalid_values = sizeof(valid_values) / sizeof(valid_values[0]);

    for (size_t i = 0; i < nvalid_values; i++) {
        if (value == valid_values[i]) {
            return true;
        }
    }
    return false;
}
