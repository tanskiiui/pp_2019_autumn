// Copyright 2019 Tanskii Yuriy
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include <vector>
#include "../../../modules/task_3/tanskii_u_radix_batcher_float/radix_batcher_float.h"

TEST(Parallel_Operations_MPI, test_paralell_eq_seq) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<double> parallel_vec;
    std::vector<double> seq_vec;
    std::vector<double> global_vec;
    int n = 8;
    if (rank == 0)
        global_vec = { 3.5, 2.4, 7.8, 4.5, 1.2, 5.7, 3.8, 4.9 };
    seq_vec = RadixSort(global_vec, n);
    parallel_vec = ParralelRadixSortBatcherMerge(global_vec, n);
    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            EXPECT_EQ(global_vec[i], parallel_vec[i]);
        }
    }
}
TEST(Parallel_Operations_MPI, test_size_below_zero) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<double> global_vec;
    int n = -1;
    if (rank == 0) {
        ASSERT_ANY_THROW(global_vec = getRandomArray(n));
    }
}

TEST(Parallel_Operations_MPI, test_correct_ans) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<double> parallel_vec;
    std::vector<double> global_vec;
    std::vector<double> correct_vec;
    int n = 8;
    if (rank == 0) {
        global_vec = { 3.5, 2.4, 7.8, 4.5, 1.2, 5.7, 3.8, 4.9 };
        correct_vec = { 1.2, 2.4, 3.5, 3.8, 4.5, 4.9, 5.7, 7.8 };
    }
    parallel_vec = ParralelRadixSortBatcherMerge(global_vec, n);
    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            EXPECT_EQ(correct_vec[i], parallel_vec[i]);
        }
    }
}
TEST(Parallel_Operations_MPI, test_check_vec_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<double> global_vec;
    size_t n = 50;
    if (rank == 0) {
        global_vec = getRandomArray(n);
        EXPECT_EQ(global_vec.size(), n);
    }
}
TEST(Parallel_Operations_MPI, correct_sort_negatives) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<double> parallel_vec;
    std::vector<double> global_vec;
    std::vector<double> correct_vec;
    int n = 8;
    if (rank == 0) {
        global_vec = { 3.5, -2.4, 7.8, -4.5, 1.2, -5.7, 3.8, 4.9 };
        correct_vec = { -5.7, -4.5, -2.4, 1.2, 3.5, 3.8, 4.9, 7.8 };
    }
    parallel_vec = ParralelRadixSortBatcherMerge(global_vec, n);
    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            EXPECT_EQ(correct_vec[i], parallel_vec[i]);
        }
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);
    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();
    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());
    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}

