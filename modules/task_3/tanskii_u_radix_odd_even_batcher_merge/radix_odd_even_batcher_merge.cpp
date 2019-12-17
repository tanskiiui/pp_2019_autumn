// Copyright 2019 Tanskii Yuriy
#include <mpi.h>
#include <vector>
#include <random>
#include <ctime>
#include <stdexcept>
#include <algorithm>
#include "../../../modules/task_3/tanskii_u_radix_odd_even_batcher_merge/radix_odd_even_batcher_merge.h"

std::vector<double> getRandomArray(const int size) {
    if (size <= 0)
        throw std::runtime_error("vec size<=0");
    std::vector<double> randVec(size);
    std::mt19937 gen;
    std::random_device d;
    std::uniform_real_distribution<double> urd(1, 2 * size);
    gen.seed(d());
    for (int i = 0; i < size; i++) {
        randVec[i] = urd(gen);
    }
    return randVec;
}
void SetCounters(int* counters, int i, int& sum) {
    int tmp = counters[i];
    counters[i] = sum;
    sum += tmp;
}
void Restores(std::vector<double>& dst, int* counters, unsigned char* rmemory, int index, int i, std::vector<double>& vec) {
    dst[counters[rmemory[index]]] = vec[i];
    counters[rmemory[index]]++;
}
void RSort(std::vector<double>& vec, std::vector<double>& dst, int size, int offset) {
    unsigned char* rmemory = (unsigned char*)vec.data();
    int counters[256];
    int sum = 0;
    for (int i = 0; i < 256; i++)
        counters[i] = 0;
    for (int i = 0; i < size; i++)
        counters[rmemory[8 * i + offset]]++;
    for (int i = 0; i < 256; i++) {
        SetCounters(counters, i, sum);
    }
    for (int i = 0; i < size; i++) {
        int index = 8 * i + offset;
        Restores(dst, counters, rmemory, index, i, vec);
    }
}
void RSortLast(std::vector<double>& vec, std::vector<double>& dst, int size, int offset) {
    unsigned char* rmemory = (unsigned char*)vec.data();
    int counters[256];
    int sum = 0;
    for (int i = 0; i < 256; i++) counters[i] = 0;
    for (int i = 255; i > 127; i--) {
        counters[i] += sum;
        sum = counters[i];
    }
    for (int i = 0; i < 128; i++) {
        SetCounters(counters, i, sum);
    }
    for (int i = 0; i < size; i++) {
        int index = 8 * i + offset;
        if (rmemory[index] < 128) {
            Restores(dst, counters, rmemory, index, i, vec);
        }
        else {
            counters[rmemory[index]]--;
            dst[counters[rmemory[index]]] = vec[i];
        }
    }
}
void RadixSort(std::vector<double>& vec, int n) {
    std::vector<double> tmp(n);
    std::vector<double> dst(n);
    for (int i = 0; i < 8; i++) {
        RSort(vec, dst, n, i);
        tmp = vec;
        vec = dst;
        dst = tmp;
    }
    RSortLast(vec, dst, n, 7);
}
std::vector<double> ParralelRadixSortBatcherMerge(std::vector<double> data, int n) {
    int size, rank;
    int localn;
    std::vector<double> recdata;
    std::vector<double> recdata2;
    std::vector<double> temp;
    int i;
    int root_process;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    root_process = 0;
    data.resize(n);
    int avgn = n / size;
    int lastn = n % size;
    localn = avgn;
    recdata.resize(localn);
    if (n < size) {
        RadixSort(recdata, n);
        return recdata;
    }
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Send(&data[0] + i * localn + lastn, localn, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
        recdata = std::vector<double>(data.begin(), data.begin() + localn + lastn);
    }
    else {
        MPI_Status status;
        MPI_Recv(&recdata[0], localn, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
    }
    RadixSort(recdata, localn);
    int oddrank, evenrank;
    if (rank % 2 == 0) {
        oddrank = rank - 1;
        evenrank = rank + 1;
    }
    else {
        oddrank = rank + 1;
        evenrank = rank - 1;
    }
    if (oddrank == -1 || oddrank == size)
        oddrank = MPI_PROC_NULL;
    if (evenrank == -1 || evenrank == size)
        evenrank = MPI_PROC_NULL;
    int p;
    recdata2.resize(localn);
    temp.resize(localn);
    for (p = 0; p < size - 1; p++) {
        if (p % 2 == 1) {
            MPI_Sendrecv(&recdata[0], localn, MPI_DOUBLE, oddrank, 1, &recdata2[0], localn, MPI_DOUBLE, oddrank, 1, MPI_COMM_WORLD, &status);
        }
        else {
            MPI_Sendrecv(&recdata[0], localn, MPI_DOUBLE, evenrank, 1, &recdata2[0],
                localn, MPI_DOUBLE, evenrank, 1, MPI_COMM_WORLD, &status);
        }
        for (i = 0; i < localn; i++) {
            temp[i] = recdata[i];
        }
        if (status.MPI_SOURCE == MPI_PROC_NULL)	continue;
        else if (rank < status.MPI_SOURCE) {
            int i, j, k;
            for (i = j = k = 0; k < localn; k++) {
                if (j == localn || (i < localn && temp[i] < recdata2[j]))
                    recdata[k] = temp[i++];
                else
                    recdata[k] = recdata2[j++];
            }
        }
        else {
            int i, j, k;
            for (i = j = k = localn - 1; k >= 0; k--) {
                if (j == -1 || (i >= 0 && temp[i] >= recdata2[j]))
                    recdata[k] = temp[i--];
                else
                    recdata[k] = recdata2[j--];
            }
        }
    }
    MPI_Gather(&recdata[0], localn, MPI_DOUBLE, &data.front(), localn, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    return data;
}
