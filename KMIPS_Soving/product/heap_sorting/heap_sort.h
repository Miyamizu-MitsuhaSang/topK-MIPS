//
//  heap_sort.h
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/29.
//

//TODO: 仅维护大小为 topk 的小顶堆
#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <vector>
#include <list>

struct Matrix {
    int vec_id;
    float product;
    
    Matrix() {}
    Matrix(int id, float product) : vec_id(id), product(product) {}
    
    void operator = (const Matrix& original);
    
};

bool operator < (const Matrix& x, const Matrix& y);
bool operator > (const Matrix& x, const Matrix& y);
bool operator == (const Matrix& x, const Matrix& y);
bool operator <= (const Matrix& x, const Matrix& y);
bool operator >= (const Matrix& x, const Matrix& y);

class Sortable_List {
public:
    void heap_sort();
    void heap_insert(const Matrix& current);
    
    Sortable_List(int topk);
    Sortable_List(const std::vector<Matrix>& original, int topk);
    Sortable_List(const Sortable_List& original);
    
    const std::vector<Matrix>& get_list() const;
    size_t size() const;
    
protected:
    void build_heap();
    void insert_heap(const Matrix& current, size_t low, size_t high);
    void insert_new(int index);
    
    std::vector<Matrix> list;
    int count;
    int topk;
};

#endif
