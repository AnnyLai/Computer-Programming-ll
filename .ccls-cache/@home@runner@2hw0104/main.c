#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _node
{
  char *key;
  struct _node *back;
  struct _node *next;
  struct _node *forward;
}node;

node *read( char *json );
int main() 
{
  char json[8193] = {0};
  char buf[50] = {0};
  int8_t choice = -1;
  printf( "Please enter the JSON string:\n" );
  fgets( &json[0] , 8193 , stdin );

  printf( "Choice (0:Exit ,1:Get) : " );
  scanf( "%hhd" , &choice );
  if( choice == 0 )
  {
    return 0;
  }
  else if( choice == 1 )
  {
    printf( "Key: " );
    fgets( &buf[0] , 50 , stdin );
    printf( "Value: " );
  }
  return 0;
}

//{ "firstName": "John", 
//  "lastName": "Smith", 
//  "sex": "male", 
//  "age": 25, 
//  "address": 
//    { "streetAddress": "21 2nd Street", 
//      "city": "New York", 
//      "state": "NY",
//      "postalCode": "10021" }, 
//  "phoneNumber": 
//   [ { "type": "home", "number": "212555-1234" },
//     { "type": "fax", "number": "646 555-4567" } ] }
node *read( char *json )
{
  node *start = calloc( 1 , sizeof(node) );
  node *now = start;
  int32_t i = 0;
  while( 1 )
  {
    if( json[i] == '{' )
    {
      if( i == 0 )
      {
        continue;
      }
      else
      {
        now -> forward = calloc( 1 , sizeof(node) );
        (now->forward) -> back = now;
        (now->forward) -> forward = NULL;
        (now->forward) -> next = NULL;
        now = now -> forward;
      }
    }
    else if( json[i] == '"' )
    {
      int32_t count = 1;
      while( 1 )
      {
        if( json[i+count] == '"' )
        {
          break;
        }
        count++;
      }
      now -> key = calloc( count , sizeof(char) );
      for( size_t k = 1 ; k < count ; k++ )
      {
        (now->key)[k] = json[i+k];
      }
    }
  }
}
