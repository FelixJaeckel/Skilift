#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



struct Uhrzeit {
    int stunde;
    int minute;
};

void Uhrzeit(){
// wait
//min & stu -> eigene funktion
    int i;
struct Uhrzeit t1 = {8, 0};
    for (i = 0; ; i++) {
        // Delay 5 sekunden f�r 1 min
        delay(5000);
        struct t.minute++;
        printf("%d seconds have passed\n", i + 1);
        if(t.minute = 60){
        t.minute = 0; //stunde vergeht
        t.stunde++;
        }
    }
}

void uhrzeitAusgeben(struct Uhrzeit t) {
    printf("Uhrzeit: %d:%d\n", t.stunde, t.minute);//Ausgabe form
}

 void delay(unsigned int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}

int main(void) {
	void Uhrzeit();
	
	int B1, B2, R1, R2, S1;//Pisten
	int w1, w2, w3 , w4;//Warteschlangen
	int LiMB, LiTM;//Liftbenutzer
	int Bi;//Bistro
	int ges, Kat, TKat, Ski, Pak, Hal; // Menu Counters
	
	B1 = 0;
	B2 = 0;
	R1 = 0;
	R2 = 0;
	S1 = 0;
	w1 = 0;
	w2 = 0;
	w3 = 0;
	w4 = 0;
	LiMB = 0;
	LiTM = 0;
	Bi = 0;
	ges = 0;
	Kat = 0;
	TKat = 0;
	Ski = 0;
	Pak = 0;
	Hal = 0;
	
	printf("                                                   ___Bergstation    Lift ab:  %d\n", w1);
	printf("                                                  /        |    |\n");
	printf("                                                 /        /     |\n");
	printf("                                                -        /      |\n");
	printf("                                               /        |       |\n");
	printf("Lift M<>B:  %d                                 B2: %d   R2:   %d  /\n", LiMB,B2, R2);
	printf("                                             /        /       /\n");
	printf("                                         ----        |       /\n");
	printf("                                        /           /       /       Lift auf:  %d\n", w2);
	printf("                                        Mittelstation      |\n");
	printf("                                   _____Bistro:  %d        /         Lift ab:   %d\n", Bi, w3);
	printf("                                  /        \\             |\n");
	printf("                                  \\        |            /\n");
	printf("Lift T<>M:  %d                   B1:  %d    R1: %d     S1:  %d\n", LiTM, B1, R1, S1);
	printf("                                    \\        \\       /\n");
	printf("                                     \\       /      /\n");
	printf("                                     ----Talstation--               Lift auf:  %d\n", w4);
	//Bestimmte stings anwenden in zeilen mit ver�ndenden zahlen die verschiedene anzahl an Leerzeichen ausgibt zb. 1 bei 1000+, 2 bei 100+, 3 bei 10+ usw.
	//oder anzeige im men�
		printf("\n                  ������������������������������������������ͻ                ");
	printf("\n  ���������������ĺ                                          ���������������Ŀ");
	printf("\n  �               �      %sbersicht %sber den Berg             �              �", "\x9a", "\x81");
	printf("\n  ���������������ĺ                   Uhrzeit: %d:%d         ���������������Ĵ", uhrzeitAusgeben(t1););
	printf("\n  �               ������������������������������������������ͼ               �");
	printf("\n  �                    �           Allgemeine Zahlen:                        �");
	printf("\n  �                    �          Personen auf Berg:  %d                     �", ges);
	printf("\n  �                    �          10er-Karten:  %d                           �", Kat);
	printf("\n  �                    �          Tageskarten: %d                            �", TKat);
	printf("\n  �                    �          Skifahrten:   %d                           �", Ski);
	printf("\n  �                    �          Parkende Wagen:  %d Auto                   �", Pak);
	printf("\n  �                    �          Busse an diesem Tag:  %d                   �", Hal);
	printf("\n  �                    �                                                     �");
	printf("\n  �                    �          M�gliche Eingaben:                         �");
	printf("\n  �                    �          (T)urbo                                    �");
	printf("\n  �                    �          (P)ause                                    �");
	printf("\n  �                    �          (0)  Programmende                          �");
	printf("\n  ����������������������������������������������������������������������������");
//Counter f�r zu fu� , bis zu 60 aus schneedorf, mit auto1-5 max 50 autos, bus im tackt mit bis zu 50 leuten pro bus
	/*
Per string einf�gen
� \x84
� \x94
� \x81
� \x8e
� \x99
� \x9a
� \xe1
	*/

}
