#include <stdio.h>
#include <stdlib.h> // qsort için eklendi
#include <x86intrin.h>

#define N (1<<20)

// compare function
static int cmp_int(const void *a, const void *b){
  if(*(int *)a < *(int *)b) return -1;
  if(*(int *)a > *(int *)b) return 1;
  return 0;
}

int main(void){
  int* a = (int *) malloc (4 * N);
  int i, k, sum = 0;

  long long int start = 0LL, finish = 0LL;

  for(k = 0; k < 16; k++){
    for(i = 0; i < N; i++){
      a[i] = (rand() % 3) - 1;
    }
  }

  start = _rdtsc();
  for(i = 0; i < N; i++){
    if(a[i] == 1){
      sum++;
    }
  }
  finish += __rdtsc() - start;

  printf("Karisik : %d: %lld\n", sum, finish>>4);

  finish = 0LL;
  sum = 0;

  for(k = 0; k < 16; k++){
    for(i = 0; i < N; i++){
      a[i] = (rand() % 3) - 1;
    }
  }

  qsort(a, N, sizeof(int), cmp_int);
  
  start = _rdtsc();
  for(i = 0; i < N; i++){
    if(a[i] == 1){
      sum++;
    }
  }
  finish += __rdtsc() - start;

  printf("Sirali :  %d: %lld\n", sum, finish>>4);
  return 0;
}

