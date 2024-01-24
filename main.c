#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

struct Uhrzeit; /* muss vor eigentlicher definition leer deklariert werden, damit der Prototyp Bescheid weiß, was eine Uhrzeit ist */

int cursorSetzen(HANDLE, unsigned short, unsigned short);
void uhrzeitAnpassen(int);
void uhrzeitAusgeben(struct Uhrzeit);

typedef struct Uhrzeit 
{
    int stunde;
    int minute;
} Uhrzeit;

Uhrzeit uhrzeit; /* uhrzeit ist globale Variable, um UhrzeitAnpassen() zu erleichtern */


int main(int argc, char *argv[]) {
	
	int zehnerkarten, bergstation_lift, tageskarten, minuten, loop_anzahl;
	char input;
	
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	minuten = 540; /* wir starten bei 540 Minuten, weil der Skilift 9:00 Uhr aufmacht */
	uhrzeit.stunde = 9; 
	uhrzeit.minute = 0;
	
	loop_anzahl = 1; /* bestimmt, wie oft pro Sekunde der Hauptloop durchlaufen wird. Standardwert ist 1, Turbo ist 10, Pause ist 0 */
	
	/* Variablen zu Testzwecken */
	zehnerkarten = 15;
	bergstation_lift = 2;
	tageskarten = 51;
	
	/* loop läuft bis 1320 Minuten, also bis 22:00 Uhr */
	while(minuten <= 1320)
	{
		for (int i = 0; i < loop_anzahl; i++)
		{
			printf( "10er-Karten:  %i                                   ___Bergstation    Lift ab:  %i\n"
					"Tageskarten:  %i                                  /        |    |\n"
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
					"                                    \\       /       /\n"
					"                                     ----Talstation--               Lift auf:  2\n"
					"  :   Uhr                               (H):  0\n"
				   	"Personen auf Berg:  83                  [P]:  1 Auto\n"
					"...(T)urbo\n"
					"...(P)ause"                                                
					, zehnerkarten, bergstation_lift, tageskarten);
			
			uhrzeitAusgeben(uhrzeit); /* uhrzeit hat ein paar Eigenheiten, weswegen sie eine extrafunktion zum printen kriegt */
			
			/* nur zu testzwecken hier */
			zehnerkarten++;
			bergstation_lift++; 
			tageskarten++;
			
			minuten++; /* eine minute vergeht */
			uhrzeitAnpassen(minuten); /* minuten werden in uhrzeitformat umgewandelt */		
			cursorSetzen(hStdout, 0, 0); /* setzt Cursor an den Anfang, damit Ausgabe scheinbar konstant bleibt */	
		}

		Sleep(1000); /* wartet eine sekunde */
		
		if (kbhit())  // Überprüfen, ob eine Taste gedrückt wurde
		{
            input = tolower(getchar()); // Benutzereingabe lesen
            
			//Turbo
            if (input == 't') // Turbo aktiveren/Deaktivieren
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
            
			//Pause
            if (input == 'p') // Falls 'p' gedrückt wurde, pausieren
			{ 
				if (loop_anzahl != 0) /* wenn Pause aus ist, wechsel zu Pause */
				{
					loop_anzahl = 0;
				} 
				else /* wenn Pause an ist, wechsel zu Standard */
				{
					loop_anzahl = 1;
				}
                /* printf("Die Uhr ist pausiert. Drücken Sie 'r', um fortzufahren.\n"); */
                /* while (1) 
				{
                    input = tolower(getchar();
                    if (input == 'p') // Falls 'r' gedrückt wurde, fortsetzen
					{ 
                        break;
                        fflush(stdin);
                    }
                } */
            }
            else if (input == '0') // Progamm beendung mit 0
			{ 
                  
				  break;
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