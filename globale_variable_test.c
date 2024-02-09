#include <stdio.h>
#include <stdlib.h>

int a;

void main(){
	a = 5;
	printf("%d", a);
	a_aendern();
	printf("\n%d", a);
}

void a_aendern(){
	a++;
}