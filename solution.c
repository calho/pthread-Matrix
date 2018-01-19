//notes: matrixgen -> data.input -> solution -> data.output -> serialtester
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "time.h"
#include "lab1_IO.h"
#include <math.h>

int **A;
int **B;
int **C;
const int MAX_THREADS = 64;
int thread_count;
int n;

int matrixMulti (int** matrix_A, int** matrix_B, int** matrix_C, int size)
{
	// C = malloc(n * sizeof(int*));

	int i;
	int j;
	int k;

	// for (i = 0; i < n; i++)
	// {
	//   (C)[i] = malloc(n * sizeof(int));
	// }

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			int sum = 0;
			for (k = 0; k < size; k++)
			{
				sum += matrix_A[i][k] * matrix_B[k][j];
			}

			matrix_C[i][j] = sum;		
		}
	}
	return 0;

}

void printM(int** matrix, int n)
{

	int i;
	int j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%i ", matrix[i][j] );
		}
		printf("\n");
	}
}

void *pMatrixMulti(void* rank)
{
	long k = (long)rank;
	// printf("hello from %ld\n", k);
	int x = floor(k/sqrt(thread_count));

	int y = fmod(k,sqrt(thread_count));

	//printf("x = %i, y = %i\n",x, y );

	int i_bot = (n/sqrt(thread_count))*x;
	int i_top = (n/sqrt(thread_count))*(x+1)-1;

	int i_range = abs(i_top - i_bot);

	int j_bot = (n/sqrt(thread_count))*y;
	int j_top = (n/sqrt(thread_count))*(y+1)-1;

	int j_range = abs(j_top - j_bot);

	//printf("k: %i\n",k );
	//printf("i_bot: %i i_top: %i j_bot: %i j_top: %i\n",i_bot, i_top, j_bot, j_top );

	int **p_A;
	int **p_B;
	int **p_C;

	p_A = malloc(i_range * sizeof(int*));
	p_B = malloc(i_range * sizeof(int*));
	p_C = malloc(i_range * sizeof(int*));

	int i;
	int j;

	for (i = 0; i <= i_range; i++)
	{
	  (p_A)[i] = malloc(j_range * sizeof(int));
	}
	for (i = 0; i <= i_range; i++)
	{
	  (p_B)[i] = malloc(j_range * sizeof(int));
	}
	for (i = 0; i <= i_range; i++)
	{
	  (p_C)[i] = malloc(j_range * sizeof(int));
	}


	//printf("i_range: %i, j_range: %i\n",i_range, j_range );
	int p_i;
	int p_j;

    for (i = i_bot, p_i = 0; p_i <= i_range; i++, p_i++)
    {
        for (j = j_bot, p_j = 0; p_j <= j_range; j++, p_j++)
        {
        	p_A[p_i][p_j] = A[i][j];
        }

    }

    for (i = i_bot, p_i = 0; p_i <= i_range; i++, p_i++)
    {
        for (j = j_bot, p_j = 0; p_j <= j_range; j++, p_j++)
        {
        	p_B[p_i][p_j] = B[i][j];
        }

    }


  	matrixMulti(p_A, p_B, p_C, i_range);

    for (i = i_bot, p_i = 0; p_i <= i_range; i++, p_i++)
    {
        for (j = j_bot, p_j = 0; p_j <= j_range; j++, p_j++)
        {
        	C[i][j] = p_C[p_i][p_j];
        }

    }

 //  	printf("p_A:\n");
 //  	printM(p_A, i_range);
 //  	printf("p_B:\n");
 //  	printM(p_B, i_range);
	// printf("p_C:\n");
 //  	printM(p_C, i_range);
    return NULL;

}

void *Hello(void* rank) {
	long my_rank = (long) rank; /* Use long in case of 64-bit system */
	printf("Hello from thread %ld of %d\n", my_rank, thread_count);
	return NULL;
}

int main (int argc, char* argv[])
{


long thread;

pthread_t* thread_handles;

if (argc < 2)
{
   printf("not enough parameters");
    return 0;
}

thread_count = strtol(argv[1], NULL, 10);

thread_handles = malloc(thread_count*sizeof(pthread_t));




Lab1_loadinput(&A, &B, &n);

//printM(A, n);

C = malloc(n * sizeof(int*));

int i;
for (i = 0; i < n; i++)
{
  (C)[i] = malloc(n * sizeof(int));
}

//int partitions = n/sqrt(thread_count);

//printf("%i\n", partitions);

//printf("C:\n");
//printM(C, n);
for (thread = 0; thread < thread_count; thread++)
{	
	pthread_create(&thread_handles[thread], NULL, pMatrixMulti, (void*) thread);
}
// printf("hello from main\n");
for (thread = 0; thread < thread_count; thread++)
{
	pthread_join(thread_handles[thread], NULL);
}


// int k;
// for (k = 0; k < thread_count; k++)
// {
	
//  //  	printf("p_A:\n");
//  //  	printM(p_A, i_range);
//  //  	printf("p_B:\n");
//  //  	printM(p_B, i_range);
// 	// printf("p_C:\n");
//  //  	printM(p_C, i_range);



// }
	// printf("A: \n");
	// printM(A, n);
	// printf("B: \n");
	// printM(B, n);
	// printf("C: \n");
	// printM(C, n);

	// printf("done\n");

	return 0;

}

