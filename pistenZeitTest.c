#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

int main(){
    int r, pistenzeit, zeit_bis_schluss;
    double i, durchschnitt, summe;
    zeit_bis_schluss = 1320;
    summe = 0;
    durchschnitt = 0;
    i = 0;
    for (; i < 1000; i++){
        r = rand() % 100;
        if (r < 10){
            pistenzeit = 9;
        } else if (r >= 10 && r < 30){
            pistenzeit = (rand() % 25) + 9;
        } else if (r >= 30 && r < 70){
            pistenzeit = 34;
        } else if (r >= 70 && r < 90){
            pistenzeit = (rand() % 25) + 34;
        } else if (r > 90){
            pistenzeit = (rand() % zeit_bis_schluss) + 9;
        }
        printf("\n%d", pistenzeit);
        summe = summe + pistenzeit;
        durchschnitt = summe/i; 
    }
    printf("\n Durchschnitt: %f", durchschnitt);
	return 0;
}

