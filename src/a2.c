#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "format.h"

/*
bool is_equal_matrices(
    const struct non_zero_value m1[],
    const struct non_zero_value m2[],
    const size_t nnz1,
    const size_t nnz2
); // helper matrix in future
bool is_later_inmat(const struct non_zero_value test, const struct non_zero_value ref); // matrix helper in future
bool is_valid_operation(const char op); // matrix helper in future
*/

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

    print_stage_header(1);

    // call active_operation function

    return 0;
}


// this is all for part 2

/*

struct ls_nz_struct {
    bool is_present;
    size_t ind;
};

struct ls_nz_struct ls_nz(
    const struct non_zero_value non_zero[],
    const struct non_zero_value entry,
    const size_t nnz) {

        struct ls_nz_struct nz_pos;

        for (size_t nz_ind = 0; nz_ind < nnz; nz_ind++) {
            if (entry.row == non_zero[nz_ind].row &&
                entry.col == non_zero[nz_ind].col) {
                    nz_pos.is_present = true;
                    nz_pos.ind = nz_ind;
                    break;
                } else if (is_later_inmat(entry, non_zero[nz_ind])) {
                    nz_pos.is_present = false;
                    nz_pos.ind = nz_ind;
                    break;
                }
        }
        return nz_pos;
}

*/


/* 
compares a test non-zero value to a reference non-zero value to see whether the test is later in the matrix than reference
according to row major column minor order.

parameters:
    test is the non-zero value to be tested against whether it is later in the matrix comapared to ref non-zero value

returns:
    true if test is later in position than ref.
    false if test is not later in position than ref.
*/

/*
bool is_later_inmat(const struct non_zero_value test, const struct non_zero_value ref) {
    if (test.row > ref.row) {
        return true;
    } else if (test.row == ref.row && test.col > ref.col) {
        return true;
    }

    return false;
}
*/


// build scaffolding to just one operation then figure out how to repeat it

/*

void active_operation() {
    int curr_op = getchar();
    getchar(); // clear the : mark after the operation code is inputted

    if (curr_op != EOF) { // check that it didn't read end of file
        char curr_op = (char) curr_op;
    } else {
        return;
    }

    if (is_valid_operation(curr_op)) {
        switch (curr_op) {
            case 's':
                operation_set();
            case 'S':
                operation_swap();
            case 'm':
                operation_multiply();
            case 'a':
                operation_add(); */

            /*
            case 'r':
                operation_copy_row
            case 'c':
                operation_copy_col
            case 'R':
                operation_swap_row
            case 'C':
                operation_swap_col
            */

            /*
            default:
                return;
        }    
    }

}

void operation_set(
    const size_t nrows,
    const size_t ncols,
    struct non_zero_value non_zero[],
    size_t nnz) {
        size_t set_row = 0;
        size_t set_col = 0;
        long set_val = 0;

        read_nz_line(&set_row, &set_col, &set_val);

        struct non_zero_value inserted_nz = {
            .row = set_row,
            .col = set_col,
            .value = set_val
        };

        
}

*/



// we are going to use linear search here


/*
bool is_valid_dim(size_t dim, size_t max_dim) {
    return dim <= max_dim;
}

bool is_valid_val() {

}


bool is_valid_operation(const char op) {
    char valid_operations[] = {'s', 'S', 'm', 'a', 'r', 'c', 'R', 'C'};

    for (size_t i = 0; i < sizeof(valid_operations) / sizeof(valid_operations[0]); i++) {
        if (op == valid_operations[i]) {
            return true;
        }
    }

    return false;
}

*/

/* 
checks whether or not two matrices represented in non-zero sparse form are exactly equal.

parameters:
    m1 and m2 are arrays containing the non-zero values of the two matrices to be comapred in sparse form.
    nnz1 and nnz2 are the number of non-zero values 
*/

/*
bool is_equal_matrices(
    const struct non_zero_value m1[],
    const struct non_zero_value m2[],
    const size_t nnz1,
    const size_t nnz2) {

        if (nnz1 != nnz2) {
            return false;
        }

        for (size_t nz_ind = 0; nz_ind < nnz1; nz_ind++) {
            if (m1[nz_ind].row != m2[nz_ind].row ||
                m1[nz_ind].col != m2[nz_ind].col ||
                m1[nz_ind].value != m2[nz_ind].value) {
                    return false;
                }
            }
            return true;
        }
*/
