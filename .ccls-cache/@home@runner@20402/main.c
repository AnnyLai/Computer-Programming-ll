#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

int main() 
{ 
  //printf( "2^-1 = %lf\n" , BIT(50) );
  //printf( "Set 10010(18)'s 2 bit as 1 => %d\n" , SETBIT(18,2) );
  //printf( "Set 10010(18)'s 0 bit as 0 => %d\n" , CLEARBIT(18,0) );
  //printf( "Get 10010(18)'s 4 bit => %d\n" , GETBIT(18,4) );
  //printf( "Turn 10010(18)'s 0 bit as the opposite => %d\n" , TOGGLEBIT(18,0) );
  printf( "Turn 10010(18)'s 0 bit as the opposite => %d\n" , TOGGLEBIT(18,0) );

  return 0; 
}