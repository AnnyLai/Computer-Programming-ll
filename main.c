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
  
    printf( "Please enter the JSON string:\n" );
    fgets( json , 8193 , stdin );
    jsono = read( &json[0] );

    while( 1 )
    {
        char choice[3] = {0};
        printf( "Choice (0:Exit ,1:Get) : " );
        fgets( choice , 3 , stdin );
        if( choice[0] == '0' )
        {
            printf( "Bye\n" );
            return 0;
        }
        else if( choice[0] == '1' )
        {
            find( jsono );
        }
    }

    return 0;
}

node *read( char *json )
{
  node *start = calloc( 1 , sizeof(node) );
  node *now = start;
  now -> key = NULL;
  now -> back = NULL;
  now -> next = NULL;
  now -> forward = NULL;
  int32_t i = 0;
  while( json[i] != 0 )
  {
    if( json[i] == ':' )
    {
        now -> forward = calloc( 1 , sizeof(node) );
        (now->forward) -> key = NULL;
        (now->forward) -> back = now;
        (now->forward) -> next = NULL;
        (now->forward) -> forward = NULL;
        
        now = now -> forward;
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
            (now->key)[k-1] = json[i+k];
        }
        (now->key)[count-1] = 0;
        i += count;
    }
    else if( json[i] == ',' )
    {
        now = now -> back;
        if( *(now->key) > 47 && *(now->key) < 58 )
        {
            now -> next = calloc( 1 , sizeof(node) );
            (now->next) -> key = calloc( 2 , sizeof(char) );
            ((now->next)->key)[0] = (now->key)[0] + 1;//what if > 10?
            ((now->next)->key)[1] = 0;
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
        now -> key = calloc( 2 , sizeof(char) );
        (now->key)[0] = '0';
        (now->key)[1] = 0;
        now -> forward = calloc( 1 , sizeof(node) );
        (now->forward) -> key = NULL;
        (now->forward) -> back = now;
        (now->forward) -> next = NULL;
        (now->forward) -> forward = NULL;

        now = now -> forward;
    }
    else if( json[i] > 47 && json[i] < 58 )
    {
        int32_t count = 1;
        while( 1 )
        {
            if( json[i+count] < 48 || json[i+count] > 57 )
            {
                break;
            }
            count++;
        }
        now -> key = calloc( count + 1 , sizeof(char) );
        for( size_t k = 0 ; k < count ; k++ )
        {
            (now->key)[k] = json[i+k];
        }
        (now->key)[count] = 0;
        i += (count-1);
    }
    i++;
  }

  return start;
}

void find( node *st )
{
    node *now = st;
    char buf[50] = {0};
    printf( "Key: " );
    fgets( buf , 50 , stdin );

    int8_t flag = 0;
    int32_t prei = 0;

    for( size_t i = 0 ; i < 50 ; i++ )
    {
        if( buf[i] == '[' || buf[i] == ']' || buf[i] == 10 )
        {
            flag = 0;
            while( now != NULL )
            {
                for( size_t j = prei ; j < i ; j++)
                {
                    if( (now->key)[j-prei] != buf[j] )
                    {
                        break;
                    }
                    else if( (now->key)[j-prei] == buf[j] && j == i-1 )
                    {
                        flag = 1;
                        now = now -> forward;
                    }
                }
                if( flag == 1 )
                {
                break;
                }
                now = now -> next;
            }
            prei = i+1;
        }
        else if( buf[i] == '.' )
        {
            if( buf[i-1] == ']' )
            {
                prei += 1;
                continue;
            }
            else
            {
                flag = 0;
                while( now != NULL )
                {
                    for( size_t j = prei ; j < i ; j++)
                    {
                        if( (now->key)[j-prei] != buf[j] )
                        {
                            break;
                        }
                        else if( (now->key)[j-prei] == buf[j] && j == i-1 )
                        {
                            flag = 1;
                            now = now -> forward;
                        }
                    }
                    if( flag == 1 )
                    {
                        break;
                    }
                    now = now -> next;
                }
                prei = i+1;
            }
        }
    }
  
    printf( "Value: " );
    puts( now -> key );
}



