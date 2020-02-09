#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum { input, and, or, not, flipflop } operation_type;

/* nodes[] array'i aşağıda tanımlanan struct'ın tipinde bir array'dir. nodes[] array'inin eleman sayısı; "circuit.txt" dosyasında bulunan tüm input değişkenlerinin ve tüm gate'lerin toplamına eşittir. nodes[] array'i nin elemansayısı "circuit.txt" dosyası okunduktan sonra dinamik olarak belirlenmektedir. Örnek olarak "circuit.txt" dosyasında 5 adet input değişkeni 2 adet "and" gate'i 2 adet "or" gate'i 1 adet "flipflop" gate'i ve 1 adet "not" gate'i varsa nodes[] array'inin eleman sayısı = 5 + 2+ 2 + 1 + 1 = 11 dir.    */

typedef struct
{
	operation_type type;	//type değişkeni bir node'un "and" , "not", "input" gibi hangi tipte değişken olduğunun bilgisini tutar.
	char name[30];			
	int value;				
	char first_element_name[30];	//first_element_name[] karakter array'i "and" ve "or" kapılarına bağlanan ilk node'un veya ilk inputun adını tutar. first_element_name[] karakter array'i "not" ve "flipflop" gate' lerine bağlanan input'un veya gate'in adını tutar.
 	char second_element_name[30]; //first_element_name[] karakter array'i "and" ve "or" kapılarına bağlanan ikinci node'un veya ikinci inputun adını tutar.
	int previous_value;	//previous value "flipflop" gate'i nin önceki değerini tutar.
} circuit_node_t;

int
count_nodes( char file_name[] , int *number_of_inputs); 

void
fill_nodes( char file_name[], circuit_node_t nodes[]   );

int
find_place( char name[] , circuit_node_t nodes[] , int size );

void
find_output_pin( char output_name[] , circuit_node_t nodes[] , int size );

int
evaluate_output( char node_name[] , circuit_node_t nodes[] , int size );

void
fill_input_and_print_evaluation( char file_name[] , int number_of_inputs , char node_name[] , circuit_node_t nodes[] , int size );


int
main(void)
{

	circuit_node_t *nodes;
	char file[15] = "circuit.txt";
	char input_file[15] = "input.txt";
	int number_of_nodes;
	char output_name[30];
	int number_of_inputs;
	char line[ 100 ];

	number_of_nodes = count_nodes( file , &number_of_inputs );
	nodes = (circuit_node_t *) malloc( number_of_nodes * sizeof( circuit_node_t ) );
	fill_nodes( file , nodes );
	find_output_pin( output_name , nodes , number_of_nodes );
	fill_input_and_print_evaluation( input_file , number_of_inputs , output_name , nodes , number_of_nodes );

	free( nodes );
}

//"circuit.txt" dosyasında bulunan tüm input değişkenlerinin ve tüm gate'lerin sayısının toplamını bularak return eder. Input'ların sayısını *number_of_inputs pointer'ına kaydeder.
int
count_nodes( char file_name[] , int *number_of_inputs )
{
	FILE *fp;
	char line[100];
	char word[50];
	char *token;
	int number_of_nodes = 0;
	*number_of_inputs = 0;

	fp = fopen( file_name , "r" );
	
	while( fgets( line, 100, fp ) != NULL )
	{
		word[0] = '\0';
		sscanf( line , "%s", word );
		if( strcmp( "INPUT" , word ) == 0 )
		{
			token = strtok( line, " 	" );
			while( token != NULL )
			{
				token = strtok( NULL , " 	" );
				if( token != NULL )
				{
					number_of_nodes++;
					*number_of_inputs = *number_of_inputs + 1;
				}
			}
		}

		else if( strcmp( "AND" , word ) == 0 )
		{
			number_of_nodes++;
		}

		else if( strcmp( "OR" , word ) == 0 )
		{	
			number_of_nodes++;
		}

		else if( strcmp( "NOT" , word ) == 0 )
		{
			number_of_nodes++;
		}

		else if( strcmp( "FLIPFLOP" , word ) == 0 )
		{
			number_of_nodes++;
		}
	}
	fclose( fp );

	return number_of_nodes;
}

