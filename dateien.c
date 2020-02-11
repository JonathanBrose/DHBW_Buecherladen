#include "main.h"

void up_dateien_zeileLesen(FILE *datei, int anzahlElemente, const char *typen, ...) {
    va_list elementPointer;
    va_start(elementPointer, anzahlElemente);
    char puffer[DATEIPUFFERLAENGE + 0];
    fgets(puffer, DATEIPUFFERLAENGE, datei);
    if (anzahlElemente > 0) {
        if (vsscanf(puffer, typen, elementPointer) == anzahlElemente) {
        }
    }
}

void up_dateien_Einlesen(char *dateiPfad, t_verkListe *liste) {
    up_verkListe_Loeschen(liste);
    FILE *datei;
    datei = fopen(dateiPfad, "r");
    if (!datei) printf("Kann Datei nicht oeffnen\n");
    else {
        char puffer[DATEIPUFFERLAENGE + 0];
        up_dateien_zeileLesen(datei, 0, ""); //Kommentarzeile
        while (!feof(datei)) {
          //  up_dateien_zeileLesen(f, datei, 4, "%[^|]*c%[^|]*c%[^|]*c%[^\n]*c", f->titel, f->autor, f->verlag,&f->preis);
        }
        fclose(datei);
        printf("\nDatei erfolgreich geladen...\n");
    }
}

void up_dateien_zeileSchreiben(FILE *datei, int anzahlElemente, const char *typen, ...) {
    va_list elementPointer;
    va_start(elementPointer, anzahlElemente);
    char puffer[STRINGLAENGE * anzahlElemente];
    vsprintf(puffer, typen, elementPointer);
    fputs(puffer, datei);
    fputs("\n", datei);
}

void up_dateien_Speichern(char *dateiPfad, t_verkListe *liste){
    FILE *datei;
    datei = fopen(dateiPfad, "w");
    if (!datei) fprintf(stderr, "Kann Datei nicht oeffnen\n");
    else {
        t_vL_element *mom = liste->start;
        up_dateien_zeileSchreiben(datei, 4, "%s|%s|%s|%s", "Titel", "Autor", "Verlag", "Preis");
        while (mom) {
            //up_dateien_zeileSchreiben(datei, 4, "%s|%s|%s|%f", mom->titel, mom->autor, mom->verlag, mom->preis);
            mom = mom->danach;
        }
        fclose(datei);
        printf("\nDatei erfolgreich gespeichert...\n");
    }
}
