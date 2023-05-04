#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

struct option long_options[] =
{
    { "width" ,  1 , NULL , 'w' },
    { "height" ,  1 , NULL , 'h' },
    { "number" ,  1 , NULL , 'n' },
    { "input" ,  1 , NULL , 'i' },
    { "output" ,  1 , NULL , 'o' },
    { "help" ,  0 , NULL , 9999 },
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
void header_init( BmpHeader *in );

int main( int argc , char *argv[] )
{
	int32_t x = -1, y = -1;
	int32_t w = 0, h = 0;
	int32_t n = 2;
	char *inname = NULL;
	char *outname = NULL;
	int32_t i = 0;
	
	int32_t option = 0;
	int32_t index = 0;
	int8_t countx = 0, county = 0, countw = 0, counth = 0, countn = 0, counti = 0, counto = 0;
	while ( ( option = getopt_long( argc, argv, "x:y:w:h:n:i:o:", long_options, &index ) ) != -1 )
	{
		switch( option )
		{
			case 'x':
				countx++;
				i = 0;
				x = 0;
				while( optarg[i] != 0 )
				{
					x = x * 10 + optarg[i] - '0';
					i++;
				}
				break;
			case 'y':
				county++;
				i = 0;
				y = 0;
				while( optarg[i] != 0 )
				{
					y = y * 10 + optarg[i] - '0';
					i++;
				}
				break;
			case 'w':
				countw++;
				i = 0;
				w = 0;
				while( optarg[i] != 0 )
				{
					w = w * 10 + optarg[i] - '0';
					i++;
				}
				break;
			case 'h':
				counth++;
				i = 0;
				h = 0;
				while( optarg[i] != 0 )
				{
					h = h * 10 + optarg[i] - '0';
					i++;
				}
				break;
			case 'n':
				countn++;
				i = 0;
				n = 0;
				while( optarg[i] != 0 )
				{
					n = n * 10 + optarg[i] - '0';
					i++;
				}
				break;
			case 'i':
				counti++;
				i = 0;
				inname = (char *)calloc( strlen(optarg)+1 , sizeof(char) );
				while( optarg[i] != 0 )
				{
					inname[i] = optarg[i];
					i++;
				}
				inname[strlen(optarg)] = 0;
				break;
			case 'o':
				counto++;
				i = 0;
				outname = (char *)calloc( strlen(optarg)+1 , sizeof(char) );
				while( optarg[i] != 0 )
				{
					outname[i] = optarg[i];
					i++;
				}
				outname[strlen(optarg)] = 0;
				break;
			case 9999:
				printf( "-x              mandatory, x value.\n-y              mandatory, y value.\n" );
				printf( "-w, −−width     mandatory, w value.\n-h, −−height    mandatory, h value.\n-n, −−number    optional, n value. Default n is 2.\n" );
				printf( "-i, −−input     mandatory, the input BMP file name.\n-o, −−output    optional, the output BMP file name. Default name is output.bmp.\n" );
				printf( "–help           print the usage help.\n" );
				return 0;
			default:
				printf( "Unknown option.\n" ); 
				break;
		}
	}

	if( x < 0 || y < 0 || w <= 0 || h <= 0 || n <= 0 || inname == NULL || n > w || n > h )
	{
		printf( "Not enough or invalid inputs.\n" );
		return 0;
	}
	if( countx > 1 || county > 1 || countw > 1 || counth > 1 || countn > 1 || counti > 1 || counto > 1 )
	{
		printf( "Too many variables.\n");
		return 0;
	}
	
	FILE *pIn = NULL;
	FILE *pOut = NULL;

	BmpHeader header;
	header_init( &header );

	pIn = fopen( inname , "rb");
	if( pIn == NULL )
	{
		printf( "Unable to open input file.\n" );
		perror("Error");
		return 0;
	}

	if( outname == NULL )
	{
		outname = (char *)calloc( 11 , sizeof(char) );
		outname[0] = 'o';
		outname[1] = 'u';
		outname[2] = 't';
		outname[3] = 'p';
		outname[4] = 'u';
		outname[5] = 't';
		outname[6] = '.';
		outname[7] = 'b';
		outname[8] = 'm';
		outname[9] = 'p';
		outname[10] = 0;
	}
	pOut = fopen( outname , "wb" );
	if( pOut == NULL )
	{
		printf( "Unable to create output file.\n" );
		return 0;
	}

	int64_t count = 0;
	count = fread( &header , sizeof(BmpHeader) , 1 , pIn );
	fwrite( &header , sizeof(BmpHeader) , 1 , pOut );

	if( x > header.height || y > header.width )
	{
		printf( "Invalid input.\n" );
		free( inname );
		free( outname );
		fclose( pIn );
		fclose( pOut );
		return 0;
	}
	
	uint8_t *buf = NULL;
	buf = (uint8_t *)calloc( header.width*3 + header.width%4 + 1 , sizeof(uint8_t) );

	for( i = 0 ; i < header.height-x-h ; i++ )
	{
		count = fread( buf , 1 , header.width*3+header.width%4 , pIn );
		fwrite( buf , 1 , count , pOut );
	}
	count = fread( buf , 1 , y*3 , pIn );
	fwrite( buf , 1 , count , pOut );

	uint64_t change[3] = {0};
	uint8_t *save = NULL;
	save = (uint8_t *)calloc( (w/n) * 3 , sizeof(uint8_t) );
	uint64_t set = (header.width*3+header.width%4);

	for( size_t q = 0 ; q < h/n ; q++ )
	{
		for( size_t k = 0 ; k < w/n ; k++ )
		{
			save[k*3] = 0;
			save[k*3+1] = 0;
			save[k*3+2] = 0;
		}
		fseek( pIn , -set , SEEK_CUR );
		for( size_t k = 0 ; k < w/n ; k++ )
		{
			for( size_t k = 0 ; k < 3 ; k++ )
			{
				change[k] = 0;
			}
			fseek( pIn , n*3 , SEEK_CUR );
			for( i = 0 ; i < n ; i++ )
			{
				fseek( pIn , set , SEEK_CUR );
				fseek( pIn , -n*3 , SEEK_CUR );
				count = fread( buf , 1 , n*3 , pIn );
				for( size_t j = 0 ; j < n*3 ; j+=3 )
				{
					change[0] += buf[j];
					change[1] += buf[j+1];
					change[2] += buf[j+2];
				}
			}
			for( size_t j = 0 ; j < 3 ; j++ )
			{
				change[j] /= (n * n);
			}
			save[k*3] = (uint8_t)change[0];
			save[k*3+1] = (uint8_t)change[1];
			save[k*3+2] = (uint8_t)change[2];
			fseek( pIn , -n*set , SEEK_CUR );
		}
	
		fseek( pIn , set , SEEK_CUR );
		fseek( pIn , -(w/n)*n*3 , SEEK_CUR );

		for( size_t k = 0 ; k < n ; k++ )
		{
			for( size_t j = 0 ; j < w/n ; j++ )
			{
				for( size_t q = 0 ; q < n ; q++ )
				{
					fwrite( &save[j*3] , 1 , 3 , pOut );
				}
			}
			fseek( pIn , (w/n)*n*3 , SEEK_CUR );
			if( w % n != 0 )
			{
				count = fread( buf , 1 , (w%n)*3 , pIn );
				fwrite( buf , 1 , count , pOut );
			}
			
			count = fread( buf , 1 , (header.width-y-w)*3+header.width%4 , pIn );
			fwrite( buf , 1 , count , pOut );
			if( !feof(pIn) )
			{
				count = fread( buf , 1 , y*3 , pIn );
				fwrite( buf , 1 , count , pOut );
			}
		}
	}

	while( !feof(pIn) )
	{
		count = fread( buf , 1 , sizeof( buf ) , pIn );
		fwrite( buf , 1 , count , pOut );
	}

	free( inname );
	free( outname );
	free( buf );
	free( save );
	fclose( pIn );
	fclose( pOut );
	
	return 0;
}

void header_init( BmpHeader *in )
{
    in -> bm[0] = 0;
    in -> bm[1] = 0;
    in -> size = 0;
    in -> reserve = 0;
    in -> offset = 0;
    in -> header_size = 0;
    in -> width = 0;
    in -> height = 0;
    in -> planes = 0;
    in -> bpp = 0;
    in -> compression = 0;
    in -> bitmap_size = 0;
    in -> hres = 0;
    in -> vres = 0;
    in -> used = 0;
    in -> important = 0;
}

