#include <stdio.h>
#include <stdlib.h>

typedef struct dizi dizi;
struct dizi {
  int n;
  int *a;
  void (*init)(dizi *d, int n, int* a);
};

#define DIZI_LIMIT 128
dizi tx[DIZI_LIMIT];
//#define dizi.init(a, b) tx;tx.init=dizi_struct_init;tx.init(tx++, a, b);

void dizi_struct_init(dizi *d, const int n, int *a){
  printf("dizi initializing... array size: %d\n", n);
  int array[n];
  d->n = n;
  d->a = (int *) malloc (sizeof(int) * n);
}

int main(void){
  // Bu şekilde yapılabilir mi? 
  // dizi.init(5, b);

  int *b;
  dizi c;
  
  c.init = dizi_struct_init;
  c.init(&c, 15, b);
  printf("Size of array: %d\n", c.n);

  return 0;
}