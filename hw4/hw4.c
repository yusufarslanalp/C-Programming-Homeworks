#include <stdio.h>
#include <string.h>
#include <math.h>

typedef enum { minus, plas } sign;

void
remove_spaces( char polinom[] ); //Bu fonksiyon verilen herhangi bir karakter tipindeki array'in tümspace tab ve new line karakterlerini siler.

void
find_signs( char arr[], sign signs[], int *size_signs ); //bu fonksiyona polinom içeren bir array verildiğinde polinomun tüm monomial'lerinin işaretlerini sırasıyla signs[] array'ine kaydeder.

void
find_coefficient( char monomials[][30], int size, double coefficients[] ); //bu fonksiyon monomials[][] adında bir array alarak her maonaomial'in coefficient'ini coefficients[] arrayine kaydeder. 

void
find_exponent( char monomials[][30], int size, int exponents[] ); //bu fonksiyon monomials[][] adında bir array alarak her maonaomial'in exponet'ini exponents[] array'ine kaydeder.

double
calculate_monomial( double number, sign sign_monomial, double coefficient, int exponent ); //bu fonsiyon p(x) gibi bir plinom için x sayısı yerine number parametresi alır.bu fonksiyon ayrıca bir monomial için sign, coefficient ve exponent parametreleri alarak p(x) polinomunun herhangi bir monomial'inin değerini hesaplar.


int
main(void)
{
	int size_of_monomials = 0, i = 0;	//size_of_monomials verilen polinomdaki monomialler'in sayısını sakalar.
	double coefficients[501];	//polinomdaki monomiallerin coefficient'lerinin değerlerini sırasıyla saklar.
	int exponents[501];			//polinomdaki monomiallerin exponent'lerinin değerlerini sırasıyla saklar.
	char monomials[501][30];	//polinomun monomial'leri işaretsiz olarak sırasıyla saklar. 
	sign signs[501];			//fonksiyondaki monomial'lerin işaretlerini sırasıyla saklar.	
	char *token;				//strtoken fonksiyonu ile kullanılarak her monomial'i geçici olarak saklar. 
	char polynom[1000];			//polynomial.txt dosyasındaki karakter dizisi buraya kaydedilir.
	char ch;
	double result_of_polynom = 0.0;	//value.txt dosyasındaki polinomda x yerine koyduktan sonra bulunan değeri geçici olarak saklar.
	double number;

	FILE *get_polynom;
	FILE *get_values;
	FILE *write_results;
	get_polynom = fopen( "polynomial.txt", "r" );

	for( ch = fgetc(get_polynom); ch != EOF ; ch = fgetc(get_polynom) )
	{
		polynom[i] = ch;
		i++;
	}
	polynom[i] = 0;
	fclose( get_polynom );

	remove_spaces( polynom );	//polynomial.txt osyasından alınan tüm karakterler space tab ve new line karakterlerinden arındırıldı.
	find_signs( polynom, signs, &size_of_monomials );	//tüm monomil'lerin işaretleri sırasıyla bulunarak signs[] array'ine kaydedildi.

	token = strtok( polynom, "+-" );
	i = 0;
	while( token != NULL )	//buradak döngü ile tüm monomialler işaretsiz olarak ve sırasıyla monomials[][] array'ine kaydedildi.
	{
		memcpy( monomials[i], token, sizeof(char) * strlen(token) +1 );
		i++;
		token = strtok( NULL, "+-" );
	}

	find_coefficient( monomials, size_of_monomials, coefficients );	//tüm monomial'ler in coefficient'leri coefficients[] array'ine kaydedildi.
	find_exponent( monomials, size_of_monomials, exponents );		//tüm monomial'ler in exponent'leri coefficients[] array'ine kaydedildi.

	get_values = fopen( "values.txt","r" );
	write_results = fopen( "evaluations.txt","w+" );

	while( fscanf( get_values, "%lf", &number ) == 1 )	//buradaki döngü ile values.txt dosyasından alınan tüm değerler polinomda x yerine konolup hesaplanarak
	{													//evaluations array'ine yazıldı.
		result_of_polynom = 0;
		for( i = 0; i < size_of_monomials; i++ )
		{
			result_of_polynom = result_of_polynom + calculate_monomial( number, signs[i], coefficients[i], exponents[i] );
		}
		fprintf( write_results, "%.2f\n", result_of_polynom );
	}
	fclose( get_values );
	fclose( write_results );
}

void
remove_spaces( char polinom[] )
{
	int i, top = 0;
	char temp[1000];
	for( i = 0; i < strlen( polinom ); i++ )
	{
		if( polinom[i] != ' ' && polinom[i] != '	' && polinom[i] != 10 )
		{
			temp[top] = polinom[i];
			top++;
		}
	}
	temp[top] = '\0';

	memcpy( polinom, temp, sizeof(char) * strlen(temp) + 1 );
}



void
find_signs( char arr[], sign signs[], int *size_signs )
{
	int i, top = 1, beginning;

	for( i = 0; i < strlen(arr); i++ ) // bu döngü sadece ilk monomial'in işaretini belirlemek için kullanılır.
	{
		if( arr[i] == '+' )
		{
			signs[0] = plas;
			beginning = i + 1;
			*size_signs += 1;
			break;
		}

		else if( arr[i] == '-' )
		{
			signs[0] = minus;
			beginning = i + 1;
			*size_signs += 1;
			break;
		}

		else if ( arr[i] == 'x' )
		{
			signs[0] = plas;
			beginning = i + 1;
			*size_signs += 1;
			break;
		}

	}

	for( i = beginning; i < strlen( arr ); i++ )	//ikinci monomial ve sonraki monomial'llerin işaretleri bu dngü ile elde ediir.
	{
		if( arr[i] == '+' )
		{
			signs[ top ] = plas;
			top++;
			*size_signs += 1;
		}

		else if( arr[i] == '-' )
		{
			signs[ top ] = minus;
			top++;
			*size_signs += 1;
		}
	}
}


void
find_coefficient( char monomials[][30], int size, double coefficients[] )
{
	int i,j,top;
	char temp[30];
	for( i = 0; i < size; i++ )
	{
		top = 0;
		for( j = 0; j < strlen( monomials[i] ); j++ )
		{
			if( monomials[i][j] != 'x')
			{
				temp[top] = monomials[i][j];
				top++;
			}
			else break;
		}
		temp[j] = '\0';
		if( 1 != sscanf( temp, "%lf", (coefficients + i) ) ) coefficients[i] = 1.0;
	}
}


void
find_exponent( char monomials[][30], int size, int exponents[] )
{
	int i, j, place_exp_sign, top;
	char temp[30];

	for( i = 0; i < size; i++ )
	{
		place_exp_sign = 0;
		for( j = 0; j < strlen( monomials[i] ); j++ )
		{
			if( monomials[i][j] == '^' ) break;
			place_exp_sign++;
		}

		top = 0;
		for( j = (place_exp_sign + 1); j < strlen( monomials[i] ); j++ )
		{
			temp[top] = monomials[i][j];
			top++;
		}
		temp[top] = '\0';
		if( 1 != sscanf( temp, "%d", (exponents + i) ) ) exponents[i] = 1;
	}
}

double
calculate_monomial( double number, sign sign_monomial, double coefficient, int exponent )
{
	double result;

	if( sign_monomial == plas )
	{
		result = +1 * coefficient * pow( number, exponent );
		return result;
	}

	else if( sign_monomial == minus )
	{
		result = -1 * coefficient * pow( number, exponent );
		return result;
	}
}


