#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int
is_seperator( double num, int *count);

double
*find_place_of_min_element( double array[], int array_size );

void
change_value(double *a, double *b);

void
change_row( int array[][2], int num1, int num2);

void
sort_chunks( double avarages_of_chunks[], int array_size, int places_of_chunks[][2] );


int
main(void)
{
	double numbers[1000];
	int len_numbers;
	double num;
	int places_of_chunks[250][2];	//bu array'in ilk sütununda chunk'ların başladıkları adresler bulunur ikinci sütununda chunk'ların bittikleri adresler bulunur.
	double avarages_of_chunks[250];
	int count = 0;
	int place = 0;
	int begining = 0;	//bir chunk'ın numbers arrayi üzerindeki başlangıç yerini ifade eder. 
	int end = 0;		//bir chunk'ın numbers arrayi üzerindeki bitiş yerini ifade eder. 
	int i = 0;
	int j;
	int order_of_min;
	int len_places_of_chunks;
	double sum = 0;
	double temp;
	double *min;
		

	FILE *fp = fopen("input.txt","r");
	while( fscanf(fp, "%lf", &num) == 1 ) //input dosyasındaki arrayler numbers array'ine yazılır.
	{
		numbers[i] = num;
		i++;
	}
	len_numbers = i;
	fclose(fp);

	for( i = 0; i < len_numbers; i++ )
	{

		if( is_seperator( numbers[i], &count ) == 1 )
		{
			count = 0;

			if( i - begining == 2 ) begining = i+1; //bu koşul ardarda iki seperator olduğunda chunk oluşumunu engeller.

			else
			{
				end = i-3;	//numbers arry'inde seperator'den önceki ilk sayıyının konumu(chunk'ın son elemanı) end değişkenine atanır.
				places_of_chunks[place][0] = begining;
				places_of_chunks[place][1] = end;
				place++;
				begining = i + 1; //seperator'den sonraki ilk eleman begining değişkenine atanır.
			}
		}
	}

	if( begining != len_numbers ) //bu koşul numbers array'i bir chunk ile bitmediğinde son chunk'ın başlangıç ve bitiş konumunu places_of_chunks
	{							  //array'ine kaydeder.
		end = len_numbers -1;
		places_of_chunks[place][0] = begining;
		places_of_chunks[place][1] = end;
		place++;
	}


	len_places_of_chunks = place;

	for( i = 0; i < len_places_of_chunks; i++ )		//bu döngü chunk'ların ortalamalarını avarages_of_chunks array'ine kaydeder.
	{
		for( j = places_of_chunks[i][0]; j <= places_of_chunks[i][1] ; j++ ) 
		{
			sum = sum + numbers[j];
		}
		avarages_of_chunks[i] = sum / ( places_of_chunks[i][1] - places_of_chunks[i][0] + 1);
		sum = 0;
	}

	sort_chunks( avarages_of_chunks, len_places_of_chunks, places_of_chunks );
	
	fp = fopen("output.txt","w+");	//bu döngü sıralanmış chukları output.txt dosyasına yazar.
	for( i = 0; i < len_places_of_chunks; i++ )
	{
		for( j = places_of_chunks[i][0]; j <= places_of_chunks[i][1] ; j++ )
		{
			fprintf(fp,"%f ",numbers[j]);

		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}


int
is_seperator( double num, int *count)	//bu fonksiyon num parametresine 3 tane ardarda 0 aldığında 1 değeri return eder.
{

	if( num == 0.0) *count = *count + 1;
	else *count = 0;

	if(*count == 3) return 1;
	else return 0;
}

double
*find_place_of_min_element( double array[], int array_size )	//bu fonksiyon verilen bi array'in en küçük elemanının adresini return eder.
{
	double *min;
	int i;
	min = &array[0];
	for( i = 1; i < array_size ; i++ )
	{
		if( array[i] < *min )
		{
			min = &array[i];
		}
	}	
	return min;
}

void
change_value(double *a, double *b)	//bu fonksiyon verilen iki pointer'ın işaret ettikleri yerlerdeki değerleri değiştirir.
{
	double temp = *a;
	*a = *b;
	*b = temp;
}

void
change_row( int array[][2], int num1, int num2) //bu fonksiyon satır numaraları verilen bir array'in satırlarınındaki değerlerin yerini değiştirir.
{
	double temp[1][2];
	temp[0][0] = array[num1][0];
	temp[0][1] = array[num1][1];

	array[num1][0] = array[num2][0];
	array[num1][1] = array[num2][1];

	array[num2][0] = temp[0][0];
	array[num2][1] = temp[0][1];
}

void
sort_chunks( double avarages_of_chunks[], int array_size, int places_of_chunks[][2] ) //bu fonksion avarages_of_chunks array'indeki değerlere göre
{																					  //chunk'ları sıralar.
	int i;
	int order_of_min_chunk;
	double *min;
	for( i = 0; i < array_size  ; i++ )
	{
		min = find_place_of_min_element( (avarages_of_chunks + i), array_size );
		order_of_min_chunk = min - avarages_of_chunks;
		change_value( min, &avarages_of_chunks[i] );
		change_row( places_of_chunks, order_of_min_chunk, i );
		array_size = array_size - 1;
	}
}

