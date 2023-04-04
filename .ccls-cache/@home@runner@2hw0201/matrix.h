#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _sMatrix
{
    int32_t height;
    int32_t width;
    int32_t *val;
}sMatrix;

sMatrix * matrix_init( uint8_t m, uint8_t n)
{
    sMatrix *ret;
    ret = (sMatrix *)calloc( 1 , sizeof( sMatrix ) );
    ret -> height = m;
    ret -> width = n;
    ret -> val = (int32_t *)calloc( m*n , sizeof(int32_t) );

    return ret;
}

int32_t matrix_set( sMatrix *pM, uint8_t m, uint8_t n, int32_t value )
{
    if( pM == NULL || pM->val == NULL || m >= pM->height || n >= pM->width )
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

void matrix_print( const sMatrix *pM )
{
    if( pM != NULL && pM->height > 0 && pM->width > 0 && pM->val != NULL )
    {
        int32_t max = 0;
        int32_t min = 0;
        for( size_t i = 0 ; i < pM->height*pM->width ; i++ )
        {
            if( pM->val[i] > max )
            {
                max = pM->val[i];
            }
            if( pM->val[i] < min )
            {
                min = pM->val[i];
            }
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
        int32_t d = 1;
        for( size_t i = 0 ; i < pM->height ; i++ )
        {
            for( size_t j = 0 ; j < pM->width ; j++ )
            {
                max = pM->val[i*pM->width+j];
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
                for( size_t k = 0 ; k < (maxd-d) ; k++ )
                {
                    printf( " " );
                }
                printf( "%d  " , pM->val[i*pM->width+j] );
            }
            printf( "\n" );
        }
    }
}

int32_t matrix_add( sMatrix *pA, const sMatrix *pB, const sMatrix *pC )
{
    if( pB->height != pC->height || pB->width != pC->width || pB->height <= 0 || pB->width <= 0 || pC->height <= 0 || pC->width <= 0 || pA == NULL || pA->val == NULL )
    {
        return -1;
    }
    for( size_t i = 0 ; i < pA->height ; i++ )
    {
        for( size_t j = 0 ; j < pA->width ; j++ )
        {
            pA->val[i*pA->width+j] = pB->val[i*pB->width+j] + pC->val[i*pC->width+j];       
	}
    }

    return 0;
}

int32_t matrix_multiply( sMatrix *pA, const sMatrix *pB, const sMatrix *pC )
{
    if( pB->width != pC->height || pB->height <= 0 || pB->width <= 0 || pC->width <= 0 || pA == NULL || pA->val == NULL )
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
            }
        }
    }

    return 0;
}

int32_t matrix_transpose( sMatrix *pA)
{
    if( pA == NULL || pA->height <= 0 || pA->width <= 0 )
    {
        return -1;
    }
    
    int32_t *origin = (int32_t *)calloc( pA->width * pA->height , sizeof(int32_t) );
    for( size_t i = 0 ; i < pA->height ; i++ )
    {
        for( size_t j = 0 ; j < pA->width ; j++ )
        {
            origin[i*pA->width+j] = pA->val[i*pA->width+j];
        }
    }
    int32_t temp = 0;
    temp = pA -> height;
    pA -> height = pA -> width;
    pA -> width = temp;

    for( size_t i = 0 ; i < pA->height ; i++ )
    {
        for( size_t j = 0 ; j < pA->width ; j++ )
        {
            pA->val[i*pA->width+j] = origin[j*pA->height+i];
        }
    }

    free( origin );
    origin = NULL;

    return 0;
}

int32_t matrix_det(const sMatrix *pA, int32_t *pAns)
{
    if( pA == NULL || pA->height <= 0 || pA->height != pA->width || pA->val == NULL || pAns == NULL )
    {
        return -1;
    }
    int32_t *origin = (int32_t *)calloc( pA->height*pA->width , sizeof(int32_t) );
    for( size_t i = 0 ; i < pA->height ; i++ )
    {
        for( size_t j = 0 ; j < pA->width ; j++ )
        {
            origin[i*pA->width+j] = pA -> val[i*pA->width+j];
        }
    }

    for( size_t j = 0 ; j < (pA->width-1) ; j++ )
    {
        for( size_t i = j+1 ; i < pA->height ; i++ )
        {
            int32_t mul = 0;
            mul = origin[i*pA->width+j] / origin[j*pA->width+j];
            for( size_t k = j ; k < pA->width ; k++ )
            {
                origin[i*pA->width+k] -= (origin[j*pA->width+k] * mul);
            }
        }
    }

    *pAns = 1;
    for( size_t i = 0 ; i < pA->height ; i++ )
    {
        *pAns = (*pAns) * (origin[i*pA->width+i]);
    }
    free( origin );

    return 0;
}

int32_t matrix_free( sMatrix *pA)
{
    free( pA -> val );
    free( pA );

    return 0;
}
