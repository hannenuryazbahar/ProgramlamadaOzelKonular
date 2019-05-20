#include <stdio.h>

// pragma elemanları paketlerken 1 e göre paketliyor
#pragma pack(16)
// kalanı en yakın diğer elemanın katına yuvarlıyor
// typedef __attribute__(__packed__) struct ...
 
typedef struct typedef_example
{
  //int  int_arr[10];
  char c_arr[10];
  //     2 2 2 2 2
  //     + + + + +
  //     4 4 4
  // 10  + + 2 => 2
  //     8 8
  // 10  + 2   => 6
  // + char c_arr[2];
  long long int ll_arr[10];
} uni_t, uni[1];
// 10 * char + 10 * long long int
// 10 * 1 + 10 * 8 = 90

/*
 char 16
 char 10  => 6
 ll   80

*/

int main(){
    uni_t a;
    uni_t *b = &a;
    
    printf("uni_t: %ld\tuni: %ld\n", sizeof(a), sizeof(long long int));

    printf("uni_t: %ld\tuni: %ld\n", sizeof(long long int), sizeof(char));
    return 0;
}


// 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6
// + + 
// - - - - - - - - - - - - - - - -