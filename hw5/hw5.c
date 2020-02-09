#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void
find_bi_grams( int bi_grams[][27] , char file_name[] ); // BU fonksiyon dosyadan aldığı tüm bi-gram çeşitlerinin sayısını bi_grams[27][27] array'ine kaydeder.
							//27 sayısı: ingilizce alfabedeki har sayısı(26) + space karakteri(1)

void
fill_bi_grams_zero( int bi_grams[][27] ); // Bu fonksiyon bi_grams array'inin tüm elemanlarını sıfırla doldurur.

int
find_sum_of_bi_grams( int bi_grams[][27] ); //Bu fonksiyon bi_gram çeşitlerinin sayısını tutan bi_grams arry'inin tüm elemanlarını toplar ve sonucu return eder.

void
dissimilarity( int language1_bi_grams[][27] , int language2_bi_grams[][27] ); // bu fonksiyon iki dile ait bi-grams çeşitlerinin sayısını parametre olarak verilen bi_grams[27][27] vasıtasıyla alarak iki dilin dissimilarity değerlerini hesaplar ve sonucu ekrana basar.


int
main(void)
{
	int language1_bi_grams[27][27];
	int language2_bi_grams[27][27];
	int language3_bi_grams[27][27];
	int language4_bi_grams[27][27];
	int language5_bi_grams[27][27];
	int languagex_bi_grams[27][27];

	char language1[15] = "language_1.txt"; //dosya adları fonksiyonlara parametre olarak verilebilmek için karakter arraylerine kaydedildi.
	char language2[15] = "language_2.txt";
	char language3[15] = "language_3.txt";
	char language4[15] = "language_4.txt";
	char language5[15] = "language_5.txt";
	char languagex[15] = "language_x.txt";

	fill_bi_grams_zero( language1_bi_grams );
	fill_bi_grams_zero( language2_bi_grams );
	fill_bi_grams_zero( language3_bi_grams );
	fill_bi_grams_zero( language4_bi_grams );
	fill_bi_grams_zero( language5_bi_grams );
	fill_bi_grams_zero( languagex_bi_grams );

	find_bi_grams( language1_bi_grams , language1 );
	find_bi_grams( language2_bi_grams , language2 );
	find_bi_grams( language3_bi_grams , language3 );
	find_bi_grams( language4_bi_grams , language4 );
	find_bi_grams( language5_bi_grams , language5 );
	find_bi_grams( languagex_bi_grams , languagex );


	dissimilarity( language1_bi_grams, languagex_bi_grams );
	dissimilarity( language2_bi_grams, languagex_bi_grams );
	dissimilarity( language3_bi_grams, languagex_bi_grams );
	dissimilarity( language4_bi_grams, languagex_bi_grams );
	dissimilarity( language5_bi_grams, languagex_bi_grams );

}


void
find_bi_grams( int bi_grams[][27] , char file_name[] ) // BU fonksiyon dosyadan aldığı tüm bi-gram çeşitlerinin sayısını bi_grams[27][27] array'ine kaydeder.
{
	/* int bi_grams[27][27] arrayi dosyası okanan dile ait bi-gram çeşitlerinin sayısını depolamak için kullanılmıştır. array'in satırları bi-gram'ların ilk harflerini temsil ederken array'in sutunları bi-gramların ikinci harflerini temsil etmektedir. array'in ilk satırı ilk karakteri space olan bigramların sayısını saklar, array'in ikinci satırı bi-gramlarının ilk karakteri a olan bi-gramların sayısını saklar array'in üçüncü satırı bi-gramlarının ilk karakteri b olan bi-gramların sayısını saklar ..... array'in 27. satırı    bi-gramlarının ilk karakteri z olan bi-gramların sayısını saklar *****ÖRNEK OLARAK:
aa bi-gram'larının sayısı bi-grams[1][1] array'inde bulunur,
ab bigram'larının sayısı bi_grams[1][2] array'inde bulunur, 
ac bigram'larının sayısı bi_grams[1][3] array'inde bulunur,
bb bigram'larının sayısı bi_grams[2][2] array'inde bulunur
space space bigram'larının sayısı bi_grams[0][0] array'inde bulunur,
space a bigram'larının sayısı bi_grams[0][1] array'inde bulunur..... ***** */

	char first_char;
	char second_char;
	char third_char; /* fgetc() fonksiyonu dosyanın sonunda new-line(\n) karakteri olmamasına rağmen dosyanın sonundan new-line karakteri okuduğu için üçüncü bir karakter değişkeni kullanılarak aslında dosyanın sonunda olmayıpda okunan new-line karakteri ihmal edildi.*/

	int first_element;
	int second_element;

	FILE *fp;
	fp = fopen( file_name, "r" );

	first_char = fgetc( fp );
	if( first_char != EOF )
	{		
		second_char = fgetc( fp );
		if( second_char != EOF )
		{
			third_char = fgetc( fp );
			while( third_char != EOF ) // bu döngü ile bi-grams çeşitlerinin sayılarına göre bi_grams array'i dolduruldu.
			{
				if( first_char == ' ' ) first_element = 0; 
				else if( first_char >= 'a' && first_char <= 'z' ) first_element = (first_char - 'a' + 1) ;
				else first_element = 0;

				if( second_char == ' ' ) second_element = 0; 
				else if( second_char >= 'a' && second_char <= 'z' ) second_element = (second_char - 'a' + 1) ;
				else second_element = 0;

				bi_grams[ first_element ][ second_element ] += 1;
				
				first_char = second_char;
				second_char = third_char;
				third_char = fgetc( fp );
			}
		}
	}
	fclose( fp );
	bi_grams[0][0] = 0; // space-space bi-gramı geçersiz sayıldığı için bi_grams[][] array'indeki  bu bi-gram'ın sayısını tutan bi_grams[0][0] yerine sıfır sayısı kaydedildi.
}


void
fill_bi_grams_zero( int bi_grams[][27] ) // Bu fonksiyon bi_grams array'inin tüm elemanlarını sıfırla doldurur.
{
	int i, j;

	for( i = 0; i < 27; i++ )
	{
		for( j = 0; j < 27; j++ )
		{
			bi_grams[i][j] = 0;
		}
	}
}


int
find_sum_of_bi_grams( int bi_grams[][27] ) //Bu fonksiyon bi_gram çeşitlerinin sayısını tutan bi_grams arry'inin tüm elemanlarını toplar ve sonucu return eder.
{
	int sum = 0, i, j;
	for( i = 0; i < 27; i++ )
	{
		for( j =0; j < 27; j++ )
		{
			sum += bi_grams[i][j];
		}
	}
	return sum;
}

void
dissimilarity( int language1_bi_grams[][27] , int language2_bi_grams[][27] ) // bu fonksiyon iki dile ait bi-grams çeşitlerinin sayısını parametre olarak verilen bi_grams[27][27] vasıtasıyla alarak iki dilin dissimilarity değerlerini hesaplar ve sonucu ekrana basar.
{
	double total_language1_bi_grams = find_sum_of_bi_grams( language1_bi_grams );
	double total_language2_bi_grams = find_sum_of_bi_grams( language2_bi_grams );
	int i, j;
	double dissimilarity_value = 0;
	double value;

	for( i = 0; i < 27; i++ )
	{
		for( j = 0; j < 27; j++ )
		{
			value = language1_bi_grams[i][j] / total_language1_bi_grams - language2_bi_grams[i][j] / total_language2_bi_grams;
			dissimilarity_value += fabs( value );
		}
	}
	printf( "%f\n", dissimilarity_value );
}