/* Bu fonksiyon nodes[] array'inin elemanlarını dolduran fonksiyondur.

Bu fonksiyon input değişkeni için nodes[] array'inin type değişkenini input tipi olarak doldurur ve değiken adını name[] karakter array'ine yazar.

Bu fonksiyon and gate'i için nodes[] array'inin type değişkenini and tipi olarak doldurur. first_element_name[] ve second_element_name[] karakter arrayler'ine and gate'inin aldığı input'un adını veya gate'lerin adını yazar.and gate'inin adını name[] karakter array'ine yazar.

Bu fonksiyon or gate'i için nodes[] array'inin type değişkenini or tipi olarak doldurur. first_element_name[] ve second_element_name[] karakter arrayler'ine and gate'inin aldığı input'un adını veya gate'in adını yazar. or gate'inin adını name[] karakter array'ine yazar.

Bu fonksiyon not gate'i için nodes[] array'inin type değişkenii not tipi olarak doldurur. first_element_name[] karakter array'ine not gate'inin aldığı input'un adını veya gate'in adını yazar.

Bu fonksiyon flipflop gate'i için nodes[] array'inin type değişkenii flipflop tipi olarak doldurur. first_element_name[] karakter array'ine flipflop gate'inin aldığı input'un adını veya gate'in adını yazar. previous value değerini bir defa olmak üzere sıfır yapar.  */
void
fill_nodes( char file_name[], circuit_node_t nodes[]   )
{
	FILE *fp;
	char line[100];
	char word[50];
	char *token;
	int order = 0;

	fp = fopen( file_name , "r" );
	
	while( fgets( line, 100, fp ) != NULL )
	{
		word[0] = '\0';
		sscanf( line , "%s", word );

		if( strcmp( "INPUT" , word ) == 0 )   
		{									
			token = strtok( line, " 	\n" );
			while( token != NULL )
			{
				token = strtok( NULL , " 	\n" );
				if( token != NULL )
				{
					nodes[order].type = input;
					strncpy( nodes[order].name , token , (strlen(token) + 1) );
					nodes[order].first_element_name[0] = '\0';
					nodes[order].second_element_name[0] = '\0';
					order++;
				}
			}
		}

		else if( strcmp( "AND" , word ) == 0 )
		{
			nodes[order].type = and;
			token = strtok( line, " 	\n" );
			token = strtok( NULL , " 	\n" );
			strncpy( nodes[order].name , token , (strlen(token) + 1) );
			token = strtok( NULL , " 	\n" );
			strncpy( nodes[order].first_element_name , token , (strlen(token) + 1) );
			token = strtok( NULL , " 	\n" );
			strncpy( nodes[order].second_element_name , token , (strlen(token) + 1) );
			order++;
		}

		else if( strcmp( "OR" , word ) == 0 )
		{	
			nodes[order].type = or;
			token = strtok( line, " 	\n" );
			token = strtok( NULL , " 	\n" );
			strncpy( nodes[order].name , token , (strlen(token) + 1) );
			token = strtok( NULL , " 	\n" );
			strncpy( nodes[order].first_element_name , token , (strlen(token) + 1) );
			token = strtok( NULL , " 	\n" );
			strncpy( nodes[order].second_element_name , token , (strlen(token) + 1) );
			order++;			
		}

		else if( strcmp( "NOT" , word ) == 0 )
		{
			nodes[order].type = not;
			token = strtok( line, " 	\n" );
			token = strtok( NULL , " 	\n" );
			strncpy( nodes[order].name , token , (strlen(token) + 1) );
			token = strtok( NULL , " 	\n" );
			strncpy( nodes[order].first_element_name , token , (strlen(token) + 1) );
			nodes[order].second_element_name[0] = '\0';
			order++;			
		}

		else if( strcmp( "FLIPFLOP" , word ) == 0 )
		{
			nodes[order].type = flipflop;
			token = strtok( line, " 	\n" );
			token = strtok( NULL , " 	\n" );
			strncpy( nodes[order].name , token , (strlen(token) + 1) );
			token = strtok( NULL , " 	\n" );
			strncpy( nodes[order].first_element_name , token , (strlen(token) + 1) );
			nodes[order].previous_value = 0;
			nodes[order].second_element_name[0] = '\0';
			order++;			
		}
	}
	fclose( fp );
}


