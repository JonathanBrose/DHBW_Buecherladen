#include "main.h"

int main() {
    t_ListVerwaltung feld, *f;
    f = &feld;
    f->start = 0;
    f->momentan = 0;
    f->ende = 0;
    strcpy(f->datei, "Hannes.txt");
    strcpy(f->titel, "test");
    strcpy(f->autor, "ich");
    strcpy(f->verlag, "du");
    f->preis = 99;
    up_BuchHinzufuegen(f);
    strcpy(f->titel, "xd");
    f->preis = 23;
    up_BuchHinzufuegen(f);
    strcpy(f->titel, "Herr");
    strcpy(f->autor, "der");
    strcpy(f->verlag, "Ringe");
    f->preis = 19.99;
    up_BuchHinzufuegen(f);
    strcpy(f->titel, "lol");
    f->preis = 177;
    up_BuchHinzufuegen(f);
    menu(f);
    return 0;
}

void menu(t_ListVerwaltung *f) {
    char eingabe, success;
    while (1) {
        do {
            //system("clear");
            printf("\nWillkommen beim Buchladen der DHBW!\n");
            printf("(1) Datensatz einlesen\n");
            printf("(2) Datensatz ausgeben\n");
            printf("(3) Datensatz loeschen\n");
            printf("(4) Datei einlesen\n");
            printf("(5) Datei speichern\n");
            printf("(6) Daten sortieren\n");
            printf("(7) Listenzeiger ausgeben\n");
            printf("(q) Programm beenden\n\n");
            success = scanf("%c", &eingabe);
            clearInputbuffer();
            if (!success) fprintf(stderr, "Fehlerhafte Eingabe\n");
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
                        up_DateiEinlesen(f);
                        break;
                    case '5':
                        up_DateiSpeichern(f);
                        break;
                    case '6':
                        up_verkListe_sort(f, up_vergleicheBuchPreis);
                        break;
                    case '7':
                        up_ListenZeigerAnzeigen(f);
                        break;
                    case 'q':
                        printf("\nBis bald...\n");
                        return;
                    default:
                        fprintf(stderr, "Fehlerhafte Eingabe\n");
                }
            }
        } while (!success);
    }
}

void up_eingabeDatensatz(t_ListVerwaltung *f) {
    int i = 1;
    char success, again;
    while (1) {
        printf("Gib den %d. Datensatz ein...", i);
        do {
            printf("\nTitel des Buches: ");
            success = scanf("%10s", f->titel);
            clearInputbuffer();
            if (!success) fprintf(stderr, "Fehlerhafte Eingabe\n");
        } while (!success);
        do {
            printf("Autor des Buches \"%s\": ", f->titel);
            success = scanf("%s", &(f->autor));
            clearInputbuffer();
            if (!success) fprintf(stderr, "Fehlerhafte Eingabe\n");
        } while (!success);
        do {
            printf("Verlag des Buches \"%s\": ", f->titel);
            success = scanf("%s", &(f->verlag));
            clearInputbuffer();
            if (!success) fprintf(stderr, "Fehlerhafte Eingabe\n");
        } while (!success);
        do {
            printf("Preis des Buches \"%s\": ", f->titel);
            success = scanf("%f", &(f->preis));
            clearInputbuffer();
            if (!success) fprintf(stderr, "Fehlerhafte Eingabe\n");
        } while (!success);
        up_BuchHinzufuegen(f);
        i++;

        do {
            printf("\nweiterer Datensatz? (y,j)/(n)\n");
            success = scanf("%c", &again);
            clearInputbuffer();
            if (!success) fprintf(stderr, "Fehlerhafte Eingabe\n");
            else {
                switch (again) {
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
                        fprintf(stderr, "Fehlerhafte Eingabe\n");
                        success = 0;
                }
            }
        } while (!success);
    }
}
