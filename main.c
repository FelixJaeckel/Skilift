#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define ABWESEND 					100
#define SCHLANGE_TAL 				101
#define SCHLANGE_MITTE_ZU_BERG 		102
#define SCHLANGE_BERG 				103
#define SCHLANGE_MITTE_ZU_TAL 	104
#define LIFT_TAL_ZU_MITTE			105
#define LIFT_MITTE_ZU_BERG			106
#define LIFT_BERG_ZU_MITTE			107
#define LIFT_MITTE_ZU_TAL			108
#define PISTE_S1					109
#define PISTE_B2					110
#define PISTE_R2					111
#define PISTE_B1					112
#define PISTE_R1					113

typedef struct Skifahrer
{
	int ankunftsart;
	int uebrige_fahrten;
	int aktuelle_position;
	int gesamtfahrten;
	int index;
	int uebrige_zeit_auf_piste;
} Skifahrer;

typedef struct Lift
{
	Skifahrer skifahrer1;
	Skifahrer skifahrer2;
	Skifahrer skifahrer3;
	Skifahrer skifahrer4;
} Lift;

/* Ich bin mir nicht sicher, aber ich glaube diese Struktur ist komplett unnötig. Warteschlange kann vermutlich ein einfaches Array sein */
typedef struct Warteschlange
{
	int wartschlange_index;
	int skifahrer_index;
} Warteschlange;

typedef struct Uhrzeit 
{
    int stunde;
    int minute;
} Uhrzeit;


int cursorSetzen(HANDLE, unsigned short, unsigned short);
void cursorVerstecken();

int zurueckAuf110(int);
void SkifahrerListeMitDummysFuellen();
void positionenChecken(Skifahrer[]);
void zaehlvariablenAufNullSetzen();
void getGesamtFahrten();
void getPersonenAufBerg();

void uhrzeitAnpassen(int);
void uhrzeitAusgeben(struct Uhrzeit);

void neuenSkifahrerErstellen(Skifahrer[]);
void mehrereSkifahrerErstellen(int);

void liftBetretenTal(int);
void liftBetretenBerg(int);
void liftVerlassenTal(int);
void liftVerlassenBerg(int);

void warteschlangeBetretenTal(Skifahrer);
void warteschlangeBetretenBerg(Skifahrer);

void pisteBetreten(Skifahrer, int);
void uebrigeZeitAufPisteSenken(Skifahrer[]);

void skifahrerEntscheidung(Skifahrer);

int getS1time();
int getB1time();
int getB2time();
int getR1time();
int getR2time();


/* Globale Variablen sollten an sich vermieden werden, aber bei einem Projekt dieser Größe sollten sie zu managen sein. Die Alternative (Pointer) hat nicht funktioniert bzw war zu komplex */
int zehnerkarten, tageskarten, 
	warteschlange_tal_index, warteschlange_berg_index,
	skifahrer_liste_index,
	tag_gesamtfahrten, personen_auf_berg,
	minuten, loop_anzahl, neue_skifahrer_pro_minute,
	schlangenlaenge_tal, 		   anzahl_tal_zu_mitte,	 anzahl_R1,
	schlangenlaenge_berg,	 	   anzahl_mitte_zu_berg, anzahl_B1, 
	schlangenlaenge_mitte_zu_berg, anzahl_berg_zu_mitte, anzahl_B2,      
	schlangenlaenge_mitte_zu_tal,  anzahl_mitte_zu_tal,	 anzahl_R2, anzahl_S1,	
	S1randZeit, S1feierabendzeit,  S1ungewoehnlichhoch,  S1reverseminute,
	B1randZeit, B1feierabendzeit,  B1ungewoehnlichhoch,  B1reverseminute,
	B2randZeit, B2feierabendzeit,  B2ungewoehnlichhoch,  B2reverseminute,
	R1randZeit, R1feierabendzeit,  R1ungewoehnlichhoch,  R1reverseminute,
	R2randZeit, R2feierabendzeit,  R2ungewoehnlichhoch,  R2reverseminute;
	

