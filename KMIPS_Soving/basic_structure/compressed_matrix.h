//
//  compressed_matrix.h
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/28.
//

#ifndef COMPRESSED_MATRIX_H
#define COMPRESSED_MATRIX_H

struct CSR_Matrix {
    unsigned int* indptr;
    unsigned int* indice;
    float* data; //float may cause value missing
    
    int rows;       //num of vectors
    int cols;       //size of id_table
    int nnz;        //num not zero
    
    CSR_Matrix(int row, int col, int nnz);
    ~CSR_Matrix();
};

#endif
