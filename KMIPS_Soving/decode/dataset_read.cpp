//
//  dataset_read.cpp
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/6/1.
//

#include "dataset_read.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <stdexcept>

void read_dataset(const std::string& filename,
                  int64_t &num_rows, int64_t &num_cols, int64_t &nnz,
                  int64_t** indptr, int32_t** indices, float** data)
{
    std::ifstream infile(filename, std::ios::binary);
    if (!infile) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    // Read header: num_rows, num_cols, nnz
    int64_t sizes[3];
    infile.read(reinterpret_cast<char*>(sizes), 3 * sizeof(int64_t));
    if (!infile) {
        throw std::runtime_error("Failed to read header");
    }
    num_rows = sizes[0];
    num_cols = sizes[1];
    nnz = sizes[2];

    // Allocate and read indptr
    *indptr = new int64_t[num_rows + 1];
    infile.read(reinterpret_cast<char*>(*indptr), (num_rows + 1) * sizeof(int64_t));
    if (!infile) {
        delete[] *indptr;
        throw std::runtime_error("Failed to read indptr");
    }

    // Allocate and read indices
    *indices = new int32_t[nnz];
    infile.read(reinterpret_cast<char*>(*indices), nnz * sizeof(int32_t));
    if (!infile) {
        delete[] *indptr;
        delete[] *indices;
        throw std::runtime_error("Failed to read indices");
    }

    // Allocate and read data
    *data = new float[nnz];
    infile.read(reinterpret_cast<char*>(*data), nnz * sizeof(float));
    if (!infile) {
        delete[] *indptr;
        delete[] *indices;
        delete[] *data;
        throw std::runtime_error("Failed to read data");
    }
    
    //query

    infile.close();
}

void print_to_testfile()
{
    freopen("/Users/godrictan/Desktop/C:C++/KMIPS_Soving/KMIPS_Soving/Library/1.in", "w", stdout);
    int64_t num_rows, num_cols, nnz;
    int64_t* indptr = nullptr;
    int32_t* indices = nullptr;
    float* data = nullptr;
    
    const std::string filename = "/Users/godrictan/Desktop/C:C++/KMIPS_Soving/KMIPS_Soving/Library/base_small.csr";
        
    read_dataset(filename, num_rows, num_cols, nnz, &indptr, &indices, &data);
    std::cout << num_rows << ' ' << num_cols << ' ' << nnz << ' ' << std::endl;
    for (int i = 0; i <= num_rows ; i++)
        std::cout << indptr[i] << ' ';
    std::cout << std::endl;
    for (int i = 0; i < nnz; i++)
        std::cout << indices[i] << ' ';
    std::cout << std::endl;
    for (int i = 0; i < nnz; i++)
        std::cout << data[i] << ' ';
    std::cout << std::endl;
}

void csr2query()
{
    freopen("query.out", "w", stdout);
    int64_t num_rows, num_cols, nnz;
    int64_t* indptr = nullptr;
    int32_t* indices = nullptr;
    float* data = nullptr;
    
    const std::string filename = "/Users/godrictan/Desktop/C:C++/KMIPS_Soving/KMIPS_Soving/Library/queries.dev.csr";
    
    read_dataset(filename, num_rows, num_cols, nnz, &indptr, &indices, &data);
    
    //nq
    std::cout << num_rows << std::endl;
    
    //nnz_list
    for (int i = 0; i < num_rows; i++) {
        int64_t query_nnz = indptr[i + 1] - indptr[i];
        std::cout << query_nnz << std::endl;
        //vec_id
        for (int64_t index = indptr[i]; index < indptr[i + 1]; index++)
            std::cout << indices[index] << ' ';
        std::cout << std::endl;
        
        //values
        for (int64_t index = indptr[i]; index < indptr[i + 1]; index++)
            std::cout << data[index] << ' ';
        std::cout << std::endl;
    }
}
