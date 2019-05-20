#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>

// gcc -fno_inline .. ile yapıştırma yapmak yerine fonksiyon olarak kullanır

#define N 10000
#define max(a,b) { (a > b) ? a : b }


#define fib_hoca(N, __return_value__) {\
  int f[N]; \
  f[0] = 1, f[1] = 1;\
  for(int i = 2; i <= N; i++) { \
    f[i] = f[i - 1] + f[i - 2]; \
  } \
  __return_value__ = f[N]; \
}

#define fib(N, __return_value__) {\
  int temp_before = 0, temp_now = 1;\
  for(int i = 1 ; i < N; i++ ){\
    temp_now    = temp_now + temp_before;\
    temp_before = temp_now - temp_before;\
  }\
  __return_value__ = temp_now;\
}

static inline int fib_hoca_inline(const int n) {\
  int f[n];
  f[0] = 1, f[1] = 1;
  for(int i = 2; i <= n; i++) {
    f[i] = f[i - 1] + f[i - 2];
  }
  return f[n];
}


static inline int fib_inline(int n) {
  int temp_before = 0, temp_now = 1;
  for(int i = 1 ; i < n; i++ ){
    temp_now    = temp_now + temp_before;
    temp_before = temp_now - temp_before;
  }
  return temp_now;
}

double fib_hoca_test(int n, const int loop_count){
    int res = 0;
    unsigned long long int temp = 0, total = 0;
    
    for(int i = 0; i < loop_count; i++) {
        temp = _rdtsc();
        fib_hoca(n, res);
        total += _rdtsc() - temp;
    }

    return (double) (total / loop_count);
}

double fib_hoca_inline_test(int n, const int loop_count){
    unsigned long long int temp = 0, total = 0;
    
    for(int i = 0; i < loop_count; i++) {
        temp = _rdtsc();
        fib_hoca_inline(n);
        total += _rdtsc() - temp;
    }

    return (double) (total / loop_count);
}

double fib_test(int n, const int loop_count){
    int res = 0;
    unsigned long long int temp = 0, total = 0;
    
    for(int i = 0; i < loop_count; i++) {
        temp = _rdtsc();
        fib(n, res);
        total += _rdtsc() - temp;
    }
    
    return (double) (total / loop_count);
}

double fib_inline_test(int n, const int loop_count){
    unsigned long long int temp = 0, total = 0;
    
    for(int i = 0; i < loop_count; i++) {
        temp = _rdtsc();
        fib_inline(n);
        total += _rdtsc() - temp;
    }
    
    return (double) (total / loop_count);
}


int main(int argc, char * argv[]){
    int temp_time = 0;
    int test_count = 10000;
    double bef, af;    
    bef = fib_hoca_test(N, test_count);
    af  = fib_hoca_inline_test(N, test_count);
    printf("h: %.4f\n", bef - af);
    
    bef = fib_test(N, test_count);
    af  = fib_inline_test(N, test_count);
    printf("m: %.4f\n", bef - af);
    putchar('\n');
    return 0;
}