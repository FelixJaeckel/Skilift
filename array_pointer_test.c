#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void main() 
{
	int zahlen_array[] = {0, 1, 2, 3, 4, 5};	
	int *array_ptr, i;
	array_ptr = zahlen_array;
	i = 0;
	
	while(1)
	{
		printf("\n%d", array_ptr[i]);
		i++;
		if (i == 6)
		{
			i = 0;
		}
	}
}