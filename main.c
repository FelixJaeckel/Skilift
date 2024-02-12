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
/*void uhrzeitAusgeben(struct Uhrzeit);*/
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

int zehnerkarten, schlangenlaenge_berg, tageskarten, schlangenleange_berg, lift_berg_ab, skifahrten, anzahl_berg_zu_mitte, B2Piste, R2Piste, anzahl_mitte_zu_berg, bistro, anzahl_mitte_zu_tal, anzahl_tal_zu_mitte, B1Piste, R1Piste, S1Piste, lift_tal_auf, schlangenlaenge_tal, haltestelle, personen_auf_berg, parkende_wagen,
	schlangenlaenge_mitte_hoch, schlangenlaenge_mitte_runter, 
	anzahl_S1, anzahl_B2, anzahl_R2, anzahl_B1, anzahl_R1, 
	minuten, loop_anzahl,
	S1randZeit, S1feierabendzeit, S1ungewoehnlichhoch, S1reverseminute,
	B1randZeit, B1feierabendzeit, B1ungewoehnlichhoch, B1reverseminute,
	B2randZeit, B2feierabendzeit, B2ungewoehnlichhoch, B2reverseminute,
	R1randZeit, R1feierabendzeit, R1ungewoehnlichhoch, R1reverseminute,
	R2randZeit, R2feierabendzeit, R2ungewoehnlichhoch, R2reverseminute;
	int zehnerkarten, bergstation_lift, tageskarten;
	int PersonenGesamtaufBerg, VerkaufteZehnerKarten, VerkaufteTageskarten, Skifarten, SchneedorfGaesteAufDerPiste, ParkendeWagen, BuseDieHeuteDaWaren; // Menu Counters
	char* Busn;
	char* Leer1;//Tabelle Puffer Veriabelen
	char* Leer2;
	char* Leer3;
	char* Leer4;
	char* Leer5;
	char* Leer6;
	char* Leer7;

		/*Randomzeit für die S1*/
		void getS1time(){
		if(S1reverseminute <= 9)
		{
			/*deaktiviert switch case*/
			/*printf("S1 ist Geschlossen");*/
			S1randZeit = 0;
		} else if(S1reverseminute <= 59)
		{
			S1randZeit = (rand() % S1feierabendzeit)+9;
		} else if(rand() % 100 > 10){
			S1randZeit = (rand() % 51)+9;/*Zufällige zeit zwischen 9 und 59*/
		}else{
			S1randZeit = (rand() % S1ungewoehnlichhoch)+59;
				
		}
		}
		
		/*Randomzeit für die B1*/
		void getB1time(){
		if(B1reverseminute <= 3)
		{
			/*deaktiviert switch case*/
			/*printf("B1 ist Geschlossen");*/
			B1randZeit = 0;
		} else if(B1reverseminute <= 23)
		{
			B1randZeit = (rand() % B1feierabendzeit)+3;
		} else if(rand() % 100 > 10){
			B1randZeit = (rand() % 21)+3;/*Zufällige zeit zwischen 3 und 24*/
		}else{
			B1randZeit = (rand() % B1ungewoehnlichhoch)+23;
				
		}
		}
		
		/*Randomzeit für die B2*/
		void getB2time(){	
		if(B2reverseminute <= 5)
		{
			/*deaktiviert switch case*/
			/*printf("B2 ist Geschlossen");*/
			B2randZeit = 0;
		} else if(B2reverseminute <= 42)
		{
			B2randZeit = (rand() % B2feierabendzeit)+5;
		} else if(rand() % 100 > 10){
			B2randZeit = (rand() % 38)+5;/*Zufällige zeit zwischen 5 und 42*/
		}else{
			B2randZeit = (rand() % B2ungewoehnlichhoch)+42;
				
		}	
		}
		
		/*Randomzeit für die R1*/
		void getR1time(){		
		if(R1reverseminute <= 3)
		{
			/*deaktiviert switch case*/
			/*printf("R1 ist Geschlossen");*/
			R1randZeit = 0;
		} else if(R1reverseminute <= 20)
		{
			R1randZeit = (rand() % R1feierabendzeit)+3;
		} else if(rand() % 100 > 10){
			R1randZeit = (rand() % 18)+3;/*Zufällige zeit zwischen 3 und 20*/
		}else{
			R1randZeit = (rand() % R1ungewoehnlichhoch)+20;
				
		}
		}
		
		/*Randomzeit für die R2*/
		void getR2time(){			
		if(R2reverseminute <= 3)
		{
			/*deaktiviert switch case*/
			/*printf("R2 ist Geschlossen");*/
			R2randZeit = 0;
		} else if(R2reverseminute <= 37)
		{
			R2randZeit = (rand() % R2feierabendzeit)+3;
		} else if(rand() % 100 > 10){
			R2randZeit = (rand() % 35)+3;/*Zufällige zeit zwischen 3 und 38*/
		}else{
			R2randZeit = (rand() % R2ungewoehnlichhoch)+37;
				
		}
		}
	
	
