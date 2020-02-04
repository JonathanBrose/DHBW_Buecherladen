#include "zeug.h"

void up_zeileLesen(t_ListVerwaltung *f, FILE *datei, int anzahlElemente, const char *typen, ...){
    va_list elementPointer;
    va_start(elementPointer, anzahlElemente);
    char puffer[DATEIPUFFERLAENGE + 0];
    fgets(puffer, DATEIPUFFERLAENGE, datei);
    if(anzahlElemente > 0) {
        if (vsscanf(puffer, typen, elementPointer) == anzahlElemente) {
            up_BuchHinzufuegen(f);
        }
    }
}
void up_DateiEinlesen(t_ListVerwaltung *f) {
    FILE *datei;
    datei = fopen(f->datei, "r");
    if (!datei) printf("Kann Datei nicht oeffnen\n");
    else {
        char puffer[DATEIPUFFERLAENGE + 0];
        up_zeileLesen(f, datei, 0, ""); //Kommentarzeile
        while (!feof(datei)) {
            up_zeileLesen(f, datei, 4, "%[^|]*c%[^|]*c%[^|]*c%[^\n]*c", f->titel, f->autor, f->verlag, &f->preis);
        }
        fclose(datei);
        printf("\nDatei erfolgreich geladen...\n");
    }
}

void up_zeileSchreiben(FILE *datei, int anzahlElemente, const char *typen, ...) {
    va_list elementPointer;
    va_start(elementPointer, anzahlElemente);
    char puffer[STRINGLAENGE*anzahlElemente];
    vsprintf(puffer,typen, elementPointer);
    fputs(puffer, datei);
    fputs("\n", datei);
}

void up_DateiSpeichern(t_ListVerwaltung *f) {
    FILE *datei;
    datei = fopen(f->datei, "w");
    if (!datei) fprintf(stderr,"Kann Datei nicht oeffnen\n");
    else {
        t_BuchL *mom = f->start;
        up_zeileSchreiben(datei, 4, "%-30s|%-30s|%-30s|%-30s", "Titel", "Autor", "Verlag", "Preis");
        while (mom) {
            up_zeileSchreiben(datei, 4, "%-30s|%-30s|%-30s|%-30.2f", mom->titel, mom->autor, mom->verlag, mom->preis);
            mom = mom->danach;
        }
        fclose(datei);
        printf("\nDatei erfolgreich gespeichert...\n");
    }
}
