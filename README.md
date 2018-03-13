# CloudComputingPA2
Cloud Computing Assignment 2 by Ion Raicu CS-553 IIT.

Sorting Large datasets of 128 GB, 1 TB with Hadoop, Spark, Shared Memory and MPI

SHARED MEMORY TERA SORT

1. The main aim of this code is to perform sorting on large datasets, considering this I have opted for Merge Sort and k-way external merge sort.
2. Sorting is performed based on integer values that are produced at random.
3. I performed the operation by dividing the chunks into 2GB data chunks and then applying merge sort to the data that was read.
4. Once the chunks are created I use a k-way file merge method which reads the 1st element of every chunk and create a minheap.
5. Based on the root element of the minheap we now read the chunks based on the position of the element and call heapify to maintain the min heap property.
6. We loop through this until all the chunks are read and the root of all these elements are written to the output file.

Steps to execute

./file_gen will generate the input.txt file to be sorted

to Run shared memory execute ./smt
to execute MPI

mpicc -o mpi_ext mpi_external_sort.c -std=c99

mpirun -np 1 ./mpi_ext

Note : - if you wanna change the number of processes in which the code runs put 2 after -mp.