Warteschlange warteschlange_tal[500];  
Warteschlange warteschlange_berg[500];  
Skifahrer skifahrer_liste[2010];
Lift lift_liste[110]; 
Uhrzeit uhrzeit;
Skifahrer skifahrer_liste[2010];


int main(int argc, char *argv[]) {
	
	int lift_in_station_tal_index, lift_in_station_mitte_hoch_index, lift_in_station_berg_index, lift_in_station_mitte_runter_index;
	skifahrer_liste_index = 0;
	warteschlange_tal_index = 0;
	warteschlange_berg_index = 0;
	zehnerkarten = 0;
	tag_gesamtfahrten = 0;
	neue_skifahrer_pro_minute = 100;
	zaehlvariablenAufNullSetzen(); /* initalisiert alle Zaehler-Variablen zum ersten Mal, auch wenn der Hauptnutzen der Funktion in positionenChecken() liegt */
	
	lift_in_station_tal_index 		   = 0;
	lift_in_station_mitte_hoch_index   = 27;
	lift_in_station_berg_index 		   = 55;
	lift_in_station_mitte_runter_index = 82;
	

	/* Die Lift-Variablen hier sind aktuell nutzlos und ein Ueberbleibsel von vorherigen Versuchen */
//	Lift lift_in_station_tal          = lift_liste[lift_in_station_tal_index];
//	Lift lift_in_station_mitte_hoch   = lift_liste[lift_in_station_mitte_hoch_index];
//	Lift lift_in_station_berg         = lift_liste[lift_in_station_berg_index];
//	Lift lift_in_station_mitte_runter = lift_liste[lift_in_station_mitte_runter_index];
	
	SkifahrerListeMitDummysFuellen();
		
	cursorVerstecken();
	char input;
	input = '\0';

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	minuten = 540; /* wir starten bei 540 Minuten, weil der Skilift 9:00 Uhr aufmacht */
	uhrzeit.stunde = 9; 
	uhrzeit.minute = 0;
	
	loop_anzahl = 1; /* bestimmt, wie oft pro Sekunde der Hauptloop durchlaufen wird. Standardwert ist 1, Turbo ist 10, Pause ist 0 */
	
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
		int i, j, k;
		
		for (i = 0; i < loop_anzahl; i++)
		{	
			mehrereSkifahrerErstellen(neue_skifahrer_pro_minute);
			for (j = 0; j < 6; j++)
			{
				cursorSetzen(hStdout, 0, 0);
//				printf("\nwarteschlange_tal skifahrer index main: %d", warteschlange_tal[warteschlange_tal_index - 1].skifahrer_index);
//				test(warteschlange_tal, &warteschlange_tal_index);
				printf("skifahrer_liste_index: %3d", skifahrer_liste_index);
				printf("\nwarteschlange_tal_index: %3d", warteschlange_tal_index);
				printf("\nskifahrer_liste[2].pos: %3d", skifahrer_liste[2].aktuelle_position);
				
				liftVerlassenBerg(lift_in_station_berg_index);
//				printf("\nskifahrer_liste[2].pos: %3d", skifahrer_liste[2].aktuelle_position);
				liftVerlassenTal(lift_in_station_tal_index);		
				
				liftBetretenTal(lift_in_station_tal_index);
//				printf("\nskifahrer_liste[index].pos main: %3d", skifahrer_liste[skifahrer_liste_index -1 ].aktuelle_position);
//				printf("\nlift_liste[108].skifahrer1.pos: %3d", lift_liste[108].skifahrer1.aktuelle_position);
				liftBetretenBerg(lift_in_station_berg_index);
				
				
				/* Liftbewegung */
				lift_in_station_tal_index--;
				lift_in_station_mitte_hoch_index--;
				lift_in_station_berg_index--;
				lift_in_station_mitte_runter_index--;
				
				lift_in_station_tal_index 		   = zurueckAuf110(lift_in_station_tal_index);
				lift_in_station_mitte_hoch_index   = zurueckAuf110(lift_in_station_mitte_hoch_index);
				lift_in_station_berg_index 		   = zurueckAuf110(lift_in_station_berg_index);
				lift_in_station_mitte_runter_index = zurueckAuf110(lift_in_station_mitte_runter_index);			
			}
			
			uebrigeZeitAufPisteSenken(skifahrer_liste);
			positionenChecken(skifahrer_liste);
			getGesamtFahrten();
			getPersonenAufBerg();
			
			cursorSetzen(hStdout, 0, 6); /* setzt Cursor an den Anfang, damit Ausgabe scheinbar konstant bleibt */
			printf( "\n10er-Karten:  %3d                                   ___Bergstation Schlange: %d	\n"
					"Tageskarten:  %3d                                   /        |    |  Lift ab: %d 	\n"
					"Skifahrten:   %4d                                 /        /     |					\n"
					"                                                -        /      |					\n"
					"                                               /        |       |					\n"
					"Lift M<>B:  22                               B2: %3d   R2: %3d /					\n"
					"                                             /        /       /					\n"
					"                                         ----        |       /						\n"
					"                                        /           /       /       Lift auf:  %3d \n"
					"                                        Mittelstation      |						\n"
					"                                   _____Bistro:  7        /         Lift ab:   %3d \n"
					"                                  /       \\             |							\n"
					"                                  \\        |           /							\n"
					"Lift T<>M:  14                   B1:  %3d    R1: %3d   /  S1:  %3d					\n"
					"                                   \\        \\       /							\n"
					"                                    \\       /       /           Lift auf:  %3d	\n"
					"                                     ----Talstation Schlange: %3d					\n"
					"%02d:%02d Uhr                               (H):  0								\n"
				   	"Personen auf Berg:  %4d                  [P]:  1 Auto								\n"
					"Gesamtfahrten heute: %4d															\n"
					"...(T)urbo\n"
					"...(P)ause"                                                
					, zehnerkarten, schlangenlaenge_berg, tageskarten, anzahl_berg_zu_mitte, tag_gesamtfahrten, anzahl_B2, anzahl_R2, anzahl_mitte_zu_berg, anzahl_mitte_zu_tal, anzahl_B1, anzahl_R1
					, anzahl_S1, anzahl_tal_zu_mitte, warteschlange_tal_index, uhrzeit.stunde, uhrzeit.minute, personen_auf_berg, tag_gesamtfahrten);
						
			
//			uhrzeitAusgeben(uhrzeit); /* uhrzeit hat ein paar Eigenheiten, weswegen sie eine extrafunktion zum printen kriegt */           
			
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
			
			neue_skifahrer_pro_minute = neue_skifahrer_pro_minute - 10;
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
			cursorSetzen(hStdout, 0, 32); /* Cursor ans Ende setzen, damit die exit-messsage nicht ins Programm geprintet wird */
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

void neuenSkifahrerErstellen(Skifahrer skifahrer_liste[]){
	Skifahrer skifahrer; /* Skifahrerobjekt erstellen */
	Warteschlange schlangenplatz; /* Platz des Skifahrers in der Warteschlange erstellen */
	
	skifahrer.aktuelle_position = SCHLANGE_TAL;	/* ein frisch erstellter Skifahrer wird sich immer zuerst im Tal anstellen */
	skifahrer.ankunftsart = 1;	/* TODO: verschiedene ankunftsarten impementieren */
	skifahrer.gesamtfahrten = 0;  /* Gesamtfahrten am Anfang bei 0 */
	skifahrer.uebrige_zeit_auf_piste = 9999;  /* startet bei 9999 (0 wäre problematisch, siehe uebriegeZeitAufPisteSenken()), kriegt eigentliche Zeit, wenn Fahrer Piste betritt */
	skifahrer.index = skifahrer_liste_index;  /* Index des Skifahrers ist auch index in der skifahrer_liste */
	
	/* 50/50 chance, ob 10er oder Tageskarte */
	int r; 
	r = rand() % 2;
	 if (r == 0)
	 {
	 	skifahrer.uebrige_fahrten = 10;	
	 	zehnerkarten++;
	 } else if (r == 1){
	 	skifahrer.uebrige_fahrten = 9999;	
	 	tageskarten++;
	 }

	skifahrer_liste[skifahrer_liste_index] = skifahrer; /* skifahrer wird in skifahrer liste geschrieben */

	/* TODO: Warteschlangen sind LIFO, müssen aber FIFO sein */
	/* Platz in Warteschlange wird ein skifahrer und der entsprechende Eintrag im Warteschlangen-Array jeweils per index zugeordnet */
	schlangenplatz.skifahrer_index = skifahrer.index;  
	schlangenplatz.wartschlange_index = warteschlange_tal_index; /* an dem Punkt bin ich mir unsicher, wozu ich überhaupt einen indexwert beim schlangenplatz erstellt hab */
	warteschlange_tal[warteschlange_tal_index] = schlangenplatz;
	skifahrer_liste_index = skifahrer_liste_index +1;  /* skifahrer listen index um eins erhöhen, damit der nächste skifahrer dorthin geschrieben wird */
	warteschlange_tal_index++;  /* warteschlangen index erhöhen */
}

void skifahrerEntscheidung(Skifahrer skifahrer)
{	
	int r;
	switch (skifahrer.aktuelle_position)
	{
		case LIFT_MITTE_ZU_BERG: 
			r = rand() % 4;
			if (r == 0){
				warteschlangeBetretenBerg(skifahrer); break;
			} else if (r == 1){
				pisteBetreten(skifahrer, PISTE_S1); break;
			} else if (r == 2){
				pisteBetreten(skifahrer, PISTE_B1); break;
			} else if (r == 3){
				pisteBetreten(skifahrer, PISTE_R1); break;
			}
		case LIFT_MITTE_ZU_TAL:
			r = rand() % 2;
			if (r == 0){
				skifahrer.aktuelle_position = ABWESEND; break;
			} else if (r == 1){
				warteschlangeBetretenTal(skifahrer); break;
			}
		case PISTE_S1:
			r = rand() % 2;
			if (r == 0){
				skifahrer.aktuelle_position = ABWESEND; break;
			} else if (r == 1){
				warteschlangeBetretenTal(skifahrer); break;
			}
		case PISTE_B2:
			r = rand() % 2;
			if (r == 0){
				skifahrer.aktuelle_position = ABWESEND; break;
			} else if (r == 1){
				warteschlangeBetretenTal(skifahrer); break;
			}
		case PISTE_R2:
			r = rand() % 2;
			if (r == 0){
				skifahrer.aktuelle_position = ABWESEND; break;
			} else if (r == 1){
				warteschlangeBetretenTal(skifahrer); break;
			}			
	}
}

void liftBetretenTal(int lift_in_station_tal_index)
{	
	int temp_skifahrer_liste_index; /* temporaerer index für den Skifahrer, der in dieser Funktion den Lift betritt */
	warteschlange_tal_index = warteschlange_tal_index -1; /* um eins senken, weil index vorher bei leerer Stelle ist */ 
	temp_skifahrer_liste_index = warteschlange_tal[warteschlange_tal_index].skifahrer_index;  /* Index von Skifahrer in Warteschlange holen */
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = LIFT_MITTE_ZU_BERG;  /* position von Skifahrer updaten */
	lift_liste[lift_in_station_tal_index].skifahrer1 = skifahrer_liste[temp_skifahrer_liste_index]; /* skifahrer in die lift_liste schreiben */

	warteschlange_tal[warteschlange_tal_index] = (Warteschlange){0}; /* skifahrer aus warteschlange loeschen. Warteschlange_index hat jetzt wieder den vordersten leeren Punkt der Schlange */
}

void liftBetretenBerg(int lift_in_station_berg_index)
{	
	int temp_skifahrer_liste_index; /* temporaerer index für den Skifahrer, der in dieser Funktion den Lift betritt */
	warteschlange_berg_index = warteschlange_berg_index -1; /* um eins senken, weil index vorher bei leerer Stelle ist */ 
	temp_skifahrer_liste_index = warteschlange_berg[warteschlange_berg_index].skifahrer_index;  /* Index von Skifahrer in Warteschlange holen */
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = LIFT_MITTE_ZU_TAL;  /* position von Skifahrer updaten */
	lift_liste[lift_in_station_berg_index].skifahrer1 = skifahrer_liste[temp_skifahrer_liste_index]; /* skifahrer in die lift_liste schreiben */

	warteschlange_berg[warteschlange_berg_index] = (Warteschlange){0}; /* skifahrer aus warteschlange loeschen. Warteschlange_index hat jetzt wieder den vordersten leeren Punkt der Schlange */
}

void liftVerlassenTal(int lift_in_station_tal_index)
{
	if (lift_liste[lift_in_station_tal_index].skifahrer1.index == 0) 
	{
		return;	
	}

	int temp_skifahrer_liste_index; /* temporaerer index für den Skifahrer, der hier ankommt */
	
	temp_skifahrer_liste_index = lift_liste[lift_in_station_tal_index].skifahrer1.index; /* temporaerer Index ist Index von skifahrer1 aus dem Lift der aktuell oben ist. 
																							 Wenn niemand da ist, defaultet der Wert zu 0. Das ist ein Problem */
	printf("\n liftVerlassenTal temp_index: %3d", temp_skifahrer_liste_index);
	lift_liste[lift_in_station_tal_index].skifahrer1 = (Skifahrer){0}; /* Skifahrer wird aus Lift entfernt */
	skifahrerEntscheidung(skifahrer_liste[temp_skifahrer_liste_index]);
	/* TODO: Skifahrer müssen verschiedene Wege einschlagen können */
}

/* TODO: irgendwas dagegen machen, dass der standardwert für nicht zuweisbare ints 0 ist, weswegen skifahrer_liste[0] sich sofort hier hoch beamt */	
void liftVerlassenBerg(int lift_in_station_berg_index)
{
	if (lift_liste[lift_in_station_berg_index].skifahrer1.index == 0) {
		return;	
	}
	int temp_skifahrer_liste_index; /* temporaerer index für den Skifahrer, der hier ankommt */
	
	temp_skifahrer_liste_index = lift_liste[lift_in_station_berg_index].skifahrer1.index; /* temporaerer Index ist Index von skifahrer1 aus dem Lift der aktuell oben ist. 
																							 Wenn niemand da ist, defaultet der Wert zu 0. Das ist ein Problem */
	printf("\n liftVerlassenBerg temp_index: %3d", temp_skifahrer_liste_index);
	lift_liste[lift_in_station_berg_index].skifahrer1 = (Skifahrer){0}; /* Skifahrer wird aus Lift entfernt */
	skifahrerEntscheidung(skifahrer_liste[temp_skifahrer_liste_index]);
	/* TODO: Skifahrer müssen verschiedene Wege einschlagen können */
}

void warteschlangeBetretenTal(Skifahrer skifahrer)
{
	int temp_skifahrer_liste_index;
	temp_skifahrer_liste_index = skifahrer.index;
	warteschlange_tal[warteschlange_tal_index].skifahrer_index = skifahrer.index;
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = SCHLANGE_TAL;
	skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = 9999;
	
	warteschlange_tal_index++;
}

void warteschlangeBetretenBerg(Skifahrer skifahrer)
{
	int temp_skifahrer_liste_index;
	temp_skifahrer_liste_index = skifahrer.index;
	warteschlange_berg[warteschlange_berg_index].skifahrer_index = skifahrer.index;
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = SCHLANGE_BERG;
	skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = 9999;
	
	warteschlange_berg_index++;
}

void pisteBetreten(Skifahrer skifahrer, int piste)
{
	int temp_skifahrer_liste_index;
	temp_skifahrer_liste_index = skifahrer.index;
	// printf("  pisteBetreten temp_index: %3d", temp_skifahrer_liste_index);
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = piste;	
	skifahrer_liste[temp_skifahrer_liste_index].uebrige_fahrten--;	
	skifahrer_liste[temp_skifahrer_liste_index].gesamtfahrten++;	
	// printf("\npisteBetrten fahrer_liste[index].pos: %3d", skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position);
	
	switch (piste)
	{
		case PISTE_S1: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = getS1time(); break;
		case PISTE_R1: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = getR1time(); break;
		case PISTE_B1: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = getB1time(); break;
		case PISTE_R2: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = getR2time(); break;
		case PISTE_B2: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = getB2time(); break;
		default: printf("\n aus irgendeinem Grund ist der im default gelandet"); break;
	}
}

void uebrigeZeitAufPisteSenken(Skifahrer skifahrer_liste[])
{
	int i;
	for (i = 0; i <= 2010; i++)
	{
		if(skifahrer_liste[i].uebrige_zeit_auf_piste == 0)
		{
			skifahrerEntscheidung(skifahrer_liste[i]);
		} else {
			skifahrer_liste[i].uebrige_zeit_auf_piste--;			
		}
	}
	
}

void SkifahrerListeMitDummysFuellen()
{
	int i;
	i = 0;
	for (i; i <= 2010; i++)
	{
		Skifahrer skifahrer;
		skifahrer_liste[i].aktuelle_position = ABWESEND;
		skifahrer_liste[i].ankunftsart = 1;
		skifahrer_liste[i].gesamtfahrten = 0;
		skifahrer_liste[i].index = 9999; /* Wert, der außerhalb der eigentlichen länge der Liste liegt, damit nicht irgendwie ausversehen drauf zugegriffen wird */
		skifahrer_liste[i].uebrige_fahrten = 0;
		skifahrer_liste[i].uebrige_zeit_auf_piste = 9999;
	}
}

/* setzt Zahl auf 110, wenn sie -1 erreicht. Fuer Lift-loop benoetigt */
int zurueckAuf110(int zahl){
	if (zahl == -1){
		zahl = 110;
	}
	return zahl;
}

/* Randomzeit fuer die S1 */
int getS1time()
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
		S1randZeit = (rand() % 51)+9;/*ZufÃ¤llige zeit zwischen 9 und 59*/
	}else{
		S1randZeit = (rand() % S1ungewoehnlichhoch)+59;	
	}
	return S1randZeit;
}
	
