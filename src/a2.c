#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "format.h"

int main (void) {
    size_t nrows, ncols;

    read_dim(&nrows, &ncols);

    struct nz_value *non_zeros_initial = malloc(0), *non_zero_target = malloc(0);

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

    return 0;
}
