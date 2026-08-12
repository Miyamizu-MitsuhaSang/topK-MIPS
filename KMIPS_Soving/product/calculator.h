//
//  calculator.h
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/29.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "../basic_structure/Library.h"
#include "../basic_structure/inverted_index.h"

#include <vector>
#include <unordered_map>

class Calculator {
public:
    static float inner_product(const std::unordered_map<int, std::vector<Posting>>& index,
                               const std::vector<Query>& query,
                               const std::unordered_map<int, float>& max_posting_value,
                               const std::vector<float>& max_contributions,
                               int candidate_vec_id,
                               float min_product,
                               float tot_max);
    
    static bool index_binary_search(const std::vector<Posting>& it,
                                    int target,
                                    size_t& vec_id, size_t size);
};

#endif
