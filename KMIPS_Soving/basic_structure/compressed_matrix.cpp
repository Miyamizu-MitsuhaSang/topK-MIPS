//
//  compressed_matrix.cpp
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/28.
//

#include "compressed_matrix.h"

#include <iostream>
using namespace std;

void optimizeIO() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

//col unused
CSR_Matrix::CSR_Matrix(int row, int col, int nnz) : rows(row), cols(col), nnz(nnz) {
    indptr = new unsigned int[row + 1];
    indice = new unsigned int[nnz];
    data = new float[nnz];
    //indptr
    for (int i = 0; i <= row; i++) {
        int tmp;
        cin >> tmp;
        indptr[i] = tmp;
    }
    
    //indice
    for (int i = 0; i < nnz; i++) {
        int tmp;
        cin >> tmp;
        indice[i] = tmp;
    }
    
    //data
    for (int i = 0; i < nnz; i++) {
        float tmp;
        cin >> tmp;
        data[i] = tmp;
    }
}

CSR_Matrix::~CSR_Matrix() {
    delete[] indptr;
    delete[] indice;
    delete[] data;
}
