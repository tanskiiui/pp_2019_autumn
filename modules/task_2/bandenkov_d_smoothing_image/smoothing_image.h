// Copyright 2019 Bandenkov Daniil
#ifndef MODULES_TASK_2_BANDENKOV_D_SMOOTHING_IMAGE_SMOOTHING_IMAGE_H_
#define MODULES_TASK_2_BANDENKOV_D_SMOOTHING_IMAGE_SMOOTHING_IMAGE_H_

#include <vector>

std::vector<int> getImg(const int  rows, const int cols);
std::vector<int> SequintialSmoothing(const std::vector<int> &mat, int rows, int cols, int koff);
std::vector<int> ParallelSmoothing(const std::vector<int> &Matrix, int rows, int cols, int koff);
#endif  // MODULES_TASK_2_BANDENKOV_D_SMOOTHING_IMAGE_SMOOTHING_IMAGE_H_
