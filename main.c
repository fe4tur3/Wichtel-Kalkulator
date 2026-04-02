#include <stdio.h>                      // printf, scanf,....
#include <string.h>                     // strcpy, strlen,...

#define MAX_WUENSCHE 20                 // # = Präprozessor-Aufgaben, also vor eigentl. Compilieren ausführen
#define MAX_Name 50
#define MAX_BESCHREIBUNG 200

typedef struct {
    char beschreibung[MAX_BESCHREIBUNG];
    float preis;
    int prioritaet;                     // 1 = hoch, 2 = mittel, 3 = niedrig
    int menge;

} Wunsch;                               // Name der struct dahinter

typedef struct {
    char name[MAX_Name];
    float budget;
    Wunsch wuensche[MAX_WUENSCHE];
    int anzahl_wuensche;
} Person;                               // Ende Datei-Struktur 1. Includes& Defines, 2. Struchts & Definitionen
                                        // 3. main und Funktionen, folgen nun:
                                        
void wunsch_eingeben(Person *person, char *name) {  // Funktionen!!    * = Pointerm Originalspeicheradresse wird verwandt, keine Kopie erstellt
    if (person->anzahl_wuensche >= MAX_WUENSCHE) {
        printf("Maximale Anzahl an Wünschen erreicht! \n");
        return;
    }
    
    Wunsch w;
    w.menge = 1; 
    
    strcpy(w.beschreibung, name); 
    
    /*printf("Nenne einen Wunsch: ");
    while (getchar() != '\n');
    scanf(" %99[^\n]", w.beschreibung);*/  // ^\n = lies bist zum Zeilenumbruch! sonst würde bereits bei Leerzeile das Auslesen beendet 
    
    
    printf("\nPreis in Euro: \n");
    scanf("%f", &w.preis);
    while (getchar() != '\n');
    
    
    do {
    printf("\nPrioritaet festlegen bitte ((1) = hoch; (3) = niedrig): \n");
    scanf("%d", &w.prioritaet);
    while (getchar() != '\n');
        
        if(w.prioritaet <1 || w.prioritaet >3) {
            printf("Ungültige Eingabe! Nutze die Zahlen 1,2 oder 3:\n")
        }
        
    } while (w.prioritaet <1 || w.prioritaet > 3);
    
    
    person->wuensche[person->anzahl_wuensche] = w;      //legt Eingabe an den vorgegebenem Pfad (nä. freier Platz im Array) ab
    person->anzahl_wuensche++;
    
    printf("Wunsch hinzugefügt!\n");
}                                      // Blöcke, wie Fuktionen, main() oder if/else, for... kein Semikolon

void vorschlag_berechnen(Person *person, int auswahl[]) {
    float gesamt =0;
    
    for (int prio = 1; prio <= 3; prio++) {
        for(int i =0; i < person->anzahl_wuensche; i++) {
            if(person->wuensche[i].prioritaet == prio) {
                if(gesamt + person->wuensche[i].preis <= person->budget)  {
                    auswahl[i] =1;      // Wunsch ausgewählt
                    gesamt += person->wuensche[i].preis;
                }
            }
        }
    }


printf("\n ~~ Automatischer Vorgschlag ~~\n");
printf("Verfügbares Budget: %.2f Euro\n\n", person->budget);

for(int i =0; i < person->anzahl_wuensche; i++) {
    printf("%d. [%s] %s - %.2f Euro (Prio: %d)\n",
    i+1,
    auswahl[i] ? "X" : " ",
    person-> wuensche[i].beschreibung,
    person-> wuensche[i].preis,
    person-> wuensche[i].prioritaet);
    }
    
    printf("nGesamt: %.2f Euro\n", gesamt);
    }

    
void manuell_anpassen(Person *person, int auswahl[]) {
    int wahl;
    float gesamt = 0;
    
    for (int i = 0; i <person->anzahl_wuensche; i++) {   //aktuelle Summe vorschlag_berechnen
        if (auswahl[i]) gesamt += person->wuensche[i].preis;
}    

while (1) {                                             // Endlosschleife erstellt, break durch die Eingabe von "0"
    printf("Budget: %.2f | Aktuell: %.2f | Verbleibend: %.2f Euro\n",
    person->budget, gesamt, person->budget - gesamt);
    printf("Nummer eingeben zum An/Abwählen, 0 = fertig\n\n");
    
    for (int i = 0; i < person->anzahl_wuensche; i++) {
            printf("%d. [%s] %s - %.2f Euro\n",
                i+1,
                auswahl[i] ? "X" : " ",
                person->wuensche[i].beschreibung,
                person->wuensche[i].preis);
        }
        
        scanf("%d", &wahl);
        while (getchar() != '\n');
        
        if (wahl == 0) break;           // fertig
        
        if (wahl < 1 || wahl > person->anzahl_wuensche) {
            printf("Ungültige Eingabe!\n");
            continue;
        }
        
        // An/Abwählen
 /*        int idx = wahl - 1;
        if (auswahl[idx]) {
            auswahl[idx] = 0;
            gesamt -= person->wuensche[idx].preis;
        } else {
            auswahl[idx] = 1;
            gesamt += person->wuensche[idx].preis;
        }
        
        if (gesamt > person->budget) {
            printf("Budget überschritten um %.2f Euro!\n", gesamt - person->budget);
        } */
        
        int idx = wahl - 1;
        if (auswahl[idx]) {
            auswahl[idx] = 0;
            gesamt -= person->wuensche[idx].preis * person->wuensche[idx].menge;
        } else {
            auswahl[idx] = 1;
            printf("Menge: ");
            scanf("%d", &person->wuensche[idx].menge);
            while (getchar() != '\n');
            gesamt += person->wuensche[idx].preis * person->wuensche[idx].menge;
        }
    }
}
    

                                        
                                        
                                        
                                        
int main() {                            // main()
    Person person;
    int auswahl[MAX_WUENSCHE] = {0};
    char eingabe[MAX_BESCHREIBUNG];
    
    printf("Name der Person: ");        //Name eingeben bitte
    scanf("%49s", person.name);        // s = Sting, 49 = "nach 49 Zeichen breche ich ab, damit nichts überläuft"
    
    printf("Budget in Euro: ");         // Budget eingeben
    scanf("%f", &person.budget);         // f = float; &=Speicheradresse vorgeben (nicht bei string oder char wegen Array)

    person.anzahl_wuensche = 0;          // Startwert: keine Wünsche
    
    printf("\n ==Wichtelkalkulator== \n", person.name, person.budget);
    printf("Person: %s | Budget: %.2f Euro\n", person.name, person.budget);
    
    while (getchar() != '\n');  // Puffer leeren
    
    do {                                // Wünsche eingeben
        printf("\nHier den Wunsch eintragen, oder 'Ende' schreiben, wenn Wunschliste zuende: \n\n");
        scanf("%9[^\n]", eingabe);
        while (getchar() != '\n');
        
        if (strcmp(eingabe, "Ende") !=0) {
            wunsch_eingeben(&person, eingabe);
        }
    } while (strcmp(eingabe, "Ende") !=0);
    
    vorschlag_berechnen(&person, auswahl);
    manuell_anpassen(&person, auswahl);
    
    printf("\nViel Spaß beim Shoppen!\n");
    return 0;
}

