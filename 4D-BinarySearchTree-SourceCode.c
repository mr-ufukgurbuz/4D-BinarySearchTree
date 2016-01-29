/* UFUK GURBUZ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

struct agacDugumu {
	struct agacDugumu *solPtr;
	int id;
	char name[30];						// Tree Struct
	char surname[30];
	int internday;
	int depth;
	char sayi[1000];
	struct agacDugumu *sagPtr;
};

typedef struct agacDugumu AgacDugumu;
typedef AgacDugumu *AgacDugumuPtr;

void dugumEkle( AgacDugumuPtr *, int, char *, char *, int, int );
void preOrder( AgacDugumuPtr, char * );
void inOrder( AgacDugumuPtr, char * );
void postOrder( AgacDugumuPtr, char * );
void selectedSearch( AgacDugumuPtr, char *, char, char *, char, int, char, int, char, char * );
void sayiEsitle( AgacDugumuPtr *agacPtr, char *kopyalanacak,char *eklenecek );
int binaryToDecimal( int );

FILE *cf2Ptr;

int main()
{
	system("color 17");
	
	int id;
	char name[30];
	char surname[30];
	int internday;
	
	AgacDugumuPtr rootPtr = NULL;
	
	FILE *cfPtr;
	
	if ( ( cfPtr = fopen( "input.txt", "r" ) ) == NULL ){
		printf( "Input dosyasi acilamadi !\n" );				// Input file
		exit(0);
	}
	//////////
	if ( ( cf2Ptr = fopen( "output.txt", "w" ) ) == NULL ){
		printf( "Output dosyasi acilamadi !\n" );				// Output file
		exit(0);
	}
	///////////
	printf("			   << DATAS FROM INPUT >>\n\n");
	printf( " 		%-10s%-13s%-13s%s\n", "Id", "Name", "Surname", "Internday" );
	printf( " 		----------------------------------------------\n\n" );
	
	fprintf( cf2Ptr, "%-10s%-13s%-13s%s\n", "Id", "Name", "Surname", "Internday" );
	fprintf( cf2Ptr, "----------------------------------------------\n\n" );
	
	while ( !feof( cfPtr ) ) {
		fscanf( cfPtr, "%d%s%s%d", &id, name, surname, &internday);
		printf( " 		%-10d%-13s%-13s%5.2d\n", id, name, surname, internday);			// Inputtan okur, console a yazar
		fprintf( cf2Ptr, "%-10d%-13s%-13s%5.2d\n", id, name, surname, internday);		// Inputtan okur, outputa yazar ve treeye ekler.
		dugumEkle( &rootPtr, id, name, surname, internday, 0);
	}
	fclose(cfPtr);
	
	sayiEsitle( &rootPtr, "1", "" );
	
	char buffer[100]="The data was read from file and the tree was created.";
	MessageBox(NULL, buffer, "Display", MB_ICONINFORMATION );							// MessageBox ile text goruntuleme
	
	
	char array[15000], array2[15000], array3[15000];
	
	/* aðaçta preOrder biçiminde ilerle*/
	fprintf( cf2Ptr, "\n\npreOrder(NLR) ilerleme :\n\n" );
	fprintf( cf2Ptr, "%5s%8s %6s%15s%16s%17s\n","Depth", "Number", "Id", "Name", "Surname", "Internday" );		// preOrder sekilde traverse yapar.
	fprintf( cf2Ptr, "--------------------------------------------------------------------\n\n" );
	preOrder( rootPtr, array );
	
	/* aðaçta inOrder biçiminde ilerle*/
	fprintf( cf2Ptr, "\n\ninOrder(LNR) ilerleme :\n\n" );
	fprintf( cf2Ptr, "%5s%8s %6s%15s%16s%17s\n","Depth", "Number", "Id", "Name", "Surname", "Internday" );		// inOrder sekilde traverse yapar.
	fprintf( cf2Ptr, "--------------------------------------------------------------------\n\n" );
	inOrder( rootPtr, array2 );
	
	/* aðaçta postOrder biçiminde ilerle */
	fprintf( cf2Ptr, "\n\npostOrder(LRN) ilerleme:\n\n" );
	fprintf( cf2Ptr, "%5s%8s %6s%15s%16s%17s\n","Depth", "Number", "Id", "Name", "Surname", "Internday" );		// postOrder sekilde traverse yapar.
	fprintf( cf2Ptr, "--------------------------------------------------------------------\n\n" );
	postOrder( rootPtr, array3 );
	
	printf("\n ------------------------------------------------------------------------------");
	printf("\n			   << VIEWING TRAVERSE >>\n");
	char dizi[20000], dizi2[20000], dizi3[20000];				// Choosing preOrder, inOrder, postOrder
	char secim; printf("\n Please enter \"0\" for \"preOrder\" results, \"1\" for \"inOrder\" results,\n \"2\" for \"preOrder\" results: "); scanf("%c", &secim);
	
	if( secim == '0'){
		sprintf( dizi, "%s    %s \t        %s\t\t%s\t\t%s \t              %s\n%s\n\n%s", 
				"Depth", "Number", "Id", "Name", "Surname", "Internday", 
				"--------------------------------------------------------------------------------------------------", array );

		MessageBox(NULL, dizi, "preOrder Results", NULL);
	}
	else if( secim == '1'){
		sprintf( dizi2, "%s    %s \t        %s\t\t%s\t\t%s \t              %s\n%s\n\n%s", 
				"Depth", "Number", "Id", "Name", "Surname", "Internday", 
				"--------------------------------------------------------------------------------------------------", array2 );

		MessageBox(NULL, dizi2, "inOrder Results", NULL);
	}
	else{
		sprintf( dizi3, "%s    %s \t        %s\t\t%s\t\t%s \t              %s\n%s\n\n%s", 
				"Depth", "Number", "Id", "Name", "Surname", "Internday", 
				"--------------------------------------------------------------------------------------------------", array3 );

		MessageBox(NULL, dizi3, "postOrder Results", NULL);
	}
	
	printf("\n ------------------------------------------------------------------------------");
	printf("\n			   << FILTERING DATAS >>\n");
	
	char namecmp, surnamecmp, idcmp, interndaycmp;
	
	printf( "\n Please enter name, surname, id number and numbers of intern day for filtering\n");							// ------
	printf( " ----------------------------------------------------------------------------\n");				
	
	fprintf( cf2Ptr, "\n\n\nPlease enter name, surname, id number and numbers of intern day\n");
	fprintf( cf2Ptr, "-----------------------------------------------------------------\n");				// Kullanicidan isim, soyisim, id, staj alma
																										
	fprintf( cf2Ptr, "Name: ");		printf( " Name: ");		 scanf("%s", name);		fprintf( cf2Ptr, "%s", name);
	////Character Name
	fprintf( cf2Ptr, "\nEnter \'G\' for greater, \'L\' for less: "); 
	printf( "\n Enter \'G\' for greater, \'L\' for less: "); 	
	scanf("%c", &namecmp);
	if( namecmp == '\n')
		scanf("%c", &namecmp);	
	fprintf( cf2Ptr, "%c", namecmp);
	/////
	fprintf( cf2Ptr, "\nSurname: ");	printf( "\n Surname: ");	 scanf("%s", surname);		fprintf( cf2Ptr, "%s", surname);
	////Character Surname
	fprintf( cf2Ptr, "\nEnter \'G\' for greater, \'L\' for less: "); 
	printf( "\n Enter \'G\' for greater, \'L\' for less: "); 	
	scanf("%c", &surnamecmp);	
	if( surnamecmp == '\n')
		scanf("%c", &surnamecmp); 
	fprintf( cf2Ptr, "%c", surnamecmp);
	/////
	fprintf( cf2Ptr, "\nId Number: "); 		printf( "\n Id Number: ");		scanf("%d", &id);		fprintf( cf2Ptr, "%d", id);
	////Character Id
	fprintf( cf2Ptr, "\nEnter \'G\' for greater, \'L\' for less: "); 
	printf( "\n Enter \'G\' for greater, \'L\' for less: "); 	
	scanf("%c", &idcmp);	
	if( idcmp == '\n')
		scanf("%c", &idcmp); 
	fprintf( cf2Ptr, "%c", idcmp);
	/////
	fprintf( cf2Ptr, "\nNumber of Intern day: "); printf( "\n Number of Intern day: ");	scanf("%d", &internday);	fprintf( cf2Ptr, "%d", internday);
	////Character Internday
	fprintf( cf2Ptr, "\nEnter \'G\' for greater, \'L\' for less: "); 
	printf( "\n Enter \'G\' for greater, \'L\' for less: "); 	
	scanf("%c", &interndaycmp);	
	if( interndaycmp == '\n')
		scanf("%c", &interndaycmp); 
	fprintf( cf2Ptr, "%c", interndaycmp);																			//----------
	/////
	
	fprintf( cf2Ptr, "\n\n%5s%8s %6s%15s%16s%17s\n", "Depth", "Number", "Id", "Name", "Surname", "Internday" );
	fprintf( cf2Ptr, "--------------------------------------------------------------------\n\n" );
	
	
	char buffer2[20000];
	char buffer3[14000];
	// Kosula gore output dosyasina yazdirma																							
	selectedSearch( rootPtr, name, namecmp, surname, surnamecmp, id, idcmp, internday, interndaycmp, buffer3 );
	fclose(cf2Ptr);
	
	
	sprintf( buffer2, "%s    %s \t      %s \t\t %s \t                %s  %s\n%s\n\n%s", 
				"Depth", "Number", "Id", "Name", "Surname", "Internday", 
				"--------------------------------------------------------------------------------------", buffer3 );

	MessageBox(NULL, buffer2, "Filtered Results", NULL);
	
	return 0;
}

