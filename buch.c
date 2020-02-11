#include "main.h"

int up_vergleicheStrings(char *s1, char *s2) {
    return strcmp(s1, s2);
}

int up_buch_vergleichePreis(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return ((t_Buch *) buch1->inhalt)->preis - ((t_Buch *) buch2->inhalt)->preis;
}

int up_buch_vergleicheTitel(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return up_vergleicheStrings(((t_Buch *) buch1)->titel, ((t_Buch *) buch2)->titel);
}

int up_buch_vergleicheAutor(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return up_vergleicheStrings(((t_Buch *) buch1)->autor, ((t_Buch *) buch2)->autor);
}

int up_buch_vergleicheVerlag(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return up_vergleicheStrings(((t_Buch *) buch1)->autor, ((t_Buch *) buch2)->autor);
}

//Es werden alle Buecher angezeigt, bei denen suche in min. einem der Felder enthalten ist.
void up_buch_BuecherAnzeigen(t_verkListe *liste, char *suche) {
    t_vL_element *element = liste->start;
    t_Buch *buch;
    int i = 0, laenge = 0, zeilenBreite[4] = {0, 0, 0, 0};
    char format[STRINGLAENGE], s_preis[STRINGLAENGE];
    //bestimmen der zeilenbreiten...
    while (element) {
        buch = (t_Buch *) element->inhalt;
        sprintf(s_preis, "%10.2f", buch->preis);
        if (strstr(buch->titel, suche) || strstr(buch->autor, suche) || strstr(buch->verlag, suche) ||
            strstr(s_preis, suche)) {
            laenge = strlen(buch->titel);
            if (laenge > zeilenBreite[0]) zeilenBreite[0] = laenge;
            laenge = strlen(buch->autor);
            if (laenge > zeilenBreite[1]) zeilenBreite[1] = laenge;
            laenge = strlen(buch->verlag);
            if (laenge > zeilenBreite[2]) zeilenBreite[2] = laenge;
            laenge = strlen(s_preis);
            if (laenge > zeilenBreite[3]) zeilenBreite[3] = laenge;
        }
        element = element->danach;
    }
    //ausgeben...
    sprintf(format, "%%-4d: %%%ds %%%ds %%%ds %%%ds\n", zeilenBreite[0], zeilenBreite[1], zeilenBreite[2],
            zeilenBreite[3]);
    printf(format, 0, "Titel", "Autor", "Verlag", "Preis");
    element = liste->start;
    while (element) {
        buch = (t_Buch *) element->inhalt;
        sprintf(s_preis, "%10.2f", buch->preis);
        if (strstr(buch->titel, suche) || strstr(buch->autor, suche) || strstr(buch->verlag, suche) ||
            strstr(s_preis, suche)) {
            printf(format, i, buch->titel, buch->autor, buch->verlag, buch->preis);
        }
        element = element->danach;
        i++;
    }
}

t_verkListe *up_buch_erzeugeBuecherListe(void) {
    t_verkListe *buecherListe = up_verkListe_erzeugeListe();
    return buecherListe;
}

void up_buch_BuchHinzufuegen(t_verkListe *buecherListe, t_Buch buch) {
    t_Buch *buchNeu = (t_Buch *) malloc(sizeof(t_Buch));
    strcpy(buchNeu->autor, buch.autor);
    strcpy(buchNeu->titel, buch.titel);
    strcpy(buchNeu->verlag, buch.verlag);
    buchNeu->preis = buch.preis;
    up_verkListe_hinzufuegen(buecherListe, buchNeu);
}
