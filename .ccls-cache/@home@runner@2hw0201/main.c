#include <stdio.h>
#include <stdint.h>
#include "matrix.h"

int main() 
{
  sMatrix *mat = NULL;
  sMatrix *A = NULL;
  sMatrix *B = NULL;
  int32_t *ans = NULL;

  printf( "\nmatrix_init:" );
  mat = matrix_init( 3 , 3 );
  if( mat == NULL )
  {
    printf( "Failed!\n" );
  }
  else
  {
    printf( "Succeeded!\n" );
  }
  //B = matrix_init( 3 , 4 );
  B = matrix_init( 4 , 2 );
  if( B == NULL )
  {
    printf( "Failed!\n" );
  }
  else
  {
    printf( "Succeeded!\n" );
  }
    //A = matrix_init( 3 , 4 );
    A = matrix_init( 3 , 2 );
  printf( "\nmatrix_set:\n" );
  if( matrix_set( mat , 0 , 0 , 1 ) == 0 )
  {
    printf( "%d\n" , mat->val[0*mat->width+0] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 0 , 1 , 2 ) == 0 )
  {
    printf( "%d\n" , mat->val[0*mat->width+1] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 0 , 2 , 3 ) == 0 )
  {
    printf( "%d\n" , mat->val[0*mat->width+2] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 0 , 3 , 4 ) == 0 )
  {
    printf( "%d\n" , mat->val[0*mat->width+3] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 1 , 0 , 5 ) == 0 )
  {
    printf( "%d\n" , mat->val[1*mat->width+0] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 1 , 1 , 6 ) == 0 )
  {
    printf( "%d\n" , mat->val[1*mat->width+1] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 1 , 2 , 7 ) == 0 )
  {
    printf( "%d\n" , mat->val[1*mat->width+2] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 1 , 3 , 8 ) == 0 )
  {
    printf( "%d\n" , mat->val[1*mat->width+3] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 2 , 0 , 9 ) == 0 )
  {
    printf( "%d\n" , mat->val[2*mat->width+0] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 2 , 1 , 10 ) == 0 )
  {
    printf( "%d\n" , mat->val[2*mat->width+1] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 2 , 2 , 11 ) == 0 )
  {
    printf( "%d\n" , mat->val[2*mat->width+2] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( mat , 2 , 3 , 12 ) == 0 )
  {
    printf( "%d\n" , mat->val[2*mat->width+3] );
  }
  else
  {
    printf( "\n" );
  }
  /*if( matrix_set( B , 0 , 0 , 1 ) == 0 )
  {
    printf( "%d\n" , B->val[0*B->width+0] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 0 , 1 , 2 ) == 0 )
  {
    printf( "%d\n" , B->val[0*B->width+1] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 0 , 2 , 3 ) == 0 )
  {
    printf( "%d\n" , B->val[0*B->width+2] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 0 , 3 , 4 ) == 0 )
  {
    printf( "%d\n" , B->val[0*B->width+3] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 1 , 0 , 5 ) == 0 )
  {
    printf( "%d\n" , B->val[1*B->width+0] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 1 , 1 , 6 ) == 0 )
  {
    printf( "%d\n" , B->val[1*B->width+1] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 1 , 2 , 7 ) == 0 )
  {
    printf( "%d\n" , B->val[1*B->width+2] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 1 , 3 , 8 ) == 0 )
  {
    printf( "%d\n" , B->val[1*B->width+3] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 2 , 0 , 9 ) == 0 )
  {
    printf( "%d\n" , B->val[2*B->width+0] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 2 , 1 , 10 ) == 0 )
  {
    printf( "%d\n" , B->val[2*B->width+1] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 2 , 2 , 11 ) == 0 )
  {
    printf( "%d\n" , B->val[2*B->width+2] );
  }
  else
  {
    printf( "\n" );
  }
  if( matrix_set( B , 2 , 3 , 12 ) == 0 )
  {
    printf( "%d\n" , B->val[2*B->width+3] );
  }
  else
  {
    printf( "\n" );
  }
  */
  matrix_set( B , 0 , 0 , 1 );
  matrix_set( B , 0 , 1 , 5 );
  matrix_set( B , 1 , 0 , 2 );
  matrix_set( B , 1 , 1 , 6 );
  matrix_set( B , 2 , 0 , 3 );
  matrix_set( B , 2 , 1 , 7 );
  matrix_set( B , 3 , 0 , 4 );
  matrix_set( B , 3 , 1 , 8 );

  printf( "\nmatrix_print:\n" );
  matrix_print( mat );
  
  /*printf( "\nmatrix_add:\n" );
  matrix_add( A , mat , B );
  //printf( "%d\n" , A->val[0] );
  matrix_print( A );*/

  /*printf( "\nmatrix_multiply:\n" );
  matrix_multiply( A , mat , B );
  //printf( "%d\n" , A->val[0] );
  matrix_print( A );*/

  /*printf( "\nmatrix_transpose:\n" );
  //printf( "before: %p\n" , B );
  matrix_transpose( B );
  //printf( "after:  %p\n" , B );
  matrix_print( B );*/

  ans = (int32_t *)calloc( 1 , sizeof(int32_t) );
  printf( "\nmatrix_det:\n" );
  matrix_det( mat , ans );
  printf( "%d\n" , *ans );

  //printf( "\nmatrix_free:\n");
  matrix_free( B );
  matrix_free( mat );
  matrix_free( A );

  free( ans );
  
  return 0;
}

