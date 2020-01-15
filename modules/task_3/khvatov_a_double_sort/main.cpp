// Copyright 2019 Khvatov Alexander
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>

#include "./sort.h"

TEST(Seq_Sort, sort_vector_positive) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (0 == rank) {
        int size = 5;
        double *vector = new double[size]{ 2.0, 8.66667, 1.69, 99.147, 57.3579 };
        bool result = false;

        seq_sort(vector, size);
        result = is_sorted(vector, size);

        ASSERT_EQ(true, result);
    }
}

TEST(Seq_Sort, sort_large_vector) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (0 == rank) {
        int size = 1000;
        double *vector = new double[size];
        for (int i = 0; i < size; i++) vector[i] = (size - i) * 0.001 + (i + size / 2);
        bool result = false;

        seq_sort(vector, size);
        result = is_sorted(vector, size);

        ASSERT_EQ(true, result);
    }
}

TEST(Seq_Sort, sort_is_correct) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (0 == rank) {
        int size = 5;
        double *result = new double[size]{ 1.69, 2.0, 8.66667, 57.3579, 99.147};
        double *vector = new double[size]{ 2.0, 8.66667, 1.69, 99.147, 57.3579 };

        seq_sort(vector, size);

        for (int i = 0; i < size; i++) {
            ASSERT_NEAR(result[i], vector[i], 0.01);
        }
    }
}

TEST(Par_Sort, sort_vector) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 5;
    double *vector = new double[size]{ 99.147, 8.66667, 1.69, 2.0, 57.3579 };

    par_sort(&vector, size);

    if (0 == rank) {
        bool result = false;
        result = is_sorted(vector, size);
        ASSERT_EQ(true, result);
    }
    delete[] vector;
}

TEST(Par_Sort, sort_large_vector) {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 1000;
    double *vector = new double[size];
    for (int i = 0; i < size; i++) vector[i] = (size - i) * 0.001 + (i + size / 2);

    par_sort(&vector, size);

    if (0 == rank) {
        bool result = false;
        result = is_sorted(vector, size);
        ASSERT_EQ(true, result);
    }
    delete[] vector;
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
