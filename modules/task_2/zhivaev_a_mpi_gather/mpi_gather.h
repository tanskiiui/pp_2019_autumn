// Copyright 2019 Zhivaev Artem
#ifndef MODULES_TASK_2_ZHIVAEV_A_MPI_GATHER_MPI_GATHER_H_
#define MODULES_TASK_2_ZHIVAEV_A_MPI_GATHER_MPI_GATHER_H_

#include <mpi.h>

int MPI_Gather_c(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                 void *recvbuf, int recvcount, MPI_Datatype recvtype,
                 int root, MPI_Comm comm);

#endif  // MODULES_TASK_2_ZHIVAEV_A_MPI_GATHER_MPI_GATHER_H_

