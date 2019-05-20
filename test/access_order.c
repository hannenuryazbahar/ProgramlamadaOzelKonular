#include <stdio.h>
#include <x86intrin.h>
#define N (1<<12)    //shift işlemi
#define STEP 4

// 10101011
// 01010110
/* 
Boyut olarak L3>L2>L1
Hız olarak   L1>L2>L3
RAM -> L3 Cache -> L2 Cache -> L1 Cache -> CPU
*/

int main(void){
  //int a[N*N], b[N*N], c[N*N];
  int *a, *b, *c;
  a = (int*)malloc(4LL* N * N);   //4LL long long int tipinde
  b = (int*)malloc(4LL* N * N);
  c = (int*)malloc(4LL* N * N);

  int i, j, n, k;
  long long int at1, bt1, ct1, start;

  for(n = 1; n <= N; n<<=1){

    start = _rdtsc();
    for(k = 0; k <= 16; k++){
      // Satırda sıralı erişim
      for(i = 0; i < n; i++){
        for(j = 0;j < n; j+=STEP){
          a[i * n + j] = j;
        }
        /*
        for(j = 0;j < n; j++){
          a[i * n + j] = j;
        }
        */
      }
    }
    at1 = _rdtsc() - start;

    start = _rdtsc();
    for(k = 0; k <= 16; k++){
      // Sütunda Sıralı Erişim
      for(i = 0; i < n; i += STEP){
        for(j = 0;j < n; j++){
          b[j * n + i] = i;
        }
      }
      /*
      for(i = 0; i < n; i++){
        for(j = 0;j < n; j++){
          b[j * n + i] = i;
        }
      }
      */
    }
    bt1 = _rdtsc() - start;

    start = _rdtsc();
    for(k = 0; k <= 16; k++){
      // Rastgele Sıralı Erişim
      for(i = 0; i < n; i++){
        for(j = 0;j < n; j+=STEP){
          //c[(long long int)(rand() % ((n)*(n)))] = j;
          // rastgele erişim için bir sayı üretiyor
          // bu işleme göre erişiyor
          c[((long long int)(rand() % (n * n))) & 0xfffffff0] = j;
        }
        /*
        for(j = 0;j < n; j++){
          c[rand() % ((n)*(n))] = j;
        }
        */
      }
    }
    ct1 = _rdtsc() - start;
    printf("%15lld (%.2f), %15lld (%.2f), %15lld (%.2f);\n", at1, (double)at1/at1, bt1, (double)bt1/at1, ct1, (double)ct1/at1);
  }

  return 0;
}

// Satırda sıralı erişim
/*
    1   2   3
    4   5   6
    7   8   9
*/
// Sutünda sıralı erişim
/*
    1   4   7
    2   5   8
    3   6   9
*/
// Rastgele sıralı erişim
/*
    Karışık :)
*/