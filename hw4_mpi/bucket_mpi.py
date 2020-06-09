from mpi4py import MPI
import random, sys

dataset_size = int(sys.argv[1])
data = []
for _ in range(dataset_size):
    data.append(random.randint(1, dataset_size))

start = MPI.Wtime()
comm = MPI.COMM_WORLD
thread_num = comm.size

data_min = min(data)
data_max = max(data)
bucket_size = int((data_max - data_min) / thread_num) + 1
new_list = []
for rank in range(thread_num):
    new_list.append([x for x in data if (x >= data_min + bucket_size * rank) and (x < data_min + bucket_size * (rank + 1))])

v = comm.scatter(new_list, 0)
v = sorted(v)
g = comm.gather(v, 0)

data_sorted = []
if comm.rank == 0:
    for i in range(len(g)):
        data_sorted.extend(g[i])
    end = MPI.Wtime()
    print("Size of data: ", dataset_size)
    print("Number of threads: ", thread_num)
    print("Time: ", end - start)
    print("\n")