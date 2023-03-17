#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "mystring.h"

char *mystrchr(const char *s, int c);
char *mystrrchr(const char *s, int c);
size_t mystrspn(const char *s, const char *accept);
size_t mystrcspn(const char *s, const char *reject);
char *mystrpbrk(const char *s, const char *accept);
char *mystrstr(const char *haystack , const char *needle);
char *mystrtok(char *str, const char *delim);

int main() 
{
  char test[50] = "geeks for geeks";
  char *hello = " ;";
  char letter = 0;
  
  //printf("%s\n",hello);

  //printf("%p\n",test);
  /*
  printf("%s\n", strchr(test,letter));
  printf("%s\n", mystrchr(test,letter));
  */
  /*
  printf("%s\n", strrchr(test,letter));
  printf("%s\n", mystrrchr(test,letter));
  */
  /*
  printf("%lu\n", strspn(test,hello));
  printf("%lu\n", mystrspn(test,hello));
  */
  /*
  printf("%lu\n", strcspn(test,hello));
  printf("%lu\n", mystrcspn(test,hello));
  */
  /*
  printf("%s\n", strpbrk(test,hello));
  printf("%s\n", mystrpbrk(test,hello));
  */
  /*
  printf("%s\n", strstr(test,hello));
  printf("%s\n", mystrstr(test,hello));
  */

  char *tok = NULL;
  /*
  tok = strtok( test , hello );
  while( tok != NULL )
  {
    printf("%s\n", tok);

    tok = strtok( NULL , hello );
  }
  */
  tok = mystrtok( test , hello );
  while( tok != NULL )
  {
    printf("%s\n", tok);

    tok = mystrtok( NULL , hello );
  }
  
  //puts( next );
  
  return 0;
}

char *mystrchr(const char *s, int c)
{
  long int i = 0;

  while( 1 )
  {
    if( *(s + i) == c )
    {
      return (s + i);
    }
    else if( *(s + i) == 0 )
    {
      break;
    }
    else
    {
      i += 1;
    }
  }
  
  return NULL;
}

char *mystrrchr(const char *s, int c)
{
  long int i = 0;
  long int n = 0;
  while( 1 )
  {
    if( *(s + i) == 0 )
    {
      break;
    }
    else
    {
      i += 1;
    }
  }
  n = i;
  while( n >= 0 )
  {
    if( *(s + n) == c )
    {
      return (s + n);
    }
    else
    {
      n -= 1;
    }
  }

  return NULL;
}

size_t mystrspn(const char *s, const char *accept)
{
  long int i = 0;
  int8_t flag = 0;
  while( 1 )
  {
    long int j = 0;
    while( *(accept + j) != 0 )
    {
      if( *(accept + j) == *(s + i) )
      {
        break;
      }
      if( *(accept + j) != *(s + i) && *(accept + j + 1) == 0 )
      {
        flag = 1;
        break;
      }
      j++;
    }
    if( flag == 1 )
    {
      break;
    }
    i++;
  }

  return i;
}

size_t mystrcspn(const char *s, const char *reject)
{
  long int i = 0;
  int8_t flag = 0;
  while( 1 )
  {
    long int j = 0;
    while( *(reject + j) != 0 )
    {
      if( *(reject + j) == *(s + i) )
      {
        flag = 1;
        break;
      }
      j++;
    }
    if( flag == 1 )
    {
      break;
    }
    i++;
  }
  return i;
}

char *mystrpbrk(const char *s, const char *accept)
{
  long int i = 0;
  while( 1 )
  {
    long int j = 0;
    while( *(accept + j) != 0 )
    {
      if( *(s + i) == *(accept + j) )
      {
        return (s + i);
      }
      else
      {
        j++;
      }
    }
    if( *(s + i) == 0 )
    {
      break;
    }
    else
    {
      i += 1;
    }
  }
  return NULL;
}

char *mystrstr(const char *haystack , const char *needle)
{
  long int i = 0;
  while( *(haystack + i) != 0 )
  {
    if( *(haystack + i) == *needle )
    {
      long int j = 0;
      while( *(needle + j) != 0 )
      {
        if( *(haystack + i + j) != *(needle + j) )
        {
          break;
        }
        if( *(needle + j + 1) == 0 )
        {
          return (haystack + i);
        }
        j++;
      }
    }
    i += 1;
  }
  
  return NULL;
}

char *mystrtok(char *str, const char *delim)
{
  static char *next = NULL;
  long int i = 0;
  int8_t flag = 0;
  // if( next != NULL )
  // {
  //   printf( "next: " );
  //   puts( next );
  // }
  if( str == NULL )
  {
    if( next == NULL )
    {
      return NULL;
    }
    char *ret = next;
    while( 1 )
    {
      //printf( "%ld\n" , i );
      long int j = 0;
      while( *(delim + j) != 0 )
      {
        //printf( "%c %c\n" , str[i] , *(delim+j) );
        if( *(next + i) == *(delim + j) )
        {
          flag = 1;
          break;
        }
        j++;
      }
      if( flag == 1 )
      {
        *(next + i) = 0;
        next = (next + i + 1);
        break;
      }
      if( *(next + i) == 0 )
      {
        next = NULL;
        break;
      }
      i++;
    }
    
    return ret;
  }
  else
  {
    //printf( "\n" );
    while( 1 )
    {
      //printf( "%ld\n" , i );
      long int j = 0;
      while( *(delim + j) != 0 )
      {
        //printf( "%c %c\n" , str[i] , *(delim+j) );
        if( str[i] == *(delim + j) )
        {
          flag = 1;
          break;
        }
        j++;
      }
      if( flag == 1 )
      {
        str[i] = 0;
        next = (str + i + 1);
        return str;
      }
      if( str[i] == 0 )
      {
        break;
      }
      i++;
    }
    
    return NULL;
  }
}

