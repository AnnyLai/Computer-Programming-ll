// hw0103.c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include "abacus.h"

typedef struct _sAbacus
{
  uint8_t number; // 0-255
  uint8_t *pUpperRod; // Each element is in {0,1}
  uint8_t *pLowerRod; // Each element is in {0,1,2,3,4}
}sAbacus;

sAbacus * abacus_init( void );
void abacus_free( sAbacus * );

int32_t abacus_set( sAbacus *pA, char *pStr );

int32_t abacus_add( sAbacus *pA, sAbacus b, sAbacus c );
int32_t abacus_del( sAbacus *pA, sAbacus b, sAbacus c );

int32_t abacus_print( sAbacus a );
void carry( int8_t *start , int16_t n );

int main() 
{
    // Initialize abacus, abacus2, abacus3
    sAbacus *abacus = abacus_init();
    sAbacus *abacus2 = abacus_init();
    sAbacus *abacus3 = abacus_init();

    // Set the values of abacus and abacus2 to "1234" and "5678"
    if(abacus_set(abacus, "345") != 0) 
    {
        printf("Error: Set operation failed\n");
        return -1;
    }
    if(abacus_set(abacus2, "12345") != 0) 
    {
        printf("Error: Set operation failed\n");
        return -1;
    }

    
    // Add abacus and abacus2, store result in abacus3
    if(abacus_add(abacus3, *abacus, *abacus2) != 0) 
    {
        printf("Error: Add operation failed\n");
        return -1;
    }
    
    // Print abacus3
    if(abacus_print(*abacus3) != 0) 
    {
        printf("Error: Print operation failed\n");
        return -1;
    }
    
    //printf( "\n" );
  
    /*
    // Subtract abacus from abacus2, store result in abacus3
    if(abacus_del(abacus3, *abacus2, *abacus) != 0) 
    {
        printf("Error: Del operation failed\n");
        return -1;
    }

    // Print abacus3
    if(abacus_print(*abacus3) != 0) 
    {
        printf("Error: Print operation failed\n");
        return -1;
    }
    */
    /*
    abacus_print(*abacus);
    printf( "\n" );
    abacus_print(*abacus2);
    printf( "\n" );
    */
  
    // Free memory
    abacus_free(abacus);
    abacus_free(abacus2);
    abacus_free(abacus3);

    return 0;
}

sAbacus * abacus_init( void )
{
  sAbacus *init;
  init = calloc( 1 , sizeof(sAbacus) );

  return init;
}
void abacus_free( sAbacus * aba )
{
  free( aba->pUpperRod );
  free( aba->pLowerRod );
  free( aba );
}


int32_t abacus_set( sAbacus *pA, char *pStr )
{
  int16_t n = 0;
  while( n <= 255 )
  {
    if( *(pStr + n) == 0 )
    {
      if( n == 0 )
      {
        return -1;
      }
      break;
    }
    if( *(pStr + n) < 48 || *(pStr + n) > 57 )
    {
      return -1;
    }
    if( n == 255 && *(pStr + n + 1) != 0 )
    {
      return -1;
    }
    n++;
  }
  pA -> number = n;
  pA -> pUpperRod = calloc( n , sizeof(uint8_t) );
  pA -> pLowerRod = calloc( n , sizeof(uint8_t) );
  for( size_t i = 0 ; i < n ; i++ )
  {
    if( *(pStr + i) >= 53 )
    {
      *(pA->pUpperRod + i) = 1;
      *(pA->pLowerRod + i) = *(pStr + i) - 53;
    }
    else
    {
      *(pA->pLowerRod + i) = *(pStr + i) - 48;
    }
  }
  
  return 0;
}

int32_t abacus_add( sAbacus *pA, sAbacus b, sAbacus c )
{
  if( b.number == 0 || c.number == 0 )
  {
    return -1;
  }
  if( pA == NULL )
  {
    pA = abacus_init();
  }

  char *pnew = NULL;
  if( b.number >= c.number )
  {
    int8_t add[b.number+1];
    for( size_t i = 0 ; i <= b.number ; i++ )
    {
      if( i == 0 )
      {
        add[i] = 0;
        continue;
      }
      if( i < (b.number - c.number + 1) )
      {
        add[i] = ( (b.pUpperRod)[i-1]*5 + (b.pLowerRod)[i-1] );
      }
      else
      {
        add[i] = ( (b.pUpperRod)[i-1]*5 + (b.pLowerRod)[i-1] ) + ( (c.pUpperRod)[i-b.number+c.number-1]*5 + (c.pLowerRod)[i-b.number+c.number-1] );
      }
    }

    carry( add , b.number+1 );

    if( b.number + 1 == 256 && add[0] != 0 )
    {
      return -1;
    }
    for( size_t i = 0 ; i < b.number+1 ; i++ )
    {
      if( add[i] > 9 )
      {
        return -1;
      }
    }

    if( add[0] == 0 )
    {
      pnew = calloc( b.number , sizeof(uint8_t) );
      for( size_t i = 0 ; i < b.number ; i++ )
      {
        pnew[i] = add[i+1] + 48;
      }
    }
    else
    {
      pnew = calloc( b.number+1 , sizeof(uint8_t) );
      for( size_t i = 0 ; i <= b.number ; i++ )
      {
        pnew[i] = add[i] + 48;
      }
    }
  }
  else
  {
    int8_t add[c.number+1];
    for( size_t i = 0 ; i <= c.number ; i++ )
    {
      if( i == 0 )
      {
        add[i] = 0;
        continue;
      }
      if( i < (c.number - b.number + 1) )
      {
        add[i] = ( (c.pUpperRod)[i-1]*5 + (c.pLowerRod)[i-1] );
      }
      else
      {
        add[i] = ( (c.pUpperRod)[i-1]*5 + (c.pLowerRod)[i-1] ) + ( (b.pUpperRod)[i-c.number+b.number-1]*5 + (b.pLowerRod)[i-c.number+b.number-1] );
      }
    }

    carry( add , c.number+1 );

    if( c.number + 1 == 256 && add[0] != 0 )
    {
      return -1;
    }
    for( size_t i = 0 ; i < c.number+1 ; i++ )
    {
      if( add[i] > 9 )
      {
        return -1;
      }
    }

    if( add[0] == 0 )
    {
      pnew = calloc( c.number , sizeof(uint8_t) );
      for( size_t i = 0 ; i < c.number ; i++ )
      {
        pnew[i] = add[i+1] + 48;
      }
    }
    else
    {
      pnew = calloc( c.number+1 , sizeof(uint8_t) );
      for( size_t i = 0 ; i <= c.number ; i++ )
      {
        pnew[i] = add[i] + 48;
      }
    }
  }

  abacus_set( pA , pnew );
  return 0;
}

