#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct non_zero_value {
    int row;
    int col;
    int value;
};

struct non_zero_value *populate_non_zero(struct non_zero_value *non_zero, int *p_nnz);
void print_stage_header(int stage);
int char_to_int(char character);

int main (void) {
    
    enum { MATRIX_DIM_FORMAT = 3 };

    char dim_buffer[MATRIX_DIM_FORMAT + 1];

    fgets(dim_buffer, sizeof(dim_buffer), stdin);

    struct non_zero_value *non_zeros_initial = malloc(0); // set as intially taking up no space

    int nnz = 0;

    non_zeros_initial = populate_non_zero(non_zeros_initial, &nnz);

    print_stage_header(0);

    printf("Initial matrix: %s, nnz=%d\n", dim_buffer, nnz);

    // int initial_matrix[char_to_int(dim_buffer[0])][char_to_int(dim_buffer[3])];

    // for each of the non-zeros positions, index into the dummy matrix and place the value

    // print out the dummy matrix in 

    // repeat the exact same thing for the target matrix

    return 0;
}

struct non_zero_value *populate_non_zero(struct non_zero_value *non_zero, int *p_nnz) {

    enum { NON_ZERO_VALUE_FORMAT = 5 };

    char nz_buffer_str[NON_ZERO_VALUE_FORMAT + 1 + 1];

    fgets(nz_buffer_str, sizeof(nz_buffer_str), stdin); // need to check whether initial line is already terminated

    for (;;) {
        fgets(nz_buffer_str, sizeof(nz_buffer_str), stdin);
        
        if (nz_buffer_str[0] == '#') {
            break;
        }

        (*p_nnz)++;

        struct non_zero_value nz_buffer_int = { // turn into corresponding ASCII values by removing the ASCII offset
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

void print_stage_header(int stage) {
    printf("==STAGE %d", stage);
    for (int i = 0; i < 27; i++) {
        printf("=");
    }
    printf("\n");
}

int char_to_int(char character) {
    return character - '0';
}
