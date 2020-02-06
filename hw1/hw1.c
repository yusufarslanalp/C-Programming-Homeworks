#include <stdio.h>


int
is_location_legal( double deedctor_center_x, double dedector_center_y ,double latitude_of_dedector, double longditude_of_dedector, double latitude_of_plane, double longditude_of_plane );

void
find_intersection_points( double marked_center_point, double marked_axsis_legth, double dedector_center_point, double dedector_axis_length,double *smaler_max_axis, double *bigger_min_axis );

double
find_min( double num1, double num2 );

double
find_max( double num1, double num2 );



//** BU PROGRAMDAKİ X ve Y KORDİNATLARI ANALİTİK DÜZLEMDEKİ 1.BÖLGEYE GÖRE TASARLANMIŞTIR. **//

int
main(void)
{
	int attemps_remaining = 6;
	double dedector_center_x, dedector_center_y, latitude_of_dedector = 60, longditude_of_dedector = 60; //DEDEKTÖR BİLGİLERİ BU SATIRDAN DÜZENLENİLEBİLİR.
	double latitude_of_plane = 200, longditude_of_plane = 200;	//PLANE BİLGİLERİ BU SATIRDAN DÜZENLENİLEBİLİR.
	double marked_center_x = 10, marked_center_y = 10, latitude_of_marked = 20, longditude_of_marked = 20;	//MARKED REGİON BİLGİLERİ BU SATRDAN DÜZENLENİLEBİLİR.
	double intersection_length_x, intersection_length_y;
	double marked_area;
	double intersection_area;
	double bigger_min_axis_x, smaler_max_axis_x, bigger_min_axis_y, smaler_max_axis_y;
	int saved_attemps_remaining = attemps_remaining; //kullanıcının kaç hamlede oyunu bitirdiğini bulabilmek için attems_rmaining değişkeninin ilk değeri kaydedilir.

	printf("Board = [200 x 200], Dedector = [60 x 60], Marked region = [20 x 20]\n");

	while( attemps_remaining > 0 )
	{

		
		printf("enter the x cordinate of dedector center: ");
		scanf( "%lf", &dedector_center_x );
		printf("enter the y cordinate of dedector center: ");
		scanf( "%lf", &dedector_center_y );

		//aşağıdaki if condition'ı girilen dedektör merkez değeri plane'in dışında olduğu durumda kullanıcıdan tekrar merkez değeri alınmasını sağlar.  
		if( is_location_legal( dedector_center_x, dedector_center_y, latitude_of_dedector, longditude_of_dedector, latitude_of_plane, longditude_of_plane ) == 0 )
		{
			marked_area = latitude_of_marked * longditude_of_marked;

			find_intersection_points( marked_center_x, latitude_of_marked, dedector_center_x, latitude_of_dedector, &smaler_max_axis_x, &bigger_min_axis_x );
			find_intersection_points( marked_center_y, longditude_of_marked, dedector_center_y, longditude_of_dedector, &smaler_max_axis_y, &bigger_min_axis_y );

			intersection_length_x = smaler_max_axis_x - bigger_min_axis_x;
			intersection_length_y = smaler_max_axis_y - bigger_min_axis_y;
			intersection_area = intersection_length_x * intersection_length_y;


			if ( intersection_length_x <= 0 || intersection_length_y <= 0 ) 
			{
				latitude_of_dedector = latitude_of_dedector / 2;
				longditude_of_dedector = longditude_of_dedector / 2;
				attemps_remaining = attemps_remaining -1;
				printf("you miss the marked region\n");
			}

			else if ( intersection_area == marked_area )
			{
				attemps_remaining = attemps_remaining -1;
				printf("you win with %d moves\n", saved_attemps_remaining - attemps_remaining);
				return 0;
			}

			else
			{
				marked_center_x = bigger_min_axis_x + ( intersection_length_x / 2 );
				marked_center_y = bigger_min_axis_y + ( intersection_length_y / 2 );

				latitude_of_marked = intersection_length_x;		
				longditude_of_marked = intersection_length_y;		

				latitude_of_dedector = latitude_of_dedector / 2;
				longditude_of_dedector = longditude_of_dedector / 2;

				attemps_remaining = attemps_remaining -1;
				printf( "Partial hit!\nmarked region was shirked to [%.1f x %.1f]\n", latitude_of_marked, longditude_of_marked );
				
				
			}

			printf("your detector was shirked to [%.1f x %.1f]\n", latitude_of_dedector, longditude_of_dedector );
			printf( "remaining attemp: %d\n", attemps_remaining );
		}

		else
		{
			printf("your dedctor is out of plane.please try again\n");
		}

	}
	
	printf("you lost\n");
}

