#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
    int8_t code = -1;
    char *key = NULL;
    char *inname = NULL;
    char *outname = NULL;
    int32_t i = 0;
    int32_t j = 0;
  
    int32_t option = 0;
    int8_t counte = 0, countd = 0, countk = 0, counti = 0, counto = 0;
    while ( ( option = getopt( argc, argv, "edk:i:o:" ) ) != -1 )
    {
        switch( option )
        {
            case 'e':
                counte++;
                code = 0;
                break;
            case 'd':
                countd++;
                code = 1;
                break;
            case 'k':
                countk++;
                i = 0;
                while( optarg[i] != 0 )
                {
                  i++;
                }
                key = (char *)calloc( i+1 , sizeof(char) );
                for( j = 0 ; j < i ; j++ )
                {
                  key[j] = optarg[j];
                }
                key[i] = 0;
                break;
            case 'i':
                counti++;
                i = 0;
                while( optarg[i] != 0 )
                {
                  i++;
                }
                inname = (char *)calloc( i+1 , sizeof(char) );
                for( j = 0 ; j < i ; j++ )
                {
                  inname[j] = optarg[j];
                }
                inname[i] = 0;
                break;
            case 'o':
                counto++;
                i = 0;
                while( optarg[i] != 0 )
                {
                  i++;
                }
                outname = (char *)calloc( i+1 , sizeof(char) );
                for( j = 0 ; j < i ; j++ )
                {
                  outname[j] = optarg[j];
                }
                outname[i] = 0;
                break;
            default:
                printf( "Unknown option.\n" ); 
                break;
        }
    }

    if( (counte >= 1 && countd >= 1) || key == NULL || strlen(key) == 0 || inname == NULL || strlen(inname) == 0 || outname == NULL || strlen(outname) == 0 )
    {
        printf( "Invalid input.\n" );
        return 0;
    }
    if( counte > 1 || countd > 1 || countk > 1 || counti > 1 || counto > 1 )
    {
        printf( "Too many variables.\n" );
    }

    FILE *pK = NULL;
    FILE *pIn = NULL;
    FILE *pOut = NULL;

    i = 0;
    pK = fopen( key , "r" );
    if( pK == NULL )
    {
        printf( "Key file could not be opened.\n" );
        i++;
    }
    pIn = fopen( inname , "r" );
    if( pIn == NULL )
    {
        printf( "Input file could not be opened.\n" );
        i++;
    }
    if( i == 0 )
    {
        pOut = fopen( outname , "w+" );
        if( pOut == NULL )
        {
            printf( "Output file could not be opened.\n" );
            i++;
        }
    }
    if( i > 0 )
    {
        if( pK )
        {
            fclose( pK );
        }
        if( pIn )
        {
            fclose( pIn );
        }
        if( pOut )
        {
            fclose( pOut );
        }
        return 0;
    }

    char keybuf[1024] = {0};
    char inbuf[1024] = {0};
    char c = 0;
    
    j = fread( &keybuf[0] , 1 , 1024 , pK );
    int32_t q = 0;
    while( !feof(pIn) )
    {
        i = fread( &inbuf[0] , 1 , 1024 , pIn );
        for( size_t k = 0 ; k < i ; k++ )
        {
          if( q >= j )
          {
              j = fread( &keybuf[0] , 1 , 1024 , pK );
              q = 0;
          }
          c = inbuf[k] ^ keybuf[q];
          fwrite( &c , 1 , 1 , pOut );
          q++;
        }
    }

    free( key );
    free( inname );
    free( outname );
    fclose( pK );
    fclose( pIn );
    fclose( pOut );
    
    return 0;
}
