//
//  inverted_index.cpp
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/29.
//

#include "inverted_index.h"
#include "compressed_matrix.h"
#include "query_matrix.h"
#include "../product/calculator.h"
#include "../product/heap_sorting/heap_sort.h"

#include <algorithm>
#include <random>

void InvertedIndex::build_index(const CSR_Matrix &matrix) {
    this->num_vectors = matrix.rows;
    this->num_features = matrix.cols;
    
    for (int vec_id = 0; vec_id < num_vectors; vec_id++) {
        int start = matrix.indptr[vec_id],
            end = matrix.indptr[vec_id + 1];
        for (int i = start; i < end; i++) {
            int term_id = matrix.indice[i];
            float value = matrix.data[i];
            
            index[term_id].emplace_back(vec_id, value);
        }
    }
    
    for (auto& [term_id, postings] : index) {
        float max_val = 0.0f;
        for (const auto& p : postings)
            max_val = std::max(max_val, p.value);
        max_posting_value[term_id] = max_val;
    }
}

InvertedIndex::InvertedIndex() : num_vectors(0), num_features(0) {
}

InvertedIndex::InvertedIndex(const CSR_Matrix& csr) {
    build_index(csr);
}

void InvertedIndex::insert(int term_id, int vec_id, float val) {
    index[term_id].push_back({vec_id, val});
}

std::optional<const std::vector<Posting>*> InvertedIndex::get_postings(int term_id) const {
    auto it = index.find(term_id);
    if (it != index.end())
        return &it->second;
    return nullopt;
}

int InvertedIndex::get_word_frequency(int term_id) const {
    auto it = index.find(term_id);
    if (it != index.end())
        return  int(it->second.size());
    return 0;
}

int InvertedIndex::get_vectors() const {
    return num_vectors;
}

int InvertedIndex::get_features() const {
    return num_features;
}

std::unordered_map<int, std::vector<Posting>>& InvertedIndex::get_index() {
    return index;
}

void InvertedIndex::clear() {
    index.clear();
    num_vectors = 0;
    num_features = 0;
}

//filter
std::unordered_set<int> InvertedIndex::filter_by_threshold(const QueryMatrix& query, float value_threshold) {
    const std::vector<Query>& query_list = query.getquery();
    std::unordered_set<int> candidates;
    candidates.reserve(query_list.size() * 5);  //减少哈希表重新计算次数
    candidates.max_load_factor(0.6f);
    
    for (const auto& pair : query_list) {
        auto it = index.find(pair.term_id);
        if (it != index.end())
            for(const auto& posting : it->second) {
                if (posting.value > value_threshold)
                    candidates.insert(posting.vec_id);
            }
    }
    return candidates;
}

void InvertedIndex::sample_postings(const std::vector<Posting> &postings, std::unordered_set<int> &candidates, float term_weight) {
    
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    for (const auto& posting : postings) {
        // 避免重复采样
        float dynamic_ratio = SAMPLE_RATIO * posting.value;
        if (dis(gen) < dynamic_ratio && candidates.find(posting.vec_id) == candidates.end()) {
            candidates.insert(posting.vec_id);
        }
        if (candidates.size() >= MAX_CANDIDATES)
            break;
    }
    
    // 更新候选向量集合
}

//对 query 进行降序排序（Query-to-Inverted Index 思路）
//
//预处理每个 query term 的最大可能贡献
//
//使用新的剪枝函数 inner_product_pruned

Sortable_List InvertedIndex::candidate_calculator(const QueryMatrix& query, int topk) {
    std::vector<Query> sorted_query = query.getquery();
    std::sort(sorted_query.begin(), sorted_query.end(), [](const Query& a, const Query& b) {
        return a.value > b.value;
    });
    
    std::vector<float> max_contributions(sorted_query.size());
    float total_max = 0.0f;
    for (size_t i = 0; i < sorted_query.size(); ++i) {
        float max_val = max_posting_value.count(sorted_query[i].term_id) ?
                        max_posting_value.at(sorted_query[i].term_id) : 0.0f;
        max_contributions[i] = sorted_query[i].value * max_val;
        total_max += max_contributions[i];
    }
    
    float value_threshold = 0.1;
    std::unordered_set<int> candidates = filter_by_threshold(query, value_threshold);
    
    for (const auto& pair : query.getquery()) {
        auto it = index.find(pair.term_id);
        if (it != index.end()) {
            sample_postings(it->second, candidates, pair.value);
        }
    }
    
    Sortable_List candidate_heap{topk};
    float min_product = -1;
    for (const auto& candidate : candidates) {
        float product = Calculator::inner_product(index,
                                                  sorted_query,
                                                  max_posting_value,
                                                  max_contributions,
                                                  candidate,
                                                  min_product,
                                                  total_max);
        if (candidate_heap.size() < topk || product > min_product) {
            candidate_heap.heap_insert(Matrix(candidate, product));
            if (candidate_heap.size() == topk)
                min_product = candidate_heap.get_list()[0].product;
        }
    }
    return candidate_heap;
}
