//
//  inverted_index.h
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/29.
//

#ifndef INVERTED_INDEX
#define INVERTED_INDEX

#include "Library.h"

#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <random>

using namespace std;

class CSR_Matrix;
class QueryMatrix;
class Sortable_List;

class InvertedIndex {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
    
    const double SAMPLE_RATIO = 0.1;
    const int MAX_CANDIDATES = 1000;
    //(term_id, (vec_id, value))
    std::unordered_map<int, std::vector<Posting>> index;
    std::unordered_map<int, float> max_posting_value;
    int num_vectors;
    int num_features;
    
    void build_index(const CSR_Matrix& matrix);
    
    //filter
    std::unordered_set<int> filter_by_threshold(const QueryMatrix& query,
                                                float value_threshold = 0.0);
    
    void sample_postings(const std::vector<Posting>& postings,
                         std::unordered_set<int>& candidates,
                         float term_weight);
    
public:
    InvertedIndex();
    InvertedIndex(const CSR_Matrix& csr);
    
    void insert(int term_id, int vec_id, float val);
    std::optional<const std::vector<Posting>*> get_postings(int term_id) const;
    
    int get_word_frequency(int feature_id) const;
    int get_vectors() const;
    int get_features() const;
    std::unordered_map<int, std::vector<Posting>>& get_index();
    
    Sortable_List candidate_calculator(const QueryMatrix& query, int topk);
    
    void clear();
};

#endif
