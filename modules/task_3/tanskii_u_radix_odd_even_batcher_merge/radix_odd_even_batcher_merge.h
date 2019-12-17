// Copyright 2019 Tanskii Yuriy
#ifndef MODULES_TASK_3_TANSKII_U_RADIX_ODD_EVEN_BATCHER_MERGE_RADIX_ODD_EVEN_BATCHER_MERGE_H_
#define MODULES_TASK_3_TANSKII_U_RADIX_ODD_EVEN_BATCHER_MERGE_RADIX_ODD_EVEN_BATCHER_MERGE_H_

#include <vector>

std::vector<double> getRandomArray(const int size);
void RadixSort(std::vector<double>& vec, int n);
std::vector<double> ParralelRadixSortBatcherMerge(std::vector<double> data, int n);
void SetCounters(int* counters, int i, int& sum);
void Restores(std::vector<double>& dst, int* counters, unsigned char* rmemory, int index, int i, std::vector<double>& vec);
void RSort(std::vector<double>& vec, std::vector<double>& dst, int size, int offset);
void RSortLast(std::vector<double>& vec, std::vector<double>& dst, int size, int offset);
#endif  // MODULES_TASK_3_TANSKII_U_RADIX_ODD_EVEN_BATCHER_MERGE_RADIX_ODD_EVEN_BATCHER_MERGE_H_
