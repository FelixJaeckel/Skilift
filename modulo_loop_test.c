#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void main(){
	unsigned int a, b, c, d;
	a = 0;
	b = 27;
	c = 55;
	d = 82;
	
	int i;
	while (i <= 110){
		printf("\nRunde: %3d   tal: %3d   mitte_hoch: %3d   berg: %3d   mitte_runter: %3d", i, a, b, c, d);
		a--; b--; c--; d--;
		a = zurueckAuf110(a);
		b = zurueckAuf110(b);
		c = zurueckAuf110(c);
		d = zurueckAuf110(d);
		i++;
	}
}

int zurueckAuf110(int zahl){
	if (zahl == -1){
		zahl = 110;
	}
	return zahl;
}