#include <stdio.h>     // printf icin
#include <x86intrin.h> //_rdtsc() icin

// gcc -fno_inline .. ile inline kullanımı compiler'a bırakılır
// yapıştırma yapmak yerine fonksiyon olarak kullanır

#define N 100

// macro ve inline kullanımı

// N yukarıda tanımlandığı icin burada parametre
// olarak almasakta olur
// ters slashlar çook önemli \n i hiçe say.
#define fib(__return_value__, N) {\
  int f[N]; \
  f[0] = 1, f[1] = 1;\
  for(int i = 2; i <= N; i++) { \
    f[i] = f[i - 1] + f[i - 2]; \
  } \
  __return_value__ = f[N]; \
}

static inline int fib_inline(const int n) {\
  int f[n];
  f[0] = 1, f[1] = 1;
  for(int i = 2; i <= n; i++) {
    f[i] = f[i - 1] + f[i - 2];
  }
  return f[n];
}

// macro ve inline kullanımı

// testler
double fib_inline_test(int n, const int loop_count){
    unsigned long long int temp = 0, total = 0;
    
    for(int i = 0; i < loop_count; i++) {
        temp = _rdtsc();
        fib_inline(n);
        total += _rdtsc() - temp;
    }

    return (double) (total / loop_count);
}

double fib_test(int n, const int loop_count) {
    int res = 0;
    unsigned long long int temp = 0, total = 0;
    
    for(int i = 0; i < loop_count; i++) {
        temp = _rdtsc();
        fib(res, n);
        total += _rdtsc() - temp;
    }
    
    return (double) (total / loop_count);
}
// testler 

int main(int argc, char * argv[]) {
    int test_count = 10000;
    
    printf("macro olculen sure:  %.4f\n", fib_test(N, test_count));
    printf("inline olculen sure: %.4f\n", fib_inline_test(N, test_count));

    return 0;
}