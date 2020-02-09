#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <string.h>

typedef enum { column, row } line_t;
typedef enum { right, left, up, down } direction_t;



int
main(void)
{
	int i, j, n;	// n oluşturulacak olan küp'ün bir kenarının uzunluğudur.
	int face_num;	
	line_t line_type;	// row or column
	char line_name[50]; // row or column
	int line_num;	// row num or column num
	direction_t direction_type; //up , down, riht left
	char direction_name[50];	//up , down, riht left
	int temp;
	char line_file[200]; //dosyadan okunan satırlar.
	char word[50];

	//*** Aşağıda gerekli file poiter'ları oluşturulmuş ve dosyalar gerekli biçimlerde açılmıştır. ***//
	FILE *fp_commands;
	FILE *fp_result;
	fp_commands = fopen( "commands.txt" , "r" );
	fp_result = fopen( "result.txt" , "w+" );


	//***** Burada commands.txt dosyasının ilk satırında bılunan tamsayı değeri okunarak oluşturulacak küpün boyutu elde edilmiştir. *****//
	if( fgets( line_file, 200 , fp_commands ) != NULL )
	{
		sscanf( line_file , "%d", &n );
	}


	// Burada malloc ile birlikte kullanılmak üzere küpün altı yüzeyi için poiter'lar oluşturulmuştur. 
	int **face_0;
	int **face_1;
	int **face_2;
	int **face_3;
	int **face_4;
	int **face_5;


//********** burda her face için malloc kullanarak iki boyutlu memeory allocation yapılmaktadır. **********//	

	face_0 = (int**)malloc( (int)sizeof( int* ) * n );
	for( i = 0; i < n; ++i )
	{
		face_0[i] = (int*)malloc( (int)sizeof(int) * n  );
	}

	face_1 = (int**)malloc( (int)sizeof( int* ) * n );
	for( i = 0; i < n; ++i )
	{
		face_1[i] = (int*)malloc( (int)sizeof(int) * n  );
	}

	face_2 = (int**)malloc( (int)sizeof( int* ) * n );
	for( i = 0; i < n; ++i )
	{
		face_2[i] = (int*)malloc( (int)sizeof(int) * n  );
	}

	face_3 = (int**)malloc( (int)sizeof( int* ) * n );
	for( i = 0; i < n; ++i )
	{
		face_3[i] = (int*)malloc( (int)sizeof(int) * n  );
	}

	face_4 = (int**)malloc( (int)sizeof( int* ) * n );
	for( i = 0; i < n; ++i )
	{
		face_4[i] = (int*)malloc( (int)sizeof(int) * n  );
	}

	face_5 = (int**)malloc( (int)sizeof( int* ) * n );
	for( i = 0; i < n; ++i )
	{
		face_5[i] = (int*)malloc( (int)sizeof(int) * n  );
	}


//********** burda her face dizisinin içi face numarasına göre doldurulmuştur. **********//	

	for( i = 0; i < n; ++i ) for( j = 0; j < n; ++j ) face_0[i][j] = 0;

	for( i = 0; i < n; ++i ) for( j = 0; j < n; ++j ) face_1[i][j] = 1;

	for( i = 0; i < n; ++i ) for( j = 0; j < n; ++j ) face_2[i][j] = 2;

	for( i = 0; i < n; ++i ) for( j = 0; j < n; ++j ) face_3[i][j] = 3;

	for( i = 0; i < n; ++i ) for( j = 0; j < n; ++j ) face_4[i][j] = 4;

	for( i = 0; i < n; ++i ) for( j = 0; j < n; ++j ) face_5[i][j] = 5;




//********* tüm rotate işlemleri aşağıdaki while döngüsünde yapılmaktadır. *********//

	// bu while döngüsünün içindeki fgets fonksiyonu ile dosyadan commands.txt dosyasından satır alınır.//
	// alınan satırlar içerisindeki bilgiler sscanf fonksiyonu ile elde edilir.//
	// Bu işlem dosyada satır kalmayıncaya kadar tekrar edilir. //
	while( fgets( line_file, 200 , fp_commands ) != NULL )
	{
		word[0] = '\0';
		sscanf( line_file , "%s", word );
		if( strcmp( "rotate" , word ) == 0 ) //eğer okunan satırın ilk kelimesinde "rotate" string'i varsa if koşulunun içine girilir.
		{
			sscanf( line_file , "%s %d %s %d %s", word , &face_num , line_name , &line_num , direction_name  );			

			//sscanf fonksiyonu ile elde edilen bilgiler kullanım kolaylığı sağlamak için enum karşılıklarına dönderilir. //
			if( strcmp( "row" , line_name ) == 0 ) line_type = row;
			if( strcmp( "column" , line_name ) == 0 ) line_type = column;
			if( strcmp( "right" , direction_name ) == 0 ) direction_type = right;
			if( strcmp( "left" , direction_name ) == 0 ) direction_type = left;
			if( strcmp( "up" , direction_name ) == 0 ) direction_type = up;
			if( strcmp( "down" , direction_name ) == 0 ) direction_type = down;




			//*** aşağıda if koşulu içerisindeki or operatörleri ile birbirine bağlanmış her komut: küp yüzeyinde aynı sonuçlara sebep olmaktadır. ***//
			//***  Bu yüzden aşağıda if koşulu içerisinde bulunan komutlar aynı işleme tabi tutulmuştur. ***//
			if( (face_num == 0 && line_type == row && direction_type == right) ||
				(face_num == 1 && line_type == row && direction_type == right) ||
				(face_num == 2 && line_type == row && direction_type == right) ||
				(face_num == 3 && line_type == row && direction_type == right)
			  )
			{
				for( i = 0; i < n; i++ )
				{
					temp = face_1[ line_num ][ i ];
					face_1[ line_num ][ i ] = face_0[ line_num ][ i ];
					face_0[ line_num ][ i ] = face_3[ line_num ][ i ];
					face_3[ line_num ][ i ] = face_2[ line_num ][ i ];
					face_2[ line_num ][ i ] = temp;
				}
			}


			//*** aşağıda if koşulu içerisindeki or operatörleri ile birbirine bağlanmış her komut: küp yüzeyinde aynı sonuçlara sebep olmaktadır. ***//
			//***  Bu yüzden aşağıda if koşulu içerisinde bulunan komutlar aynı işleme tabi tutulmuştur. ***//
			else if( (face_num == 0 && line_type == row && direction_type == left) ||
				(face_num == 1 && line_type == row && direction_type == left) ||
				(face_num == 2 && line_type == row && direction_type == left) ||
				(face_num == 3 && line_type == row && direction_type == left)
			  )
			{
				for( i = 0; i < n; i++ )
				{
					temp = face_2[ line_num ][ i ];
					face_2[ line_num ][ i ] = face_3[ line_num ][ i ];
					face_3[ line_num ][ i ] = face_0[ line_num ][ i ];
					face_0[ line_num ][ i ] = face_1[ line_num ][ i ];
					face_1[ line_num ][ i ] = temp;

				}
			}


			//*** aşağıda if koşulu içerisindeki or operatörleri ile birbirine bağlanmış her komut: küp yüzeyinde aynı sonuçlara sebep olmaktadır. ***//
			//***  Bu yüzden aşağıda if koşulu içerisinde bulunan komutlar aynı işleme tabi tutulmuştur. ***//
			else if( (face_num == 0 && line_type == column && direction_type == up) ||
				(face_num == 4 && line_type == column && direction_type == up) ||
				(face_num == 2 && line_type == column && direction_type == down) ||
				(face_num == 5 && line_type == column && direction_type == up)
			  )
			{
				if( face_num == 2 && line_type == column && direction_type == down )
				{
					line_num = (n - 1) - line_num;
				}

				for( i = 0; i < n; i++ )
				{
					temp = face_4[ i ][ line_num ];
					face_4[ i ][ line_num ] = face_0[ i ][ line_num ];
					face_0[ i ][ line_num ] = face_5[ i ][ line_num ];
					face_5[ i ][ line_num ] = face_2[ (n - 1) - i ][ (n - 1) - line_num ];
					face_2[ (n - 1) - i ][ (n - 1) - line_num ] = temp;
				}
			}



			//*** aşağıda if koşulu içerisindeki or operatörleri ile birbirine bağlanmış her komut: küp yüzeyinde aynı sonuçlara sebep olmaktadır. ***//
			//***  Bu yüzden aşağıda if koşulu içerisinde bulunan komutlar aynı işleme tabi tutulmuştur. ***//
			else if( (face_num == 0 && line_type == column && direction_type == down) ||
				(face_num == 4 && line_type == column && direction_type == down) ||
				(face_num == 2 && line_type == column && direction_type == up) ||
				(face_num == 5 && line_type == column && direction_type == down)
			  )
			{
				if( face_num == 2 && line_type == column && direction_type == up )	
				{
					line_num = (n - 1) - line_num;
				}

				for( i = 0; i < n; i++ )
				{
					temp = face_2[ (n - 1) - i ][ (n - 1) - line_num ];
					face_2[ (n - 1) - i ][ (n - 1) - line_num ] = face_5[ i ][ line_num ];
					face_5[ i ][ line_num ] = face_0[ i ][ line_num ];
					face_0[ i ][ line_num ] = face_4[ i ][ line_num ];
					face_4[ i ][ line_num ] = temp;
				}
			}


			//*** aşağıda if koşulu içerisindeki or operatörleri ile birbirine bağlanmış her komut: küp yüzeyinde aynı sonuçlara sebep olmaktadır. ***//
			//***  Bu yüzden aşağıda if koşulu içerisinde bulunan komutlar aynı işleme tabi tutulmuştur. ***//
			else if( (face_num == 1 && line_type == column && direction_type == up) ||
				(face_num == 4 && line_type == row && direction_type == left) ||
				(face_num == 3 && line_type == column && direction_type == down) ||
				(face_num == 5 && line_type == row && direction_type == right)
			  )
			{
				if( face_num == 4 && line_type == row && direction_type == left )
				{
					line_num = (n - 1) - line_num;
				}

				if( face_num == 3 && line_type == column && direction_type == down )
				{
					line_num = (n - 1) - line_num;
				}

				for( i = 0; i < n; i++ )
				{
					temp = face_4[ (n - 1) - line_num ][ i ];
					face_4[ (n - 1) - line_num ][ i ] = face_1[ i ][ line_num ];
					face_1[ i ][ line_num ] = face_5[ line_num ][ (n - 1) - i ];
					face_5[ line_num ][ (n - 1) - i ] = face_3[ (n - 1) - i ][ (n - 1) - line_num ];
					face_3[ (n - 1) - i ][ (n - 1) - line_num ] = temp;
				}
			}


			//*** aşağıda if koşulu içerisindeki or operatörleri ile birbirine bağlanmış her komut: küp yüzeyinde aynı sonuçlara sebep olmaktadır. ***//
			//***  Bu yüzden aşağıda if koşulu içerisinde bulunan komutlar aynı işleme tabi tutulmuştur. ***//
			else if( (face_num == 1 && line_type == column && direction_type == down) ||
				(face_num == 4 && line_type == row && direction_type == right) ||
				(face_num == 3 && line_type == column && direction_type == up) ||
				(face_num == 5 && line_type == row && direction_type == left)
			  )
			{
				if( face_num == 4 && line_type == row && direction_type == right )
				{
					line_num = (n - 1) - line_num;
				}

				if( face_num == 3 && line_type == column && direction_type == up )
				{
					line_num = (n - 1) - line_num;
				}

				for( i = 0; i < n; i++ )
				{
					temp = face_3[ (n - 1) - i ][ (n - 1) - line_num ];
					face_3[ (n - 1) - i ][ (n - 1) - line_num ] = face_5[ line_num  ][ (n - 1) - i ];
					face_5[ line_num  ][ (n - 1) - i ] = face_1[ i ][ line_num ];
					face_1[ i ][ line_num ] = face_4[ (n - 1) - line_num ][ i ];
					face_4[ (n - 1) - line_num ][ i ] = temp;
				}
			}

		}
	}


//********************************************** aşağısı arraylerin hepsini sırasına göre result.txt dosyasına yazar.. ************************************//

	for( i = 0; i < n; ++i )
	{
		for( j = 0; j < n; ++j ) fprintf( fp_result , "%d ", face_0[i][j] );
		fprintf( fp_result , "\n" );
	}
	fprintf( fp_result , "\n" );

	for( i = 0; i < n; ++i )
	{
		for( j = 0; j < n; ++j ) fprintf( fp_result , "%d ", face_1[i][j] );
		fprintf( fp_result , "\n" );
	}
	fprintf( fp_result , "\n" );


	for( i = 0; i < n; ++i )
	{
		for( j = 0; j < n; ++j ) fprintf( fp_result , "%d ", face_2[i][j] );
		fprintf( fp_result , "\n" );
	}
	fprintf( fp_result , "\n" );


	for( i = 0; i < n; ++i )
	{
		for( j = 0; j < n; ++j ) fprintf( fp_result , "%d ", face_3[i][j] );
		fprintf( fp_result , "\n" );
	}
	fprintf( fp_result , "\n" );


	for( i = 0; i < n; ++i )
	{
		for( j = 0; j < n; ++j ) fprintf( fp_result , "%d ", face_4[i][j] );
		fprintf( fp_result , "\n" );
	}
	fprintf( fp_result , "\n" );


	for( i = 0; i < n; ++i )
	{
		for( j = 0; j < n; ++j ) fprintf( fp_result , "%d ", face_5[i][j] );
		fprintf( fp_result , "\n" );
	}

//********** Aşağıda mallok ile oluşturulan ram kısımları free edilmiştir. **********//

	for( i = 0; i < n; ++i ) free( face_0[i] );
	free( face_0 );

	for( i = 0; i < n; ++i ) free( face_1[i] );
	free( face_1 );

	for( i = 0; i < n; ++i ) free( face_2[i] );
	free( face_2 );

	for( i = 0; i < n; ++i ) free( face_3[i] );
	free( face_3 );

	for( i = 0; i < n; ++i ) free( face_4[i] );
	free( face_4 );

	for( i = 0; i < n; ++i ) free( face_5[i] );
	free( face_5 );


	fclose( fp_commands ); //sol tarafta açılan dosyalar kapatılmıştır.
	fclose( fp_result );
}


