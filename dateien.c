#include "main.h"

int up_dateien_zeileLesen(FILE *datei, t_Buch *buch) {
    char puffer[DATEIPUFFERLAENGE];
    fgets(puffer, DATEIPUFFERLAENGE, datei);
    if(buch){
        char *ptr = strtok(puffer, "|");
        if(ptr){
            strcpy(buch->titel, ptr);
        }else{
            return 0;
        }
        ptr = strtok(NULL, "|");
        if(ptr){
            strcpy(buch->autor, ptr);
        }else{
            return 0;
        }
        ptr = strtok(NULL, "|");
        if(ptr){
            strcpy(buch->verlag, ptr);
        }else{
            return 0;
        }
        ptr = strtok(NULL, "|");
        if(ptr){
           sscanf(ptr,"%f",&buch->preis);
        }else{
            return 0;
        }
    }
    return 1;
}

void up_dateien_Einlesen(char *dateiPfad, t_verkListe *liste) {
    FILE *datei;
    datei = fopen(dateiPfad, "r");
    if (!datei) printf("Kann Datei nicht oeffnen\n");
    else {
        t_Buch buch;
        up_dateien_zeileLesen(datei, NULL);
        while (!feof(datei)) {
            if(up_dateien_zeileLesen(datei, &buch)){
                up_buch_BuchHinzufuegen(liste, buch);
            }
        }
        fclose(datei);
        printf("\nDatei erfolgreich eingelesen...\n");
        clearInputbuffer();
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

void up_dateien_Speichern(char *dateiPfad, t_verkListe *liste) {
    FILE *datei;
    datei = fopen(dateiPfad, "w");
    if (!datei) fprintf(stderr, "Kann Datei nicht oeffnen\n");
    else {
        t_Buch *buch;
        t_vL_element *mom = liste->start;
        up_dateien_zeileSchreiben(datei, 4, "%s|%s|%s|%s", "Titel", "Autor", "Verlag", "Preis");
        while (mom) {
            buch = (t_Buch *) mom->inhalt;
            up_dateien_zeileSchreiben(datei, 4, "%s|%s|%s|%f", buch->titel, buch->autor, buch->verlag, buch->preis);
            mom = mom->danach;
        }
        fclose(datei);
        printf("\nDatei erfolgreich gespeichert...\n");
        clearInputbuffer();
    }
}

int up_ueberpruefeDateipfad(char *dateipfad) {
    FILE *datei = fopen(dateipfad, "r");
    if (!datei)return 0;
    fclose(datei);
    return 1;
}

int up_ueberpruefeDateipfadErweitert(char *dateipfad) {
    if (up_ueberpruefeDateipfad(dateipfad)) {
        if (!up_EingabeWeiter("Datei existiert bereits, wollen sie diese ueberschreiben?\n")) {
            return 0;
        }
    } else {
        FILE *datei = fopen(dateipfad, "w");
        if (!datei) {
            fprintf(stderr, "Konnte Datei nicht erstellen, bitte andere Versuchen");
            return 0;
        }
    }
    return 1;
}

void up_ueberpruefeDateipfadVorhanden(t_menu *menu, char modus) {
    int(*funktion)(char *) = up_ueberpruefeDateipfadErweitert;
    char fehlermeldung[STRINGLAENGE] = "";
    if(modus == 'r') {
        funktion = up_ueberpruefeDateipfad;
        sprintf(fehlermeldung, "Datei nicht gefunden\n");
    }
    if (!up_ueberpruefeDateipfad(menu->dateipfad)) {
            up_EingabeString(menu->dateipfad, "Bitte geben sie den Dateipfad ein...\n",
                             funktion,
                             fehlermeldung);
    }
}
