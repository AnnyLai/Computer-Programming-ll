#pragma once

#include <stdio.h>

#include <stdint.h>
#include <stdlib.h>

int mystrbracket(char ***pppList , int *pCounter , const char *pStr, const char left_bracket , const char right_bracket)
{
    if( left_bracket == right_bracket || left_bracket == 0 || right_bracket == 0 )
    {
        return -1;
    }
    int64_t i = 0;
    int64_t l = 0, r = 0;
    int32_t count = 0;
    while( pStr[i] != 0 )
    {
        if( pStr[i] == left_bracket )
        {
            l++;
        }
        else if( pStr[i] == right_bracket && l > 0 )
        {
            l--;
            r++;
        }
        i++;
    }
    count = r;
    *pCounter = count;
    //printf( "Counter = %d\n" , *pCounter );

    *pppList = (char **)calloc( count , sizeof(char *) );
    //printf( "List = %p\n" , *pppList );

    char **now = *pppList;

    l = 0;
    r = i;
    while( count > 0 )
    {
        //printf( "l = %ld, r = %ld\n" , l , r );
        if( pStr[l] != left_bracket )
        {
            l++;
        }
        if( pStr[r] != right_bracket )
        {
            r--;
        }
        //printf( "l = %ld, r = %ld\n" , l , r );
  
        if( pStr[l] == left_bracket && pStr[r] == right_bracket )
        {
            //printf( "l = %ld, r = %ld\n" , l , r );
            *now = (char *)calloc( r-l , sizeof(char) );
            l++;
            for( i = l ; i < r+1 ; i++ )
            {
                if( i == r )
                {
                    *(*now+i-l) = 0;
                }
                else
                {
                    *(*now+i-l) = pStr[i];
                }
            }
            r--;
            now++;
            count--;
        }
        //printf( "count = %d\n" , count );
    }

    return 0;
}
