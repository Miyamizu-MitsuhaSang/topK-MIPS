//
//  heap_sort.cpp
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/29.
//

#include "heap_sort.h"

Sortable_List::Sortable_List(int topk) : count(0), topk(topk) {
    list.reserve(topk);
}

Sortable_List::Sortable_List(const std::vector<Matrix>& original, int topk) : topk(topk) {
    list = original;
    this->count = int(original.size());
}

Sortable_List::Sortable_List(const Sortable_List& original) {
    this->list = original.list;
    this->count = original.count;
}

//void Sortable_List::build_heap() {
//    int low;
//    for (low = int(count) / 2 - 1; low >= 0; low--) {
//        Matrix current = list[low];
//        insert_heap(current, low, list.size() - 1);
//    }
//}

const std::vector<Matrix>& Sortable_List::get_list() const {
    return list;
}

size_t Sortable_List::size() const {
    return count;
}

//小根堆
//ShiftDown
void Sortable_List::insert_heap(const Matrix& current,
                                size_t low,
                                size_t high) {
    size_t small = 2 * low + 1;
    while (small <= high) {
        if (small < high && list[small] > list[small + 1])
            small++;
        if (current <= list[small])
            break;
        else {
            list[low] = list[small];
            low = small;
            small = 2 * low + 1;
        }
    }
    list[low] = current;
}

//void Sortable_List::heap_sort() {
//    Matrix current;
//    size_t last_unsorted;
//    build_heap();
//    for (last_unsorted = count - 1; last_unsorted > count - topk - 1; last_unsorted--) {
//        current = list[last_unsorted];
//        list[last_unsorted] = list[0];
//        insert_heap(current, 0, last_unsorted - 1);
//    }
//}

void Sortable_List::heap_insert(const Matrix& current) {
    if (count < topk) {
        list.push_back(current);
        count++;
        insert_new(count - 1);
    }
    //count == topk
    else {
        if (current > list[0])
            insert_heap(current, 0, count - 1);
    }
}

void Sortable_List::insert_new(int index) {
    while (index) {
        int parent = (index - 1) / 2;
        if (list[parent] > list[index])
            std::swap(list[parent], list[index]);
        index = parent;
    }
}

void Matrix::operator=(const Matrix &original) {
    this->vec_id = original.vec_id;
    this->product = original.product;
}

bool operator < (const Matrix& x, const Matrix& y)
{
    return x.product < y.product;
}

bool operator > (const Matrix& x, const Matrix& y)
{
    return x.product > y.product;
}

bool operator == (const Matrix& x, const Matrix& y)
{
    return x.product == y.product;
}

bool operator <= (const Matrix& x, const Matrix& y)
{
    return x.product <= y.product;
}

bool operator >= (const Matrix& x, const Matrix& y)
{
    return x.product >= y.product;
}
