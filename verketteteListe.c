#include "main.h"

int up_verkListe_AnzahlElemente(t_vL_element *liste) {
    int i = 0;
    while (liste) {
        i++;
        liste = liste->danach;
    }
    return i;
}

void up_verkListe_hinzufuegen(t_verkListe *liste, void *inhalt) {
    t_vL_element neu;
    neu.inhalt = inhalt;
    neu.davor = liste->ende;
    neu.danach = 0;
    if (!liste->ende) liste->start = &neu;
    else liste->ende->danach = &neu;
    liste->ende = &neu;
    liste->anzahlElemente++;
}

//negative anzahl löscht nach oben statt nach unten
void up_verkListe_ElementeLoeschen(t_verkListe *liste, t_vL_element *löschBeginn, int anzahl) {
    //Überprüfung ob Liste leer, oder löschelement = NUll usw...
    if (liste->anzahlElemente == 0) {
        fprintf(stderr, "Liste ist leer!\n");
        return;
    } else if (!löschBeginn) {
        printf(stderr, "Zu löschendes Element nicht vorhanden!\n");
        return;
    }
    //Überprüfung ob löschelement in Liste
    t_vL_element *temp = löschBeginn, *löschEnde = löschBeginn;
    if (liste->start != löschBeginn) {
        while (temp != liste->start) {
            if (temp) temp = temp->davor;
            else {
                printf(stderr, "Zu löschendes Element nicht in Liste vorhanden!\n");
                return;
            }
        }
    }
    //Bestimmen des Löschbereichs
    temp = löschBeginn;
    int i = 0;
    if (anzahl < 0) {
        i--;
        while (löschEnde->davor && i > anzahl) {
            löschEnde = löschEnde->davor;
            i--;
        }
        löschBeginn = löschEnde;
        löschEnde = temp;
        liste->anzahlElemente += anzahl;
    } else {
        i++;
        while (löschEnde->danach && i < anzahl) {
            löschEnde = löschEnde->danach;
            i++;
            liste->anzahlElemente -= anzahl;
        }
    }
    if (liste->anzahlElemente <= 0) {
        liste->anzahlElemente = 0;
        liste->start = 0;
        liste->ende = 0;
    }
    //Löschung
    if (löschBeginn->davor) {
        löschBeginn->davor->danach = löschEnde->danach;
    } else {
        liste->start = löschEnde->danach;
    }
    if (löschEnde->danach) {
        löschEnde->danach->davor = löschBeginn->davor;
    }
    while (löschBeginn != löschEnde) {
        temp = löschBeginn;
        löschBeginn = löschBeginn->danach;
        free(temp);
    }
    free(löschEnde);
}

t_vL_element *up_verklisteIndex(t_verkListe *liste, int index) {
    if (index < 0 || index >= liste->anzahlElemente) {
        fprintf(stderr, "Index nicht in der Liste!");
        return NULL;
    }
    int i = 0;
    t_vL_element *temp = liste->start;
    while (temp->danach && i < index - 1) {
        temp = temp->danach;
        i++;
    }
    return temp;
}


void up_verkListe_Loeschen(t_verkListe *liste) {
    up_verkListe_ElementeLoeschen(liste, liste->start, liste->anzahlElemente);
}