#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define ABWESEND 					404
#define SCHLANGE_TAL 				101
#define SCHLANGE_MITTE_ZU_BERG 		102
#define SCHLANGE_BERG 				103
#define SCHLANGE_MITTE_ZU_TAL 		104
#define SCHLANGE_BUS				105
#define LIFT_TAL_ZU_MITTE			106
#define LIFT_MITTE_ZU_BERG			107
#define LIFT_BERG_ZU_MITTE			108
#define LIFT_MITTE_ZU_TAL			109
#define PISTE_S1					110
#define PISTE_B2					111
#define PISTE_R2					112
#define PISTE_B1					113
#define PISTE_R1					114
#define Bistro						115
#define ZU_FUSS						201
#define AUTO						202
#define BUS							203

/* Strukturen */
typedef struct Skifahrer
{
	int ankunftsart;
	int uebrige_fahrten;
	int aktuelle_position;
	int gesamtfahrten;
	int index;
	int uebrige_zeit_auf_piste;
	int uebrige_zeit_im_lift;
} Skifahrer;

typedef struct Warteschlange
{
	int warteschlange_index;
	int skifahrer_index;
} Warteschlange;

typedef struct Uhrzeit 
{
    int stunde;
    int minute;
} Uhrzeit;

/*Funktionen Prototypen*/
void cursorVerstecken();

void allgemeineWerteDefinieren();
void pistenWerteDefinieren();
void skifahrerListeMitDummysFuellen();
void warteschlangenMitDummysFuellen();
void positionenChecken();
void zaehlvariablenAufNullSetzen();
void getPersonenAufBerg();

void uhrzeitAnpassen(int);
void uhrzeitAusgeben(struct Uhrzeit);

void neuenSkifahrerErstellen(int);
void mehrereSkifahrerErstellen(int);

void busKommtAn();
void warteschlangeBetretenBus(Skifahrer);
void busFaehrtAb();

void liftBetretenTal();
void liftBetretenBerg();
void liftBetretenMitteHoch();
void liftBetretenMitteRunter();
void uebrigeZeitImLiftSenken();

void warteschlangeBetretenTal(Skifahrer);
void warteschlangeBetretenBerg(Skifahrer);
void warteschlangeBetretenMitteHoch(Skifahrer);
void warteschlangeBetretenMitteRunter(Skifahrer);

void pisteBetreten(Skifahrer, int);
void uebrigeZeitAufPisteSenken();

void skifahrerEntscheidung(Skifahrer);

void skipistenPrint();
void zaehlerPisten();

int getS1time();
int getB1time();
int getB2time();
int getR1time();
int getR2time();

/* Globale Variablen auf die in allen Funktionen zugegriffen wird. */
int zehnerkarten, tageskarten, 
	warteschlange_tal_index, warteschlange_berg_index, warteschlange_mitte_hoch_index, warteschlange_mitte_runter_index, warteschlange_bus_index,
	skifahrer_liste_index,
	tag_gesamtfahrten, personen_auf_berg,
	minuten, loop_anzahl, neue_skifahrer_pro_minute,
	schlangenlaenge_bus, 
	schlangenlaenge_tal, 		   anzahl_tal_zu_mitte,	 anzahl_R1,
	schlangenlaenge_berg,	 	   anzahl_mitte_zu_berg, anzahl_B1, 
	schlangenlaenge_mitte_zu_berg, anzahl_berg_zu_mitte, anzahl_B2,      
	schlangenlaenge_mitte_zu_tal,  anzahl_mitte_zu_tal,	 anzahl_R2, anzahl_S1, anzahl_bistro,
	S1randZeit, S1feierabendzeit,  S1ungewoehnlichhoch,  S1reverseminute,
	B1randZeit, B1feierabendzeit,  B1ungewoehnlichhoch,  B1reverseminute,
	B2randZeit, B2feierabendzeit,  B2ungewoehnlichhoch,  B2reverseminute,
	R1randZeit, R1feierabendzeit,  R1ungewoehnlichhoch,  R1reverseminute,
	R2randZeit, R2feierabendzeit,  R2ungewoehnlichhoch,  R2reverseminute;
	char input;
	char* busStatus;
/* Eine Warteschlange pro Lift, die Liste mit allen Skifahrern (auch abwesende) und die Uhrzeit werden erstellt */
Warteschlange warteschlange_tal[5000];  
Warteschlange warteschlange_berg[5000];  
Warteschlange warteschlange_bus[5000];
Warteschlange warteschlange_mitte_hoch[5000];
Warteschlange warteschlange_mitte_runter[5000];
Skifahrer skifahrer_liste[5000];
Uhrzeit uhrzeit;


