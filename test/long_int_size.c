#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#define kullanilmayacak_fonksiyon(x, y) kullanilmayacak_fonksiyon_##x((y))

#if __LONG_MAX__ == __LONG_LONG_MAX__
  typedef long int mylong;
#else
  typedef long long int mylong;
#endif

void short_loop(){
  int value = 0;
  short int i;
  for(i = SHRT_MIN; i < SHRT_MAX; i++) {
    value++;
  }

  printf("value = %d\n", value);
}

void kullanilmayacak_fonksiyon_short(short a){
  printf("short : %hd\n", a);
}

void kullanilmayacak_fonksiyon_int(int a){
  printf("int : %d\n", a);
}

int main(){
  printf("LONG_MAX: %ld\n", __LONG_MAX__);
  printf("LONG_LONG_MAX: %lld\n", __LONG_LONG_MAX__);
  printf("GCC VERSION: %s\n", __VERSION__);
  printf("Size of long int: %ld\n", sizeof(long int));
  printf("Size of long long int: %ld\n", sizeof(long long int));

  #ifdef __linux
    printf("Linux kullandiginiz icin tebrik ederim.\n");
  #else
    printf("Linux kullanmadiginiz icin teessuf ederiz!\n");
  #endif

  short_loop();

  int a = 1;
  kullanilmayacak_fonksiyon(short,a);
  kullanilmayacak_fonksiyon_short(a);
  kullanilmayacak_fonksiyon(int, a);
  kullanilmayacak_fonksiyon_int(a);

  kullanilmayacak_fonksiyon_short(1);
  kullanilmayacak_fonksiyon_int(2);

  return 0;
}
