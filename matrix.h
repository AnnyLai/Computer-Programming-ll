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

int32_t matrix_free( sMatrix *pA);
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
    if( pM->val == NULL )
    {
        pM -> val = (int32_t *)calloc( m*n , sizeof(int32_t) );
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
    if( pM->height > 0 && pM->width > 0 && pM->val != NULL )
    {
        const int32_t *p = pM -> val;
        int32_t max = 0;
        int32_t min = 0;
        for( size_t i = 0 ; i < pM->height*pM->width ; i++ )
        {
            if( *p > max )
            {
                max = *p;
            }
            if( *p < min )
            {
                min = *p;
            }
            p++;
        }
        int32_t maxd = 1;
        int32_t mind = 1;
        if( min < 0 )
        {
            mind++;
        }
        while( (max / 10) > 0 )
        {
            maxd++;
            max /= 10;
        }
        while( (min / 10) != 0 )
        {
            mind++;
            min /= 10;
        }
        if( mind > maxd )
        {
            maxd = mind;
        }
        //printf( "maxd = %d\n" , maxd );
        int32_t d = 1;
        p = pM -> val;
        for( size_t i = 0 ; i < pM->height ; i++ )
        {
            for( size_t j = 0 ; j < pM->width ; j++ )
            {
                max = *p;
                d = 1;
                if( max < 0 )
                {
                    d++; 
                }
                while( (max / 10) != 0 )
                {
                    d++;
                    max /= 10;
                }
                //printf( "d = %d\n" , d );
                for( size_t k = 0 ; k < (maxd-d) ; k++ )
                {
                    printf( " " );
                }
                printf( "%d  " , *p );
                p++;
            }
            printf( "\n" );
        }
    }
}

// A = B + C
// If error , return -1; otherwise , return 0;
int32_t matrix_add( sMatrix *pA, const sMatrix *pB, const sMatrix *pC )
{
    if( pB->height != pC->height || pB->width != pC->width || pB->height < 0 || pB->width < 0 || pC->height < 0 || pC->width < 0 || pA == NULL )
    {
        return -1;
    }
    //printf( "a\n" );
    //sMatrix *p = pA;
    for( size_t i = 0 ; i < pA->height ; i++ )
    {
        for( size_t j = 0 ; j < pA->width ; j++ )
        {
            pA->val[i*pA->width+j] = pB->val[i*pB->width+j] + pC->val[i*pC->width+j];
            //printf( "%d\n" , pA->val[i*pA->width+j] );
        }
    }

    return 0;
}

// A = B * C
// If error , return -1; otherwise , return 0;
int32_t matrix_multiply( sMatrix *pA, const sMatrix *pB, const sMatrix *pC )
{
    if( pB->width != pC->height || pB->height < 0 || pB->width < 0 || pC->width < 0 || pA == NULL )
    {
        return -1;
    }
    for( size_t i = 0 ; i < pA->height ; i++ )
    {
        for( size_t j = 0 ; j < pA->width ; j++ )
        {
            pA->val[i*pA->width+j] = 0;
        }
    }
    for( size_t i = 0 ; i < pA->height ; i++ )
    {
        for( size_t j = 0 ; j < pA->width ; j++ )
        {
            for( size_t k = 0 ; k < pB->width ; k++ )
            {
                pA->val[i*pA->width+j] += pB->val[i*pB->width+k] * pC->val[k*pC->width+j];
                //printf( "%d\n" , pA->val[i*pA->width+j] );
            }
        }
    }
}

// A = A^T
// If error , return -1; otherwise , return 0;
int32_t matrix_transpose( sMatrix *pA)
{
    if( pA == NULL || pA->height < 0 || pA->width < 0 )
    {
        return -1;
    }
    
    /*sMatrix *new = NULL;
    new = matrix_init( pA->width , pA->height );
    for( size_t i = 0 ; i < pA->width ; i++ )
    {
        for( size_t j = 0 ; j < pA->height ; j++ )
        {
            new->val[i*new->width+j] = pA->val[j*pA->width+i];
        }
    }

    sMatrix *temp = pA;
    pA = new;
    matrix_free( temp );*/
    
    
    int32_t *or = (int32_t *)calloc( pA->width , pA->height );
    for( size_t i = 0 ; i < pA->height ; i++ )
    {
        for( size_t j = 0 ; j < pA->width ; j++ )
        {
            or[i*pA->width+j] = pA->val[i*pA->width+j];
            //printf( "%d " , or[i*pA->width+j] );
        }
        //printf( "\n" );
    }
    int32_t temp = 0;
    temp = pA -> height;
    pA -> height = pA -> width;
    pA -> width = temp;

    for( size_t i = 0 ; i < pA->height ; i++ )
    {
        for( size_t j = 0 ; j < pA->width ; j++ )
        {
            pA->val[i*pA->width+j] = or[j*pA->height+i];
            //printf( "%d " , pA->val[i*pA->width+j] );
        }
        //printf( "\n" );
    }

    //free( or );

    return 0;
}

// Determinant
// Determinant should be put to *pAns
// If error , return -1; otherwise , return 0;
int32_t matrix_det(const sMatrix *pA, int32_t *pAns);

// Free
// If error , return -1; otherwise , return 0;
int32_t matrix_free( sMatrix *pA)
{
    free( pA -> val );
    free( pA );

    return 0;
}