void dugumEkle( AgacDugumuPtr *agacPtr, int numara, char * isim, char * soyisim, int staj, int derinlik )
{
	if ( *agacPtr == NULL ) { /* *agacPtr NULL’dur */
		*agacPtr = malloc( sizeof( AgacDugumu ) );
		
		if ( *agacPtr != NULL ) {
			( *agacPtr )->solPtr = NULL;
			( *agacPtr )->id = numara;
			strcpy( ( *agacPtr )->name, isim );
			strcpy( ( *agacPtr )->surname, soyisim );				// Dugum olusturma
			( *agacPtr )->internday = staj;
			( *agacPtr )->depth = derinlik;
			strcpy( ( *agacPtr )->sayi , "1" );			// !!!!!!!!!!!!
			( *agacPtr )->sagPtr = NULL;
		}
		else
			printf( "Kayit eklenemedi. Yetersiz hafýza.\n");
	}
	else
	
	    if ( ( *agacPtr )->depth %4 == 0 ){		//**********
		
			if ( strcasecmp( isim , ( *agacPtr )->name ) < 0 )
				dugumEkle( &( ( *agacPtr )->solPtr ), numara, isim, soyisim, staj, ++derinlik );		// Ýsme gore ekle
			else if ( strcasecmp( isim , ( *agacPtr )->name ) > 0 )
				dugumEkle( &( ( *agacPtr )->sagPtr ), numara, isim, soyisim, staj, ++derinlik );
			else
				fprintf( cf2Ptr, "Same name !\n" );
		}
		
		else if ( ( *agacPtr )->depth %4 == 1 ){		//**********
		
			if ( strcasecmp( soyisim , ( *agacPtr )->surname ) < 0 )
				dugumEkle( &( ( *agacPtr )->solPtr ), numara, isim, soyisim, staj, ++derinlik );
			else if ( strcasecmp( soyisim , ( *agacPtr )->surname ) > 0 )									// Soyisime gore ekle
				dugumEkle( &( ( *agacPtr )->sagPtr ), numara, isim, soyisim, staj, ++derinlik );
			else
				fprintf( cf2Ptr, "Same surname !\n" );
		}
		
		else if ( ( *agacPtr )->depth %4 == 2 ){		//**********
			
			if ( numara < ( *agacPtr )->id )
				dugumEkle( &( ( *agacPtr )->solPtr ), numara, isim, soyisim, staj, ++derinlik );
			else if ( numara > ( *agacPtr )->id )															// Numaraya gore ekle
				dugumEkle( &( ( *agacPtr )->sagPtr ), numara, isim, soyisim, staj, ++derinlik );
			else
				fprintf( cf2Ptr, "Same id number !\n" );
		}

		
		else if ( ( *agacPtr )->depth %4 == 3 ){		//**********
		
			if ( staj < ( *agacPtr )->internday )
				dugumEkle( &( ( *agacPtr )->solPtr ), numara, isim, soyisim, staj, ++derinlik );
			else if ( staj > ( *agacPtr )->internday )														// Staja gore ekle
				dugumEkle( &( ( *agacPtr )->sagPtr ), numara, isim, soyisim, staj, ++derinlik );
			else
				fprintf( cf2Ptr, "Same number of intern day !\n" );
		}
}

