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
void find( node *st );
int main() 
{
  char json[8193] = {0};
  node *jsono = NULL;
  
  int8_t choice = -1;
  printf( "Please enter the JSON string:\n" );
  fgets( &json[0] , 8193 , stdin );
  jsono = read( &json[0] );

  printf( "Choice (0:Exit ,1:Get) : " );
  scanf( "%hhd" , &choice );
  if( choice == 0 )
  {
    return 0;
  }
  else if( choice == 1 )
  {
    find( jsono );
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
  while( json[i] != 0 )
  {
    if( json[i] == ':' )
    {
      if( i == 0 )
      {
        i++;
        continue;
      }
      else
      {
        now -> forward = calloc( 1 , sizeof(node) );
        (now->forward) -> key = NULL;
        (now->forward) -> back = now;
        (now->forward) -> next = NULL;
        (now->forward) -> forward = NULL;
        
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
      i += count;
    }
    else if( json[i] == ',' )
    {
      now = now -> back;
      if( *(now->key) > 47 && *(now->key) < 58 )
      {
        now -> next = calloc( 1 , sizeof(node) );
        (now->next) -> key = calloc( 1 , sizeof(char) );
        *((now->next)->key) = *(now->key) + 1;//what if > 10?
        (now->next) -> back = now -> back;
        (now->next) -> next = NULL;

        now = now -> next;
        now -> forward = calloc( 1 , sizeof(node) );
        (now->forward) -> key = NULL;
        (now->forward) -> back = now;
        (now->forward) -> next = NULL;
        (now->forward) -> forward = NULL;

        now = now -> forward;
      }
      else
      {
        now -> next = calloc( 1 , sizeof(node) );
        (now->next) -> key = NULL;
        (now->next) -> back = now -> back;
        (now->next) -> next = NULL;
        (now->next) -> forward = NULL;

        now = now -> next;
      }
    }
    else if( json[i] == '}' || json[i] == ']' )
    {
      now = now -> back;
    }
    else if( json[i] == '[' )
    {
      now -> key = calloc( 1 , sizeof(char) );
      *(now->key) = '0';
      now -> forward = calloc( 1 , sizeof(node) );
      (now->forward) -> key = NULL;
      (now->forward) -> back = now;
      (now->forward) -> next = NULL;
      (now->forward) -> forward = NULL;

      now = now -> forward;
    }
    i++;
  }

  return start;
}

void find( node *st )
{
  char buf[50] = {0};
  printf( "Key: " );
  fgets( &buf[0] , 50 , stdin );
  printf( "Value: " );
}

