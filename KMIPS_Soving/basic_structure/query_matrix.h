//
//  query_matrix.h
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/29.
//

#ifndef QUERY_MATRIX_H
#define QUERY_MATRIX_H

#include "compressed_matrix.h"
#include "Library.h"

#include <vector>

class QueryMatrix {
public:
    QueryMatrix(int nnz);
    size_t size() const;
    
    const std::vector<Query>& getquery() const;
    
protected:
    std::vector<Query> query;
    size_t nnz;
    
    void read_in(int nnz);
};

#endif
