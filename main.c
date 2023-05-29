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
  int32_t i = 0;
  for RANGE( i , 0 , -1 )
  {
    printf( "%d " , i );
  }
  printf( "\n" );
  /*int8_t item = 76;
  int8_t arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  FOREACH( item , arr )
  for( size_t i = 0 ; i < 10 ; i++ )
  {
    printf( "%d\n" , arr[i] );
  }*/

  return 0; 
}