//Bu fonksiyon input veya gate'lerden birinin adını name[] parametresi olarak alır ve name[] adındaki gate'in veya inputun yerini nodes[] array'inde bularak return eder.
int
find_place( char name[] , circuit_node_t nodes[] , int size )
{
	int i;

	for( i = 0; i < size; i++ )
	{
		if( strcmp( name, nodes[i].name ) == 0 ) 
		{
			return i;
		}
	}
}

//Bu fonksiyon nodes[] array'ideki output_pin'i bulur ve output_pin'in adını parametre olarak aldığı output_name[] array'ine yazar.
void
find_output_pin( char output_name[] , circuit_node_t nodes[] , int size )
{
	int i, j;
	int is_output_pin;

	for( i = 0; i < size; i++ )
	{
		is_output_pin = 1;
		for( j = 0; j < size; j++ )
		{
			if( ( strcmp( nodes[i].name , nodes[j].first_element_name ) == 0  ) ||  ( strcmp( nodes[i].name , nodes[j].second_element_name ) == 0  ) )
			{
				is_output_pin = 0;
				break;
			}
		}

		if( is_output_pin == 1 )
		{
			strcpy( output_name , nodes[i].name );
			break;
		}
	}
}


//Bu fonksiyon output_pin node'unun ismini node_name[] parametresi ile alır ve nodes[] arrayinin oluşturduğu lojik devrenin sonucunu "recursive" kullanarak hesaplar.
int
evaluate_output( char node_name[] , circuit_node_t nodes[] , int size )
{
	int i;
	int previous;
	i = find_place( node_name , nodes , size );

	if( nodes[i].type == input ) return nodes[i].value;

	else
	{
		if( nodes[i].type == and )
		{
			return ( evaluate_output( nodes[i].first_element_name , nodes , size ) && evaluate_output( nodes[i].second_element_name , nodes , size ) );
		}

		else if( nodes[i].type == or )
		{
			return ( evaluate_output( nodes[i].first_element_name , nodes , size ) || evaluate_output( nodes[i].second_element_name , nodes , size ) );
		}

		else if( nodes[i].type == not )
		{
			return !( evaluate_output( nodes[i].first_element_name , nodes , size ) );
		}

		else if( nodes[i].type == flipflop )
		{
			previous = ( evaluate_output( nodes[i].first_element_name , nodes , size ) != nodes[i].previous_value );
			nodes[i].previous_value = previous;
			return previous;
		}
	}
}

//Bu fonksiyon "input.txt" dosyasından aldığı değerleri nodes[] array'indeki input'ların value değerlerine yazar ve evaluate_output() fonksiyonunu kullanarak devrenin sonucunu hesaplayıp ekrana basar. Bu işlemi "input.txt" dosyasında okunacak değer kalmayıncaya kadar tekrar eder.
void
fill_input_and_print_evaluation( char file_name[] , int number_of_inputs , char node_name[] , circuit_node_t nodes[] , int size )
{
	FILE *fp;
	char *token;
	char line[100];
	int num;
	int i = 0;
	int result;
	fp = fopen( "input.txt", "r" );

	while( fscanf(fp, "%d", &num) == 1 )
	{
		nodes[i].value = num;
		i++;
		if( i == number_of_inputs )
		{
			result = evaluate_output( node_name , nodes , size );
			printf( "%d\n", result );
			i = 0;
		}
	}
	fclose( fp );
}