int32_t abacus_del( sAbacus *pA, sAbacus b, sAbacus c )
{
  if( b.number == 0 || c.number == 0 )
  {
    return -1;
  }
  if( pA == NULL )
  {
    pA = abacus_init();
  }

  char *pnew = NULL;
  if( b.number >= c.number )
  {
    int8_t del[b.number];
    for( size_t i = 0 ; i < b.number ; i++ )
    {
      if( i < (b.number - c.number) )
      {
        del[i] = ( (b.pUpperRod)[i]*5 + (b.pLowerRod)[i] );
      }
      else
      {
        del[i] = ( (b.pUpperRod)[i]*5 + (b.pLowerRod)[i] ) - ( (c.pUpperRod)[i-b.number+c.number]*5 + (c.pLowerRod)[i-b.number+c.number] );
      }
    }
    
    carry( del , b.number );

    for( size_t i = 0 ; i < b.number ; i++ )
    {
      if( del[i] < 0 )
      {
        return -1;
      }
    }

    pnew = calloc( b.number , sizeof(uint8_t) );
    for( size_t i = 0 ; i < b.number ; i++ )
    {
      pnew[i] = del[i] + 48;
    }
  }
  else
  {
    return -1;
  }

  abacus_set( pA , pnew );
  return 0;
}

int32_t abacus_print( sAbacus a )
{
  int8_t flag = 0;
  if( a.number == 0 )
  {
    return -1;
  }
  for( size_t j = 0 ; j < 8 ; j++ )
  {
    flag = 0;
    for( size_t i = 0 ; i < a.number ; i++ )
    {
      if( flag == 0 && (a.pUpperRod)[i] == 0 && (a.pLowerRod)[i] == 0 && i != (a.number-1) )
      {
        continue;
      }
      flag = 1;
      if( j == 0 )
      {
        if( (a.pUpperRod)[i] == 0 )
        {
          printf( "\033[1;31m""*" );
        }
        else if( (a.pUpperRod)[i] == 1 )
        {
          printf( " " );
        }
      }
      else if( j == 1 )
      {
        if( (a.pUpperRod)[i] == 0 )
        {
          printf( " " );
        }
        else if( (a.pUpperRod)[i] == 1 )
        {
          printf( "*" );
        }
      }
      else if( j == 2 )
      {
        printf( "\033[1;37m""-" );
      }
      else if( j == 3 )
      {
        if( (a.pLowerRod)[i] == 0 || (a.pLowerRod)[i] == 5 )
        {
          printf( " " );
        }
        else
        {
          printf( "\033[1;33m""*" );
        }
      }
      else if( j == 4 )
      {
        if( (a.pLowerRod)[i] == 1 || (a.pLowerRod)[i] == 6 )
        {
          printf( " " );
        }
        else
        {
          printf( "*" );
        }
      }
      else if( j == 5 )
      {
        if( (a.pLowerRod)[i] == 2 || (a.pLowerRod)[i] == 7 )
        {
          printf( " " );
        }
        else
        {
          printf( "*" );
        }
      }
      else if( j == 6 )
      {
        if( (a.pLowerRod)[i] == 3 || (a.pLowerRod)[i] == 8 )
        {
          printf( " " );
        }
        else
        {
          printf( "*" );
        }
      }
      else if( j == 7 )
      {
        if( (a.pLowerRod)[i] == 4 || (a.pLowerRod)[i] == 9 )
        {
          printf( " " );
        }
        else
        {
          printf( "*" );
        }
      }
    }
    printf( "\n" );
  }
  
  return 0;
}


void carry( int8_t *start , int16_t n )
{
  for( size_t i = 1 ; i <= n ; i++ )
  {
    if( start[n-i] > 9 && (n - i) > 0 )
    {
      start[n-i] -= 10;
      start[n-i-1] += 1;
    }
    if( start[n-i] < 0 && (n - i) > 0 )
    {
      start[n-i] += 10;
      start[n-i-1] -= 1;
    }
  }
}
