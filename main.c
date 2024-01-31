#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define abwesend 					100
#define schlange_tal 				101
#define schlange_mitte_zu_hoch 		102
#define schlange_berg 				103
#define schlange_mitte_zu_runter 	104
#define lift_tal_zu_mitte			105
#define lift_mitte_zu_berg			106
#define lift_berg_zu_mitte			107
#define lift_mitte_zu_tal			108
#define piste_S1					109
#define piste_B2					110
#define piste_R2					111
#define piste_B1					112
#define piste_R1					113

struct Uhrzeit; /* muss vor eigentlicher definition leer deklariert werden, damit der Prototyp Bescheid weiß, was eine Uhrzeit ist */
struct Skifahrer;
struct Lift;

int cursorSetzen(HANDLE, unsigned short, unsigned short);
void uhrzeitAnpassen(int);
void uhrzeitAusgeben(struct Uhrzeit);
void cursorVerstecken();
void tal_zu_mitte(struct Skifahrer, struct Lift);
void positionen_checken(struct Skifahrer);

typedef struct Skifahrer
{
	int ankunftsart;
	int uebrige_fahrten;
	int aktuelle_position;
	int gesamtfahrten;
} Skifahrer;

typedef struct Lift
{
	Skifahrer skifahrer1;
	Skifahrer skifahrer2;
	Skifahrer skifahrer3;
	Skifahrer skifahrer4;
} Lift;

typedef struct Uhrzeit 
{
    int stunde;
    int minute;
} Uhrzeit;

Uhrzeit uhrzeit;

Skifahrer skifahrer_liste[2010];
Skifahrer tal_warteschlange[500];
Lift lift_liste[110]; /* evtl sollte man für die stationen mit nem pointer auf die Liste hier zeigen und dann immer den wert ändern 
						d.h. tal_schlange zeigt auf lift_liste[0] und dann wird immer nur der Wert von lift_liste[0] geändert.
						Dementsprechend gibt es keine warteschlangen arrays mehr */

int zehnerkarten, tageskarten,
	schlangenlaenge_tal, schlangenlaenge_berg, schlangenlaenge_mitte_hoch, schlangenlaenge_mitte_runter, 
	anzahl_tal_zu_mitte, anzahl_mitte_zu_berg, anzahl_berg_zu_mitte, anzahl_mitte_zu_tal,
	anzahl_S1, anzahl_B2, anzahl_R2, anzahl_B1, anzahl_R1, 
	minuten, loop_anzahl;

