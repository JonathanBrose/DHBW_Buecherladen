#include "zeug.h"

int main() {
    t_ListVerwaltung feld, *f;
    f = &feld;
    f->start = 0;
    f->momentan = 0;
    f-> zwischen = 0;
    strcpy(f->datei, "Hannes.txt");
    menu(f);
    return 0;
}
void menu(t_ListVerwaltung *f){
    char eingabe, success;
    while(1) {
        do {
            system("clear");
            printf("\nWillkommen beim Buchladen der DHBW!\n");
            printf("(1) Datensatz einlesen\n");
            printf("(2) Datensatz ausgeben\n");
            printf("(3) Datensatz löschen\n");
            printf("(4) Datei einlesen\n");
            printf("(5) Datei speichern\n");
            printf("(6) Daten sortieren\n");
            printf("(7) Listenzeiger ausgeben\n");
            printf("(9) Programm beenden\n\n");
            success = scanf("%c", &eingabe);
            clear();
            if (!success) fprintf(stderr,"Fehlerhafte Eingabe\n");
            else {
                switch (eingabe) {
                    case '1':
                        up_eingabeDatensatz(f);
                        break;
                    case '2':
                        up_BuecherAnzeigen(f);
                        break;
                    case '3':
                        up_BuchLoeschen(f);
                        break;
                    case '4':
                        up_DateiEinlesenP(f);
                        break;
                    case '5':
                        up_DateiSpeichernP(f);
                        break;
                    case '6':
                        break;
                    case '7':
                        up_ListeAnzeigen(f);
                        break;
                    case '9':
                        printf("\nBis bald...\n");
                        return;
                    default:
                        fprintf(stderr,"Fehlerhafte Eingabe\n");
                }
            }
        } while (!success);
    }
}
void up_eingabeDatensatz(t_ListVerwaltung *f){
    int i = 1;
    char success, again;
    while(1){
        printf("Gib den %d. Datensatz ein...", i);
        do{
            printf("\nTitel des Buches: ");
            success = scanf("%s", f->titel);
            clear();
            if (!success) fprintf(stderr,"Fehlerhafte Eingabe\n");
        }while(!success);
        do{
            printf("Autor des Buches \"%s\": ", f->titel);
            success = scanf("%s", &(f->autor));
            clear();
            if (!success) fprintf(stderr,"Fehlerhafte Eingabe\n");
        }while(!success);
        do{
            printf("Verlag des Buches \"%s\": ", f->titel);
            success = scanf("%s", &(f->verlag));
            clear();
            if (!success) fprintf(stderr,"Fehlerhafte Eingabe\n");
        }while(!success);
        do{
            printf("Preis des Buches \"%s\": ", f->titel);
            success = scanf("%f", &(f->preis));
            clear();
            if (!success) fprintf(stderr,"Fehlerhafte Eingabe\n");
        }while(!success);
        up_BuchHinzufuegen(f);
        i++;

        do{
            printf("\nweiterer Datensatz? (y,j)/(n)\n");
            success = scanf("%c", &again);
            clear();
            if (!success) fprintf(stderr,"Fehlerhafte Eingabe\n");
            else{
                switch(again){
                    case 'y':
                    case 'Y':
                    case 'J':
                    case 'j':
                        success = 1;
                        break;
                    case 'N':
                    case 'n':
                        return;
                    default:
                        fprintf(stderr,"Fehlerhafte Eingabe\n");
                        success = 0;
                }
            }
        }while(!success);
    }
}
