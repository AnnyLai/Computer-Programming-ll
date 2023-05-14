#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int8_t modify( int8_t num );

int main() 
{ 
  int8_t num = 0;
  printf( "Which file are you going to modify: " );
  scanf( "%hhd" , &num );

  if( modify( num ) == 0 )
  {
    printf( "Modification succeeded.\n" );
  }
  else
  {
    printf( "Modification failed.\n" );
  }
  
  return 0; 
}

int8_t modify( int8_t num )
{
  if( num < 1 || num > 3 )
  {
    printf( "Invalid file number.\n" );
    return -1;
  }

  char filename[7] = "R1.GRP";
  if( num == 2 )
  {
    filename[1] = '2';
  }
  else if( num == 3 )
  {
    filename[1] = '3';
  }

  FILE *fp = NULL;
  fp = fopen( &filename[0] , "r+" );
  if( fp == NULL )
  {
    printf( "Can't open file.\n" );
    return -1;
  }

  printf( "What do you want to change?\n" );
  printf( "1. Level\n2. Experience\n3. Health Point\n4. Max value of Health Point.\n5. Physical Strength\n6. Internal Force faction\n7. Internal Force\n8. Max value of Internal Force\n9. Attack\n10. Defence\n" );
  printf( "11. Qinggong\n12. Medical Ability\n13. ")

  fclose( fp );
  return 0;
}
