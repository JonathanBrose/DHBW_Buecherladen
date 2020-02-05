#include "main.h"

int up_vergleicheBuchPreis(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return ((t_Buch*)buch1->inhalt)->preis - ((t_Buch*)buch2->inhalt)->preis;
}

int up_vergleicheBuchTitel(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return ((t_Buch*)buch1->inhalt)->titel[0] - ((t_Buch*)buch2->inhalt)->titel[0];
}

int up_teile(t_vL_element **daten, int links, int rechts, int(*vergleiche)(t_vL_element *, t_vL_element *)) {
    int i = links;
    int j = rechts - 1;
    t_vL_element *pivot = daten[rechts], *temp;
    do {
        while (i < rechts && vergleiche(daten[i], pivot) < 0) {
            i++;
        }
        while (j > links && vergleiche(daten[j], pivot) >= 0) {
            j--;
        }
        if (i < j) {
            temp = daten[i];
            daten[i] = daten[j];
            daten[j] = temp;
        }
    } while (i < j);
    temp = daten[i];
    daten[i] = daten[rechts];
    daten[rechts] = temp;
    return i;
}

void up_quick(t_vL_element **daten, int links, int rechts, int(*vergleiche)(t_vL_element *, t_vL_element *)) {
    if (links < rechts) {
        int teiler = up_teile(daten, links, rechts, vergleiche);
        up_quick(daten, links, teiler - 1, vergleiche);
        up_quick(daten, teiler + 1, rechts, vergleiche);
    }
}

void up_verkListe_sort(t_ListVerwaltung *f, int(*vergleiche)(t_vL_element *, t_vL_element *)) {
    int anzahl = up_verkListe_AnzahlElemente(f);
    t_vL_element *daten[anzahl], *momentan = f->start;
    for (int i = 0; i < anzahl; i++) {
        daten[i] = momentan;
        momentan = momentan->danach;
    }
    up_quick(daten, 0, anzahl - 1, vergleiche);
    f->start = daten[0];
    daten[0]->davor = NULL;
    for (int i = 0; i < anzahl; i++) {
        if (i < anzahl - 1)
            daten[i]->danach = daten[i + 1];
        if (i > 0)
            daten[i]->davor = daten[i - 1];
    }
    daten[anzahl - 1]->danach = NULL;
    f->ende = daten[anzahl - 1];
    f->momentan = f->ende;
}

void up_verkListe_Vertauschen(t_ListVerwaltung *f, t_vL_element *element1, t_vL_element *element2) {
    if (element1 && element2) {
        t_vL_element temp = *element1;
        element1->davor = element2->davor;
        element1->danach = element2->danach;
        element2->davor = temp.davor;
        element2->danach = temp.danach;

        if (element1->danach) {
            if (element1->danach == element1) {
                element1->danach = element2;
                element2->danach = element1;
            } else {
                element1->danach->davor = element1;
            }
        }
        if (element2->danach) {
            if (element2->danach == element2) {
                element2->danach = element1;
                element1->davor = element2;
            } else {
                element2->danach->davor = element2;
            }
        }
        if (element1->davor)
            element1->davor->danach = element1;
        else
            f->start = element1;

        if (element2->davor)
            element2->davor->danach = element2;
        else
            f->start = element2;
    }
}
