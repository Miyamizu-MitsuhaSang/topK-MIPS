//
//  query_matrix.cpp
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/29.
//

#include "query_matrix.h"

#include <iostream>

QueryMatrix::QueryMatrix(int nnz) : nnz(nnz) {
    query.reserve(nnz);
    read_in(nnz);
}

void QueryMatrix::read_in(int nnz) {
    int* ids = new int[nnz];
    for (int i = 0; i < nnz; i++) {
        int tmp;
        std::cin >> tmp;
        ids[i] = tmp;
    }
    for (int i = 0; i < nnz; i++) {
        float tmp;
        std::cin >> tmp;
        query.push_back({ids[i], tmp});
    }
    delete[] ids;   //memory leak
}

size_t QueryMatrix::size() const {
    return size_t(nnz);
}

const std::vector<Query>& QueryMatrix::getquery() const {
    return query;
}
