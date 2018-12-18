/*
 ============================================================================
 Name        : ParabolicTrajectory.c
 Author      : Zuzanna Santorowska
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_N_OBSTAC 100
#define PI 3.141592654
#define STANDARD_GRAVITY 9.80665

typedef struct obstacle{
	int dist;//distance
	int high;//hight
}obstacle;

double parabole( int dist, int high, int range )
{
	double d = (double) dist;
	double h = (double) high;
	double r = (double) range;
	if( dist > range )
		return 1;//tg(45)=1
	return ( h / ( d * ( 1 - ( d / ( 2 * r ) ) ) ) );
}

double max(double a, double b)
{
	if( a > b )
		return a;
	else
		return b;
}

int readCoordinate(bool *eof)
{
	char *h = malloc(10*sizeof(char));
	scanf("%10s", h);
	int j = 0, w = 0;
	while( j < 10 )
	{
		if( h[j] == '\0' ){
			break;
		}
		else if(! (( h[j] >= '0' ) && ( h[j] <= '9' )) ){
			puts("To nie liczba!");
			return -1;
		}
		w = w*10 + (h[j] - 48);
		j++;
	}
	char c = getchar();//wczytaj biały znak
	c = getchar();
	if(c == EOF){
		(*eof) = true;
	}
	else{
		ungetc(c, stdin);
	}
	return w;
}

obstacle* getObstacles ()
{
	bool eof = false;
	obstacle *arr = malloc(MAX_N_OBSTAC * sizeof(obstacle));
	puts("Please, enter coordinates of obstacles");

	for(int i = 0; i < MAX_N_OBSTAC; i++)
	{
		if(!eof){
			arr[i].dist = readCoordinate(&eof);
			if(!eof)
				arr[i].high = readCoordinate(&eof);
			else{
				printf("Dla odległości %d nie ma wysokości!", arr[i].dist);
				exit -1;
			}
		}
		else{
			arr[i].dist = -1;
			arr[i].high = -1;
		}
	}
	return arr;
}

int findRange( obstacle *arr )
{
	int i = 0;
	while( ( i < MAX_N_OBSTAC ) && ( arr[i].dist != -1 ) && ( arr[i].high != -1 ) )
	{
		if( arr[i].high == 0 )
			return arr[i].dist;
		i++;
	}
	return -1;
}

double findBigestAngle( obstacle *arr, int *r )
{
	double tanA = 1.0;//shortest way without obstacles is when alpha=45 degrees so tg alpha=1
	int range = findRange(arr);
	if(range == -1){
		puts("You didn't give range!");
		exit -1;
	}

	int i = 0;
	while( ( i < MAX_N_OBSTAC ) && ( arr[i].dist != -1 ) && ( arr[i].high != -1 ) )
	{
		tanA = max( parabole( arr[i].dist, arr[i].high, range ) , tanA );

		i++;
	}
	(*r)=range;
	return  atan(tanA);
}

double getSpeedFromAngle( double angle, int range )
{
	double r = (double) range;
	double x =  r *  STANDARD_GRAVITY / sin( 2 * angle );
	return ( sqrt( x ) );
}

int main(int argc, char* argv[]) {

	obstacle *arr = getObstacles();
	int range;
	double mangle = findBigestAngle(arr, &range);//angle is in radians
	double speed0 = getSpeedFromAngle(mangle, range);
	printf("Speed0 = %lf Angle = %lf", speed0, (mangle * 180 ) / PI);

	/*for( int i = 0; i < MAX_N_OBSTAC; i++)
	{
		printf("x:%d y:%d", arr[i].dist, arr[i].high);
	}*/



//	char c[50];
//	int i=0;
//	c[0] = getchar() -48;
//	while((i<50)&&(c[i-1]!=EOF))
//	{
//		c[i] = getchar() -48;
//		i++;
////	}
//	for( int i=0; i<50; i++)
//	{
//		printf(" %d ", s[i]-48);
//	}




	/*while(eof != true)
	{
		int w = readCoordinate(& eof);
	}*/
	//int w = readCoordinate();
	//printf("%d", w);
	//int x = readCoordinate();
		//printf("%d", x);
	/*char c = getchar();
	printf("%c", c);
	 ungetc(c, stdin);
	 char b = getchar();
	 printf("%c", b);*/
	return 0;
}