int main(int argc, char *argv[]) {

	/* Variablen zu Testzwecken */
	
	zehnerkarten = 15;
	schlangenlaenge_berg = 0;
	tageskarten = 51;
	lift_berg_ab = 2;
	skifahrten = 0;
	anzahl_berg_zu_mitte = 0;
	B2Piste = 0;
	R2Piste = 0;
	anzahl_mitte_zu_berg = 0;
	bistro = 0;
	anzahl_mitte_zu_tal = 0;
	anzahl_tal_zu_mitte = 0;
	B1Piste = 0;
	R1Piste = 0;
	S1Piste = 0;
	lift_tal_auf = 0;
	schlangenlaenge_tal = 0;
	haltestelle = 0;
	personen_auf_berg = 0;
	parkende_wagen = 0;
	PersonenGesamtaufBerg = 0;
	VerkaufteZehnerKarten = -1;
	VerkaufteTageskarten = 0;
	Skifarten = 0;
	SchneedorfGaesteAufDerPiste = 0;
	ParkendeWagen = 0;
	BuseDieHeuteDaWaren = 0;

	/*
	int zehnerkarten, tageskarten,
		schlangenlaenge_tal, schlangenlaenge_berg, schlangenlaenge_mitte_hoch, schlangenlaenge_mitte_runter, 
		anzahl_tal_zu_mitte, anzahl_mitte_zu_berg, anzahl_berg_zu_mitte, anzahl_mitte_zu_tal,
		anzahl_S1, anzahl_B2, anzahl_R2, anzahl_B1, anzahl_R1, 
		minuten, loop_anzahl;
		*/
	char input;
	/*input = NULL;*/

	
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	minuten = 540; /* wir starten bei 540 Minuten, weil der Skilift 9:00 Uhr aufmacht */
	uhrzeit.stunde = 9; 
	uhrzeit.minute = 0;
	
	loop_anzahl = 1; /* bestimmt, wie oft pro Sekunde der Hauptloop durchlaufen wird. Standardwert ist 1, Turbo ist 10, Pause ist 0 */
	

	
	/* einzelner Skifahrer zu testzwecken */
	skifahrer_liste[0].ankunftsart = 0;
	skifahrer_liste[0].gesamtfahrten = 0;
	skifahrer_liste[0].uebrige_fahrten = 9999;
	skifahrer_liste[0].aktuelle_position = schlange_tal;	tal_warteschlange[0] = skifahrer_liste[0];
	
	tal_zu_mitte(skifahrer_liste[0], lift_liste[0]);
	/*printf("%d", skifahrer_liste[0].aktuelle_position); die Position ändert sich nur während der funktion, nicht permanent */
	/*Variabeln für S1*/
		S1randZeit = 0;
		S1feierabendzeit =770;
		S1ungewoehnlichhoch = 720;
		S1reverseminute = 780;
		
		/*Variabeln für B1*/
		B1randZeit = 0;
		B1feierabendzeit =776;
		B1ungewoehnlichhoch = 758;
		B1reverseminute = 780;
		/*Variabeln für B2*/
		B2randZeit = 0;
		B2feierabendzeit =774;
		B2ungewoehnlichhoch = 737;
		B2reverseminute = 780;
		/*Variabeln für R1*/
		R1randZeit = 0;
		R1feierabendzeit =776;
		R1ungewoehnlichhoch = 759;
		R1reverseminute = 780;
		/*Variabeln für R2*/
		R2randZeit = 0;
		R2feierabendzeit =775;
		R2ungewoehnlichhoch = 743;
		R2reverseminute = 780;
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
			   dass sich Dateien nicht mehr öffnen ließen, weil die Umlaute kaputt waren. Eventuell lags daran.*/

	/*funktionen f�r pisten zeiten*/
		getS1time();
		getB1time();
		getB2time();	
		getR1time();	
		getR2time();
	
	/*	Zu testzwecken 
		printf("%d\t\t %d\n", S1randZeit, S1reverseminute);
		printf("%d\n", B1randZeit);
		printf("%d\n", B2randZeit);
		printf("%d\n", R1randZeit);
		printf("%d\n", R2randZeit);*/
		/*Aktivierungszeiten*/
		S1reverseminute--;
		B1reverseminute--;
		B2reverseminute--;
		R1reverseminute--;
		R2reverseminute--;
		/*Max Zeiten*/
		S1ungewoehnlichhoch--;
		S1feierabendzeit--;
		
		B1ungewoehnlichhoch--;
		B1feierabendzeit--;
		
		B2ungewoehnlichhoch--;
		B2feierabendzeit--;
		
		R1ungewoehnlichhoch--;
		R1feierabendzeit--;
		
		R2ungewoehnlichhoch--;
		R2feierabendzeit--;
	
		int i;
		
		for (i = 0; i < loop_anzahl; i++)
		{
			
			
			
			cursorSetzen(hStdout, 0, 1); /* setzt Cursor an den Anfang, damit Ausgabe scheinbar konstant bleibt */
			printf( "\n10er-Karten:  %03.d                                    ___Bergstation Schlange: %03.d\n"
					"Tageskarten:  %03.d                                   /        |    |  Lift ab: %03.d \n"
					"Skifahrten:   %03.d                                 /        /     |\n"
					"                                                -        /      |\n"
					"                                               /        |       |\n"
					"Lift M<>B:  %03.d                        B2:  %03.d   R2:   %03.d  /\n"
					"                                             /        /       /\n"
					"                                         ----        |       /\n"
					"                                        /           /       /       Lift auf:  %03.d\n"
					"                                        Mittelstation      |\n"
					"                                   _____Bistro:  %03.d        /         Lift ab:   %03.d\n"
					"                                  /       \\             |\n"
					"                                  \\        |           /\n"
					"Lift T<>M:  %03.d                   B1:  %03.d    R1: %03.d     S1:  %03.d\n"
					"                                   \\        \\        /\n"
					"                                    \\       /       /           Lift auf:  %03.d\n"
					"                                     ----Talstation Schlange: %03.d\n"
					"  %02.d:%02.d   Uhr                               (H):  %03.d\n"
				   	"Personen auf Berg:  %03.d                  [P]:  %03.d Auto\n"
				"\n                  ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»                "
		"\n  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄº                                          ºÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿"
		"\n  ³               º      Übersicht über den Berg             º               ³"
		"\n  ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄº                                          ºÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´"
		"\n  ³               ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼               ³"
		"\n  ³                    ³           Allgemeine Zahlen:                        ³"
		"\n  ³                    ³          Personen auf Berg:  %03.d%s                   ³"
		"\n  ³                    ³          10er-Karten:  %03.d%s                         ³"
		"\n  ³                    ³          Tageskarten: %03d%s                          ³"
		"\n  ³                    ³          Skifahrten:   %03d%s                         ³"
		"\n  ³                    ³          Schneedorf Besucher:   %03d%s                ³"
		"\n  ³                    ³          Parkende Wagen:  %03d Auto %s                ³"
		"\n  ³                    ³          Busse an diesem Tag:  %03d  %s               ³"
		"\n  ³                    ³          %s                                        ³"
		"\n  ³                    ³          M%sgliche Eingaben:                         ³"
		"\n  ³                    ³          (T)urbo                                    ³"
		"\n  ³                    ³          (P)ause                                    ³"
		"\n  ³                    ³          (0)  Programmende                          ³"
		"\n  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ"                                               
					, zehnerkarten, schlangenlaenge_berg, tageskarten, lift_berg_ab, skifahrten, anzahl_berg_zu_mitte, B2Piste, R2Piste, anzahl_mitte_zu_berg, bistro, anzahl_mitte_zu_tal, anzahl_tal_zu_mitte, 
				 B1Piste, R1Piste, S1Piste, lift_tal_auf, schlangenlaenge_tal, uhrzeit.stunde, uhrzeit.minute, haltestelle, personen_auf_berg, parkende_wagen
				 /* PersonenGesamtaufBerg, Leer1, VerkaufteZehnerKarten, Leer2, VerkaufteTageskarten, Leer3, Skifarten, Leer4, SchneedorfGaesteAufDerPiste, Leer5, ParkendeWagen, Leer6, BuseDieHeuteDaWaren, Leer7, Busn, "\x94"*/);
	


	
			/*uhrzeitAusgeben(uhrzeit);  uhrzeit hat ein paar Eigenheiten, weswegen sie eine extrafunktion zum printen kriegt */
			
			/* nur zu testzwecken hier */
			
			minuten++; /* eine minute vergeht */
			uhrzeitAnpassen(minuten); /* minuten werden in uhrzeitformat umgewandelt */		
			positionen_checken(skifahrer_liste[0]);				
		}

		Sleep(1000); /* wartet eine sekunde */  
	
		/*input = NULL;*/
		if (kbhit()) /* checkt, ob Taste gedrückt wurde */
		{
	        input = tolower(getch()); // Benutzereingabe lesen	
			fflush(stdout);	
		} else {
			/*input = NULL;*/
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


/* sorgt dafür, dass uhrzeit immer mit zwei Ziffern vor und hinter dem Doppelpunkt ausgegeben wird 
void uhrzeitAusgeben(Uhrzeit uhrzeit)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); */
	/* wird fuer cursorSetzen() benoetigt */

	/* packt 0 vor die Stunde wenn es um 9 ist, ansonsten wird die Stunde einfach nur geprintet 
	cursorSetzen(hStdout, 0, 17);	
	if (uhrzeit.stunde == 9) 
	{
		printf("0%i", uhrzeit.stunde);
	} 
	else 
	{
		printf("%i", uhrzeit.stunde);
	}*/
	
	/* packt 0 vor einstellige Minuten 
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
}*/

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
