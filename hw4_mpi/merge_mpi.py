from mpi4py import MPI
import random, sys
import numpy as np
import heapq

def merge_sort(l):
	if len(l) <= 1:
		return l
	num = int(len(l) / 2)
	left = merge_sort(l[ : num])
	right = merge_sort(l[num : ])
	return merge(left,right)
	
def merge(left, right):
	l, r = 0, 0
	result = []
	while l < len(left) and r < len(right):
		if left[l] <= right[r]:
			result.append(left[l])
			l += 1
		else:
			result.append(right[r])
			r += 1
	result.extend(left[l:])
	result.extend(right[r:])
	return result

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
v = merge_sort(v)
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