/*Randomzeit fuer die B1*/
int getB1time()
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
		B1randZeit = (rand() % 21)+3;/*ZufÃ¤llige zeit zwischen 3 und 24*/
	} else {
		B1randZeit = (rand() % B1ungewoehnlichhoch)+23;	
	}
	return B1randZeit;
}
	
/*Randomzeit fuer die B2*/
int getB2time()
{	
	if(B2reverseminute <= 5)
	{
		/*deaktiviert switch case*/
		/*printf("B2 ist Geschlossen");*/
		B2randZeit = 0;
	} else if(B2reverseminute <= 42){
		B2randZeit = (rand() % B2feierabendzeit)+5;
	} else if(rand() % 100 > 10){
		B2randZeit = (rand() % 38)+5;/*ZufÃ¤llige zeit zwischen 5 und 42*/
	} else {
		B2randZeit = (rand() % B2ungewoehnlichhoch)+42;		
	}
	return B2randZeit;
}

/*Randomzeit fuer die R1*/
int getR1time(){		
	if(R1reverseminute <= 3)
	{
		/*deaktiviert switch case*/
		/*printf("R1 ist Geschlossen");*/
		R1randZeit = 0;
	} else if(R1reverseminute <= 20)
	{
		R1randZeit = (rand() % R1feierabendzeit)+3;
	} else if(rand() % 100 > 10){
		R1randZeit = (rand() % 18)+3;/*ZufÃ¤llige zeit zwischen 3 und 20*/
	}else{
		R1randZeit = (rand() % R1ungewoehnlichhoch)+20;
	}
	return R1randZeit;
}
	
