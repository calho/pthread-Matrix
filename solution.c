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

int matrixMulti (int i_bot, int i_top, int j_bot, int j_top, int size)
{
	// C = malloc(n * sizeof(int*));

	int i;
	int j;
	int k;

	// for (i = 0; i < n; i++)
	// {
	//   (C)[i] = malloc(n * sizeof(int));
	// }

	for (i = i_bot; i <= i_top; i++)
	{
		for (j = j_bot; j <= j_top; j++)
		{
			int sum = 0;
			for (k = 0; k < size; k++)
			{
				sum += A[i][k] * B[k][j];
			}

			C[i][j] = sum;		
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


	int j_bot = (n/sqrt(thread_count))*y;
	int j_top = (n/sqrt(thread_count))*(y+1)-1;



  	matrixMulti(i_bot, i_top, j_bot, j_top, n);

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

for (thread = 0; thread < thread_count; thread++)
{	
	pthread_create(&thread_handles[thread], NULL, pMatrixMulti, (void*) thread);
}
// printf("hello from main\n");
for (thread = 0; thread < thread_count; thread++)
{
	pthread_join(thread_handles[thread], NULL);
}




// }
	// printf("A: \n");
	// printM(A, n);
	// printf("B: \n");
	// printM(B, n);
	// printf("C: \n");
	printM(C, n);

	// printf("done\n");

	return 0;

}
/*-19 -30 27 -42 -36 -9 10 -42 -5 16
-7 2 18 -8 -1 5 -10 -14 -49 10
13 -8 10 -14 0 -25 -23 -7 5 -22
-34 0 -2 -33 32 9 51 36 -62 18
10 -28 21 -28 -1 23 40 8 11 -37
0 -20 31 -39 1 -4 9 -4 -5 -21
-7 32 16 -10 -49 -4 17 2 2 -20
-35 -10 -10 -20 27 -32 39 35 -22 37
-1 -18 -32 -1 -19 15 19 -16 11 19
1 -44 -33 -8 100 -24 -43 -24 -27 14*/

