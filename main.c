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

int cursorSetzen(HANDLE, unsigned short, unsigned short);
void uhrzeitAnpassen(int);
void uhrzeitAusgeben(struct Uhrzeit);
void cursorVerstecken();
//void tal_zu_mitte(struct Skifahrer *skifahrer1, struct Lift *lift1);
void neuenSkifahrerErstellen(Skifahrer[], Skifahrer[], int*, int*);
void positionen_checken(struct Skifahrer);
void getS1time();
void getB1time();
void getB2time();
void getR1time();
void getR2time();


Uhrzeit uhrzeit;

//Skifahrer skifahrer_liste[2010];
Lift lift_liste[110]; 
/*  evtl sollte man für die stationen mit nem pointer auf die Liste hier zeigen und dann immer den wert ändern 
	d.h. tal_schlange zeigt auf lift_liste[0] und dann wird immer nur der Wert von lift_liste[0] geändert.
	Dementsprechend gibt es keine warteschlangen arrays mehr. 
	EDIT: Genau das wurde umgesetzt!*/

int zehnerkarten, tageskarten,
	minuten, loop_anzahl,
	schlangenlaenge_tal, 		  anzahl_tal_zu_mitte,	anzahl_R1,
	schlangenlaenge_berg,	 	  anzahl_mitte_zu_berg, anzahl_B1, 
	schlangenlaenge_mitte_hoch,   anzahl_berg_zu_mitte, anzahl_B2,      
	schlangenlaenge_mitte_runter, anzahl_mitte_zu_tal,	anzahl_R2, anzahl_S1,	
	S1randZeit, S1feierabendzeit, S1ungewoehnlichhoch, S1reverseminute,
	B1randZeit, B1feierabendzeit, B1ungewoehnlichhoch, B1reverseminute,
	B2randZeit, B2feierabendzeit, B2ungewoehnlichhoch, B2reverseminute,
	R1randZeit, R1feierabendzeit, R1ungewoehnlichhoch, R1reverseminute,
	R2randZeit, R2feierabendzeit, R2ungewoehnlichhoch, R2reverseminute;


void neuenSkifahrerErstellen(Skifahrer skifahrer_liste[], Skifahrer warteschlange_tal[], int *skifahrer_liste_index, int *warteschlange_tal_index){
	Skifahrer skifahrer; /* Skifahrerobjekt erstellen */
	
	skifahrer.aktuelle_position = schlange_tal;	/* ein frisch erstellter Skifahrer wird sich immer zuerst im Tal anstellen */
	skifahrer.ankunftsart = 1;	/* TODO: verschiedene ankunftsarten impementieren */
	skifahrer.gesamtfahrten = 0;  /* Gesamtfahrten am Anfang bei 0 */
	
	/* 50/50 chance, ob 10er oder Tageskarte */
	int r; 
	r = rand() % 2;
	if (r == 0)
	{
		skifahrer.uebrige_fahrten = 10;	
	} else if (r == 1){
		skifahrer.uebrige_fahrten = 9999;	
	}
	
	warteschlange_tal[*warteschlange_tal_index] = skifahrer; /* TODO: Warteschlangen sind aktuell LIFO, müssen aber FIFO sein. skifahrer wird an vorderste Stelle der Schlange gesetzt */
	skifahrer_liste[*skifahrer_liste_index] = skifahrer; /* skifahrer wird in skifahrer liste geschrieben */
	*skifahrer_liste_index = *skifahrer_liste_index +1;  /* skifahrer listen index um eins erhöhen, damit der nächste skifahrer dorthin geschrieben wird */
	*warteschlange_tal_index = *warteschlange_tal_index + 1;  /* warteschlangen index erhöhen */
	
	/* testprints */
	printf("\nskifahrer.uebrig funktion: %4d", skifahrer.uebrige_fahrten);
	printf("\nwarteschlange[index].uebrig funktion: %4d", warteschlange_tal[*warteschlange_tal_index-1].uebrige_fahrten);
}
	
