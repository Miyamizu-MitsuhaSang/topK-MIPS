//
//  calculator.cpp
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/29.
//

#include "calculator.h"
#include "../basic_structure/inverted_index.h"
#include "../basic_structure/query_matrix.h"

float Calculator::inner_product(const std::unordered_map<int, std::vector<Posting>>& index,
                                const std::vector<Query>& query,
                                const std::unordered_map<int, float>& max_posting_value,
                                const std::vector<float>& max_contributions,
                                int candidate_vec_id,
                                float min_product,
                                float tot_max) {
    float current_product = 0;
    size_t query_size = query.size();
    
    for (size_t i = 0; i < query_size; i++) {
        const auto& pair = query[i];
        // 计算 remaining_possible_sum
        tot_max -= max_contributions[i];
        const auto& it = index.find(pair.term_id);
        if (it != index.end()) {
            size_t vec_index;
            size_t size = it->second.size();
            if (index_binary_search(it->second, candidate_vec_id, vec_index, size)) {
                current_product += it->second[vec_index].value * pair.value;
            }
        }
        
        if (current_product + tot_max < min_product)
            break;
    }
    return current_product;
}

bool Calculator::index_binary_search(const std::vector<Posting>& it,
                                     int target,
                                     size_t& vec_id, size_t size) {
    int top = int(size) - 1;
    int buttom = 0;
    while (buttom <= top) {
        int mid = (buttom + top) / 2;
        int id = it[mid].vec_id;
        if (target == id) {
            vec_id = mid;
            return true;
        }
        if (target < id)    top = mid - 1;
        else    buttom = mid + 1;
    }
    return false;
}
