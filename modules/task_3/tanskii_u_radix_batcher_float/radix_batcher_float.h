// Copyright 2019 Tanskii Yuriy
#ifndef MODULES_TASK_3_TANSKII_U_RADIX_ODD_EVEN_BATCHER_MERGE_RADIX_ODD_EVEN_BATCHER_MERGE_H_
#define MODULES_TASK_3_TANSKII_U_RADIX_ODD_EVEN_BATCHER_MERGE_RADIX_ODD_EVEN_BATCHER_MERGE_H_

#include <vector>
struct param {
    std::vector<double> vec;
    std::vector<double> dst;
};
std::vector<double> getRandomArray(const int size);
std::vector<double> RadixSort(std::vector<double> vec, int n);
std::vector<double> ParralelRadixSortBatcherMerge(std::vector<double> data, int n);
void SetCounters(int* counters, int i, int* sum);
//void RSort(double* vec, double* dst, int size, int offset);
//void RSortLast(double* vec, double* dst, int size, int offset);
void RSort(param* p, int size, int offset);
void RSortLast(param* p, int size, int offset);
#endif  // MODULES_TASK_3_TANSKII_U_RADIX_ODD_EVEN_BATCHER_MERGE_RADIX_ODD_EVEN_BATCHER_MERGE_H_
