from mpi4py import MPI
import random, sys
import numpy as np
import heapq

dataset_size = int(sys.argv[1])
data = []
for _ in range(dataset_size):
    data.append(random.randint(1, dataset_size))

start = MPI.Wtime()
comm = MPI.COMM_WORLD
thread_num = comm.size

new_list = []
for rank in range(thread_num):
    new_list = np.array_split(data, thread_num)

v = comm.scatter(new_list, 0)
for i in range(len(v)):
    for j in range(len(v) - i - 1):
        if v[j] > v[j + 1]:
            v[j], v[j + 1] = v[j + 1], v[j]
g = comm.gather(v, 0)

data_sorted = []
if comm.rank == 0:
    for i in range(len(g)):
        data_sorted = list(heapq.merge(data_sorted, g[i]))
    end = MPI.Wtime()
    print("Size of data: ", dataset_size)
    print("Number of threads: ", thread_num)
    print("Time: ", end - start)
    print("\n")