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
  char *test = "geeksforgeeks";
  char *hello = "kf";
  char letter = 'H';
  
  //printf("%s\n",hello);

  //printf("%p\n",test);
  //printf("%s\n", strchr(test,letter));
  //printf("%s\n", mystrchr(test,letter));

  //printf("%s\n", strrchr(test,letter));
  //printf("%s\n", mystrrchr(test,letter));
  
  //printf("%lu\n", strspn(hello,test));
  //printf("%lu\n", mystrspn(hello,test));

  //printf("%lu\n", strcspn(test,hello));
  //printf("%lu\n", mystrcspn(test,hello));

  printf("%s\n", strpbrk(test,hello));
  printf("%s\n", mystrpbrk(test,hello));
  
  return 0;
}

char *mystrchr(const char *s, int c)
{
  long int i = 0;

  if( c == 0 )
  {
    while( 1 )
    {
      if( *(s + i) == 0 )
      {
        return (s + i);
      }
      else
      {
        i += 1;
      }
    }
  }
  while( 1 )
  {
    if( *(s + i) == 0 )
    {
      break;
    }
    if( *(s + i) == c )
    {
      return (s + i);
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
      return *(s + n);
    }
    else
    {
      n -= 1;
    }
  }
}

size_t mystrspn(const char *s, const char *accept)
{
  long int i = 0;
  while( 1 )
  {
    if( *(s + i) != *(accept + i) || *(s + i) == 0 )
    {
      break;
    }
    else
    {
      i += 1;
    }
  }
  return i;
}

size_t mystrcspn(const char *s, const char *reject)
{
  long int i = 0;
  while( 1 )
  {
    if( *(s + i) == *reject || *(s + i) == 0 )
    {
      break;
    }
    else
    {
      i += 1;
    }
  }
  return i;
}

char *mystrpbrk(const char *s, const char *accept)
{
  long int i = 0;
  while( 1 )
  {
    long int j = 0;
    while( 1 )
    {
      if( *(s + i) == *(accept + j) || *(accept + j) == 0 )
      {
        return i;
      }
      else
      {
        j += 1;
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
char *mystrstr(const char *haystack , const char *needle);
char *mystrtok(char *str, const char *delim);

