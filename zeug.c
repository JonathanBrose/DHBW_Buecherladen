#include "zeug.h";

void clearInputbuffer(void) {
    while (getchar() != '\n');
}
void up_warte(void){
    printf("\nDrücken sie eine beliebige Taste um fortzufahren...\n");
    clearInputbuffer();
    getchar();
}
void up_BuecherAnzeigen(t_ListVerwaltung *f) {
    t_BuchL *mom = f->start;
    int i = 0;
    printf("%-4d: %10s %10s %10s %10s\n",0,"Titel","Autor", "Verlag", "Preis");
    while (mom) {
       printf("%-4d: %10s %10s %10s %10.2f\n",i+1, mom->titel,mom->autor, mom->verlag, mom->preis);
       mom = mom->danach;
       i++;
    }
    up_warte();
}
void up_csvZeileLesen(t_ListVerwaltung *f,FILE *datei, int anzahlElemente, const char *typen, ...){
    va_list elementPointer;
    va_start(elementPointer, anzahlElemente);
    char puffer[DATEIPUFFERLAENGE + 1];
    fgets(puffer, DATEIPUFFERLAENGE, datei);
    if(anzahlElemente != 0) {
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
        char puffer[DATEIPUFFERLAENGE + 1];
        up_csvZeileLesen(f,datei, 0, ""); //Kommentarzeile
        while (!feof(datei)) {
            up_csvZeileLesen(f,datei, 4, "%[^|]*c%[^|]*c%[^|]*c%[^\n]*c", f->titel, f->autor, f->verlag, &f->preis);
        }
        fclose(datei);
    }
}

void up_csvZeileSchreiben(FILE *datei,int anzahlElemente, const char *typen, ...) {
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
        up_csvZeileSchreiben(datei, 4, "%-10s|%-10s|%-10s|%-10s", "Titel", "Autor", "Verlag","Preis");
        while (mom) {
            up_csvZeileSchreiben(datei, 4, "%-10s|%-10s|%-10s|%-10.2f", mom->titel, mom->autor, mom->verlag, mom->preis);
            mom = mom->danach;
        }
        fclose(datei);
        printf("\nDatei erfolgreich gespeichert...\n");
    }
}

void up_BuchVertauschen(t_BuchL *buch1, t_BuchL *buch2) {
    if (buch1 && buch2) {
        t_BuchL *temp;
        temp = buch2->danach;
        buch2->danach = buch1->danach;
        buch1->danach = temp;
        temp = buch2->davor;
        buch2->davor = buch1->davor;
        buch1->davor = temp;
        if (buch1->danach)
            buch1->danach->davor = buch1;
        if (buch1->davor)
            buch1->davor->danach = buch1;
        if (buch2->danach)
            buch2->danach->davor = buch2;
        if (buch2->davor)
            buch2->davor->danach = buch2;
    }
}

void up_structListe(t_ListVerwaltung *f) {
    strcpy(f->momentan->titel, f->titel);
    strcpy(f->momentan->autor, f->autor);
    strcpy(f->momentan->verlag, f->verlag);
    f->momentan->preis = f->preis;
}

void up_BuchHinzufuegen(t_ListVerwaltung *f) {
    f->momentan = (t_BuchL *) malloc(sizeof(t_BuchL));
    up_structListe(f);
    f->momentan->davor = f->zwischen;
    f->momentan->danach = 0;
    if (!f->zwischen) f->start = f->momentan;
    else f->zwischen->danach = f->momentan;
    f->zwischen = f->momentan;
}

void up_BuchLoeschen(t_ListVerwaltung *f) {
    //up_suche(f);
    t_BuchL *momentanNeu;
    if (f->momentan) {
        if (f->momentan->davor && f->momentan->danach) { //normales Element
            f->momentan->davor->danach = f->momentan->danach;
            f->momentan->danach->davor = f->momentan->davor;
            momentanNeu = f->momentan->danach;
        } else if (f->momentan->danach) {  // erstes Element
            f->momentan->danach->davor = 0;
            momentanNeu = f->momentan->danach;
        } else if (f->momentan->davor) { // letztes Element
            f->momentan->davor->danach = 0;
            momentanNeu = f->momentan->davor;
        } else { //einziges Element
            momentanNeu = 0;
        }
        free(f->momentan);
        f->momentan = momentanNeu;
    } else {
        printf("Liste leer\n");
    }
}

void up_ListeAnzeigen(t_ListVerwaltung *f) {
    f->momentan = f->start;
    printf("%-20s %10s %10s %10s\n", "Titel", "momentan", "danach", "davor");
    while (f->momentan) {
        printf("%-20s %10x %10x %10x\n", f->momentan->titel, f->momentan, f->momentan->danach, f->momentan->davor);
        f->momentan = f->momentan->danach;
    }
    if (f->momentan == f->start)printf("Liste leer\n");
    printf("Press any key to continue...\n");
    getchar();

}

