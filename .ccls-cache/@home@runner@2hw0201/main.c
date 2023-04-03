#include <stdio.h>
#include <stdint.h>
#include "matrix.h"

int main() 
{
  sMatrix *mat = NULL;

  printf( "\nmatrix_init:" );
  mat = matrix_init( 3 , 4 );
  if( mat == NULL )
  {
    printf( "Failed!\n" );
  }
  else
  {
    printf( "Succeeded!\n" );
  }

  printf( "\nmatrix_set:\n" );
  if( matrix_set( mat , 2 , 0 , -3 ) == 0 )
  {
    printf( "%d\n" , mat[2*mat->width+0].val );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 3 , 1 , 8 ) == 0 )
  {
    printf( "%d\n" , mat[3*mat->width+1].val );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 0 , 0 , 100 ) == 0 )
  {
    printf( "%d\n" , mat[0*mat->width+0].val );
  }
  else
  {
    printf( "\n" );
  }
  
  printf( "\nmatrix_print:\n" );
  matrix_print( mat );
  
  printf("Hello World\n");
  return 0;
}