/*Randomzeit fuer die R2*/
int getR2time(){			
	if(R2reverseminute <= 3)
	{
		/*deaktiviert switch case*/
		/*printf("R2 ist Geschlossen");*/
		R2randZeit = 0;
	} else if(R2reverseminute <= 37)
	{
		R2randZeit = (rand() % R2feierabendzeit)+3;
	} else if(rand() % 100 > 10){
		R2randZeit = (rand() % 35)+3;/*ZufÃ¤llige zeit zwischen 3 und 38*/
	}else{
		R2randZeit = (rand() % R2ungewoehnlichhoch)+37;
	}
	return R2randZeit;
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
//void uhrzeitAusgeben(Uhrzeit uhrzeit)
//{
//	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
//
//	/* packt 0 vor die Stunde wenn es um 9 ist, ansonsten wird die Stunde einfach nur geprintet */
//	cursorSetzen(hStdout, 0, 27);	
//	if (uhrzeit.stunde == 9) 
//	{
//		printf("0%i", uhrzeit.stunde);
//	} 
//	else 
//	{
//		printf("%i", uhrzeit.stunde);
//	}
//	
//	/* packt 0 vor einstellige Minuten */
//	cursorSetzen(hStdout, 3, 27);	
//	if (uhrzeit.minute >= 10) 
//	{
//		printf("%i", uhrzeit.minute);
//	} 
//	else 
//	{
//		printf("0%i", uhrzeit.minute);
//	} 
//	return;
//}

/* Geht durch gesamte skifahrer_liste durch und bestmmt position von jedem einzelnen Eintrag. Die Zählervariable der entsprechenden Position wird dann um 1 erhöht. 
   Vorher werden alle Positionen auf 0 gesetzt. Dadurch weiß man immer, wie viele Skifahrer wo sind. */
void positionenChecken(Skifahrer skifahrer_liste[])
{
	zaehlvariablenAufNullSetzen();
	int i;
	i = 1;
	while (i <= 2010)
	{
		switch(skifahrer_liste[i].aktuelle_position)
		{
			case SCHLANGE_TAL: 			 schlangenlaenge_tal++; 			break;
			case SCHLANGE_MITTE_ZU_BERG: schlangenlaenge_mitte_zu_berg++; 	break;
			case SCHLANGE_BERG: 		 schlangenlaenge_berg++; 			break;
			case SCHLANGE_MITTE_ZU_TAL:  schlangenlaenge_mitte_zu_tal++; 	break;
			case LIFT_TAL_ZU_MITTE: 	 anzahl_tal_zu_mitte++; 			break;
			case LIFT_MITTE_ZU_BERG: 	 anzahl_mitte_zu_berg++; 			break;
			case LIFT_BERG_ZU_MITTE: 	 anzahl_berg_zu_mitte++; 			break;
			case LIFT_MITTE_ZU_TAL: 	 anzahl_mitte_zu_tal++; 			break;
			case PISTE_S1: 				 anzahl_S1++; 						break;
			case PISTE_B1: 				 anzahl_B1++; 						break;
			case PISTE_R1: 				 anzahl_R1++; 						break;
			case PISTE_B2: 				 anzahl_B2++; 						break;
			case PISTE_R2: 				 anzahl_R2++; 						break;
			case ABWESEND: break;								
		}
		i++;
	}
}

void getGesamtFahrten()
{
	tag_gesamtfahrten = 0;
	int i;
	i = 1;
	while (i <= 2010)
	{
		tag_gesamtfahrten = tag_gesamtfahrten + skifahrer_liste[i].gesamtfahrten;
		i++;
	}
}

/* ziemlich selbsterklaerend. Hauptsaechlich zur Verwendung in positionenChecken() */
void zaehlvariablenAufNullSetzen()
{
	schlangenlaenge_tal 		  = 0; 			
	schlangenlaenge_mitte_zu_berg = 0; 	
	schlangenlaenge_berg 		  = 0; 			
	schlangenlaenge_mitte_zu_tal  = 0; 	
	anzahl_tal_zu_mitte  = 0; 			
	anzahl_mitte_zu_berg = 0; 			
	anzahl_berg_zu_mitte = 0; 			
	anzahl_mitte_zu_tal  = 0; 			
	anzahl_S1 = 0; 						
	anzahl_B1 = 0; 						
	anzahl_R1 = 0; 						
	anzahl_B2 = 0; 						
	anzahl_R2 = 0; 							
}

void getPersonenAufBerg()
{
	int abwesend, i;
	i = 0;
	abwesend = 0;
	while (i <= 2010)
	{
		if (skifahrer_liste[i].aktuelle_position == ABWESEND)
		{
			abwesend++;
		}
		i++;
	}
	personen_auf_berg = 2010 - abwesend;
}

void mehrereSkifahrerErstellen(int neue_skifahrer_pro_minute)
{
	for (neue_skifahrer_pro_minute; neue_skifahrer_pro_minute > 0; neue_skifahrer_pro_minute--)
	{
		neuenSkifahrerErstellen(skifahrer_liste);
	}
}