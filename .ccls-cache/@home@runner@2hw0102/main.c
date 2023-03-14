// hw0102.c
//#include "insert.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int32_t strinsert( char **ppResult , const char *pStr1 , int32_t location , const char *pStr2 );

int main() 
{
    char *result = NULL;
    int32_t location = 1;

    strinsert(&result, "Hello", location, "ABC");
    printf("Expected output: HABCello\n");
    printf("  Actual output: %s\n\n", result);
    free(result);

    location = 0;
    strinsert(&result, "World", location, "123");
    printf("Expected output: 123World\n");
    printf("  Actual output: %s\n\n", result);
    free(result);

    location = 5;
    strinsert(&result, "Testing", location, "1234");
    printf("Expected output: Testi1234ng\n");
    printf("  Actual output: %s\n\n", result);
    free(result);

    return 0;
}

int32_t strinsert( char **ppResult , const char *pStr1 , int32_t location , const char *pStr2 )
{
  int32_t n = 0;
  int32_t i = 0;
  while( *(pStr1 + i) != 0 )
  {
    //printf( "%c" , *(pStr1 + i) );
    n++;
    i++;
  }
  if( location > n )
  {
    return -1;
  }
  //printf( "\n" );
  
  i = 0;
  while( *(pStr2 + i) != 0 )
  {
    //printf( "%c" , *(pStr2 + i) );
    n++;
    i++;
  }
  //printf( "\n" );
  
  *ppResult = calloc( n+1 , sizeof(char) );
  char *now = *ppResult;
  int8_t flag = 0;

  //printf( "%d\n" , n );
  //printf( "\n" );
  for( size_t k = 0 ; k < n ; k++ )
  {
    //printf( "%lu - " , k );
    //puts( *ppResult );
    
    if( k == location )
    {
      i = 0;
      while( *(pStr2 + i) != 0 )
      {
        //printf( "  %d\n" , i );
        //puts( *ppResult );
        //puts( pStr2+i );
        *(now + i) = *(pStr2 + i);
        i++;
      }
      flag = 1;
      k += (i - 1);
      now = now + i;
    }
    else if( flag == 0 )
    {
      i = 0;
      while( i < location )
      {
        //printf( "  %d\n" , i );
        //puts( *ppResult );
        //puts( pStr1+i );
        *(now + i) = pStr1[k + i];
        i++;
      }
      k += (i - 1);
      now = now + i;

      // puts( *ppResult );
      // puts( pStr1+k );
      // **(ppResult + k) = *(pStr1 + k);
    }
    else if( flag == 1 )
    {
      i = 0;
      while( *(pStr1 + location + i) != 0 )
      {
        //puts( *ppResult );
        //puts( pStr1+location+i );
        *(now + i) = *(pStr1 + location + i);
        i++;
      }
      k += (i - 1);
      now = now + i;
    }

    //now = now + 1;
  }
  
  return 0;
}

