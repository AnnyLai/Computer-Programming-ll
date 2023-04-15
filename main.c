#include <stdio.h>
#include <stdint.h>
#include "mystr.h"

int main()
{
    char **list = NULL;
    int count = 0;

    mystrbracket( &list , &count , "[a[b]c]d]" , '[' , ']' );

    for( size_t i = 0 ; i < count ; i++ )
    {
        printf( "%lu. " , i );
        puts( list[i] );
    }

    return 0;
}