int
is_location_legal( double dedector_center_x, double dedector_center_y, double latitude_of_dedector, double longditude_of_dedector, double latitude_of_plane, double longditude_of_plane )
{
	double left_top_corner_x = dedector_center_x - latitude_of_dedector / 2;		//bu fonksiyon dedektörün plane'in dışına taşıp taşmadığını kontrol eder.
	double left_top_corner_y = dedector_center_y - longditude_of_dedector / 2;		//eğer dedektör plane'in dışına taşıyosa -1 return eder.
	double right_down_corner_x = dedector_center_x + latitude_of_dedector / 2;		//ama eşer dedektör plane'in içindeyse 0 return eder. 
	double right_down_corner_y = dedector_center_y + longditude_of_dedector / 2;

	if ( left_top_corner_x < 0 || left_top_corner_y < 0 ) return -1;
	if( right_down_corner_x > latitude_of_plane || right_down_corner_y > longditude_of_plane ) return -1;

	return 0; 

}

void
find_intersection_points( double marked_center_point, double marked_axsis_legth, double dedector_center_point, double dedector_axis_length,double *smaler_max_axis, double *bigger_min_axis )
{
	/*bu fonksiyon marked region ve dedektörün bir kenarına ait kesişim kordinatlarının bulunmasınısağlar.*/	
	
	/*bu fonksiyon marked_region'ın merkezini ve kenarlarından birinin uzunluğunu paremetre olarak alır.aldığı merkez değerine aldığı kenar uzunluğunun yarısını ekleyerek
ve çıkararak marked_region'ın kenarının uç noktalarını bulur.aynı şekilde kullanıcıdan elde edilen dedektör merkez değerini parametre olarak alır.aldığı merkez değerine
o kenara ait uzunluğun yarısını ekleyerek ve çıkararak dedektürün o kenera ait uç kordinatlarına ulaşır.dedektörün değeri küçük olan uç noktasını marked region'un 
değeri küçük noktasıyla karşılaştırır ve karşılaştırdığı bu noktalardan büyük olanını *bigger_min_axis adlı pointer değişkenine kaydeder. benzer şekilde dedektör'ün değeri 
büyük olan uç noktasını marked_region'ın değeri büyük olan uç noktasıyla karşılaştırır ve bu değerlerden küçük olanını *smaller_max_axis adlı pointer değişkenine kaydeder.   */

	/* *smaller_max_axis değişkeninden bigger min axis değişkeni çıkarıldığında bir kenara ait kesişim uzunluğu bulunur.kesişim kenarlarının uzunluğu bu main 
fonksiyonunda bulunur.*/	



	double dedector_min_axis = dedector_center_point - dedector_axis_length / 2;
	double dedector_max_axis = dedector_center_point + dedector_axis_length / 2;
	double marked_min_axis = marked_center_point - marked_axsis_legth / 2;
	double marked_max_axis = marked_center_point + marked_axsis_legth / 2;

	*bigger_min_axis = find_max( marked_min_axis, dedector_min_axis );
	*smaler_max_axis = find_min( marked_max_axis, dedector_max_axis );


}

double
find_min( double num1, double num2 )
{
	if( num1 < num2 ) return num1;	//bu fonksiyon iki tane double sayı lır ve bu sayılardan küçük olanı return eder.
	else return num2;
}

double
find_max( double num1, double num2 )
{
	if( num1 > num2 ) return num1;	//bu fonksiyon iki tane double sayı lır ve bu sayılardan büyük olanı return eder.
	else return num2;
}
