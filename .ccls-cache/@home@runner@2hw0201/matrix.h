#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _sMatrix
{
  int32_t height;
  int32_t width;
  int32_t *val;
// Your Design
// All elements are int32_t.
}sMatrix;

// Memory allocation for a m*n matrix. Fill zeros to all matrix element.
sMatrix * matrix_init( uint8_t m, uint8_t n)
{
  sMatrix *ret;
  ret = (sMatrix *)calloc( 1 , sizeof( sMatrix ) );
  ret -> height = m;
  ret -> width = n;
  ret -> val = (int32_t *)calloc( m*n , sizeof(int32_t) );

  return ret;
}

// Set the element in m-th row and n-th column to value.
// Note that m and n start from 0.
// If error , return -1; otherwise , return 0;
int32_t matrix_set( sMatrix *pM, uint8_t m, uint8_t n, int32_t value )
{
  if( m >= pM->height || n >= pM->width )
  {
    return -1;
  }
  int32_t *p = pM -> val;
  p += ( m * pM->width + n );
  *p = value;

  return 0;
}

// Print the matrix as follows
// 1 0
// 0 1
void matrix_print( const sMatrix *pM )
{
  const int32_t *p = pM -> val;
  int32_t max = 0;
  for( size_t i = 0 ; i < pM->height*pM->width ; i++ )
  {
    if( *p > max )
    {
      max = *p;
    }
    p++;
  }
  int32_t maxd = 0;
  while( (max / 10) > 0 )
  {
    maxd++;
    max /= 10;
  }
  int32_t d = 0;
  p = pM -> val;
  for( size_t i = 0 ; i < pM->height ; i++ )
  {
    for( size_t j = 0 ; j < pM->width ; j++ )
    {
        max = *p;
        while( (max / 10) > 0 )
        {
            d++;
            max /= 10;
        }
        for( size_t k = 0 ; k < (maxd-d) ; k++ )
        {
            printf( " " );
        }
      printf( "%d " , *p );
      p++;
    }
    printf( "\n" );
  }
}

// A = B + C
// If error , return -1; otherwise , return 0;
int32_t matrix_add( sMatrix *pA, const sMatrix *pB, const sMatrix *pC )
{
  if( pB->height != pC->height || pB->width != pC->width )
  {
    return -1;
  }
  
  //sMatrix *p = pA;
  for( size_t i = 0 ; i < pA->height ; i++ )
  {
    for( size_t j = 0 ; j < pA->width ; j++ )
    {
      pA->val[i*pA->width+j] = pB->val[i*pB->width+j] + pC->val[i*pC->width+j];
    }
  }

  return 0;
}

// A = B * C
// If error , return -1; otherwise , return 0;
int32_t matrix_multiply( sMatrix *pA, const sMatrix *pB, const sMatrix *pC );

// A = A^T
// If error , return -1; otherwise , return 0;
int32_t matrix_transpose( sMatrix *pA);

// Determinant
// Determinant should be put to *pAns
// If error , return -1; otherwise , return 0;
int32_t matrix_det(const sMatrix *pA, int32_t *pAns);

// Free
// If error , return -1; otherwise , return 0;
int32_t matrix_free( sMatrix *pA);