int main(int argc, char *argv[]) {
	
	cursorVerstecken();
	/*
	int zehnerkarten, tageskarten,
		schlangenlaenge_tal, schlangenlaenge_berg, schlangenlaenge_mitte_hoch, schlangenlaenge_mitte_runter, 
		anzahl_tal_zu_mitte, anzahl_mitte_zu_berg, anzahl_berg_zu_mitte, anzahl_mitte_zu_tal,
		anzahl_S1, anzahl_B2, anzahl_R2, anzahl_B1, anzahl_R1, 
		minuten, loop_anzahl;
		*/
	char input;
	input = NULL;

	
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	minuten = 540; /* wir starten bei 540 Minuten, weil der Skilift 9:00 Uhr aufmacht */
	uhrzeit.stunde = 9; 
	uhrzeit.minute = 0;
	
	loop_anzahl = 1; /* bestimmt, wie oft pro Sekunde der Hauptloop durchlaufen wird. Standardwert ist 1, Turbo ist 10, Pause ist 0 */
	
	/* Variablen zu Testzwecken */
	schlangenlaenge_tal = 1;
	schlangenlaenge_berg = 0;
	
	/* einzelner Skifahrer zu testzwecken */
	skifahrer_liste[0].ankunftsart = 0;
	skifahrer_liste[0].gesamtfahrten = 0;
	skifahrer_liste[0].uebrige_fahrten = 9999;
	skifahrer_liste[0].aktuelle_position = schlange_tal;	tal_warteschlange[0] = skifahrer_liste[0];
	
	tal_zu_mitte(skifahrer_liste[0], lift_liste[0]);
	printf("%d", skifahrer_liste[0].aktuelle_position); /*die Position ändert sich nur während der funktion, nicht permanent */
	/* loop läuft bis 1320 Minuten, also bis 22:00 Uhr */
	while(minuten <= 1320)
	{
		/*  1. Alle Variablen auf einer Zeile definieren.
			2. Die Buchstaben in den Pisten immer groß schreiben. Ich mussste kurz überlegen was "random minutes 1" ist, bis mir klar wurde, dass es es "random minute s1" ist.
			3. So wie das ganze aktuell positioniert ist, werden deine Variablen mit jedem loop wieder auf ihre Startwerte zurückgesetzt. Die müssen außerhalb des while-loops definiert werden.
			4. Das Ganze sollte am besten in einer Funktion sein, die man aufrufen kann. Optimal wäre eine allgemeine Funktion, der man die entsprechende Piste übergibt und die dementsprechend handelt.
			   Aber eine Funktion pro Piste ist auch okay. Hauptsache raus aus dem hauptloop. (das sollte ich übrigens auch mit dem Turbo- und Pausenzeugs machen)
			5. In deinen Kommentaren erwähnst du, dass eine switch-case deaktiviert wird. Aber da ist nirgendwo ein switch, der deaktiviert werden könnte. 
			6. Guck, ob du eventuell eine Möglichkeit findest, das ganze kürzer zu svhreiben. Soll heißen, dass du nicht 5 mal die gleiche Verzweigung nur mit anderen Werten in den Code schreiben musst.
			   Falls das nicht geht, ist es auch okay.
			7. Falls dev-c++ dich irgendwas wegen "utf-8 encoding" oder ähnliches beim Speichern fragt, klick auf ja. Kann sein, dass du das schon machst, ich hatte jedenfalls jetzt zwei mal das Problem,
			   dass sich Dateien nicht mehr öffnen ließen, weil die Umlaute kaputt waren. Eventuell lags daran. 
		/*Variabeln für S1*/
		int randS1Zeit, s1feierabendzeit, s1ungewoehnlichhoch, reverseminuteS1;
		randS1Zeit = 0;
		s1feierabendzeit =770;
		s1ungewoehnlichhoch = 720;
		reverseminuteS1 = 780;
		
		/*Variabeln für B1*/
		int randB1Zeit;
		randB1Zeit = 0;
		int b1feierabendzeit;
		b1feierabendzeit =776;
		int b1ungewoehnlichhoch;
		b1ungewoehnlichhoch = 758;
		int reverseminuteb1;
		reverseminuteb1 = 780;
		/*Variabeln für B2*/
		int randB2Zeit;
		randB2Zeit = 0;
		int b2feierabendzeit;
		b2feierabendzeit =774;
		int b2ungewoehnlichhoch;
		b2ungewoehnlichhoch = 737;
		int reverseminuteb2;
		reverseminuteb2 = 780;
		/*Variabeln für R1*/
		int randR1Zeit;
		randR1Zeit = 0;
		int r1feierabendzeit;
		r1feierabendzeit =776;
		int r1ungewoehnlichhoch;
		r1ungewoehnlichhoch = 759;
		int reverseminuter1;
		reverseminuter1 = 780;
		/*Variabeln für R2*/
		int randR2Zeit;
		randR2Zeit = 0;
		int r2feierabendzeit;
		r2feierabendzeit =775;
		int r2ungewoehnlichhoch;
		r2ungewoehnlichhoch = 743;
		int reverseminuter2;
		reverseminuter2 = 780;
	
		
		/*Randomzeit für die S1*/
		
		if(reverseminuteS1 <= 9)
		{
			/*deaktiviert switch case*/
			/*printf("S1 ist Geschlossen");*/
			randS1Zeit = 0;
		} else if(reverseminuteS1 <= 59)
		{
			randS1Zeit = (rand() % s1feierabendzeit)+9;
		} else if(rand() % 100 > 10){
			randS1Zeit = (rand() % 51)+9;/*Zufällige zeit zwischen 9 und 59*/
		}else{
			randS1Zeit = (rand() % s1ungewoehnlichhoch)+59;
				
		}
		/*Randomzeit für die B1*/
		
		if(reverseminuteb1 <= 3)
		{
			/*deaktiviert switch case*/
			/*printf("B1 ist Geschlossen");*/
			randB1Zeit = 0;
		} else if(reverseminuteb1 <= 23)
		{
			randB1Zeit = (rand() % b1feierabendzeit)+3;
		} else if(rand() % 100 > 10){
			randB1Zeit = (rand() % 21)+3;/*Zufällige zeit zwischen 3 und 24*/
		}else{
			randB1Zeit = (rand() % b1ungewoehnlichhoch)+23;
				
		}
			/*Randomzeit für die B2*/
			
		if(reverseminuteb2 <= 5)
		{
			/*deaktiviert switch case*/
			/*printf("B2 ist Geschlossen");*/
			randB2Zeit = 0;
		} else if(reverseminuteb2 <= 42)
		{
			randB2Zeit = (rand() % b2feierabendzeit)+5;
		} else if(rand() % 100 > 10){
			randB2Zeit = (rand() % 38)+5;/*Zufällige zeit zwischen 5 und 42*/
		}else{
			randB2Zeit = (rand() % b2ungewoehnlichhoch)+42;
				
		}	
				/*Randomzeit für die R1*/
				
		if(reverseminuter1 <= 3)
		{
			/*deaktiviert switch case*/
			/*printf("R1 ist Geschlossen");*/
			randR1Zeit = 0;
		} else if(reverseminuter1 <= 20)
		{
			randR1Zeit = (rand() % r1feierabendzeit)+3;
		} else if(rand() % 100 > 10){
			randR1Zeit = (rand() % 18)+3;/*Zufällige zeit zwischen 3 und 20*/
		}else{
			randR1Zeit = (rand() % r1ungewoehnlichhoch)+20;
				
		}	
					/*Randomzeit für die R2*/
					
						if(reverseminuter2 <= 3)
		{
			/*deaktiviert switch case*/
			/*printf("R2 ist Geschlossen");*/
			randR2Zeit = 0;
		} else if(reverseminuter2 <= 37)
		{
			randR2Zeit = (rand() % r2feierabendzeit)+3;
		} else if(rand() % 100 > 10){
			randR2Zeit = (rand() % 35)+3;/*Zufällige zeit zwischen 3 und 38*/
		}else{
			randR2Zeit = (rand() % r2ungewoehnlichhoch)+37;
				
		}	
	/*	Zu testzwecken */
		printf("%d\t\t %d\n", randS1Zeit, reverseminuteS1);
		printf("%d\n", randB1Zeit);
		printf("%d\n", randB2Zeit);
		printf("%d\n", randR1Zeit);
		printf("%d\n", randR2Zeit);
		/*Aktivierungszeiten*/
		reverseminuteS1--;
		reverseminuteb1--;
		reverseminuteb2--;
		reverseminuter1--;
		reverseminuter2--;
		/*Max Zeiten*/
		s1ungewoehnlichhoch--;
		s1feierabendzeit--;
		
		b1ungewoehnlichhoch--;
		b1feierabendzeit--;
		
		b2ungewoehnlichhoch--;
		b2feierabendzeit--;
		
		r1ungewoehnlichhoch--;
		r1feierabendzeit--;
		
		r2ungewoehnlichhoch--;
		r2feierabendzeit--;
	
		int i;
		
		for (i = 0; i < loop_anzahl; i++)
		{
			
			
			
			cursorSetzen(hStdout, 0, 1); /* setzt Cursor an den Anfang, damit Ausgabe scheinbar konstant bleibt */
			printf( "\n10er-Karten:  5                                    ___Bergstation Schlange: %d\n"
					"Tageskarten:  5                                   /        |    |  Lift ab: %d \n"
					"Skifahrten:   77                                 /        /     |\n"
					"                                                -        /      |\n"
					"                                               /        |       |\n"
					"Lift M<>B:  22                               B2:  6   R2:   8  /\n"
					"                                             /        /       /\n"
					"                                         ----        |       /\n"
					"                                        /           /       /       Lift auf:  1\n"
					"                                        Mittelstation      |\n"
					"                                   _____Bistro:  7        /         Lift ab:   0\n"
					"                                  /       \\             |\n"
					"                                  \\        |           /\n"
					"Lift T<>M:  14                   B1:  4    R1: 12     S1:  5\n"
					"                                   \\        \\        /\n"
					"                                    \\       /       /           Lift auf:  %d\n"
					"                                     ----Talstation Schlange: %d\n"
					"  :   Uhr                               (H):  0\n"
				   	"Personen auf Berg:  83                  [P]:  1 Auto\n"
					"...(T)urbo\n"
					"...(P)ause"                                                
					, schlangenlaenge_berg, anzahl_berg_zu_mitte, anzahl_tal_zu_mitte, schlangenlaenge_tal);
			
			uhrzeitAusgeben(uhrzeit); /* uhrzeit hat ein paar Eigenheiten, weswegen sie eine extrafunktion zum printen kriegt */
			
			/* nur zu testzwecken hier */
			
			minuten++; /* eine minute vergeht */
			uhrzeitAnpassen(minuten); /* minuten werden in uhrzeitformat umgewandelt */		
			positionen_checken(skifahrer_liste[0]);				
		}

		Sleep(1000); /* wartet eine sekunde */  
	
		input = NULL;
		if (kbhit()) /* checkt, ob Taste gedrückt wurde */
		{
	        input = tolower(getch()); // Benutzereingabe lesen	
			fflush(stdout);	
		} else {
			input = NULL;
		}


        if (input == '0') // Progamm beendung mit 0
		{   
			cursorSetzen(hStdout, 0, 22); /* Cursor ans Ende setzen, damit die exit-messsage nicht ins Programm geprintet wird */
			break;
        }
        else if (input == 't') // Turbo aktiveren/Deaktivieren
		{
			if (loop_anzahl != 10) /* wenn Turbo aus ist, wechsel zu Turbo */
			{
			    loop_anzahl = 10; // Wechsel des Turbo moduses	
			} 
			else /* wenn Turbo an ist, wechsel zu Standard */
			{
				loop_anzahl = 1; 
			}
            /* printf("Turbo-Modus %s\n", turbo ? "aktiviert" : "deaktiviert"); */
        }     
        else if (input == 'p') // Falls 'p' gedrückt wurde, pausieren
		{ 
			if (loop_anzahl != 0) /* wenn Pause aus ist, wechsel zu Pause */
			{
				loop_anzahl = 0;
			} 
			else /* wenn Pause an ist, wechsel zu Standard */
			{
				loop_anzahl = 1;
			}
        } 
		
	} 	
	return 0;
}


