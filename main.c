#include <unistd.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct option long_options[] =
{
  { "output" ,  1 , NULL , 'o' },
  { "help" ,  0 , NULL , 'h' },
  {  0 , 0 , 0 , 0 },
};

struct _BmpHeader
{
    char        bm[2];
    uint32_t    size;
    uint32_t    reserve;
    uint32_t    offset;
    uint32_t    header_size;
    int32_t    width;
    int32_t    height;
    uint16_t    planes;
    uint16_t    bpp;
    uint32_t    compression;
    uint32_t    bitmap_size;
    int32_t    hres;
    int32_t    vres;
    uint32_t    used;
    uint32_t    important;
}__attribute__ ((__packed__));
typedef struct _BmpHeader BmpHeader;

int main( int argc, char *argv[] )
{
  int32_t option = 0;
	int32_t index = 0;
	int64_t a = 0;
  int32_t n = 0;
  char *fname = NULL;
	while ( ( option = getopt_long( argc, argv, "a:n:o:h", long_options, &index ) ) != -1 )
	{
		switch( option )
		{
			case 'a':
				for( size_t i = 0 ; i < strlen(optarg) ; i++ )
        {
          a = a * 10 + optarg[i] - '0';
        }
				break;
			case 'n':
				for( size_t i = 0 ; i < strlen(optarg) ; i++ )
        {
          n = n * 10 + optarg[i] - '0';
        }
				break;
			case 'o':
        fname = optarg;
				break;
			case 'h':
				printf( "Options:\n" ); 
        printf( "    -a <int>          Mandatory. Set the value of a where the unit is pixel.\n" );
        printf( "                          Range: 100 - 2000\n" );
        printf( "    -n <int>          Mandatory. Set the value of n.\n" );
        printf( "    -o, --output      Set the output file name.\n" );
        printf( "    -h, --help        Display this description.\n" );
				return 0;
			default:
				printf( "Unknown option.\n" ); 
				break;
		}
	}
  
  if( a == 0 || n == 0 )
  {
    printf( "Not enough variables.\n" );
    return 0;
  }
  if( fname && (fname[strlen(fname)-1] != 'p' || fname[strlen(fname)-2] != 'm' || fname[strlen(fname)-3] != 'b' || fname[strlen(fname)-4] != '.') )
  {
    printf( "Invalid output file name. Output file must be a bmp file (ends with \".bmp\")\n" );
    return 0;
  }
  if( fname == NULL )
  {
    fname = "output.bmp";
  }

  printf( "a = %ld, n = %d, output name = %s\n" , a , n , fname );
  int64_t b = 2 * a / (1 + sqrt(5.0));
  printf( "b = %ld\n" , b );
  BmpHeader header;
  header.bm[0] = 'B';
  header.bm[1] = 'M';
  header.size = 54 + a * (a+b) * 3 + (a+b) % 4;
  header.reserve = 0;
  header.offset = 54;
  header.header_size = 40;
  header.width = ( a + b );
  header.height = a;
  header.planes = 1;
  header.bpp = 24;
  header.compression = 0;
  header.bitmap_size = a * (a+b) * 3 + ((a+b) % 4);
  header.hres = 0;
  header.vres = 0;
  header.used = 0;
  header.important = 0;

  FILE *pf = NULL;
  pf = fopen( fname , "w+" );
  if( pf == NULL )
  {
    printf( "Failed to create output file.\n" );
    return 0;
  }
  fwrite( &header , sizeof( header ) , 1 , 
 pf );

  uint8_t white = 255;
  uint8_t black = 0;
  for( size_t i = 0 ; i < a ; i++ )
  {
    for( size_t j = 0 ; j < (a+b) ; j++ )
    {
      if( i == 0 || i == a-1 || j == 0 || j == (a+b-1) )
      {
        for( size_t k = 0 ; k < 3 ; k++ )
        {
          fwrite( &black , 1 , 1 , pf );
        }
        continue;
      }
      for( size_t k = 0 ; k < 3 ; k++ )
      {
        fwrite( &white , 1 , 1 , pf );
      }
    }
    for( size_t j = 0 ; j < (a+b)%4 ; j++ )
    {
      fwrite( &black , 1, 1 , pf );
    }
  }
  fclose( pf );

  int64_t x = 0;
  int64_t y = a;
  int64_t last = a + b;
  int64_t edge = a;
  int64_t temp = 0;
  uint8_t buf[3] = {0};
  for( size_t i = 0 ; i < n ; i++ )
  {
    if( edge > last )
    {
      printf( "N is to big. In a picture of the height %ld, the biggest n is %lu.\n" , a , i );
      return 0;
    }
    pf = fopen( fname , "r+" );
    fseek( pf , header.offset , SEEK_SET );
    fseek( pf , x*((a+b)*3+(a+b)%4) + y*3 , SEEK_CUR );
    if( i % 4 == 0 )
    {
      for( size_t j = 0 ; j < edge ; j++ )
      {
        for( size_t k = 0 ; k < 3 ; k++ )
        {
          fwrite( &black , 1 , 1 , pf );
        }
        fseek( pf , (a+b-1)*3 + (a+b)%4 , SEEK_CUR );
      }
      x += (edge - (last-edge));
      temp = edge;
      edge = last - edge;
      last = temp;
    }
    else if( i % 4 == 1 )
    {
      for( size_t j = 0 ; j < edge ; j++ )
      {
        for( size_t k = 0 ; k < 3 ; k++ )
        {
          fwrite( &black , 1 , 1 , pf );
        }
      }
      y += (edge - (last-edge));
      temp = edge;
      edge = last - edge;
      last = temp;
    }
    else if( i % 4 == 2 )
    {
      for( size_t j = 0 ; j < edge ; j++ )
      {
        for( size_t k = 0 ; k < 3 ; k++ )
        {
          fwrite( &black , 1 , 1 , pf );
        }
        fseek( pf , -(a+b+1)*3 - (a+b)%4 , SEEK_CUR );
      }
      x -= (edge - (last-edge));
      temp = edge;
      edge = last - edge;
      last = temp;
    }
    else if( i % 4 == 3 )
    {
      for( size_t j = 0 ; j < edge ; j++ )
      {
        for( size_t k = 0 ; k < 3 ; k++ )
        {
          fwrite( &black , 1 , 1 , pf );
        }
        fseek( pf , -6 , SEEK_CUR );
      }
      y -= (edge - (last-edge));
      temp = edge;
      edge = last - edge;
      last = temp;
    }
    fclose( pf );
  }
  
  return 0; 
}