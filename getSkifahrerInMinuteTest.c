#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void main(){
	getSkifahrerInMinute(10);
}


void getSkifahrerInMinute(int x){
	int d;
	for(;x > 0;)
	{
	x = x - d;
	printf("\nx:  %3d", x);
	d =(rand() % 5)+1;
	}
}