/* setzt cursor zu angegebenen Koordinaten */
int cursorSetzen(HANDLE hStdout, unsigned short x, unsigned short y)
{
   return SetConsoleCursorPosition(hStdout, (COORD){x,y});
}

/* versteckt Cursor */
void cursorVerstecken()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

/* wandelt anzahl minuten in Uhrzeit-struct bestehend aus Stunden und Minuten um */
void uhrzeitAnpassen(int minuten)
{
	uhrzeit.stunde = minuten / 60;
	uhrzeit.minute = minuten % 60;
	return;
}


/* sorgt dafür, dass uhrzeit immer mit zwei Ziffern vor und hinter dem Doppelpunkt ausgegeben wird */
void uhrzeitAusgeben(Uhrzeit uhrzeit)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */

	/* packt 0 vor die Stunde wenn es um 9 ist, ansonsten wird die Stunde einfach nur geprintet */
	cursorSetzen(hStdout, 0, 17);	
	if (uhrzeit.stunde == 9) 
	{
		printf("0%i", uhrzeit.stunde);
	} 
	else 
	{
		printf("%i", uhrzeit.stunde);
	}
	
	/* packt 0 vor einstellige Minuten */
	cursorSetzen(hStdout, 3, 17);	
	if (uhrzeit.minute >= 10) 
	{
		printf("%i", uhrzeit.minute);
	} 
	else 
	{
		printf("0%i", uhrzeit.minute);
	} 
	return;
}

/* ziel ist später, eine allgemeine Funktion zum Einsteigen in den Lift zu haben. Das hier ist nur provisorisch da */
void tal_zu_mitte(Skifahrer skifahrer1, Lift lift1)
{
	lift1.skifahrer1 = skifahrer1;
	skifahrer1.aktuelle_position = lift_tal_zu_mitte;
	skifahrer1.uebrige_fahrten--;
}

/* soll durch gesamte skifahrer_liste durchgehen und deren positionen bestimmen */
void positionen_checken(Skifahrer skifahrer1)
{
	printf(" %d", skifahrer1.aktuelle_position);
	printf(" %d", anzahl_tal_zu_mitte);
	
	switch(skifahrer1.aktuelle_position)
	{
		case lift_tal_zu_mitte: anzahl_tal_zu_mitte++; 
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		break;
	}
	printf(" %d", anzahl_tal_zu_mitte);
}
