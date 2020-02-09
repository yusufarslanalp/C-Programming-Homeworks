#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
count_brackets_downward( char characters[] , int place_previous_char);

void
print_tires( int tires );

int
print_newick_format( char characters[], int size, int i );

int
main(void)
{
	int size;
	char characters[100];
	int i = 0;

	FILE *fp;
	fp = fopen("input.txt","r");
	fscanf( fp, "%s", characters );
	fclose( fp );

	size = strlen( characters );
	print_newick_format( characters, size, i );
}

int
count_brackets_downward( char characters[] , int place_previous_char) //bu fonksiyona bir harfin kaç tane parantezin içinde olduğunu hesaplar ve sonucu "tires" değişkeni ile return eder.
{
	/* bu fonksiyon ilk çağırıldığında parametre olarak verilen place_previous_char değişkeni kaç tane parantezin içinde olduğu öğrenilmek istenen harften bir önceki karakterdir. */
	/* bu fonksiyon bir karakterin kaç tane parantezin içinde olduğunu bulmak için kaç parantezin içinde olduğu merak edilen karakterden önceki tüm karakterleri kontrol eder. kaç parantezin içinde olduğu merak edilen karakterden önceki her "(" karakter için "tires değişkenini 1 arttırırken kaç parantezin içinde olduğu merak edilen karakterden önceki her ")" karakteri için tires değişkenini 1 azaltır. kaç parantezin içinde olduğu merak edilen karakterden önceki diğer karakterler içinse "tires" değişkeninin değerini değiştirmez.   */

	int tires = 0;

	if( place_previous_char < 0 ) return tires ; // bu kısım karakter dizisinin en başına kadarki tüm elemanlar kontrol edildiğinde recursive fonksiyonunun sonlanmasını ve tires değişkeninin return edilmesini sağlar.

	else
	{
		if( characters[ place_previous_char ] == '(' ) tires =  1 + count_brackets_downward( characters , place_previous_char -1 );
		else if( characters[ place_previous_char ] == ')' ) tires =  -1 + count_brackets_downward( characters , place_previous_char -1 );
		else  tires = count_brackets_downward( characters , place_previous_char -1 );
	}
}

void
print_tires( int tires ) //bu fonksiyon parametre olarak tire sayısı alır ve aldığı tiresayısı kadar tire'yi recursive olarak ekrana basar.
{
	if( tires == 0 );
	else
	{
		printf( "-" );
		print_tires( tires -1 );
	}
}

int
print_newick_format( char characters[], int size, int i ) /* Bu fonksiyon characters array'inin i'inci karakterrinden başlayarak characters array'inin sonuna kadarki tüm elemanların üstünde gezinerek üstünde gezindiği elemanlar için "count_brackets_downward" fonksiyonunu çağırır. "count_brackets_downward" fonksiyonundan aldığı return değerine göre "print_tires" fonksiyonunu çağırır. Böylece ekrana basılma istenen ifade ekrana bastırılmış olur.  */
{
	char place_previous_character;
	int tires;

	if( i == size ) ;

	else
	{
		if( characters[i] != ',' && characters[i] != '('  && characters[i] != ')' )
		{
			place_previous_character = i - 1;
			tires = count_brackets_downward( characters , place_previous_character );
			print_tires( tires );
			printf( "%c\n", characters[i] );
		}
		print_newick_format( characters, size, i+1 );
	}
}


