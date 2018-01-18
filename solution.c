//notes: matrixgen -> data.input -> solution -> data.output -> serialtester
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <lab1_IO.h>

const int MAX_THREADS = 64;

int thread_count;


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

int ***A;

int ***B;

int n;

lab1_loadinput(&A, &B, &n);






}

