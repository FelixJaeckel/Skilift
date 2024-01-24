#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>

struct Uhrzeit; /* muss vor eigentlicher definition leer deklariert werden, damit der Prototyp Bescheid weiÃŸ, was eine Uhrzeit ist */

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
	
	int zehnerkarten, bergstation_lift, tageskarten, minuten;
	char input;
	int PersonenGesamtaufBerg, VerkaufteZehnerKarten, VerkaufteTageskarten, Skifarten, SchneedorfGaesteAufDerPiste, ParkendeWagen, BuseDieHeuteDaWaren; // Menu Counters
	char* Busn;
	char* Leer1;//Tabelle Puffer Veriabelen
	char* Leer2;
	char* Leer3;
	char* Leer4;
	char* Leer5;
	char* Leer6;
	char* Leer7;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	minuten = 540; /* wir starten bei 540 Minuten, weil der Skilift 9:00 Uhr aufmacht */
	uhrzeit.stunde = 9; 
	uhrzeit.minute = 0;
	
	/* Variablen zu Testzwecken */
	zehnerkarten = 15;
	bergstation_lift = 2;
	tageskarten = 51;
	int turbo = 0; // 0 = Sleep(1), 1 = Sleep(0.1)
		PersonenGesamtaufBerg = 10;
	VerkaufteZehnerKarten = 100;
	VerkaufteTageskarten = 0;
	Skifarten = 0;
	SchneedorfGaesteAufDerPiste = 0;
	ParkendeWagen = 0;
	BuseDieHeuteDaWaren = 0;
	/* loop lÃ¤uft bis 1320 Minuten, also bis 22:00 Uhr */
	while(minuten <= 1320)
	{
			if(PersonenGesamtaufBerg>=100){
	Leer1 = (" ");
} else if(PersonenGesamtaufBerg>=10){
	Leer1 = ("  ");
} else {
	Leer1 = ("   ");
}

	if(VerkaufteZehnerKarten>=100){
	Leer2 = (" ");
} else if(VerkaufteZehnerKarten>=10){
	Leer2 = ("  ");
} else {
	Leer2 = ("   ");
}

	if(VerkaufteTageskarten>=100){
	Leer3 = (" ");
} else if(VerkaufteTageskarten>=10){
	Leer3 = ("  ");
} else {
	Leer3 = ("   ");
}
	if(VerkaufteTageskarten>=100){
	Leer3 = (" ");
} else if(VerkaufteTageskarten>=10){
	Leer3 = ("  ");
} else {
	Leer3 = ("   ");
}

	if(Skifarten>=100){
	Leer4 = (" ");
} else if(Skifarten>=10){
	Leer4 = ("  ");
} else {
	Leer4 = ("   ");
}

	if(SchneedorfGaesteAufDerPiste>=100){
	Leer5 = (" ");
} else if(SchneedorfGaesteAufDerPiste>=10){
	Leer5 = ("  ");
} else {
	Leer5 = ("   ");
}

	if(ParkendeWagen>=100){
	Leer6 = (" ");
} else if(ParkendeWagen>=10){
	Leer6 = ("  ");
} else {
	Leer6 = ("   ");
}

	if(BuseDieHeuteDaWaren>=100){
	Leer7 = (" ");
} else if(BuseDieHeuteDaWaren>=10){
	Leer7 = ("  ");
} else {
	Leer7 = ("   ");
}
		system("cls");
		printf(	"10er-Karten:  %i                                   ___Bergstation    Lift ab:  %i\n"
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
				"\n                  ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»                "
		"\n  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄº                                          ºÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿"
		"\n  ³               º      %sbersicht %sber den Berg             º               ³"
		"\n  ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄº                                          ºÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´"
		"\n  ³               ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼               ³"
		"\n  ³                    ³           Allgemeine Zahlen:                        ³"
		"\n  ³                    ³          Personen auf Berg:  %d%s                   ³"
		"\n  ³                    ³          10er-Karten:  %d%s                         ³"
		"\n  ³                    ³          Tageskarten: %d%s                          ³"
		"\n  ³                    ³          Skifahrten:   %d%s                         ³"
		"\n  ³                    ³          Schneedorf Besucher:   %d%s                ³"
		"\n  ³                    ³          Parkende Wagen:  %d Auto %s                ³"
		"\n  ³                    ³          Busse an diesem Tag:  %d  %s               ³"
		"\n  ³                    ³          %s                                        ³"
		"\n  ³                    ³          M%sgliche Eingaben:                         ³"
		"\n  ³                    ³          (T)urbo                                    ³"
		"\n  ³                    ³          (P)ause                                    ³"
		"\n  ³                    ³          (0)  Programmende                          ³"
		"\n  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ" 
		"                                                                 \n"
		"                                                                 \n"
		"                                                                 \n"
		"                                                                 \n"
		"                                                                 \n"                                            
				, zehnerkarten, bergstation_lift, tageskarten, "\x9a", "\x81", PersonenGesamtaufBerg, Leer1, VerkaufteZehnerKarten, Leer2, VerkaufteTageskarten, Leer3, Skifarten, Leer4, SchneedorfGaesteAufDerPiste, Leer5, ParkendeWagen, Leer6, BuseDieHeuteDaWaren, Leer7, Busn, "\x94");
		

		uhrzeitAusgeben(uhrzeit); /* uhrzeit hat ein paar Eigenheiten, weswegen sie eine extrafunktion zum printen kriegt */
		/* nur zu testzwecken hier */
		zehnerkarten++;
		bergstation_lift++; 
		tageskarten++;
	
		cursorSetzen(hStdout, 0, 24); /* setzt Cursor an den Anfang, damit Ausgabe scheinbar konstant bleibt */
	if (turbo) {
            usleep(100000); // Wenn turbo Modus sleep 0.1
        } else {
            sleep(1); // sleep 1 sekunden im normalen modus
        }
		minuten++; /* eine minute vergeht */
		uhrzeitAnpassen(minuten); /* minuten werden in uhrzeitformat umgewandelt */
		if (kbhit()) { // Überprüfen, ob eine Taste gedrückt wurde
            input = tolower(getchar()); // Benutzereingabe lesen
            //Turbo
             if (input == 't') { // Turbo aktiveren/Deaktivieren
                turbo = !turbo; // Wechsel des Turbo moduses
                printf("Turbo-Modus %s\n", turbo ? "aktiviert" : "deaktiviert");
            }
            //Pause
            if (input == 'p') { // Falls 'p' gedrückt wurde, pausieren
                printf("Die Uhr ist pausiert. Drücken Sie 'r', um fortzufahren.\n");
                while (1) {
                    input = getchar();
                    if (input == 'r') { // Falls 'r' gedrückt wurde, fortsetzen
                        printf("Die Uhr läuft weiter\n");
                        break;
                        fflush(stdin);
                    }
                }
            }
            else if (input == '0') { // Progamm beendung mit 0
                  
				  return;
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


/* sorgt dafÃ¼r, dass uhrzeit immer mit zwei Ziffern vor und hinter dem Doppelpunkt ausgegeben wird */
void uhrzeitAusgeben(Uhrzeit uhrzeit)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	/* packt 0 vor die Stunde wenn es um 9 ist, ansonsten wird die Stunde einfach nur geprintet */
	cursorSetzen(hStdout, 0, 2);	
	if (uhrzeit.stunde == 9) 
	{
		printf("0%i", uhrzeit.stunde);
	} 
	else 
	{
		printf("%i", uhrzeit.stunde);
	}
	
	/* packt 0 vor einstellige Minuten */
	cursorSetzen(hStdout, 3, 2);	
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


/* Portenzelle Schon vorbereiteter Code Falls er noch verwennendbar ist
Vorbereitete Skilift Variabeln
int B1, B2, R1, R2, S1;//Pisten
int WarteschlangeBergstationAbwaerz, WarteschlangeMittelstationAufwaerz, WarteschlangeMittelstationAbwaerz , WarteschlangeTalstationAufwaerz;//Warteschlangen
int LiftfahrerMittelstationBergstation, LiftfahrerTalstationMittelstation;//Liftbenutzer
int BistroGaeste;//Bistro
B1 = 0;
B2 = 0;
R1 = 0;
R2 = 0;
S1 = 0;
WarteschlangeBergstationAbwaerz = 0;
WarteschlangeMittelstationAufwaerz = 0;
WarteschlangeMittelstationAbwaerz = 0;
WarteschlangeTalstationAufwaerz = 0;
LiftfahrerMittelstationBergstation = 0;
LiftfahrerTalstationMittelstation = 0;
BistroGaeste = 0;

Busankunft & Abfahrten
if(t1.stunde == 8 & t1.minute == 30 || t1.stunde == 8 & t1.minute == 50 ||
t1.stunde == 9 & t1.minute == 10 || t1.stunde == 9 & t1.minute == 30 || t1.stunde == 9 & t1.minute == 50 ||
t1.stunde == 10 & t1.minute == 10 || t1.stunde == 10 & t1.minute == 30 || t1.stunde == 10 & t1.minute == 50 ||
t1.stunde == 11 & t1.minute == 10 || t1.stunde == 11 & t1.minute == 30 || t1.stunde == 11 & t1.minute == 50 ||
t1.stunde == 12 & t1.minute == 10 || t1.stunde == 12 & t1.minute == 30 || t1.stunde == 12 & t1.minute == 50 ||
t1.stunde == 13 & t1.minute == 10 || t1.stunde == 13 & t1.minute == 30 || t1.stunde == 13 & t1.minute == 50 ||
t1.stunde == 14 & t1.minute == 10 || t1.stunde == 14 & t1.minute == 30 || t1.stunde == 14 & t1.minute == 50 ||
t1.stunde == 15 & t1.minute == 10 || t1.stunde == 15 & t1.minute == 30 || t1.stunde == 15 & t1.minute == 50 ||
t1.stunde == 16 & t1.minute == 10 || t1.stunde == 16 & t1.minute == 30 || t1.stunde == 16 & t1.minute == 50 ||
t1.stunde == 17 & t1.minute == 10 || t1.stunde == 17 & t1.minute == 30 || t1.stunde == 17 & t1.minute == 50 ||
t1.stunde == 18 & t1.minute == 10 || t1.stunde == 18 & t1.minute == 30 || t1.stunde == 18 & t1.minute == 50 ||
t1.stunde == 19 & t1.minute == 10 || t1.stunde == 19 & t1.minute == 30 || t1.stunde == 19 & t1.minute == 50 ||
t1.stunde == 20 & t1.minute == 10){
	Busn = ("Der bus ist hier.");
} else if(t1.stunde == 8 & t1.minute == 33 || t1.stunde == 8 & t1.minute == 53 ||
t1.stunde == 9 & t1.minute == 13 || t1.stunde == 9 & t1.minute == 33 || t1.stunde == 9 & t1.minute == 53 ||
t1.stunde == 10 & t1.minute == 13 || t1.stunde == 10 & t1.minute == 33 || t1.stunde == 10 & t1.minute == 53 ||
t1.stunde == 11 & t1.minute == 13 || t1.stunde == 11 & t1.minute == 33 || t1.stunde == 11 & t1.minute == 53 ||
t1.stunde == 12 & t1.minute == 10 || t1.stunde == 12 & t1.minute == 33 || t1.stunde == 12 & t1.minute == 53 ||
t1.stunde == 13 & t1.minute == 13 || t1.stunde == 13 & t1.minute == 33 || t1.stunde == 13 & t1.minute == 53 ||
t1.stunde == 14 & t1.minute == 13 || t1.stunde == 14 & t1.minute == 33 || t1.stunde == 14 & t1.minute == 53 ||
t1.stunde == 15 & t1.minute == 13 || t1.stunde == 15 & t1.minute == 33 || t1.stunde == 15 & t1.minute == 53 ||
t1.stunde == 16 & t1.minute == 13 || t1.stunde == 16 & t1.minute == 33 || t1.stunde == 16 & t1.minute == 53 ||
t1.stunde == 17 & t1.minute == 13 || t1.stunde == 17 & t1.minute == 33 || t1.stunde == 17 & t1.minute == 53 ||
t1.stunde == 18 & t1.minute == 13 || t1.stunde == 18 & t1.minute == 33 || t1.stunde == 18 & t1.minute == 53 ||
t1.stunde == 19 & t1.minute == 13 || t1.stunde == 19 & t1.minute == 33 || t1.stunde == 19 & t1.minute == 53 ||
t1.stunde == 20 & t1.minute == 13){
	Busn = ("Der Bus ist abgefahren.");
} else {
	Busn = ("...");
}

// Zahlen runschiebe
//Holle zufalls zahl von 0-2 Leuten aus schneedorf
int getZufallszahl() {
    return rand() % 3; // ergibt eine Zufallszahl zwischen 0 und 2
}

//Holle Zufallszahl von 1-5 für Leute die im Auto kommen
int getZufallszahl() {
    int getRandomNumber() {
    return (rand() % 5) + 1; // ergibt eine Zufallszahl zwischen 0 und 4, daher wird 1 addiert
}
}

//Holle Zufallszahl von 0-50 für Leute die mit dem Bus kommen
int getRandomNumber() {
    return rand() % 51; //ergibt eine Zufallszahl zwischen 0 und 50
}

//Zwischen 9:00 und 11 uhr kommen leute aus dem dorf
void getinSchneedorfgeaste(){
	int ZufallsZahlSchneeGaesteJetzt;
	ZufallsZahlSchneeGaesteJetzt = 0;
	if (SchneedorfGaesteAufDerPiste <= 58){
	if( 9 < t.stunde < 11 ){
		getZufallszahl() = ZufallsZahlSchneeGaesteJetzt;
		PersonenGesamtaufBerg = PersonenGesamtaufBerg + ZufallsZahlSchneeGaesteJetzt;
		SchneedorfGaesteAufDerPiste = SchneedorfGaesteAufDerPiste + ZufallsZahlSchneeGaesteJetzt;
}
}
}
//Zwischen 17:00 und 22 uhr gehen leute aus dem dorf
void getoutSchneedorfgeaste(){
	int ZufallsZahlSchneeGaesteJetzt;
	ZufallsZahlSchneeGaesteJetzt = 0;
	if (SchneedorfGaesteAufDerPiste = 0){
	if( 17 < t.stunde < 22 ){
		getZufallszahl() = ZufallsZahlSchneeGaesteJetzt;
		PersonenGesamtaufBerg = PersonenGesamtaufBerg - ZufallsZahlSchneeGaesteJetzt;
		SchneedorfGaesteAufDerPiste = SchneedorfGaesteAufDerPiste - ZufallsZahlSchneeGaesteJetzt;
}
}
}

void getschneewache(){
SchneedorfGaesteAufDerPiste = 0;
ParkendeWagen =0;
PersonenGesamtaufBerg = 0;

B1 = 0;
B2 = 0;
R1 = 0;
R2 = 0;
S1 = 0;
WarteschlangeBergstationAbwaerz = 0;
WarteschlangeMittelstationAufwaerz = 0;
WarteschlangeMittelstationAbwaerz = 0;
WarteschlangeTalstationAufwaerz = 0;
LiftfahrerMittelstationBergstation = 0;
LiftfahrerTalstationMittelstation = 0;
BistroGaeste = 0;
}
*/
