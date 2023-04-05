#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct _bibletext
{
  int32_t chapter;
  int32_t verse;
  char text[256];
  char translation_id[5];
  char book_id[30];
  char book_name[30];
  struct _bibletext *next;
}bibletext;

void bible_init( bibletext *ret );

int main() 
{
  FILE *pFile = NULL;
  FILE *pOut = NULL;

  pFile = fopen( "bible.txt" , "r" );
  if( pFile == NULL )
  {
    printf( "File could not be opened.\n" );
    return -1;
  }

  pOut = fopen( "output.txt" , "w+" );

  char inputstr[2001] = {0};
  fread( &inputstr[0] , 1 , 2000 , pFile );
  if( strlen( inputstr ) == 0 )
  {
    printf("Invalid input.\n");
    return -1;
  }
  
  char key[256] = {0};
  key[0] = ' ';
  printf("Please enter the search target: ");
  fgets( &key[1] , 256 , stdin );
  for( size_t i = 0 ; i < 256 ; i++ )
  {
    if( key[i] == 0 )
    {
      break;
    }
    if( key[i] == 10 )
    {
      key[i] = ' ';
    }
  }

  bibletext *bible = NULL;
  bibletext *now = NULL;
  int32_t i = 0;
  int32_t times = 0;
  bibletext *tempt = (bibletext *)calloc( 1 , sizeof(bibletext) );

  while( !feof(pFile) )
  //for( int l = 0 ; l < 1495 ; l++ )
  {
    if( i == 2000 )
    {
      fread( inputstr , 1 , 2000 , pFile );
      //puts( &(inputstr[0]) );
      i = 0;
    }
    bible_init( tempt );
    char tag[15] = {0};
    int32_t j = 1;
    int32_t q = 0;

    //printf( "bookname[0] = %c\n" , tempt->book_name[0] );

    //printf( "b\n" );
    //printf( "%c" , inputstr[i] );
    //puts( &inputstr[0] );
    //printf( "%c\n" , inputstr[0] );
    if( inputstr[i] == '{' )
    {
      while( inputstr[i] != '}' )
      {
        if( inputstr[i] == '"' )
        {
          j = 1;
          if( i+j == 2000 )
          {
            fread( inputstr , 1 , 2000 , pFile );
            //puts( &inputstr[0] );
            i = -j;
          }
          for( size_t s = 0 ; s < 15 ; s++ )
          {
            tag[s] = 0;
          }
          
          while( inputstr[i+j] != '"' )
          {
            tag[j-1] = inputstr[i+j];
            
            j++;
            if( i+j == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              //puts( &inputstr[0] );
              i = -j;
            }
          }

          if( strstr( &tag[0] , "chapter") )
          {
            while( inputstr[i+j] < 48 || inputstr[i+j] > 57 )
            {
              j++;
              if( i+j == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j;
              }
            }
            while( inputstr[i+j] >= '0' && inputstr[i+j] <= '9' )
            {
              tempt -> chapter = (10 * tempt->chapter) + (inputstr[i+j] - '0');
              j++;
              if( i+j == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j;
              }
            }
          }
          else if( strstr(&tag[0] , "verse") )
          {
            while( inputstr[i+j] < 48 || inputstr[i+j] > 57 )
            {
              j++;
              if( i+j == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j;
              }
            }
            while( inputstr[i+j] >= '0' && inputstr[i+j] <= '9' )
            {
              tempt -> verse = (10 * tempt->verse) + (inputstr[i+j] - '0');
              j++;
              if( i+j == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j;
              }
            }
          }
          else if( strstr(tag , "text") )
          {
            j++;
            if( i+j == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j;
            }
            while( inputstr[i+j] != '"' )
            {
              j++;
              if( i+j == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j;
              }
            }
            int32_t k = 1;
            if( i+j+k == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j - k;
            }
            while( inputstr[i+j+k] != '"' )
            {
              tempt -> text[k-1] = inputstr[i+j+k];
              k++;
              if( i+j+k == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j - k;
              }
            }
            j += k;
            if( i+j == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j;
            }
          }
          else if( strstr(tag , "translation_id") )
          {
            j++;
            if( i+j == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j;
            }
            while( inputstr[i+j] != '"' )
            {
              j++;
              if( i+j == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j;
              }
            }
            int32_t k = 1;
            if( i+j+k == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j - k;
            }
            while( inputstr[i+j+k] != '"' )
            {
              tempt -> translation_id[k-1] = inputstr[i+j+k];
              k++;
              if( i+j+k == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j - k;
              }
            }
            j += k;
            if( i+j == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j;
            }
          }
          else if( strstr(tag , "book_id") )
          {
            j++;
            if( i+j == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j;
            }
            while( inputstr[i+j] != '"' )
            {
              j++;
              if( i+j == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j;
              }
            }
            int32_t k = 1;
            if( i+j+k == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j - k;
            }
            while( inputstr[i+j+k] != '"' )
            {
              tempt -> book_id[k-1] = inputstr[i+j+k];
              k++;
              if( i+j+k == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j - k;
              }
            }
            j += k;
            if( i+j == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j;
            }
          }
          else if( strstr(tag , "book_name") )
          {
            j++;
            if( i+j == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j;
            }
            while( inputstr[i+j] != '"' )
            {
              j++;
              if( i+j == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j;
              }
            }
            int32_t k = 1;
            if( i+j+k == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j - k;
            }
            while( inputstr[i+j+k] != '"' )
            {
              tempt -> book_name[k-1] = inputstr[i+j+k];
              k++;
              if( i+j+k == 2000 )
              {
                fread( inputstr , 1 , 2000 , pFile );
                i = -j - k;
              }
            }
            j += k;
            if( i+j == 2000 )
            {
              fread( inputstr , 1 , 2000 , pFile );
              i = -j;
            }
          }
          i += j;
        }
        i++;
        if( i == 2000 )
        {
          fread( inputstr , 1 , 2000 , pFile );
          //puts( &inputstr[0] );
          i = 0;
        }
      }

      /*int o = 0;
      while( tempt -> book_id[o] != 0 )
      {
        putchar( tempt -> book_id[o] );
        o++;
      }
      printf( " %d:%d " , tempt->chapter , tempt->verse );
      puts( &(tempt -> text[0]) );*/

      if( strstr( &(tempt->text[0]) , &key[0]) != NULL )
      {
        times++;
        char *num = calloc( 5 , sizeof(char) );
        int32_t Q = 0;
        if( times/10000 != 0 )
        {
          num[0] = (times / 10000) + '0';
          Q = times % 10000;
          num[1] = Q / 1000 + '0';
          Q = times % 1000;
          num[2] = Q / 100 + '0';
          Q = times % 100;
          num[3] = Q / 10 + '0';
          Q = times % 10;
          num[4] = Q + '0';
        }
        else if( times/1000 != 0 )
        {
          num[0] = (times / 1000) + '0';
          Q = times % 1000;
          num[1] = Q / 100 + '0';
          Q = times % 100;
          num[2] = Q / 10 + '0';
          Q = times % 10;
          num[3] = Q + '0';
        }
        else if( times/100 != 0 )
        {
          num[0] = (times / 100) + '0';
          Q = times % 100;
          num[1] = Q / 10 + '0';
          Q = times % 10;
          num[2] = Q + '0';
        }
        else if( times/10 != 0 )
        {
          num[0] = (times / 10) + '0';
          Q = times % 10;
          num[1] = Q + '0';
        }
        else
        {
          num[0] = times + '0';
        }
        int32_t size = strlen(&num[0]);
        fwrite( &num[0] , 1 , size , pOut );
        fwrite( &(tempt->book_id[0]) , 1 , strlen(&(tempt->book_id[0])) , pOut );
        Q = 0;
        num[0] = ' ';
        if( tempt->chapter/100 != 0 )
        {
          num[1] = (tempt->chapter / 100) + '0';
          Q = tempt->chapter % 100;
          num[2] = Q / 10 + '0';
          Q = tempt->chapter % 10;
          num[3] = Q + '0';
          num[4] = ':';
        }
        else if( tempt->chapter/10 != 0 )
        {
          num[1] = (tempt->chapter / 10) + '0';
          Q = tempt->chapter % 10;
          num[2] = Q + '0';
          num[3] = ':';
        }
        else
        {
          num[1] = tempt->chapter + '0';
          num[2] = ':';
        }
        fwrite( &num[0] , 1 , strlen(&num[0]) , pOut );
        Q = 0;
        if( tempt->verse/100 != 0 )
        {
          num[0] = (tempt->verse / 100) + '0';
          Q = tempt->verse % 100;
          num[1] = Q / 10 + '0';
          Q = tempt->verse % 10;
          num[2] = Q + '0';
          num[3] = ' ';
        }
        else if( tempt->verse/10 != 0 )
        {
          num[0] = (tempt->verse / 10) + '0';
          Q = tempt->verse % 10;
          num[1] = Q + '0';
          num[2] = ' ';
        }
        else
        {
          num[0] = tempt->verse + '0';
          num[1] = ' ';
        }
        fwrite( &num[0] , 1 , strlen(&num[0]) , pOut );
        fprintf( pOut , "%s\n" , &(tempt -> text[0]) );
        /*if( !now )
        {
          bible = (bibletext *)calloc( 1 , sizeof(bibletext) );
          bible_init( bible );
          now = bible;
        }
        else
        {
          now -> next = (bibletext *)calloc( 1 , sizeof(bibletext) );
          bible_init( now->next );
          now = now -> next;
        }
        
        now -> chapter = tempt -> chapter;
        now -> verse = tempt -> verse;
        q = 0;
        while( tempt -> text[q] != 0 )
        {
          now -> text[q]  = tempt -> text[q];
          q++;
        }
        q = 0;
        while( tempt -> translation_id[q] != 0 )
        {
          now -> translation_id[q] = tempt -> translation_id[q];
          q++;
        }
        q = 0;
        while( tempt -> book_id[q] != 0 )
        {
          now -> book_id[q] = tempt -> book_id[q];
          q++;
        }
        q = 0;
        while( tempt -> book_name[q] != 0 )
        {
          now -> book_name[q] = tempt -> book_name[q];
          q++;
        }*/
      }
    }

    i++;
    if( i == 2000 )
    {
      fread( inputstr , 1 , 2000 , pFile );
      puts( &inputstr[0] );
      i = 0;
    }
  }

  fclose( pOut );
  pOut = fopen( "output.txt" , "r" );

  if( pOut )
  {
    while( !feof(pOut) )
    {
      fread( &(inputstr[0]) , 1 , 2000 , pOut );
      inputstr[2000] = 0;
      puts( &(inputstr[0]) );
    }
  }
  /*now = bible;
  printf( "Found %d time(s)\n" , times );
  for( size_t s = 0 ; s < times ; s++ )
  {
    printf( "%lu. " , s+1 );
    i = 0;
    while( now -> book_id[i] != 0 )
    {
      putchar( now -> book_id[i] );
      i++;
    }
    printf( " %d:%d " , now->chapter , now->verse );
    puts( &(now -> text[0]) );
    now = now -> next;
  }*/

  fclose( pFile );
  fclose( pOut );
  
  return 0;
}

void bible_init( bibletext *ret )
{
  ret -> chapter = 0;
  ret -> verse = 0;
  for( size_t i = 0 ; i < 256 ; i++ )
  {
    if( i < 30 )
    {
      if( i < 5 )
      {
        ret -> translation_id[i] = 0;
      }
      ret -> book_id[i] = 0;
      ret -> book_name[i] = 0;
    }
    ret -> text[i] = 0;
  }
  ret -> next = NULL;
}

