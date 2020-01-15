// Copyright 2019 Kats Eugeniy

#ifndef MODULES_TASK_2_KATS_E_SEIDEL_SEIDEL_H_
#define MODULES_TASK_2_KATS_E_SEIDEL_SEIDEL_H_

#include <vector>

#define TYPE_A 1
#define TYPE_B 2

std::vector<double> randMatrix(int n, int type);
std::vector<double> seidel_solve(std::vector<double> A, std::vector<double> B,
                                 int n, double eps);
std::vector<double> seidel_solve_s(std::vector<double> A, std::vector<double> B,
                                   int n, double eps);

#endif  // MODULES_TASK_2_KATS_E_SEIDEL_SEIDEL_H_
