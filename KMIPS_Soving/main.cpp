//
//  main.cpp
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/28.
//

//数据预处理
//  构建 CSR 矩阵：将原始稀疏向量转换为 CSR 格式。
//  建立倒排索引：遍历 CSR 矩阵，为每个非零特征生成倒排列表。
//查询阶段
//  过滤候选向量：
//      仅考虑查询向量中非零特征对应的倒排列表中的向量。
//  计算内积：
//      对候选向量，使用 CSR 格式快速计算与查询向量的内积。
//  维护 Top-K 堆
//      动态更新当前最大的 K 个内积值。

#include "./basic_structure/compressed_matrix.h"
#include "./basic_structure/query_matrix.h"
#include "./basic_structure/inverted_index.h"
#include "./product/heap_sorting/heap_sort.h"

#include <fstream>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <chrono>
#include <algorithm>
using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);  // 关键优化
    std::cin.tie(nullptr);
    
    freopen("/Users/godrictan/Desktop/C:C++/A_KMIPS_OJ_Version/A_KMIPS_OJ_Version/Library/1.out", "w", stdout);
    
    std::ifstream CSR_file("/Users/godrictan/Desktop/C:C++/A_KMIPS_OJ_Version/A_KMIPS_OJ_Version/Library/base_small/base_small.txt");
    std::cin.rdbuf(CSR_file.rdbuf());
    
    //time_start
    auto start = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(start - start);

    int row, col, nnz, topk;
    cin >> row >> col >> nnz >> topk;
    CSR_Matrix MatrixSet = CSR_Matrix(row, col, nnz);
    
    InvertedIndex table(MatrixSet);
    
    std::ifstream query_file("/Users/godrictan/Desktop/C:C++/A_KMIPS_OJ_Version/A_KMIPS_OJ_Version/Library/base_small/queries.txt");
    std::cin.rdbuf(query_file.rdbuf());
    int nq;
    cin >> nq;
    for (int i = 0; i < nq; i++) {
        cin >> nnz;
        QueryMatrix query = QueryMatrix(nnz);
        
        Sortable_List candidates = table.candidate_calculator(query, topk);
        auto end = std::chrono::high_resolution_clock::now();
        duration += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        const std::vector<Matrix>& list = candidates.get_list();
        int length = int(list.size());
//        std::sort(list.begin(), list.end(), std::greater<>());
        
        for (int i = length - 1; i > length - topk - 1; i--) {
            cout << list[i].vec_id << ' ';
        }
        cout << endl;
        start = std::chrono::high_resolution_clock::now();
    }
    
    // std::freopen("/dev/tty", "w", stdout);
    std::cerr << "程序执行时间: " << duration.count() << " 毫秒" << std::endl;
    return 0;
}
