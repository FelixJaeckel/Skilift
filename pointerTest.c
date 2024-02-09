#include <stdio.h>
#include <stdlib.h>

void arrayUebergeben(int *array[]);

void main()
{
	int a, *b;
	a = 5;
	b = &a;
	
	*b = 4;
	printf("%d", a);
	
	int array[30];
	int *arrayPtr[30];
	array[0] = 8;
	arrayPtr[0] = &array[0];
	*arrayPtr[0] = 7;
	printf("\n%d", array[0]);
	arrayUebergeben(&array[0]);
}

void arrayUebergeben(int *array[]){
	*array[0] = 13;
	printf("\nfunktion: %d", *array[0]);
}