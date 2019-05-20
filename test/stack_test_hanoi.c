#include<stdio.h>
#include<stdlib.h>

#define push(a, x) *(++a) = x
#define pop(a) *(a--)

int tasi(char **si, char **sj)
{
    if(*(*si) != -1 && *((*sj)+1) != -1 && (*(*si) > *(*sj))){
    //if(*(*si)!=255 && *((*sj)+1)!=255){
        push(* sj, pop((*si)));
        return 0 ;
    }
    return 1;
}

int main(void){
    int i;
    char *s0 = (char *) malloc (4);
    char *s1 = (char *) malloc (4);
    char *s2 = (char *) malloc (4);

    *s0 = *(s0+4) = 255;
    *s1 = *(s1+4) = 255;
    *s2 = *(s2+4) = 255;
    push(s0, 'a');

    /*
    s0 | a
    s1 |
    s2 |
    */
    push(s0, 'b');
    /*
    s0 | a b
    s1 |
    s2 |
    */
    push(s0, 'c');
    /*
    s0 | a b c
    s1 |
    s2 |
    */
    tasi(&s0, &s2);
    /*
    s0 | a b
    s1 |
    s2 | c
    */
    tasi(&s0, &s1);
    /*
    s0 | a
    s1 | b
    s2 | c
    */    
    tasi(&s2, &s1);
    /*
    s0 | a
    s1 | b c
    s2 |
    */
    if(tasi(&s0, &s2)) 
        printf("s0 s2 dan daha kucuk\n");
    /*
    s0 | 
    s1 | b c
    s2 | a
    */

    // kullanımı gereksiz
    // tasi(&s0, &s2);

    tasi(&s1, &s0);
    /*
    s0 | c
    s1 | b
    s2 | a
    */
    tasi(&s1, &s2);
    /*
    s0 | c
    s1 | 
    s2 | a b
    */
    tasi(&s0, &s2);
    /*
    s0 |
    s1 | 
    s2 | a b c
    */

    if(tasi(&s1, &s2))
        printf("s2 dolu!!! \n");
    
    for(i = 0; i < 3; i++)
    {
        printf("%c\n", *(s2--));
    }
    return 0;   
}
