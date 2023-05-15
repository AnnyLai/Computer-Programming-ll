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
  	fp = fopen( &filename[0] , "rb+" );
  	if( fp == NULL )
  	{
    		printf( "Can't open file.\n" );
    		return -1;
  	}
	
  	int32_t choice = 0;
  	uint8_t origin[2] = {0};
  	int32_t val = 0;
  	uint8_t changed[2] = {0};
  	int64_t set = 0;
  	int8_t count = 0;

	while( 1 )
	{
  		printf( "What do you want to change?\n" );
  		printf( " 1. Level                         2. Experience\n" );
  		printf( " 3. Health Point                  4. Max value of Health Point\n" );
  		printf( " 5. Internal Force                6. Max value of Internal Force\n" );
  		printf( " 7. Physical Strength             8. Qing Gong\n" );
  		printf( " 9. Attack                       10. Defence\n" );
  		printf( "11. Martial Arts                 12. Medical Treatment\n" );
  		printf( "13. Poison                       14. Detoxification\n" );
  		printf( "15. Fly with Sword               16. Use Knife\n" );
  		printf( "17. Concealed Weapon             18. Special Weapon\n" );
  		printf( "19. Weapon Equipment             20. Defending Equipment\n" );
  		printf( "21. Xiu Lian items               22. Learnt Kung Fu\n" );
  		printf( " 0.Quit.\n" );
  		scanf( "%d" , &choice );
  		if( choice == 0 )
  		{
  			   break;
  		}

  		origin[0] = 0;
  		origin[1] = 0;
  		val = 0;
  		changed[0] = 0;
  		changed[1] = 0;
  		set = 0;
  		count = 0;
  		if( choice == 1 )
  		{
    			set = 866;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 1 , fp );
    			printf( "Level:\nRecent value = %hhu\n" , origin[0] );
    			printf( "What value do to want to modify to?(1 ~ 30) " );
    			scanf( "%d" , &val );
    			if( val > 30 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)val;
    			fseek( fp , -1 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 1 , fp );
  		}
  		else if( choice == 2 )
  		{
    			set = 868;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Experience:\nRecent value = %hu\n" , (uint16_t)((uint8_t)origin[0]+(uint8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 60000) " );
    			scanf( "%d" , &val );
    			if( val > 60000 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (uint8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
  		else if( choice == 3 )
  		{
    			set = 870;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Health Point:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			uint8_t max[2] = {0};
    			count = fread( &max[0] , 1 , 2 , fp );
    			printf( "What value do to want to modify to?(0 ~ %hd) " , (int16_t)((uint8_t)max[0]+(int8_t)max[1]*256) );
    			scanf( "%d" , &val );
    			if( val > ((uint8_t)max[0]+max[1]*256) || val < 0 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -4 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
  		else if( choice == 4 )
  		{
    			set = 872;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Max value of Health Point:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 999) " );
    			scanf( "%d" , &val );
    			if( val > 999 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
  		else if( choice == 5 )
  		{
    			set = 918;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Internal Force:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
          uint8_t max[2] = {0};
    			count = fread( &max[0] , 1 , 2 , fp );
    			printf( "What value do to want to modify to?(0 ~ %hd) " , (int16_t)((uint8_t)max[0]+(int8_t)max[1]*256) );
    			scanf( "%d" , &val );
    			if( val > ((uint8_t)max[0]+max[1]*256) || val < 0 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -4 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 6 )
      {
          set = 920;
          fseek( fp , set , SEEK_SET );
          count = fread( &origin[0] , 1 , 2 , fp );
          printf( "Max value of Internal Force:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
          printf( "What value do to want to modify to?(1 ~ 999) " );
          scanf( "%d" , &val );
          if( val > 999 || val < 1 )
          {
              printf( "Invalid value.\n\n" );
              continue;
          }
          changed[0] = (uint8_t)(val % 256);
          changed[1] = (int8_t)(val / 256);
          fseek( fp , -2 , SEEK_CUR );
          fwrite( &changed[0] , 1 , 2 , fp );
      }
    	else if( choice == 7 )
  		{
    			set = 878;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 1 , fp );
    			printf( "Physical Strength:\nRecent value = %hhu\n" , origin[0] );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)val;
    			fseek( fp , -1 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 1 , fp );
  		}
    	else if( choice == 8 )
  		{
    			set = 924;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Qing Gong:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 9 )
  		{
    			set = 922;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Attack:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 10 )
  		{
    			set = 926;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Defence:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 11 )
  		{
    			set = 936;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Martial Arts:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 12 )
  		{
    			set = 928;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Medical Treatment:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 13 )
  		{
    			set = 930;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Poison:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 14 )
  		{
    			set = 932;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Detoxification:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 15 )
  		{
    			set = 938;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Fly with Sword:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 16 )
  		{
    			set = 940;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Use Knife:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 17 )
  		{
    			set = 944;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Concealed Weapon:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 18 )
  		{
    			set = 942;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Special Weapon:\nRecent value = %hd\n" , (int16_t)((uint8_t)origin[0]+(int8_t)origin[1]*256) );
    			printf( "What value do to want to modify to?(1 ~ 100) " );
    			scanf( "%d" , &val );
    			if( val > 100 || val < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 19 )
  		{
  		    set = 882;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Weapon Equipment: " );
    			if( origin[0] == 106 && origin[1] == 0 )
    			{
    				  printf( "Xuan Tie Jian\n" );
    			}
    			else if( origin[0] == 107 && origin[1] == 0 )
    			{
    				  printf( "Jun Zi Jian\n" );
    			}
    			else if( origin[0] == 108 && origin[1] == 0 )
    			{
    				  printf( "Shu Nu Jian\n" );
    			}
    			else if( origin[0] == 109 && origin[1] == 0 )
    			{
    				  printf( "Yi Tian Jian\n" );
    			}
    			else if( origin[0] == 110 && origin[1] == 0 )
    			{
    				  printf( "Jin She Jian\n" );
    			}
    			else if( origin[0] == 111 && origin[1] == 0 )
    			{
    				  printf( "Ning Bi Jian\n" );
    			}
    			else if( origin[0] == 112 && origin[1] == 0 )
    			{
    				  printf( "Bai Long Jian\n" );
    			}
    			else if( origin[0] == 113 && origin[1] == 0 )
    			{
    				  printf( "Bai Hong Jian\n" );
    			}
    			else if( origin[0] == 114 && origin[1] == 0 )
    			{
    				  printf( "Zhou Gong Jian\n" );
    			}
    			else if( origin[0] == 115 && origin[1] == 0 )
    			{
    				  printf( "Xie Dao\n" );
    			}
    			else if( origin[0] == 116 && origin[1] == 0 )
    			{
    				  printf( "Leng Yue Bao Dao\n" );
    			}
    			else if( origin[0] == 117 && origin[1] == 0 )
    			{
    				  printf( "Tu Long Dao\n" );
    			}
    			else if( origin[0] == 118 && origin[1] == 0 )
    			{
    				  printf( "Lu Bo Xiang Lu Dao\n" );
    			}
    			else if( origin[0] == 119 && origin[1] == 0 )
    			{
    				  printf( "Pi Li Kuang Dao\n" );
    			}
    			else if( origin[0] == 192 && origin[1] == 0 )
    			{
    				  printf( "Zhen Wu Jian\n" );
    			}
    			else
    			{
    				  printf( "None.\n" );
    			}
    
    			val = (int32_t)getchar();
    			printf( "What weapon do to want to modify to? Please type it in with Pin Yin. " );
    			char buf[30] = {0};
    			fgets( &buf[0] , 30 , stdin );
    			if( strstr( &buf[0] , "Xuan Tie Jian" ) )
    			{
    				  val = 106;
    			}
    			else if( strstr( &buf[0] , "Jun Zi Jian" ) )
    			{
    				  val = 107;
    			}
    			else if( strstr( &buf[0] , "Shu Nu Jian" ) )
    			{
    				  val = 108;
    			}
    			else if( strstr( &buf[0] , "Yi Tian Jian" ) )
    			{
    				  val = 109;
    			}
    			else if( strstr( &buf[0] , "Jin She Jian" ) )
    			{
    				  val = 110;
    			}
    			else if( strstr( &buf[0] , "Ning Bi Jian" ) )
    			{
    				  val = 111;
    			}
    			else if( strstr( &buf[0] , "Bai Long Jian" ) )
    			{
    				  val = 112;
    			}
    			else if( strstr( &buf[0] , "Bai Hong Jian" ) )
    			{
    				  val = 113;
    			}
    			else if( strstr( &buf[0] , "Zhou Gong Jian" ) )
    			{
    				  val = 114;
    			}
    			else if( strstr( &buf[0] , "Xie Dao" ) )
    			{
    				  val = 115;
    			}
    			else if( strstr( &buf[0] , "Leng Yue Bao Dao" ) )
    			{
    				  val = 116;
    			}
    			else if( strstr( &buf[0] , "Tu Long Dao" ) )
    			{
    				  val = 117;
    			}
    			else if( strstr( &buf[0] , "Lu Bo Xiang Lu Dao" ) )
    			{
    				  val = 118;
    			}
    			else if( strstr( &buf[0] , "Pi Li Kuang Dao" ) )
    			{
    				  val = 119;
    			}
    			else if( strstr( &buf[0] , "Zhen Wu Jian" ) )
    			{
    				  val = 192;
    			}
    			else
    			{
    				  printf( "Not a available weapon.\n\n" );
    				  continue;
    			}
    			
    			changed[0] = (uint8_t)val;
    			changed[1] = 0;
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 20 )
  		{
  		    set = 884;
    			fseek( fp , set , SEEK_SET );
    			count = fread( &origin[0] , 1 , 2 , fp );
    			printf( "Defending Equipment: " );
    			if( origin[0] == 120 && origin[1] == 0 )
    			{
    				  printf( "Ruan Wei Jia\n" );
    			}
    			else if( origin[0] == 121 && origin[1] == 0 )
    			{
    				  printf( "Jin Si Bei Xin\n" );
    			}
    			else if( origin[0] == 122 && origin[1] == 0 )
    			{
    				  printf( "Wu Can Yi\n" );
    			}
    			else if( origin[0] == 123 && origin[1] == 0 )
    			{
    				  printf( "E Yu Pi Jia\n" );
    			}
    			else if( origin[0] == 197 && origin[1] == 0 )
    			{
    				  printf( "Pi Yi\n" );
    			}
    			else
    			{
    				  printf( "None.\n" );
    			}
    
    			val = (int32_t)getchar();
    			printf( "What defending equipment do to want to modify to? Please type it in with Pin Yin. " );
    			char buf[30] = {0};
    			fgets( &buf[0] , 30 , stdin );
    			if( strstr( &buf[0] , "Ruan Wei Jia" ) )
    			{
    				  val = 120;
    			}
    			else if( strstr( &buf[0] , "Jin Si Bei Xin" ) )
    			{
    				  val = 121;
    			}
    			else if( strstr( &buf[0] , "Wu Can Yi" ) )
    			{
    				  val = 122;
    			}
    			else if( strstr( &buf[0] , "E Yu Pi Jia" ) )
    			{
    				  val = 123;
    			}
    			else if( strstr( &buf[0] , "Pi Yi" ) )
    			{
    				  val = 197;
    			}
    			else
    			{
      				printf( "Not a available depending equipment.\n\n" );
      				continue;
    			}
    			
    			changed[0] = (uint8_t)val;
    			changed[1] = 0;
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    	else if( choice == 21 )///////////////////////////////////////////////////
      {
          set = 882;
          fseek( fp , set , SEEK_SET );
          count = fread( &origin[0] , 1 , 2 , fp );
          printf( "Weapon Equipment:\nRecent value = %hu\n" , (uint16_t)((uint8_t)origin[0]+(uint8_t)origin[1]*256) );
          printf( "What value do to want to modify to?(1 ~ 65535) " );
          scanf( "%d" , &val );
          if( val > 65535 || val < 1 )
          {
              printf( "Invalid value.\n\n" );
              continue;
          }
          changed[0] = (uint8_t)(val % 256);
          changed[1] = (uint8_t)(val / 256);
          fseek( fp , -2 , SEEK_CUR );
          fwrite( &changed[0] , 1 , 2 , fp );
      }
    	else if( choice == 22 )
  		{
    			printf( "Learnt KungFu:\n" );
    			for( size_t i = 0 ; i < 20 ; i+=2 )
    			{
      				printf( "%lu." , i/2+1 );
      				set = 962 + i;
      				fseek( fp , set , SEEK_SET );
      				count = fread( &origin[0] , 1 , 1 , fp );
      				switch( origin[0] )
      				{
        					case 1:
          						printf( "Ye Qiu Quan   " );
          						break;
        					case 2:
          						printf( "Wu Dang Chang Quan   " );
          						break;
        					case 3:
          						printf( "Luo Han Quan   " );
          						break;
        					case 4:
          						printf( "Ling She Quan   " );
          						break;
        					case 5:
          						printf( "Sheng Wang Du Zhang   " );
          						break;
        					case 6:
          						printf( "Qi Shang Quan   " );
          						break;
        					case 7:
          						printf( "Hun Yuan Quan   " );
          						break;
        					case 8:
          						printf( "Han Bing Mian Zhang   " );
          						break;
        					case 9:
          						printf( "Ying Zhua Gong   " );
          						break;
        					case 10:
          						printf( "Xiao Yao Zhang   " );
          						break;
        					case 11:
          						printf( "Tie Zhang   " );
          						break;
        					case 12:
          						printf( "Huan Yin Zhi   " );
          						break;
        					case 13:
          						printf( "Han Bing Shen Zhang   " );
          						break;
        					case 14:
          						printf( "Qian Sho Ru Lai Zhang   " );
          						break;
        					case 15:
          						printf( "Tian Shan Liu Yang Zhang   " );
          						break;
        					case 16:
          						printf( "Xuan Ming Shen Zhang   " );
          						break;
        					case 17:
          						printf( "Bing Can Du Zhang   " );
          						break;
        					case 18:
          						printf( "Long Xiang Bo Ruo Gong   " );
          						break;
        					case 19:
          						printf( "Yi Yang Zhi   " );
          						break;
        					case 20:
          						printf( "Tai Ji Quan   " );
          						break;
        					case 21:
          						printf( "Kong Ming Quan   " );
          						break;
        					case 22:
          						printf( "Ha Ma Gong   " );
          						break;
        					case 23:
          						printf( "Tai Xuan Shen Gong   " );
          						break;
        					case 24:
          						printf( "An Ran Xiao Hun Zhang   " );
          						break;
        					case 25:
          						printf( "Xiang Long Shi Ba Zhang   " );
          						break;
        					case 26:
          						printf( "Kui Hua Shen Gong   " );
          						break;
        					case 27:
          						printf( "Hua Gong Da Fa   " );
          						break;
        					case 28:
          						printf( "Xi Xing Da Fa   " );
          						break;
        					case 29:
          						printf( "Bei Ming Shen Gong   " );
          						break;
        					case 30:
          						printf( "Liu Mai Shen Jian   " );
          						break;
        					case 31:
          						printf( "Tang Shi Jian Fa   " );
          						break;
        					case 32:
          						printf( "Qing Cheng Jian Fa   " );
          						break;
        					case 33:
          						printf( "Bing Xue Jian Fa   " );
          						break;
        					case 34:
          						printf( "Heng Shan Jian Fa   " );
          						break;
        					case 35:
          						printf( "Tai Shan Jian Fa   " );
          						break;
        					case 36:
          						printf( "Heng Shan Jian Fa   " );
          						break;
        					case 37:
          						printf( "Shen Long Jian Fa   " );
          						break;
        					case 38:
          						printf( "Song Shan Jian Fa   " );
          						break;
        					case 39:
          						printf( "Quan Zhen Jian Fa   " );
          						break;
        					case 40:
          						printf( "E Mei Jian Fa   " );
          						break;
        					case 41:
          						printf( "Wu Zhang Jian Fa   " );
          						break;
        					case 42:
          						printf( "Wan Hua Jian Fa   " );
          						break;
        					case 43:
          						printf( "Po Mo Jian Fa   " );
          						break;
        					case 44:
          						printf( "Xue Shan Jian Fa   " );
          						break;
        					case 45:
          						printf( "Tai Shan Shi Ba Pan   " );
          						break;
        					case 46:
          						printf( "Hui Feng Luo Yan Jian   " );
          						break;
        					case 47:
          						printf( "Liang Yi Jian Fa   " );
          						break;
        					case 48:
          						printf( "Tai Yue San Qing Feng   " );
          						break;
        					case 49:
          						printf( "Yu Nu Su Xin Jian   " );
          						break;
        					case 50:
          						printf( "Xiao Yao Jian Fa   " );
          						break;
        					case 51:
          						printf( "Mu Rong Jian Fa   " );
          						break;
        					case 52:
          						printf( "Yi Tian Jian Fa   " );
          						break;
        					case 53:
          						printf( "Qi Xing Jian Fa   " );
          						break;
        					case 54:
          						printf( "Jin She Jian Fa   " );
          						break;
        					case 55:
          						printf( "Miao Jia Jian Fa   " );
          						break;
        					case 56:
          						printf( "Yu Xiao Jian Fa   " );
          						break;
        					case 57:
          						printf( "Xuan Tie Jian Fa   " );
          						break;
        					case 58:
          						printf( "Tai Ji Jian Fa   " );
          						break;
        					case 59:
          						printf( "Da Mo Jian Fa   " );
          						break;
        					case 60:
          						printf( "Pi Xie Jian Fa   " );
          						break;
        					case 61:
          						printf( "Du Gu Jiu Jian   " );
          						break;
        					case 62:
          						printf( "Xi Gua Dao Fa   " );
          						break;
        					case 63:
          						printf( "Xie Dao Da Fa   " );
          						break;
        					case 64:
          						printf( "Kuang Feng Dao Fa   " );
          						break;
        					case 65:
          						printf( "Fan Liang Yi Dao Fa   " );
          						break;
        					case 66:
          						printf( "Huo Yan Dao Fa   " );
          						break;
        					case 67:
          						printf( "Hu Jia Dao Fa   " );
          						break;
        					case 68:
          						printf( "Pi Li Dao Fa   " );
          						break;
        					case 69:
          						printf( "Shen Long Shuang Gou   " );
          						break;
        					case 70:
          						printf( "Da Lun Zhang Fa   " );
          						break;
        					case 71:
          						printf( "Guai Yi Wu Qi   " );
          						break;
        					case 72:
          						printf( "Lian Xin Dan   " );
          						break;
        					case 73:
          						printf( "Jiao Hua Gun Fa   " );
          						break;
        					case 74:
          						printf( "Huo Yan Fa She Qi   " );
          						break;
        					case 75:
          						printf( "E Yu   " );
          						break;
        					case 76:
          						printf( "Da Zhi Zhu   " );
          						break;
        					case 77:
          						printf( "Du Long Bian Fa   " );
          						break;
        					case 78:
          						printf( "Huang Sha Wan Li Bian   " );
          						break;
        					case 79:
          						printf( "Xue Guai   " );
          						break;
        					case 80:
          						printf( "Pan Guan Bi   " );
          						break;
        					case 81:
          						printf( "Chi Qi Pan   " );
          						break;
        					case 82:
          						printf( "Da Jian Dao   " );
          						break;
        					case 83:
          						printf( "Chi Yao Qin   " );
          						break;
        					case 84:
          						printf( "Da Mang She   " );
          						break;
        					case 85:
          						printf( "Jin Hua Zhang Fa   " );
          						break;
        					case 86:
          						printf( "Shen Long Lu Zhang   " );
          						break;
        					case 87:
          						printf( "Da Ju Gun Fa   " );
          						break;
        					case 88:
          						printf( "Wu Lun Da Fa   " );
          						break;
        					case 89:
          						printf( "Song Feng Jian Fa   " );
          						break;
        					case 90:
          						printf( "Pu Tong Gong Ji   " );
          						break;
        					case 91:
          						printf( "Shi Zi Hou   " );
          						break;
        					case 92:
          						printf( "Jiu Yang Shen Gong   " );
          						break;
        					default:
          						printf( "None.\n" );
          						break;
      				}
      
      				if( origin[0] != 0 )
      				{
        					set = 982 + i;
        					fseek( fp , set , SEEK_SET );
        					count = fread( &origin[0] , 1 , 2 , fp );
        					val = (uint8_t)origin[0] + (int8_t)origin[1] * 256;
        					printf( "%d\n" , val / 100 + 1 );
      				}
    			}
    			
    			int32_t tar = 0;
    			printf( "Which Kung Fu do to want to modify?(1 ~ 10) " );
    			scanf( "%d" , &tar );
    			if( tar > 10 || tar < 1 )
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    			
    			printf( "Do you want to change a kind of Kung Fu(1) or just modify the level(2)? " );
    			scanf( "%d" , &val );
    			if( val == 1 )
    			{
      				set = 962 + (tar-1) * 2;
      				fseek( fp , set , SEEK_SET );
      				val = (int32_t)getchar();
      				printf( "What Kung Fu do you want to change to? Please type it in with Pin Yin. " );
      				char buf[30] = {0};
      				fgets( &buf[0] , 30 , stdin );
      
      				if( strstr( &buf[0] , "Ye Qiu Quan" ) )
      				{
        					changed[0] = 1;
      				}
      				else if( strstr( &buf[0] , "Wu Dang Chang Quan" ) )
      				{
        					changed[0] = 2;
      				}
      				else if( strstr( &buf[0] , "Luo Han Quan" ) )
      				{
        					changed[0] = 3;
      				}
      				else if( strstr( &buf[0] , "Ling She Quan" ) )
      				{
      					changed[0] = 4;
      				}
      				else if( strstr( &buf[0] , "Sheng Wang Du Zhang" ) )
      				{
        					changed[0] = 5;
      				}
      				else if( strstr( &buf[0] , "Qi Shang Quan" ) )
      				{
        					changed[0] = 6;
      				}
      				else if( strstr( &buf[0] , "Hun Yuan Quan" ) )
      				{
        					changed[0] = 7;
      				}
      				else if( strstr( &buf[0] , "Han Bing Mian Zhang" ) )
      				{
        					changed[0] = 8;
      				}
      				else if( strstr( &buf[0] , "Ying Zhua Gong" ) )
      				{
        					changed[0] = 9;
      				}
      				else if( strstr( &buf[0] , "Xiao Yao Zhang" ) )
      				{
        					changed[0] = 10;
      				}
      				else if( strstr( &buf[0] , "Tie Zhang" ) )
      				{
        					changed[0] = 11;
      				}
      				else if( strstr( &buf[0] , "Huan Yin Zhi" ) )
      				{
        					changed[0] = 12;
      				}
      				else if( strstr( &buf[0] , "Han Bing Shen Zhang" ) )
      				{
        					changed[0] = 13;
      				}
      				else if( strstr( &buf[0] , "Qian Sho Ru Lai Zhang" ) )
      				{
        					changed[0] = 14;
      				}
      				else if( strstr( &buf[0] , "Tian Shan Liu Yang Zhang" ) )
      				{
        					changed[0] = 15;
      				}
      				else if( strstr( &buf[0] , "Xuan Ming Shen Zhang" ) )
      				{
        					changed[0] = 16;
      				}
      				else if( strstr( &buf[0] , "Bing Can Du Zhang" ) )
      				{
        					changed[0] = 17;
      				}
      				else if( strstr( &buf[0] , "Long Xiang Bo Ruo Gong" ) )
      				{
        					changed[0] = 18;
      				}
      				else if( strstr( &buf[0] , "Yi Yang Zhi" ) )
      				{
        					changed[0] = 19;
      				}
      				else if( strstr( &buf[0] , "Tai Ji Quan" ) )
      				{
        					changed[0] = 20;
      				}
      				else if( strstr( &buf[0] , "Kong Ming Quan" ) )
      				{
        					changed[0] = 21;
      				}
      				else if( strstr( &buf[0] , "Ha Ma Gong" ) )
      				{
        					changed[0] = 22;
      				}
      				else if( strstr( &buf[0] , "Tai Xuan Shen Gong" ) )
      				{
        					changed[0] = 23;
      				}
      				else if( strstr( &buf[0] , "An Ran Xiao Hun Zhang" ) )
      				{
        					changed[0] = 24;
      				}
      				else if( strstr( &buf[0] , "Xiang Long Shi Ba Zhang" ) )
      				{
        					changed[0] = 25;
      				}
      				else if( strstr( &buf[0] , "Kui Hua Shen Gong" ) )
      				{
        					changed[0] = 26;
      				}
      				else if( strstr( &buf[0] , "Hua Gong Da Fa" ) )
      				{
        					changed[0] = 27;
      				}
      				else if( strstr( &buf[0] , "Xi Xing Da Fa" ) )
      				{
        					changed[0] = 28;
      				}
      				else if( strstr( &buf[0] , "Bei Ming Shen Gong" ) )
      				{
        					changed[0] = 29;
      				}
      				else if( strstr( &buf[0] , "Liu Mai Shen Jian" ) )
      				{
        					changed[0] = 30;
      				}
      				else if( strstr( &buf[0] , "Tang Shi Jian Fa" ) )
      				{
        					changed[0] = 31;
      				}
      				else if( strstr( &buf[0] , "Qing Cheng Jian Fa" ) )
      				{
        					changed[0] = 32;
      				}
      				else if( strstr( &buf[0] , "Bing Xue Jian Fa" ) )
      				{
        					changed[0] = 33;
      				}
      				else if( strstr( &buf[0] , "Heng Shan Jian Fa" ) )
      				{
        					changed[0] = 34;
      				}
      				else if( strstr( &buf[0] , "Tai Shan Jian Fa" ) )
      				{
        					changed[0] = 35;
      				}
      				else if( strstr( &buf[0] , "Heng Shan Jian Fa" ) )
      				{
        					changed[0] = 36;
      				}
      				else if( strstr( &buf[0] , "Shen Long Jian Fa" ) )
      				{
        					changed[0] = 37;
      				}
      				else if( strstr( &buf[0] , "Song Shan Jian Fa" ) )
      				{
        					changed[0] = 38;
      				}
      				else if( strstr( &buf[0] , "Quan Zhen Jian Fa" ) )
      				{
        					changed[0] = 39;
      				}
      				else if( strstr( &buf[0] , "E Mei Jian Fa" ) )
      				{
        					changed[0] = 40;
      				}
      				else if( strstr( &buf[0] , "Wu Zhang Jian Fa" ) )
      				{
        					changed[0] = 41;
      				}
      				else if( strstr( &buf[0] , "Wan Hua Jian Fa" ) )
      				{
        					changed[0] = 42;
      				}
      				else if( strstr( &buf[0] , "Po Mo Jian Fa" ) )
      				{
        					changed[0] = 43;
      				}
      				else if( strstr( &buf[0] , "Xue Shan Jian Fa" ) )
      				{
        					changed[0] = 44;
      				}
      				else if( strstr( &buf[0] , "Tai Shan Shi Ba Pan" ) )
      				{
        					changed[0] = 45;
      				}
      				else if( strstr( &buf[0] , "Hui Feng Luo Yan Jian" ) )
      				{
        					changed[0] = 46;
      				}
      				else if( strstr( &buf[0] , "Liang Yi Jian Fa" ) )
      				{
        					changed[0] = 47;
      				}
      				else if( strstr( &buf[0] , "Tai Yue San Qing Feng" ) )
      				{
        					changed[0] = 48;
      				}
      				else if( strstr( &buf[0] , "Yu Nu Su Xin Jian" ) )
      				{
        					changed[0] = 49;
      				}
      				else if( strstr( &buf[0] , "Xiao Yao Jian Fa" ) )
      				{
        					changed[0] = 50;
      				}
      				else if( strstr( &buf[0] , "Mu Rong Jian Fa" ) )
      				{
        					changed[0] = 51;
      				}
      				else if( strstr( &buf[0] , "Yi Tian Jian Fa" ) )
      				{
        					changed[0] = 52;
      				}
      				else if( strstr( &buf[0] , "Qi Xing Jian Fa" ) )
      				{
        					changed[0] = 53;
      				}
      				else if( strstr( &buf[0] , "Jin She Jian Fa" ) )
      				{
        					changed[0] = 54;
      				}
      				else if( strstr( &buf[0] , "Miao Jia Jian Fa" ) )
      				{
        					changed[0] = 55;
      				}
      				else if( strstr( &buf[0] , "Yu Xiao Jian Fa" ) )
      				{
        					changed[0] = 56;
      				}
      				else if( strstr( &buf[0] , "Xuan Tie Jian Fa" ) )
      				{
        					changed[0] = 57;
      				}
      				else if( strstr( &buf[0] , "Tai Ji Jian Fa" ) )
      				{
        					changed[0] = 58;
      				}
      				else if( strstr( &buf[0] , "Da Mo Jian Fa" ) )
      				{
        					changed[0] = 59;
      				}
      				else if( strstr( &buf[0] , "Pi Xie Jian Fa" ) )
      				{
        					changed[0] = 60;
      				}
      				else if( strstr( &buf[0] , "Du Gu Jiu Jian" ) )
      				{
        					changed[0] = 61;
      				}
      				else if( strstr( &buf[0] , "Xi Gua Dao Fa" ) )
      				{
        					changed[0] = 62;
      				}
      				else if( strstr( &buf[0] , "Xie Dao Da Fa" ) )
      				{
        					changed[0] = 63;
      				}
      				else if( strstr( &buf[0] , "Kuang Feng Dao Fa" ) )
      				{
        					changed[0] = 64;
      				}
      				else if( strstr( &buf[0] , "Fan Liang Yi Dao Fa" ) )
      				{
        					changed[0] = 65;
      				}
      				else if( strstr( &buf[0] , "Huo Yan Dao Fa" ) )
      				{
        					changed[0] = 66;
      				}
      				else if( strstr( &buf[0] , "Hu Jia Dao Fa" ) )
      				{
        					changed[0] = 67;
      				}
      				else if( strstr( &buf[0] , "Pi Li Dao Fa" ) )
      				{
        					changed[0] = 68;
      				}
      				else if( strstr( &buf[0] , "Shen Long Shuang Gou" ) )
      				{
        					changed[0] = 69;
      				}
      				else if( strstr( &buf[0] , "Da Lun Zhang Fa" ) )
      				{
        					changed[0] = 70;
      				}
      				else if( strstr( &buf[0] , "Guai Yi Wu Qi" ) )
      				{
        					changed[0] = 71;
      				}
      				else if( strstr( &buf[0] , "Lian Xin Dan" ) )
      				{
        					changed[0] = 72;
      				}
      				else if( strstr( &buf[0] , "Jiao Hua Gun Fa" ) )
      				{
        					changed[0] = 73;
      				}
      				else if( strstr( &buf[0] , "Huo Yan Fa She Qi" ) )
      				{
        					changed[0] = 74;
      				}
      				else if( strstr( &buf[0] , "E Yu" ) )
      				{
        					changed[0] = 75;
      				}
      				else if( strstr( &buf[0] , "Da Zhi Zhu" ) )
      				{
        					changed[0] = 76;
      				}
      				else if( strstr( &buf[0] , "Du Long Bian Fa" ) )
      				{
        					changed[0] = 77;
      				}
      				else if( strstr( &buf[0] , "Huang Sha Wan Li Bian" ) )
      				{
        					changed[0] = 78;
      				}
      				else if( strstr( &buf[0] , "Xue Guai" ) )
      				{
        					changed[0] = 79;
      				}
      				else if( strstr( &buf[0] , "Pan Guan Bi" ) )
      				{
        					changed[0] = 80;
      				}
      				else if( strstr( &buf[0] , "Chi Qi Pan" ) )
      				{
        					changed[0] = 81;
      				}
      				else if( strstr( &buf[0] , "Da Jian Dao" ) )
      				{
        					changed[0] = 82;
      				}
      				else if( strstr( &buf[0] , "Chi Yao Qin" ) )
      				{
        					changed[0] = 83;
      				}
      				else if( strstr( &buf[0] , "Da Mang She" ) )
      				{
        					changed[0] = 84;
      				}
      				else if( strstr( &buf[0] , "Jin Hua Zhang Fa" ) )
      				{
        					changed[0] = 85;
      				}
      				else if( strstr( &buf[0] , "Shen Long Lu Zhang" ) )
      				{
      				    changed[0] = 86;
      				}
      				else if( strstr( &buf[0] , "Da Ju Gun Fa" ) )
      				{
      				    changed[0] = 87;
      				}
      				else if( strstr( &buf[0] , "Wu Lun Da Fa" ) )
      				{
      				    changed[0] = 88;
      				}
      				else if( strstr( &buf[0] , "Song Feng Jian Fa" ) )
      				{
      				    changed[0] = 89;
      				}
      				else if( strstr( &buf[0] , "Pu Tong Gong Ji" ) )
      				{
        					changed[0] = 90;
      				}
      				else if( strstr( &buf[0] , "Shi Zi Hou" ) )
      				{
      				    changed[0] = 91;
      				}
      				else if( strstr( &buf[0] , "Jiu Yang Shen Gong" ) )
      				{
      				    changed[0] = 92;
      				}
      				else
      				{
        					printf( "Invalid Kung Fu.\n\n" );
        					continue;
      				}
      
      				fwrite( &changed[0] , 1 , 1 , fp );
      
      				set = 982 + (tar-1) * 2;
      				fseek( fp , set , SEEK_SET );
    			}
    			else if( val == 2 )
    			{
      				set = 962 + (tar-1) * 2;
      				fseek( fp , set , SEEK_SET );
      				count = fread( &origin[0] , 1 , 1 , fp );
      				if( origin[0] == 0 )
      				{
        					printf( "There is no Kung Fu.\n\n" );
        					continue;
      				}
      				set = 982 + (tar-1) * 2;
      				fseek( fp , set , SEEK_SET );
      				count = fread( &origin[0] , 1 , 2 , fp );
      
      				val = (uint8_t)origin[0] + (int8_t)origin[1] * 256;
      				printf( "Recent level = %d\n" , val/100+1 );
    			}
    			else
    			{
      				printf( "Invalid value.\n\n" );
      				continue;
    			}
    
    			printf( "What level do you want to modify to? " );
    			scanf( "%d" , &val );
    			printf( "What percentage do you want to modify to?(0 ~ 99) " );
    			scanf( "%hhd" , &changed[0] );
    			val = (val-1) * 100 + changed[0];
    			changed[0] = (uint8_t)(val % 256);
    			changed[1] = (int8_t)(val / 256);
    
    			fseek( fp , -2 , SEEK_CUR );
    			fwrite( &changed[0] , 1 , 2 , fp );
  		}
    
		  printf( "\n" );
	}
  
	fclose( fp );

	return 0;
}

                    