void preOrder( AgacDugumuPtr agacPtr, char *array )		/* NLR Gezinme(Traverse) */
{
	
	if ( agacPtr != NULL ) {
		fprintf( cf2Ptr, "%2d       %-2d    %-16d%-13s%-13s%7.2d\n",agacPtr->depth, binaryToDecimal(atoi(agacPtr->sayi)), agacPtr->id, agacPtr->name, agacPtr->surname, agacPtr->internday );
		sprintf( array, "%s %d \t %d \t %d \t %s \t\t %s\t\t%d\t\n", array, agacPtr->depth, binaryToDecimal(atoi(agacPtr->sayi)), agacPtr->id, agacPtr->name, agacPtr->surname, agacPtr->internday );
		preOrder( agacPtr->solPtr, array );
		preOrder( agacPtr->sagPtr, array );
	}
}

void inOrder( AgacDugumuPtr agacPtr, char *array2 )		/* LNR Gezinme(Traverse) */
{
	
	if ( agacPtr != NULL ) {
		inOrder( agacPtr->solPtr, array2 );
		fprintf( cf2Ptr, "%2d       %-2d    %-16d%-13s%-13s%7.2d\n",agacPtr->depth, binaryToDecimal(atoi(agacPtr->sayi)), agacPtr->id, agacPtr->name, agacPtr->surname, agacPtr->internday );
		sprintf( array2, "%s %d \t %d \t %d \t %s \t\t %s\t\t%d\t\n", array2, agacPtr->depth, binaryToDecimal(atoi(agacPtr->sayi)), agacPtr->id, agacPtr->name, agacPtr->surname, agacPtr->internday );
		inOrder( agacPtr->sagPtr, array2 );
	}
}

