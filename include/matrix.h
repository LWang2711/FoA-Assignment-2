#pragma once

#include <stddef.h>

struct nz_value {
    size_t row;
    size_t col;
    long val;
};

void read_dim(size_t *nrow, size_t *ncol);

struct nz_value *populate_non_zero(
    struct nz_value *non_zero,
    size_t *p_nnz);

void insertion_sort_non_zero(
    struct nz_value non_zero[],
    size_t nnz);

void print_matrix(
    size_t nrows,
    size_t ncols,
    const struct nz_value non_zero[],
    size_t nnz);
