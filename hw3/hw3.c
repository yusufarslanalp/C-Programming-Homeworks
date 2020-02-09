#include <stdio.h>
#include <string.h>

void
find_placeof_word( char word[], char characters[][250], int len_column, int cordinate[] );

int
find_placeof_horizontal_word( char word[], char characters[][250], int len_column, int cordinate[] );

int
find_placeof_vertical_word( char word[], char characters[][250], int len_column, int cordinate[] );

int
find_max_row_len( char characters[][250] );

void
take_vertical_word( char word[], char characters[][250], char compare[], int row, int column );


int
main(void)
{

	char get_row[250];	
	char characters[100][250];	//input.txt dosyasından okunan karakterlerin yazıldığı arraydir.
	int row = 0, number_of_rows = 0, i, column; //number_of_rows characters array'inin kaç satırdan oluştuğunu saklar.
	char *word1 = "Xanthos";
	char *word2 = "Patara";
	char *word3 = "Myra";
	char *word4 = "Arycanda";
	char *word5 = "Phaselis"; 
	int cordinate[2];
	FILE *fp;
	fp = fopen("input.txt","r");	
	for( row = 0; row < 100; row++ )	//Buradaki for döngüleri ile characters array'inin tüm elemanları null karakteri ile dolduruldu.
	{
		for( column = 0; column < 250; column++ )
		{
			characters[row][column] = 0;
		}
	}

	row = 0;
	number_of_rows = 0;
	while( fscanf( fp, "%s", get_row ) == 1 )	//input.txt dosyasında boşluk ve newline karakteri ile ayrılmış tüm ardışık karakterler
	{											//characters array'ine satırlar halinde yazıldı.
		strcpy( *(characters +row) , get_row );
		row += 1;
		number_of_rows += 1;
	
	}
	
	find_placeof_word( word1, characters, number_of_rows, cordinate );
	find_placeof_word( word2, characters, number_of_rows, cordinate );
	find_placeof_word( word3, characters, number_of_rows, cordinate );
	find_placeof_word( word4, characters, number_of_rows, cordinate );
	find_placeof_word( word5, characters, number_of_rows, cordinate );
}


void
find_placeof_word( char word[], char characters[][250], int number_of_rows, int cordinate[] )	//bu fonksiyon aranacak kelimeyi önce yatayda arar.Aradığı kelimeyi bulursa kelimeyi ve kelimenin ilk karakterinin konumunu ekrana basar.Aradığı kelimeyi yatayda bulamazsa dikeyde arar.Dikeyde bulursa bulduğu kelimeyi ve kelimenin ilk karakterinin konumunu ekrana basar.
{
	if ( find_placeof_horizontal_word( word, characters, number_of_rows, cordinate ) == 1 )
	{
		printf("%s (%d,%d) Horizontal\n", word, cordinate[0], cordinate[1] );
	}

	else if(find_placeof_vertical_word( word, characters, number_of_rows, cordinate ) == 1 )
	{
		printf( "%s (%d,%d) Vertical\n", word, cordinate[0], cordinate[1] );
	}
}


int
find_placeof_horizontal_word( char word[], char characters[][250], int number_of_rows, int cordinate[] )	//bu fonksiyon verilen kelimeyi characters array'inde yatay olarak sağdan sola doğru arar.Eğer aradığı kelimeyi bulursa bulduğu kelimenin ilk karakterinin konumunu cordinate array'ine kaydeder.
{
	int row, column;
	char compare[9];	

	/* Buradaki for döngüsü ile satırın en başından başlanarak satırdan karşılaştırılacak kelime uzunluğu kadar kelime campare arry'ine kopyalaır. Compare array'i karşılaştırılmak istenen kelimeyle kıyaslanır. Compare arry'i ile aranan kelimenin eşit olduğu durumda döngüden çıkılır. */

	for( row = 0; row < number_of_rows; row++ )
	{
		for( column = 0; column <= (  strlen(*(characters + row)) - strlen(word)  ); column++ )	
		{																						
			memcpy( compare, (*( characters + row ))+column, strlen( word ) );
			compare[ strlen( word ) ] = '\0';
			cordinate[0] = row + 1;	//Cordinate array'inin ilk elemanı bulunacak kelimenin ilk karakterinin satır sırsını saklar.
			cordinate[1] = column + 1;	//Cordinate array'inin ikinci elemanı bulunacak kelimenin ilk karakterinin sütun sırsını saklar.
			if( strcmp( word, compare ) == 0 ) return 1;
		}
	}
	return 0;
}


int
find_placeof_vertical_word( char word[], char characters[][250], int number_of_rows, int cordinate[] )	//bu fonksiyon verilen kelimeyi characters array'inde dikey olarak yukarıdan aşağıya doğru arar.Eğer aradığı kelimeyi bulursa bulduğu kelimenin ilk karakterinin konumunu cordinate array'ine kaydeder.
{	
	int row, column;
	char compare[9];
	int max_row_len = find_max_row_len( characters );

	/*buradaki for döngüleri characters array'indeki sütunların başından başlayarak aşağıya doğru sırayla take_vertikal_word fonksiyonuna koum verir. */

	for( column = 0; column < max_row_len; column++ )	
	{
		for( row = 0; row <= number_of_rows - strlen( word ); row++ )
		{
			take_vertical_word( word, characters ,compare, row, column );
			if( strcmp( compare, word ) == 0 )
			{
				cordinate[0] = row +1; 	//Cordinate array'inin ilk elemanı bulunacak kelimenin ilk karakterinin satır sırsını saklar.
				cordinate[1] = column +1; //Cordinate array'inin ikinci elemanı bulunacak kelimenin ilk karakterinin sütun sırsını saklar.
				return 1;
			}
		}
	}
	return 0;
}


int
find_max_row_len( char characters[][250] )	//bu fonksiyon characters array'indeki en uzun satırın uzunluğunu bularak max_row_len değişkenine yazar.
{
	int row;
	int max_row_len;	//characters array'indeki en uzun satırın uzunluğunu saklar.
	max_row_len = strlen( *characters );
	for(row = 1; row < 100; row++ )
	{
		if( strlen( *(characters + row) ) > max_row_len )
		{
			max_row_len = strlen( *(characters + row) );
		}
	}
	return max_row_len;	
}

void
take_vertical_word( char word[], char characters[][250], char compare[], int row, int column )	//bu fonksiyon characters arrayi'nin verilen kordinatlarından başlayarak paramtre olarak verilen kelime uzunluğunda karakterleri yukarıdan aşağıya olarak alır.Aldığı keimeleri  compare array'ine kaydeder.
{	
	int i;
	int len_word = strlen( word );
	for( i = 0; i < len_word; i++ )
	{
		compare[i] = characters[ row + i ][column];
	}
	compare[ len_word ] = '\0';
	
}

