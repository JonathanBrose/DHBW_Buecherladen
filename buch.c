#include "main.h"

int up_vergleicheStrings(char *s1, char *s2) {
    char string1[STRINGLAENGE], string2[STRINGLAENGE];
    strcpy(string1, s1);
    strcpy(string2, s2);
    strlwr(string1);
    strlwr(string2);
    int i =0;
    while(string1[i]!= 0){
        if(string2[i] == 0){
            return 1;
        }
        if(string1[i] < string2[i]){
            return -1;
        }else if(string1[i]> string2[i]){
            return 1;
        }
        i++;
    }
    return 0;
}

int up_buch_vergleichePreis(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return ((t_Buch *) buch1->inhalt)->preis * 10000 - ((t_Buch *) buch2->inhalt)->preis * 10000;
}

int up_buch_vergleicheTitel(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return up_vergleicheStrings(((t_Buch *) buch1->inhalt)->titel, ((t_Buch *) buch2->inhalt)->titel);
}

int up_buch_vergleicheAutor(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return up_vergleicheStrings(((t_Buch *) buch1->inhalt)->autor, ((t_Buch *) buch2->inhalt)->autor);
}

int up_buch_vergleicheVerlag(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return up_vergleicheStrings(((t_Buch *) buch1->inhalt)->verlag, ((t_Buch *) buch2->inhalt)->verlag);
}

//Es werden alle Buecher angezeigt, bei denen suche in min. einem der Felder enthalten ist.
void up_buch_BuecherAnzeigen(t_verkListe *liste, char *suche, int ausgabezeilen) {
    t_vL_element *element = liste->start;
    t_Buch *buch;
    int i = 0, laenge = 0, zeilenBreite[5] = {5, 5, 5, 6, 5};
    char format[STRINGLAENGE], format2[STRINGLAENGE], s_preis[STRINGLAENGE], trennstrings[5][STRINGLAENGE];
    char sucheKopie[STRINGLAENGE], stringKopien[4][STRINGLAENGE];
    strcpy(sucheKopie, suche);
    strlwr(sucheKopie);
    //bestimmen der zeilenbreiten...
    while (element) {
        buch = (t_Buch *) element->inhalt;
        sprintf(s_preis, "%.2f", buch->preis);
        strcpy(stringKopien[0], buch->titel);
        strcpy(stringKopien[1], buch->autor);
        strcpy(stringKopien[2], buch->verlag);
        strcpy(stringKopien[3], s_preis);
        for (int j = 0; j < 4; j++) {
            strlwr(stringKopien[j]);
        }
        if (strstr(stringKopien[0], sucheKopie) || strstr(stringKopien[1], sucheKopie) ||
            strstr(stringKopien[2], sucheKopie) ||
            strstr(stringKopien[3], sucheKopie)) {
            laenge = strlen(buch->titel);
            if (laenge > zeilenBreite[1]) zeilenBreite[1] = laenge;
            laenge = strlen(buch->autor);
            if (laenge > zeilenBreite[2]) zeilenBreite[2] = laenge;
            laenge = strlen(buch->verlag);
            if (laenge > zeilenBreite[3]) zeilenBreite[3] = laenge;
            laenge = strlen(s_preis);
            if (laenge > zeilenBreite[4]) zeilenBreite[4] = laenge;
        }
        element = element->danach;
    }
    //ausgeben...
    for (int j = 0; j < 5; j++) {
        for (int x = 0; x < zeilenBreite[j]; x++) {
            trennstrings[j][x] = '-';
        }
        trennstrings[j][zeilenBreite[j]] = 0;
    }
    sprintf(format, "| %%%dd | %%%ds | %%%ds | %%%ds | %%%ds |\n", zeilenBreite[0], -zeilenBreite[1], -zeilenBreite[2],
            -zeilenBreite[3], zeilenBreite[4]);
    sprintf(format2, "| %%%ds | %%%ds | %%%ds | %%%ds | %%%ds |\n", zeilenBreite[0], -zeilenBreite[1], -zeilenBreite[2],
            -zeilenBreite[3], zeilenBreite[4]);
    element = liste->start;
    printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
    printf(format2, "Index", "Titel", "Autor", "Verlag", "Preis");
    printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
    while (element) {
        if (ausgabezeilen > 0 && i > 0 && (i % (ausgabezeilen+1) == 0)) {
            printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
            up_warte();
            printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
            printf(format2, "Index", "Titel", "Autor", "Verlag", "Preis");
            printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
        }
        buch = (t_Buch *) element->inhalt;
        sprintf(s_preis, "%.2f", buch->preis);
        strcpy(stringKopien[0], buch->titel);
        strcpy(stringKopien[1], buch->autor);
        strcpy(stringKopien[2], buch->verlag);
        strcpy(stringKopien[3], s_preis);
        for (int j = 0; j < 4; j++) {
            strlwr(stringKopien[j]);
        }
        if (strstr(stringKopien[0], sucheKopie) || strstr(stringKopien[1], sucheKopie) ||
            strstr(stringKopien[2], sucheKopie) ||
            strstr(stringKopien[3], sucheKopie)) {
            printf(format, i, buch->titel, buch->autor, buch->verlag, s_preis);
        }
        element = element->danach;
        i++;
    }
    if (i == 0) printf(format2, "leer", "leer", "leer", "leer", "leer");
    printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
}

t_verkListe *up_buch_erzeugeBuecherListe(void) {
    t_verkListe *buecherListe = up_verkListe_erzeugeListe();
    return buecherListe;
}

void up_buch_BuchHinzufuegen(t_verkListe *buecherListe, t_Buch buch) {
    up_verkListe_hinzufuegen(buecherListe, up_buch_klonen(buch));
}
t_Buch* up_buch_klonen(t_Buch buch){
    t_Buch *buchNeu = (t_Buch *) malloc(sizeof(t_Buch));
    if (!buchNeu) {
        fprintf(stderr,
                "Malloc fehlgeschlagen, kein Hauptspeicher mehr verfuegbar\n"
                "Bitte Datensatze abspeichern, fluechtige Daten loeschen und erneut versuchen\n");
        return NULL;
    }
    strcpy(buchNeu->autor, buch.autor);
    strcpy(buchNeu->titel, buch.titel);
    strcpy(buchNeu->verlag, buch.verlag);
    buchNeu->preis = buch.preis;
    return buchNeu;
}