void postOrder( AgacDugumuPtr agacPtr, char *array3 )		/* LRN Gezinme(Traverse) */
{
	
	if ( agacPtr != NULL ) {
		postOrder( agacPtr->solPtr, array3 );
		postOrder( agacPtr->sagPtr, array3 );
		fprintf( cf2Ptr, "%2d       %-2d    %-16d%-13s%-13s%7.2d\n",agacPtr->depth, binaryToDecimal(atoi(agacPtr->sayi)), agacPtr->id, agacPtr->name, agacPtr->surname, agacPtr->internday );
		sprintf( array3, "%s %d \t %d \t %d \t %s \t\t %s\t\t%d\t\n", array3, agacPtr->depth, binaryToDecimal(atoi(agacPtr->sayi)), agacPtr->id, agacPtr->name, agacPtr->surname, agacPtr->internday );
	}
}

void selectedSearch( AgacDugumuPtr agacPtr, char *isim, char isimcmp, char *soyisim, char soyisimcmp, int numara, char numaracmp, int staj, char stajcmp, char *buffer3 )
{
	int a,b,c,d;

	if ( agacPtr != NULL ) {
		selectedSearch( agacPtr->solPtr, isim, isimcmp, soyisim, soyisimcmp, numara, numaracmp, staj, stajcmp, buffer3 );
		
		if( isimcmp == 'G'){ a = ( strcasecmp(agacPtr->name, isim) > 0 ); }			// Isim icin buyukluk kucukluk durumu
		else { a = ( strcasecmp(agacPtr->name, isim) < 0 ); }
		
		if( soyisimcmp == 'G'){ b = ( strcasecmp(agacPtr->surname, soyisim) > 0 ); }		// Soyisim icin buyukluk kucukluk durumu
		else { b = ( strcasecmp(agacPtr->surname, soyisim) < 0 ); }
		
		if( numaracmp == 'G'){ c = ( (agacPtr->id) > numara ); }			// Numara icin buyukluk kucukluk durumu
		else { c = ( (agacPtr->id) < numara ); }
		
		if( stajcmp == 'G'){ d = ( (agacPtr->internday) > staj ) ; }		// Staj icin buyukluk kucukluk durumu
		else { d = ( (agacPtr->internday) < staj ) ; }
		
		
		if( a && b && c && d ){									// Uygun ifadelerin yazdirilmasi
			fprintf( cf2Ptr, "%2d       %-2d    %-16d%-13s%-13s%7.2d\n",agacPtr->depth, binaryToDecimal(atoi(agacPtr->sayi)), agacPtr->id, agacPtr->name, agacPtr->surname, agacPtr->internday );
			sprintf( buffer3, "%s %d\t%d\t%d \t%s\t\t%s \t       %d\n", buffer3, agacPtr->depth, binaryToDecimal(atoi(agacPtr->sayi)), agacPtr->id, agacPtr->name, agacPtr->surname, agacPtr->internday );
		} 
		
		
		selectedSearch( agacPtr->sagPtr, isim, isimcmp, soyisim, soyisimcmp, numara, numaracmp, staj, stajcmp, buffer3 );
	}
}

void sayiEsitle( AgacDugumuPtr *agacPtr, char *kopyalanacak, char *eklenecek ){		/* Function to adding "0" for left or "1" for right*/
	if ( *agacPtr != NULL ) {
		strcpy( (*agacPtr)->sayi, kopyalanacak );
		strcat( (*agacPtr)->sayi, eklenecek );
		
		sayiEsitle( &( (*agacPtr)->solPtr), (*agacPtr)->sayi, "0" );
		
		sayiEsitle( &( (*agacPtr)->sagPtr), (*agacPtr)->sayi, "1" );
	}
}

int binaryToDecimal( int n ){		/* Function to convert binary to decimal.*/
    int decimal=0, i=0, rem;
    while (n!=0)
    {
        rem = n%10;
        n/=10;
        decimal += rem*pow(2,i);
        ++i;
    }
    return decimal;
}
