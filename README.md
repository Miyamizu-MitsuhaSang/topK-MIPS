# topK-MIPS

topK-MIPS 是一个 C++ 实现的稀疏向量 Maximum Inner Product Search (MIPS) 实验项目。项目使用 CSR 矩阵存储基础向量，基于倒排索引生成候选集合，并维护固定大小的小根堆返回每个查询的 Top-K 内积结果。

## 项目结构

```text
.
├── KMIPS_Soving/
│   ├── main.cpp
│   ├── basic_structure/
│   │   ├── Library.h
│   │   ├── compressed_matrix.*
│   │   ├── inverted_index.*
│   │   └── query_matrix.*
│   ├── decode/
│   │   └── dataset_read.*
│   └── product/
│       ├── calculator.*
│       └── heap_sorting/
│           └── heap_sort.*
└── KMIPS_Soving_High_PERFORMANCE.xcodeproj/
```

## 核心流程

1. 从输入中读取基础向量集合的 CSR 表示。
2. 为 CSR 矩阵建立倒排索引。
3. 读取查询向量，并按查询项权重排序。
4. 使用阈值过滤和采样生成候选向量集合。
5. 对候选向量计算内积，并用大小为 `topk` 的小根堆保留 Top-K。
6. 输出每个查询对应的 Top-K 向量编号。

## 输入格式

当前 `main.cpp` 期望基础集合和查询集合分别按以下文本格式提供。

基础集合：

```text
row col nnz topk
indptr[0] indptr[1] ... indptr[row]
indice[0] indice[1] ... indice[nnz-1]
data[0] data[1] ... data[nnz-1]
```

查询集合：

```text
nq
query_0_nnz
query_0_term_ids...
query_0_values...
query_1_nnz
query_1_term_ids...
query_1_values...
...
```

## 构建

本仓库包含 Xcode 命令行工具工程。可以在 Xcode 中打开：

```bash
open KMIPS_Soving_High_PERFORMANCE.xcodeproj
```

也可以使用命令行构建：

```bash
xcodebuild \
  -project KMIPS_Soving_High_PERFORMANCE.xcodeproj \
  -scheme KMIPS_Soving_High_PERFORMANCE \
  -configuration Release \
  -derivedDataPath build/DerivedData \
  build
```

构建产物会写入 `build/DerivedData`，该目录已被 `.gitignore` 排除。

## 当前注意事项

- `KMIPS_Soving/main.cpp` 中仍包含本机绝对路径的输入和输出重定向。换机器运行前，需要改为本地数据路径，或进一步改造成命令行参数。
- `KMIPS_Soving/decode/dataset_read.cpp` 中的数据转换辅助函数也包含本机绝对路径。
- `KMIPS_Soving/Library/` 目录中的数据文件未提交到仓库；仓库当前只保存代码和工程配置。
- Xcode 的个人状态文件、`.DS_Store` 和构建产物已通过 `.gitignore` 排除。