int main(int argc, char *argv[]) {
	int i, j;
	
	allgemeineWerteDefinieren(); 
	
	cursorVerstecken(); 
	
	minuten = 540; /* wir starten bei 540 Minuten, weil der Skilift 9:00 Uhr aufmacht */
	uhrzeit.stunde = 9; 
	uhrzeit.minute = 0;
	
	loop_anzahl = 1; /* bestimmt, wie oft pro Sekunde der Hauptloop durchlaufen wird. Standardwert ist 1, Turbo ist 10, Pause ist 0 */
	
	pistenWerteDefinieren();
	
	/* loop laeuft bis 1320 Minuten, also bis 22:00 Uhr */
	while(minuten <= 1320)
	{
		for (i = 0; i < loop_anzahl; i++) /* Je nach Wert von loop_anzahl ist entweder normales Tempo, Turbo oder Pause */
		{	
			/* Bus kommt alle 20 minuten an und fährt dann 3 Minuten später ab */
			if (uhrzeit.minute == 10 ||uhrzeit.minute == 30 ||uhrzeit.minute == 50){
				busKommtAn();
				busStatus = "Bus kommt jetzt!      ";
			} 
			else if(uhrzeit.minute == 13 || uhrzeit.minute == 33 || uhrzeit.minute == 53){
				busFaehrtAb();
				busStatus = "Bus fahrt ab!         ";
			} else if (uhrzeit.minute == 11 || uhrzeit.minute == 31 || uhrzeit.minute == 51 || uhrzeit.minute == 12 || uhrzeit.minute == 32 || uhrzeit.minute == 52){
				busStatus = "Bus steht da!         ";
			} else{
				busStatus = "Kein Bus da!          ";
			} 

			mehrereSkifahrerErstellen(neue_skifahrer_pro_minute); 
			uebrigeZeitImLiftSenken(); 
			uebrigeZeitAufPisteSenken();

			for (j = 0; j < 6; j++)
			{
				liftBetretenTal();
				liftBetretenBerg();
				liftBetretenMitteHoch();
				liftBetretenMitteRunter();	
			}
			
			positionenChecken();
			getPersonenAufBerg();
			
				/*Bergwache holt alle vom Berg*/
			if(uhrzeit.stunde == 22 && uhrzeit.minute == 00 || uhrzeit.stunde == 22 && uhrzeit.minute == 01 || uhrzeit.stunde == 22 && uhrzeit.minute == 02 || uhrzeit.stunde == 22 && uhrzeit.minute == 03 || uhrzeit.stunde == 22 && uhrzeit.minute == 04 || uhrzeit.stunde == 22 && uhrzeit.minute == 05 || uhrzeit.stunde == 22 && uhrzeit.minute == 06 || uhrzeit.stunde == 22 && uhrzeit.minute == 07){
				zehnerkarten = 0;
				schlangenlaenge_berg = 0;
				tageskarten = 0;
				anzahl_berg_zu_mitte = 0;
				anzahl_B2 = 0;
				anzahl_R2 = 0;
				anzahl_mitte_zu_berg = 0;
				anzahl_mitte_zu_tal = 0;
				anzahl_B1 = 0;
				anzahl_R1 = 0;
				anzahl_S1 = 0;
				anzahl_tal_zu_mitte = 0;
				schlangenlaenge_tal = 0;
				schlangenlaenge_bus = 0;
				personen_auf_berg = 0;
				anzahl_bistro = 0;
			}
			
			skipistenPrint();
		
			minuten++; /* eine minute vergeht */
			uhrzeitAnpassen(minuten); /* minuten werden in uhrzeitformat umgewandelt */
			
			zaehlerPisten();
			neue_skifahrer_pro_minute--;
		}

		Sleep(1000); /* wartet eine sekunde */  
	
		input = '\0';
		if (kbhit()) /* checkt, ob Taste gedrueckt wurde */
		{
	        input = tolower(getch()); 
			fflush(stdout);	
		} else {
			input = '\0';
		}

        if (input == 'b') 
		{   
			printf("\033[0;32H");
			break;  /* beendet Programm */
        }
        else if (input == 't') 
		{
			if (loop_anzahl != 10) /* wenn Turbo aus ist, wechsel zu Turbo */
			{
			    loop_anzahl = 10; 
			} 
			else /* wenn Turbo an ist, wechsel zu Standard */
			{
				loop_anzahl = 1; 
			}
        }     
        else if (input == 'p') 
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

/* einige Werte, die am Anfang von main definiert werden muessen. Funktion dient dazu, main uebersichtlicher zu machen */
void allgemeineWerteDefinieren()
{
	skifahrer_liste_index = 1; /* startet bei 1 statt bei 0 um Ueberschneidungen mit 0 als false zu vermeiden */
	warteschlange_tal_index = 0;
	warteschlange_berg_index = 0;
	warteschlange_mitte_hoch_index = 0;
	warteschlange_mitte_runter_index = 0;
	warteschlange_bus_index = 0;
	zehnerkarten = 0;
	tag_gesamtfahrten = 0;
	neue_skifahrer_pro_minute = 50;
	input = '\0';
	
	zaehlvariablenAufNullSetzen(); /* initalisiert alle Zaehler-Variablen zum ersten Mal, auch wenn der Hauptnutzen der Funktion in positionenChecken() liegt */
	skifahrerListeMitDummysFuellen();
	warteschlangenMitDummysFuellen();
}

/* Werte, die bestimmen, wie lange Skifahrer auf Piste brauchen werden. Werden in den getPisteTime() Funktionen verwendet */
void pistenWerteDefinieren()
{
	/*Variabeln fuer S1*/
	S1randZeit = 0;
	S1ungewoehnlichhoch = 720;
	S1reverseminute = 780;
	
	/*Variabeln fuer B1*/
	B1randZeit = 0;
	B1ungewoehnlichhoch = 758;
	B1reverseminute = 780;
	
	/*Variabeln fuer B2*/
	B2randZeit = 0;
	B2ungewoehnlichhoch = 737;
	B2reverseminute = 780;
	
	/*Variabeln fuer R1*/
	R1randZeit = 0;
	R1ungewoehnlichhoch = 759;
	R1reverseminute = 780;
	
	/*Variabeln fuer R2*/
	R2randZeit = 0;
	R2ungewoehnlichhoch = 743;
	R2reverseminute = 780;
}

/* Stellt den Berg und die Anzahl Skifahrer anb allen Positionen dar */
void skipistenPrint()
{
	printf("\e[1;1H\e[2J");
	printf("\033[0;0H"); /* setzt Cursor an den Anfang, damit Ausgabe scheinbar konstant bleibt */ 
	printf("\n10er-Karten: %4d                                   ___Bergstation Schlange: %4d	\n", zehnerkarten, schlangenlaenge_berg);
	printf("Tageskarten: %4d                                 /        |    |  Lift ab: %4d 	\n", tageskarten, anzahl_berg_zu_mitte);
	printf("Skifahrten: %4d                                 /        /     |					\n", tag_gesamtfahrten);
	printf("                                                -        /      |					\n");
	printf("                                               /        |       |					\n");
	printf("Mitte-hoch Schlange: %4d          B2: %4d   R2: %4d /       /							\n", schlangenlaenge_mitte_zu_tal, anzahl_B2, anzahl_R2);
	printf("                                             /        /       /						\n");
	printf("                                         ----        |       /						\n");
	printf("                                        /           /       /       Lift auf: %4d   \n", anzahl_mitte_zu_berg);
	printf("                                        Mittelstation      |						\n");
	printf("                                   _____Bistro:  %4d      /         Lift ab: %4d    \n", anzahl_bistro, anzahl_mitte_zu_tal);
	printf("                                  /       \\             |							\n");
	printf("                                  \\        |           /							\n");
	printf("Mitte-hoch Schlange: %4d     B1: %4d    R1: %4d   /  S1: %4d					\n", schlangenlaenge_mitte_zu_berg, anzahl_B1, anzahl_R1, anzahl_S1);
	printf("                                   \\        \\       /								\n");
	printf("                                    \\       /       /           Lift auf: %4d		\n", anzahl_tal_zu_mitte);
	printf("                                     ----Talstation Schlange: %4d					\n", schlangenlaenge_tal);
	printf("%02d:%02d Uhr                                 (H): %4d								\n", uhrzeit.stunde, uhrzeit.minute, schlangenlaenge_bus);
	printf("Personen auf Berg: %4d                  [P]:  1 Auto								\n", personen_auf_berg);
	printf("Gesamtfahrten heute: %4d				Busstatus:%s								\n", tag_gesamtfahrten, busStatus);
	printf("...(T)urbo\n");
	printf("...(P)ause\n");
	printf("...(B)eenden");                                            
}

/* Werte fuer die getPisteTime() Funktionen werden gesenkt. */
void zaehlerPisten(){
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
}

/* erstellt einen Skifahrer mit angegebener ankunftsart und stellt ihn in die Talschlange */
void neuenSkifahrerErstellen(int ankunftsart){
	Skifahrer skifahrer; /* Skifahrerobjekt erstellen */
	Warteschlange schlangenplatz; /* Platz des Skifahrers in der Warteschlange erstellen */
	int r; 
	
	skifahrer.aktuelle_position = SCHLANGE_TAL;	/* ein frisch erstellter Skifahrer wird sich immer zuerst im Tal anstellen */
	skifahrer.ankunftsart = ankunftsart;	/* TODO: verschiedene ankunftsarten impementieren */
	skifahrer.gesamtfahrten = 0;  /* Gesamtfahrten am Anfang bei 0 */
	skifahrer.uebrige_zeit_auf_piste = 9999;  /* startet bei 9999 (0 wäre problematisch, siehe uebriegeZeitAufPisteSenken()), kriegt eigentliche Zeit, wenn Fahrer Piste betritt */
	skifahrer.index = skifahrer_liste_index;  /* Index des Skifahrers ist auch index in der skifahrer_liste */
	skifahrer.uebrige_zeit_im_lift = 9999;
	
	/* 50/50 chance, ob 10er oder Tageskarte */
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

	/* Platz in Warteschlange wird ein skifahrer und der entsprechende Eintrag im Warteschlangen-Array jeweils per index zugeordnet */
	schlangenplatz.skifahrer_index = skifahrer.index;  
	schlangenplatz.warteschlange_index = warteschlange_tal_index; /* an dem Punkt bin ich mir unsicher, wozu ich Ueberhaupt einen indexwert beim schlangenplatz erstellt hab */
	warteschlange_tal[warteschlange_tal_index] = schlangenplatz;
	skifahrer_liste_index++;  /* skifahrer listen index um eins erhoehen, damit der naechste skifahrer dorthin geschrieben wird */
	warteschlange_tal_index++;  /* warteschlangen index erhoehen */
}

/* basierend auf der Position aus der der Skifahrer grade kommt, wird er zufaellig eine Piste/eine Warteschlange betreten oder den Berg verlassen */
void skifahrerEntscheidung(Skifahrer skifahrer)
{	
	int r, temp_skifahrer_liste_index;

	temp_skifahrer_liste_index = skifahrer.index;
	if (skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position > 115)
	{
		return;
	}
	
	switch (skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position)
	{
		case LIFT_TAL_ZU_MITTE:
			r = rand() % 5;
			if (r == 0){
				skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = LIFT_MITTE_ZU_BERG; 
				skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_im_lift = 5; break;
			} else if (r == 1){
				warteschlangeBetretenMitteRunter(skifahrer); break;
			} else if (r == 2){
				pisteBetreten(skifahrer, PISTE_B1); break;
			} else if (r == 3){
				pisteBetreten(skifahrer, PISTE_R1); break;
			} else if (r == 4){
				pisteBetreten(skifahrer, Bistro); break;
			}
		
		case Bistro:
			r = rand() % 4;
			if (r == 0){
				skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = LIFT_MITTE_ZU_BERG; 
				skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_im_lift = 5; break;
			} else if (r == 1){
				warteschlangeBetretenMitteRunter(skifahrer); break;
			} else if (r == 2){
				pisteBetreten(skifahrer, PISTE_B1); break;
			} else if (r == 3){
				pisteBetreten(skifahrer, PISTE_R1); break;
			}
			
		case LIFT_MITTE_ZU_BERG: 
			r = rand() % 4;
			if (r == 0){
				warteschlangeBetretenBerg(skifahrer); break;
			} else if (r == 1){
				pisteBetreten(skifahrer, PISTE_S1); break;
			} else if (r == 2){
				pisteBetreten(skifahrer, PISTE_B2); break;
			} else if (r == 3){
				pisteBetreten(skifahrer, PISTE_R2); break;
			}
		case LIFT_BERG_ZU_MITTE:
			r = rand() % 5;
			if (r == 0){
				skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = LIFT_MITTE_ZU_TAL; 
				skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_im_lift = 4; break;
			} else if (r == 1){
				warteschlangeBetretenMitteHoch(skifahrer); break;		
			} else if (r == 2){
				pisteBetreten(skifahrer, PISTE_B2); break;
			} else if (r == 3){
				pisteBetreten(skifahrer, PISTE_R2); break;
			} else if (r == 4){
				pisteBetreten(skifahrer, Bistro); break;
			}
		case LIFT_MITTE_ZU_TAL:
			if (skifahrer_liste[temp_skifahrer_liste_index].ankunftsart != BUS)
			{
				r = rand() % 2;
				if (r == 0){
					skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = ABWESEND; break;
				} else if (r == 1){
					warteschlangeBetretenTal(skifahrer); break;
				}				
			} else if (skifahrer_liste[temp_skifahrer_liste_index].ankunftsart == BUS){
				r = rand() % 3;
				if (r == 0){
					skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = ABWESEND; break;
				} else if (r == 1){
					warteschlangeBetretenTal(skifahrer); break;
				} else if (r == 2){
					warteschlangeBetretenBus(skifahrer); break;
				}	
			}
		case PISTE_S1:
			if (skifahrer_liste[temp_skifahrer_liste_index].ankunftsart != BUS)
			{
				r = rand() % 2;
				if (r == 0){
					skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = ABWESEND; break;
				} else if (r == 1){
					warteschlangeBetretenTal(skifahrer); break;
				}				
			} else if (skifahrer_liste[temp_skifahrer_liste_index].ankunftsart == BUS){
				r = rand() % 3;
				if (r == 0){
					skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = ABWESEND; break;
				} else if (r == 1){
					warteschlangeBetretenTal(skifahrer); break;
				} else if (r == 2){
					warteschlangeBetretenBus(skifahrer); break;
				}	
			}
		case PISTE_B2:
			r = rand() % 5;
			if (r == 0){
				warteschlangeBetretenMitteHoch(skifahrer); break;
			} else if (r == 1){
				warteschlangeBetretenMitteRunter(skifahrer); break;
			} else if (r == 2){
				pisteBetreten(skifahrer, PISTE_B1); break;
			} else if (r == 3){
				pisteBetreten(skifahrer, PISTE_R1); break;
			} else if (r == 4){
				pisteBetreten(skifahrer, Bistro); break;
			}			
		case PISTE_R2:
			r = rand() % 5;
			if (r == 0){
				warteschlangeBetretenMitteHoch(skifahrer); break;
			} else if (r == 1){
				warteschlangeBetretenMitteRunter(skifahrer); break;
			} else if (r == 2){
				pisteBetreten(skifahrer, PISTE_B1); break;
			} else if (r == 3){
				pisteBetreten(skifahrer, PISTE_R1); break;
			} else if (r == 4){
				pisteBetreten(skifahrer, Bistro); break;
			}			
		case PISTE_B1:
			if (skifahrer_liste[temp_skifahrer_liste_index].ankunftsart != BUS)
			{
				r = rand() % 2;
				if (r == 0){
					skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = ABWESEND; break;
				} else if (r == 1){
					warteschlangeBetretenTal(skifahrer); break;
				}				
			} else if (skifahrer_liste[temp_skifahrer_liste_index].ankunftsart == BUS){
				r = rand() % 3;
				if (r == 0){
					skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = ABWESEND; break;
				} else if (r == 1){
					warteschlangeBetretenTal(skifahrer); break;
				} else if (r == 2){				
					warteschlangeBetretenBus(skifahrer); break;
				}	
			}
		case PISTE_R1:
			if (skifahrer_liste[temp_skifahrer_liste_index].ankunftsart != BUS)
			{
				r = rand() % 2;
				if (r == 0){
					skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = ABWESEND; break;
				} else if (r == 1){
					warteschlangeBetretenTal(skifahrer); break;
				}				
			} else if (skifahrer_liste[temp_skifahrer_liste_index].ankunftsart == BUS){
				r = rand() % 3;
				if (r == 0){
					skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = ABWESEND; break;
				} else if (r == 1){
					warteschlangeBetretenTal(skifahrer); break;
				} else if (r == 2){
					warteschlangeBetretenBus(skifahrer); break;
				}	
			}
		default: break;			
	}
}

/* Bus mit 0 bis 50 Skifahrer kommt an, 50 skifahrer mit ankunftsart "BUS" werden erstellt */
void busKommtAn()
{
	int skifahrer_im_bus;

	skifahrer_im_bus = rand() % 51;
	for (; skifahrer_im_bus > 0; skifahrer_im_bus--)
	{
		neuenSkifahrerErstellen(BUS);
	}
}

/* skifahrer betritt bus_warteschlange */
void warteschlangeBetretenBus(Skifahrer skifahrer)
{
	int temp_skifahrer_liste_index;

	temp_skifahrer_liste_index = skifahrer.index;
	warteschlange_bus[warteschlange_bus_index].skifahrer_index = temp_skifahrer_liste_index;
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = SCHLANGE_BUS;
	warteschlange_bus_index++;
}

/* setzt die ersten 50 Skifahrer in bus_warteschlange auf abwesend und rueckt die naechsten 50 um 50 felder vor */
void busFaehrtAb()
{
	int i, temp_skifahrer_liste_index;

	i = 0;
	for (; i<= 50; i++)
	{
		temp_skifahrer_liste_index = warteschlange_bus[i].skifahrer_index;
		skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = ABWESEND;
		warteschlange_bus[i] = warteschlange_bus[i + 50]; 
	}

	warteschlange_bus_index = warteschlange_bus_index - 50;
	if (warteschlange_bus_index < 0)
	{
		warteschlange_bus_index = 0;
	}
}

/* Skifahrer wird in Talwarteschlange gestellt */
void warteschlangeBetretenTal(Skifahrer skifahrer)
{
	int temp_skifahrer_liste_index;

	temp_skifahrer_liste_index = skifahrer.index;
	warteschlange_tal[warteschlange_tal_index].skifahrer_index = skifahrer.index;
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = SCHLANGE_TAL;
	skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = 9999; 
	
	warteschlange_tal_index++;
}

/* Skifahrer wird in die Warteschlange fuer die Mittelstation nach oben gestellt */
void warteschlangeBetretenMitteHoch(Skifahrer skifahrer)
{
	int temp_skifahrer_liste_index;

	temp_skifahrer_liste_index = skifahrer.index;
	warteschlange_mitte_hoch[warteschlange_mitte_hoch_index].skifahrer_index = skifahrer.index;
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = SCHLANGE_MITTE_ZU_BERG;
	skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = 9999;
	
	warteschlange_mitte_hoch_index++;
}

/* Skifahrer wird in Bergwarteschlange gestellt */
void warteschlangeBetretenBerg(Skifahrer skifahrer)
{
	int temp_skifahrer_liste_index;

	temp_skifahrer_liste_index = skifahrer.index;
	warteschlange_berg[warteschlange_berg_index].skifahrer_index = skifahrer.index;
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = SCHLANGE_BERG;
	skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = 9999;
	
	warteschlange_berg_index++;
}

/* Skifahrer wird in die Warteschlange fuer die Mittelstation nach unten gestellt */
void warteschlangeBetretenMitteRunter(Skifahrer skifahrer)
{
	int temp_skifahrer_liste_index;

	temp_skifahrer_liste_index = skifahrer.index;
	warteschlange_mitte_runter[warteschlange_mitte_runter_index].skifahrer_index = skifahrer.index;
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = SCHLANGE_MITTE_ZU_TAL;
	skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = 9999;
	
	warteschlange_mitte_runter_index++;
}

/* bis zu 4 Skifahrer betrteten Lift im Tal */
void liftBetretenTal()
{	
	int temp_skifahrer_liste_index, i, j; /* temporaerer index fuer den Skifahrer, der in dieser Funktion den Lift betritt */
	j = 0;
	for (; j <= 3; j++)
	{	
		if (warteschlange_tal_index == 0)
		{
			return;
		}
		
		temp_skifahrer_liste_index = warteschlange_tal[0].skifahrer_index;
		skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = LIFT_TAL_ZU_MITTE;  /* position von Skifahrer updaten */
		skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_im_lift = 4;
		warteschlange_tal[0].skifahrer_index = 0; /* skifahrer aus warteschlange loeschen */
		warteschlange_tal[0].warteschlange_index = 0; /* skifahrer aus warteschlange loeschen */

		/* alle Skifahrer ruecken um eins in der Warteschlange vor */
		i = 0;
		while (1)
		{
			if (warteschlange_tal[i + 1].skifahrer_index == 0)
			{
				break; 
			}
			warteschlange_tal[i] = warteschlange_tal[i + 1];
			i++;
		}
		warteschlange_tal_index--; /* um eins senken, weil damit index wieder bei leerer stelle ist */		
	}
}

/* so viele Skifahrer wie Plaetze frei sind betreten den Lift */
void liftBetretenMitteHoch()
{	
	int temp_skifahrer_liste_index, skifahrer_in_lift, i, j, k; /* temporaerer index fuer den Skifahrer, der in dieser Funktion den Lift betritt */
	skifahrer_in_lift = 0;
	k = 0;
	for (; k <= 5000; k++)
	{
		if (skifahrer_liste[k].uebrige_zeit_im_lift == 0 && skifahrer_liste[k].aktuelle_position == LIFT_TAL_ZU_MITTE){
			skifahrer_in_lift++;
		}
		
	}

	j = 0;
	for (; j < 24 - skifahrer_in_lift; j++)
	{
		if (warteschlange_mitte_hoch_index == 0)
		{
			return;
		}

		temp_skifahrer_liste_index = warteschlange_mitte_hoch[0].skifahrer_index;
		skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = LIFT_MITTE_ZU_BERG;  /* position von Skifahrer updaten */
		skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_im_lift = 5;
		warteschlange_mitte_hoch[0].skifahrer_index = 0; /* skifahrer aus warteschlange loeschen */
		warteschlange_mitte_hoch[0].warteschlange_index = 0; /* skifahrer aus warteschlange loeschen */

		/* alle Skifahrer ruecken um eins in der Warteschlange vor */
		i = 0;
		while (1)
		{
			if (warteschlange_mitte_hoch[i + 1].skifahrer_index == 0)
			{
				break; 
			}
			warteschlange_mitte_hoch[i] = warteschlange_mitte_hoch[i + 1];
			i++;
		}
		warteschlange_mitte_hoch_index--;
	}
}

/* bis zu 4 Skifahrer betreten Lift auf dem Berg */
void liftBetretenBerg()
{	
	int temp_skifahrer_liste_index, i, j; /* temporaerer index fuer den Skifahrer, der in dieser Funktion den Lift betritt */
	j = 0;
	for (; j <= 3; j++)
	{
		if (warteschlange_berg_index == 0)
		{
			return;
		}

		temp_skifahrer_liste_index = warteschlange_berg[0].skifahrer_index;
		skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = LIFT_BERG_ZU_MITTE;  /* position von Skifahrer updaten */
		skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_im_lift = 5;
		warteschlange_berg[0].skifahrer_index = 0; /* skifahrer aus warteschlange loeschen */
		warteschlange_berg[0].warteschlange_index = 0; /* skifahrer aus warteschlange loeschen */

		/* alle Skifahrer ruecken um eins in der Warteschlange vor */
		i = 0;
		while (1)
		{
			if (warteschlange_berg[i + 1].skifahrer_index == 0)
			{
				break; 
			}
			warteschlange_berg[i] = warteschlange_berg[i + 1];
			i++;
		}
		warteschlange_berg_index--;
	}
}

/* so viele Skifahrer wie Plaetze frei sind betreten den Lift */
void liftBetretenMitteRunter()
{	
	int temp_skifahrer_liste_index, skifahrer_in_lift, i, j, k; /* temporaerer index fuer den Skifahrer, der in dieser Funktion den Lift betritt */
	skifahrer_in_lift = 0;
	k = 0;
	for (; k <= 5000; k++)
	{
		if (skifahrer_liste[k].uebrige_zeit_im_lift == 0 && skifahrer_liste[k].aktuelle_position == LIFT_BERG_ZU_MITTE){
			skifahrer_in_lift++;
		}
		
	}

	j = 0;
	for (; j < 24 - skifahrer_in_lift; j++)
	{
		if (warteschlange_mitte_runter_index == 0)
		{
			return;
		}

		temp_skifahrer_liste_index = warteschlange_mitte_runter[0].skifahrer_index;
		skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = LIFT_MITTE_ZU_TAL;  /* position von Skifahrer updaten */
		skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_im_lift = 4;
		warteschlange_mitte_runter[0].skifahrer_index = 0; /* skifahrer aus warteschlange loeschen */
		warteschlange_mitte_runter[0].warteschlange_index = 0; /* skifahrer aus warteschlange loeschen */

		/* alle Skifahrer ruecken um eins in der Warteschlange vor */
		i = 0;
		while (1)
		{
			if (warteschlange_mitte_runter[i + 1].skifahrer_index == 0)
			{
				break; 
			}
			warteschlange_mitte_runter[i] = warteschlange_mitte_runter[i + 1];
			i++;
		}
		warteschlange_mitte_runter_index--;
	}
}

/* Skifahrer betritt angegebene Piste. Zeit auf der Piste wird von den getPisteTime() Funktionen uebergeben */
void pisteBetreten(Skifahrer skifahrer, int piste)
{
	int temp_skifahrer_liste_index;

	tag_gesamtfahrten++;
	temp_skifahrer_liste_index = skifahrer.index;
	skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_im_lift = 9999;
	skifahrer_liste[temp_skifahrer_liste_index].aktuelle_position = piste;	
	skifahrer_liste[temp_skifahrer_liste_index].uebrige_fahrten--;	
	skifahrer_liste[temp_skifahrer_liste_index].gesamtfahrten++;	
	
	switch (piste)
	{
		case PISTE_S1: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = getS1time(); break;
		case PISTE_R1: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = getR1time(); break;
		case PISTE_B1: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = getB1time(); break;
		case PISTE_R2: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = getR2time(); break;
		case PISTE_B2: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = getB2time(); break;
		case Bistro: skifahrer_liste[temp_skifahrer_liste_index].uebrige_zeit_auf_piste = (rand() % 15)+2; break;
		default: break;
	}
}

/* Checkt, ob Skifahrer auf Piste an Station angekommen sind. Wenn ja, ruft skifahrerEntscheidung() auf. Wenn nein, senkt verbleibende Zeit auf Piste um 1 */
void uebrigeZeitAufPisteSenken()
{
	int i;

	for (i = 0; i <= 5000; i++)
	{
		if(skifahrer_liste[i].uebrige_zeit_auf_piste == 0)
		{
			skifahrerEntscheidung(skifahrer_liste[i]);
		} else {
			skifahrer_liste[i].uebrige_zeit_auf_piste--;			
		}
	}
}

/* Checkt, ob Skifahrer in Lift an Station angekommen sind. Wenn ja, ruft skifahrerEntscheidung() auf. Wenn nein, senkt verbleibende Zeit im Lift um 1 */
void uebrigeZeitImLiftSenken()
{
	int i;

	i = 0;
	for (; i <= 5000; i++)
	{
		if (skifahrer_liste[i].uebrige_zeit_im_lift == 0)
		{
			skifahrer_liste[i].uebrige_zeit_im_lift = 9999;
			skifahrerEntscheidung(skifahrer_liste[i]);
		} else {
			skifahrer_liste[i].uebrige_zeit_im_lift--;
		}
	}
}

/* fuellt Skifahrer_liste mit Dummys. Soll verhindern, dass eine Funktion auf eine leere Stelle in der Liste zugreift und dabei Werte entdeckt, die es nicht geben sollte*/
void skifahrerListeMitDummysFuellen()
{
	int i;

	i = 0;
	for (; i <= 5000; i++)
	{
		skifahrer_liste[i].aktuelle_position = ABWESEND;
		skifahrer_liste[i].ankunftsart = 1;
		skifahrer_liste[i].gesamtfahrten = 0;
		skifahrer_liste[i].index = 9999; /* Wert, der ausserhalb der eigentlichen laenge der Liste liegt, damit nicht irgendwie ausversehen drauf zugegriffen wird */
		skifahrer_liste[i].uebrige_fahrten = 0;
		skifahrer_liste[i].uebrige_zeit_auf_piste = 9999;
	}
}

/* fuellt Skifahrer_liste mit Dummys. Soll verhindern, dass eine Funktion auf eine leere Stelle in den Schlangen zugreift und dabei Werte entdeckt, die es nicht geben sollte*/
void warteschlangenMitDummysFuellen()
{
	int i;

	i = 0;
	for (; i <= 5000; i++)
	{
		warteschlange_tal[i].skifahrer_index = 0;
		warteschlange_tal[i].warteschlange_index = 0; /* Ich glaub der Wert kann raus */

		warteschlange_berg[i].skifahrer_index = 0;
		warteschlange_berg[i].warteschlange_index = 0;

		warteschlange_bus[i].skifahrer_index = 0;
		warteschlange_berg[i].warteschlange_index = 0;

		warteschlange_mitte_hoch[i].skifahrer_index = 0;
		warteschlange_mitte_hoch[i].warteschlange_index = 0;

		warteschlange_mitte_runter[i].skifahrer_index = 0;
		warteschlange_mitte_runter[i].warteschlange_index = 0;
	}
}

/* Randomzeit fuer die S1 */
int getS1time()
{
	if(S1reverseminute <= 9)
	{
		S1randZeit = 0;
	} else if(rand() % 100 > 10){
		S1randZeit = (rand() % 51)+9;/*Zufaellige zeit zwischen 9 und 59*/
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
		B1randZeit = 0;
	} else if(rand() % 100 > 10){
		B1randZeit = (rand() % 21)+3;/*Zufaellige zeit zwischen 3 und 24*/
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
		B2randZeit = 0;
	} else if(rand() % 100 > 10){
		B2randZeit = (rand() % 38)+5;/*Zufaellige zeit zwischen 5 und 42*/
	} else {
		B2randZeit = (rand() % B2ungewoehnlichhoch)+42;		
	}
	return B2randZeit;
}

/*Randomzeit fuer die R1*/
int getR1time(){		
	if(R1reverseminute <= 3)
	{
		R1randZeit = 0;
	} else if(rand() % 100 > 10){
		R1randZeit = (rand() % 18)+3;/*Zufaellige zeit zwischen 3 und 20*/
	}else{
		R1randZeit = (rand() % R1ungewoehnlichhoch)+20;
	}
	return R1randZeit;
}
	
/*Randomzeit fuer die R2*/
int getR2time(){			
	if(R2reverseminute <= 3)
	{
		R2randZeit = 0;
	} else if(rand() % 100 > 10){
		R2randZeit = (rand() % 35)+3;/*Zufaellige zeit zwischen 3 und 38*/
	}else{
		R2randZeit = (rand() % R2ungewoehnlichhoch)+37;
	}
	return R2randZeit;
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

/* Geht durch gesamte skifahrer_liste durch und bestmmt position von jedem einzelnen Eintrag. Die Zaehlervariable der entsprechenden Position wird dann um 1 erhoeht. 
   Vorher werden alle Positionen auf 0 gesetzt. Dadurch weiss man immer, wie viele Skifahrer wo sind. */
void positionenChecken()
{
	int i;
	zaehlvariablenAufNullSetzen();
	i = 1;
	while (i <= 5000)
	{
		switch(skifahrer_liste[i].aktuelle_position)
		{
			case SCHLANGE_TAL: 			 schlangenlaenge_tal++; 			break;
			case SCHLANGE_MITTE_ZU_BERG: schlangenlaenge_mitte_zu_berg++; 	break;
			case SCHLANGE_BERG: 		 schlangenlaenge_berg++; 			break;
			case SCHLANGE_MITTE_ZU_TAL:  schlangenlaenge_mitte_zu_tal++; 	break;
			case SCHLANGE_BUS:			 schlangenlaenge_bus++;				break;
			case LIFT_TAL_ZU_MITTE: 	 anzahl_tal_zu_mitte++; 			break;
			case LIFT_MITTE_ZU_BERG: 	 anzahl_mitte_zu_berg++; 			break;
			case LIFT_BERG_ZU_MITTE: 	 anzahl_berg_zu_mitte++; 			break;
			case LIFT_MITTE_ZU_TAL: 	 anzahl_mitte_zu_tal++; 			break;
			case PISTE_S1: 				 anzahl_S1++; 						break;
			case PISTE_B1: 				 anzahl_B1++; 						break;
			case PISTE_R1: 				 anzahl_R1++; 						break;
			case PISTE_B2: 				 anzahl_B2++; 						break;
			case PISTE_R2: 				 anzahl_R2++; 						break;
			case Bistro:				 anzahl_bistro++;					break;
			case ABWESEND: break;								
		}
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
	schlangenlaenge_bus			  = 0;
	anzahl_tal_zu_mitte  = 0; 			
	anzahl_mitte_zu_berg = 0; 			
	anzahl_berg_zu_mitte = 0; 			
	anzahl_mitte_zu_tal  = 0; 			
	anzahl_S1 = 0; 						
	anzahl_B1 = 0; 						
	anzahl_R1 = 0; 						
	anzahl_B2 = 0; 						
	anzahl_R2 = 0;
	anzahl_bistro = 0;					
}

/* Zaehlt, wie viele Skifahrer anwesend */
void getPersonenAufBerg()
{
	int i, anwesend;
	i = 0;
	anwesend = 0;
	for (; i <= 5000; i++)
	{
		if (skifahrer_liste[i].aktuelle_position != ABWESEND)
		{
			anwesend++;
		}
	}
	personen_auf_berg = anwesend;
}

/* Erstellt neue Skifahrer die in dieser Minute ankommen. Anzahl sinkt im Verlauf des Tages */
void mehrereSkifahrerErstellen(int neue_skifahrer_pro_minute)
{
	for (; neue_skifahrer_pro_minute > 0; neue_skifahrer_pro_minute--)
	{
		neuenSkifahrerErstellen(AUTO);
	}
}
