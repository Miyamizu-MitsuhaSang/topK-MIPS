//
//  dataset_read.cpp
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/6/1.
//

#ifndef DATASET_READ_H
#define DATASET_READ_H

#include <cstdint>
#include <string>

void read_dataset(const std::string& filename,
                  int64_t &num_rows, int64_t &num_cols, int64_t &nnz,
                  int64_t** indptr, int32_t** indices, float** data);
void print_to_testfile();
void csr2query();

#endif