void liftBetreten(Lift *lift_in_station, Skifahrer warteschlange[], int *warteschlange_index)
{
	*warteschlange_index = *warteschlange_index -1; /* um eins senken, weil index vorher bei leerer Stelle ist */ 
	lift_in_station->skifahrer1 = warteschlange[*warteschlange_index]; /* skifahrer an vorderster Stelle in Warteschlange in lift setzen */ 
	lift_in_station->skifahrer1.aktuelle_position = lift_tal_zu_mitte; /* skifahrer position auf lift setzen. TODO: Muss positionsagnostisch werden */
	warteschlange[*warteschlange_index] = (Skifahrer){0}; /* skifahrer aus warteschlange löschen */
	
	printf("\n\nskifahrer in lift.position funktion: %4d", lift_in_station->skifahrer1.aktuelle_position); /* testprint */
}	
	
int main(int argc, char *argv[]) {
	
	int skifahrer_liste_index, warteschlange_tal_index;
	skifahrer_liste_index = 0;
	warteschlange_tal_index = 0;
	
//	Skifahrer *skifahrer1ptr, skifahrer1;
//	skifahrer1ptr = &skifahrer1;
	
	Skifahrer skifahrer_liste[2010];
	Skifahrer warteschlange_tal[500];
	
//	Lift *lift1ptr, lift1;
//	lift1ptr = &lift1;
//	
//    lift_liste[0].skifahrer1.ankunftsart = 1;
//    lift_liste[0].skifahrer1.uebrige_fahrten = 9999;
//    lift_liste[0].skifahrer1.aktuelle_position = 0;
//    lift_liste[0].skifahrer1.gesamtfahrten = 0;
	
	/* pointer zeigen auf lift_liste. Am Ende eines loops werden die pointer eins vorgerückt. das simuliert die Bewegung der Lifte */
	Lift *lift_in_station_tal          = lift_liste;
	Lift *lift_in_station_mitte_hoch   = &lift_liste[72];
	Lift *lift_in_station_berg         = &lift_liste[55];
	Lift *lift_in_station_mitte_runter = &lift_liste[27];
	
	cursorVerstecken();
	char input;
	input = '\0';

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	minuten = 540; /* wir starten bei 540 Minuten, weil der Skilift 9:00 Uhr aufmacht */
	uhrzeit.stunde = 9; 
	uhrzeit.minute = 0;
	
	loop_anzahl = 1; /* bestimmt, wie oft pro Sekunde der Hauptloop durchlaufen wird. Standardwert ist 1, Turbo ist 10, Pause ist 0 */
	
	/* Variablen zu Testzwecken */
//	schlangenlaenge_tal = 1;
//	schlangenlaenge_berg = 0;
	
	/* einzelner Skifahrer zu testzwecken */
//	skifahrer1ptr->ankunftsart = 0;
//	skifahrer1ptr->gesamtfahrten = 0;
//	skifahrer1ptr->uebrige_fahrten = 9999;
//	skifahrer1ptr->aktuelle_position = schlange_tal;	
	
//	tal_zu_mitte(&skifahrer1, &lift1);
//	printf("%d", skifahrer1.aktuelle_position); /*die Position ändert sich nur während der funktion, nicht permanent. Muss gefixt werden! */
	
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
		getS1time();
		getB1time();
		getB2time();	
		getR1time();	
		getR2time();
	
	/*	Zu testzwecken 
		cursorSetzen(hStdout, 0, 0);
		printf("S1randZeit: %d    S1reverseminute: %d  \n", S1randZeit, S1reverseminute);
		printf("B1randZeit: %d  \n", B1randZeit);
		printf("B2randZeit: %d  \n", B2randZeit);
		printf("R1randZeit: %d  \n", R1randZeit);
		printf("R2randZeit: %d  \n", R2randZeit);
	*/
	
	/* zu testzwecken */
		cursorSetzen(hStdout, 0, 0);
//		printf("uebrige Fahrten von Skifahrer1 TAL:          %d    \n", warteschlange_tal->			skifahrer1.uebrige_fahrten);
//		printf("uebrige Fahrten von Skifahrer1 MITTE HOCH:   %d    \n", warteschlange_mitte_hoch->	skifahrer1.uebrige_fahrten);
//		printf("uebrige Fahrten von Skifahrer1 BERG:         %d    \n", warteschlange_berg->			skifahrer1.uebrige_fahrten);
//		printf("uebrige Fahrten von Skifahrer1 MITTE RUNTER: %d    \n", warteschlange_mitte_runter->	skifahrer1.uebrige_fahrten);
	
		int i;
		
		for (i = 0; i < loop_anzahl; i++)
		{	
			neuenSkifahrerErstellen(skifahrer_liste, warteschlange_tal, &skifahrer_liste_index, &warteschlange_tal_index);
			printf("\nskifahrer.uebrig in main: %4d", skifahrer_liste[skifahrer_liste_index -1].uebrige_fahrten);
			printf("\nwarteschlange[index].uebrig main: %4d", warteschlange_tal[warteschlange_tal_index-1].uebrige_fahrten);
			
			liftBetreten(lift_in_station_tal, warteschlange_tal, &warteschlange_tal_index);
			printf("\nskifahrer in lift.position main: %4d", lift_in_station_tal->skifahrer1.aktuelle_position);
			
			cursorSetzen(hStdout, 0, 10); /* setzt Cursor an den Anfang, damit Ausgabe scheinbar konstant bleibt */
			printf( "\n10er-Karten:  %3d                                   ___Bergstation Schlange: %d\n"
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
					, zehnerkarten, schlangenlaenge_berg, anzahl_berg_zu_mitte, anzahl_tal_zu_mitte, schlangenlaenge_tal);
			
			uhrzeitAusgeben(uhrzeit); /* uhrzeit hat ein paar Eigenheiten, weswegen sie eine extrafunktion zum printen kriegt */
			
			/* nur zu testzwecken hier */              
			
			minuten++; /* eine minute vergeht */
			uhrzeitAnpassen(minuten); /* minuten werden in uhrzeitformat umgewandelt */		
//			positionen_checken(skifahrer1);			
			
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
			
			/* Liftbewegung */
			*lift_in_station_tal++;
			*lift_in_station_mitte_hoch++;
			*lift_in_station_berg++;
			*lift_in_station_mitte_runter++;
			
			zehnerkarten++;
		}

		Sleep(1000); /* wartet eine sekunde */  
	
		input = '\0';
		if (kbhit()) /* checkt, ob Taste gedrückt wurde */
		{
	        input = tolower(getch()); // Benutzereingabe lesen	
			fflush(stdout);	
		} else {
			input = '\0';
		}


        if (input == '0') // Progamm beendung mit 0
		{   
			cursorSetzen(hStdout, 0, 24); /* Cursor ans Ende setzen, damit die exit-messsage nicht ins Programm geprintet wird */
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

/*Randomzeit für die S1*/
void getS1time()
{
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
void getB1time()
{
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
	} else {
		B1randZeit = (rand() % B1ungewoehnlichhoch)+23;
	}
}
	
/*Randomzeit für die B2*/
void getB2time()
{	
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
	} else {
		B2randZeit = (rand() % B2ungewoehnlichhoch)+42;
			
	}	
}
	
/*Randomzeit für die R1*/
void getR1time()
{		
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
	} else {
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
   Da ich jetzt weiß, wie man immer die gleiche Menge Platz beim printen reserbveiert, ist diese Funktion irrelevant.
   Entfernen, wenn Zeit dafür da ist. */
void uhrzeitAusgeben(Uhrzeit uhrzeit)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */

	/* packt 0 vor die Stunde wenn es um 9 ist, ansonsten wird die Stunde einfach nur geprintet */
	cursorSetzen(hStdout, 0, 18);	
	if (uhrzeit.stunde == 9) 
	{
		printf("0%i", uhrzeit.stunde);
	} 
	else 
	{
		printf("%i", uhrzeit.stunde);
	}
	
	/* packt 0 vor einstellige Minuten */
	cursorSetzen(hStdout, 3, 18);	
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
//void tal_zu_mitte(Skifahrer *skifahrer1, Lift *lift1)
//{
//	lift1->skifahrer1 = *skifahrer1;
//	skifahrer1->aktuelle_position = lift_tal_zu_mitte;
//	skifahrer1->uebrige_fahrten--;
//}


/* soll durch gesamte skifahrer_liste durchgehen und deren positionen bestimmen */
void positionen_checken(Skifahrer skifahrer1)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	cursorSetzen(hStdout, 5, 0);
//	printf("Aktuelle_pos in funktion: %d", skifahrer1.aktuelle_position);
//	printf("    Anzahl_tal_zu_mitte in funktion: %d ", anzahl_tal_zu_mitte);
	
	switch(skifahrer1.aktuelle_position)
	{
		case lift_tal_zu_mitte: anzahl_tal_zu_mitte++; 
		break;
	}
//	printf(" Anzahl tal_zu_mitte: %d", anzahl_tal_zu_mitte);
}
