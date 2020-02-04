#include "zeug.h";

void clearInputbuffer(void) {
    while (getchar() != '\n');
}

void up_BuecherAnzeigen(t_ListVerwaltung *f) {

}

void up_DateiEinlesen(t_ListVerwaltung *f) {
    FILE *datei;
    datei = fopen(f->datei, "w");
    if (!datei) printf("ahhhh\n");
    else {
        char buffer[DATEIPUFFERLAENGE + 1];
        fgets(buffer, DATEIPUFFERLAENGE, datei);
        while (!feof(datei)) {
            if (buffer[0] != '#') {
                strncpy(f->titel, buffer, DATEIPUFFERLAENGE);
                buffer[DATEIPUFFERLAENGE] = 0;
                strncpy(f->autor, buffer + DATEIPUFFERLAENGE, DATEIPUFFERLAENGE);
                buffer[DATEIPUFFERLAENGE] = 0;
                strncpy(f->verlag, buffer + 2 * DATEIPUFFERLAENGE, DATEIPUFFERLAENGE);
                buffer[DATEIPUFFERLAENGE] = 0;
                sscanf("%f", buffer + 3 * DATEIPUFFERLAENGE);
                up_structListe(f);
            }
            fgets(buffer, DATEIPUFFERLAENGE, datei);
        }
        fclose(datei);
    }
}

void up_csvZeileSchreiben(FILE *datei, int anzahlElemente, ...) {
    va_list elementPointer;
    va_start(elementPointer, anzahlElemente);
    char buffer[STRINGLAENGE];
    for (int i = 0; i < anzahlElemente; i++) {
        strcpy(buffer, va_arg(elementPointer, char*));
        fputs(buffer, datei);
        fputs(";", datei);
    }
    fputs("\n", datei);
}

void up_DateiSpeichern(t_ListVerwaltung *f) {
    FILE *datei;
    datei = fopen(f->datei, "w");
    if (!datei) printf("Can´t open File\n");
    else {
        char buffer[STRINGLAENGE];
        t_BuchL *mom = f->start;
        while (!mom) {

            mom = mom->danach;
        }
        fclose(datei);
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

void up_BuchVertauschen(t_BuchL *item1, t_BuchL *item2) {
    if (!item1 && !item2) {
        if (!item1->davor) item1->davor->danach = item2;
        if (!item1->danach) item1->danach->davor = item2->davor;
        if (!item2->davor) item2->davor->danach = item1;
        if (!item2->danach) item2->danach->davor = item1->davor;
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

