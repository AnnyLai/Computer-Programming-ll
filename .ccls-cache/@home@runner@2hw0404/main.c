#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
int8_t header_check( BmpHeader *in );

int main( int argc, char *argv[] )
{
	int8_t purpose = 0;
	char *bmpname = NULL;
	char *fname = NULL;
	int32_t i = 0;
	int32_t j = 0;

	int32_t option = 0;
	while ( ( option = getopt( argc, argv, "i:e" ) ) != -1 )
	{
		switch( option )
		{
			case 'i':
				purpose += 1;
				fname = (char *)calloc( strlen(optarg)+1 , sizeof(char) );
				for( i = 0 ; i < strlen(optarg) ; i++ )
				{
					fname[i] = optarg[i];
				}
				fname[strlen(optarg)] = 0;
				break;
			case 'e':
				purpose += 2;
				break;
			default:
				printf( "Unknown option.\n" ); 
				break;
		}
	}

	if( purpose == 3 )
	{
		printf( "Invalid input.\n" );
		return 0;
	}

	i = 0;
	j = 0;
	if( purpose == 1 )
	{
		bmpname = (char *)calloc( strlen(argv[3])+1 , sizeof(char) );
		for( i = 0 ; i < strlen(argv[3]) ; i++ )
		{
			bmpname[i] = *(argv[3]+i);
		}
	}
	else
	{
		bmpname = (char *)calloc( strlen(argv[2])+1 , sizeof(char) );
		for( i = 0 ; i < strlen(argv[2]) ; i++ )
		{
			bmpname[i] = *(argv[2]+i);
		}
	}

	if( ( purpose == 1 && (fname == NULL || fname[strlen(fname)-1] != 'f' || fname[strlen(fname)-2] != 'd' || fname[strlen(fname)-3] != 'p') ) || bmpname == NULL || bmpname[strlen(bmpname)-1] != 'p' || bmpname[strlen(bmpname)-2] != 'm' || bmpname[strlen(bmpname)-3] != 'b' )
	{
		if( fname )
		{
			free( fname );
		}
		if( bmpname )
		{
			free( bmpname );
		}
		printf( "Invalid input.\n" );
		return 0;
	}

	FILE *pF = NULL;
	FILE *pB = NULL;

	if( purpose == 1 )
	{
		pF = fopen( fname , "r" );
		if( pF == NULL )
		{
			free( fname );
			free( bmpname );
			printf( "PDF file could not be opened.\n" );
			return 0;
		}
	}
	pB = fopen( bmpname , "r+" );
	if( pB == NULL )
	{
		if( pF )
		{
			free( fname );
			fclose( pF );
		}
		free( bmpname );
		printf( "BMP file could not be opened.\n" );
		return 0;
	}

	BmpHeader header;
	header_init( &header );
	int32_t count = 0;
	count = fread( &header , sizeof(header) , 1 , pB );

	if( header_check(&header) == -1 )
	{
		printf( "Invalid BMP file.\n" );
		return 0;
	}

	int8_t buf[1024] = {0};
	int32_t size = 0;
	if( purpose == 1 )
	{
		fseek( pB , 0 , SEEK_END );
		size = strlen( fname );
		//printf( "filename size = %d\n" , size );
		fwrite( &size , 4 , 1 , pB );
		fseek( pF , 0 , SEEK_END );
		size = ftell( pF );
		//printf( "filesize = %d\n" , size );
		fwrite( &size , 4 , 1 , pB );
		fwrite( fname , 1 , strlen(fname) , pB );
		fseek( pF , 0 , SEEK_SET );
		//printf( "%d : " , strlen(fname) );
		//puts( fname );
		while( !feof(pF) )
		{
			count = fread( &buf[0] , 1 , 1024 , pF );
			fwrite( &buf[0] , 1 , count , pB );
		}
	}
	else
	{
		fseek( pB , header.size+1 , SEEK_SET );
		//printf( "bmpsize = %d\n" , header.size );
		while( !feof(pB) )
		{
			//printf( "b\n" );
			fseek( pB , -1 , SEEK_CUR );
			//printf( "start file header = %ld\n" , ftell( pB ) );
			count = fread( &size , 4 , 1 , pB );
			//printf( "%d\n" , size );
			int32_t fsize = 0;
			count = fread( &fsize , 4 , 1 , pB );
			//printf( "filesize = %d\n" , fsize );
			while( size > 0 )
			{
				count = fread( &buf[0] , 1 , 1024 , pB );
				size -= count;
				if( size < 0 )
				{
					fseek( pB , size , SEEK_CUR );
				}
				buf[count] = 0;
			}
			//puts( &buf[0] );
			//printf( "start file content = %ld\n" , ftell( pB ) );
			while( fsize > 0 )
			{
				count = fread( &buf[0] , 1 , 1024 , pB );
				for( i = 0 ; i < count ; i++ )
				{
					printf( "%c" , buf[i] );
					fsize--;
					if( fsize == 0 )
					{
						fseek( pB , i-count+2 , SEEK_CUR );
						//printf( "pos = %ld\n" , ftell( pB ) );
						break;
					}
				}
				//printf( "c\n" );
			}
		}
	}

	if( pF )
	{
		free( fname );
		fclose( pF );
	}
	free( bmpname );
	fclose( pB );
	
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

int8_t header_check( BmpHeader *in )
{
	if( in->bm[0] != 'B' || in->bm[1] != 'M' )
	{
		return -1;
	}
	else if( in->size <= 0 || in->offset < 0 || in->header_size <= 0 )
	{
		return -1;
	}
	else if( in->planes != 1 )
	{
		return -1;
	}
	else if( in->bpp <= 0 )
	{
		return -1;
	}
	else if( in->compression < 0 || in->compression > 6 || (in->compression == 1 && in->bpp != 8) || (in->compression == 2 && in->bpp != 4) )
	{
		return -1;
	}
	else if( in->bitmap_size <= 0 || in->bitmap_size > in->size )
	{
		return -1;
	}
	return 0;
}
