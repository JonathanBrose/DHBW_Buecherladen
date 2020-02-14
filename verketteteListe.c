#include "main.h"

//neues Element an Liste anhaengen
void up_verkListe_hinzufuegen(t_verkListe *liste, void *inhalt) {
    up_verkListe_elementEinfuegen(liste, liste->ende, inhalt);
}

t_verkListe *up_verkListe_erzeugeListe(void) {
    t_verkListe *liste = (t_verkListe *) malloc(sizeof(t_verkListe));
    if (!liste) {
        fprintf(stderr,
                "Malloc fehlgeschlagen, kein Hauptspeicher mehr verfuegbar\n"
                "Bitte andere Programme schließen und nochmal versuchen\n");
        return NULL;
    }
    liste->anzahlElemente = 0;
    liste->start = NULL;
    liste->ende = NULL;
    return liste;
}

//Neues Element wird erstellt und hinter vorgaenger eingefuegt
void up_verkListe_elementEinfuegen(t_verkListe *liste, t_vL_element *vorgaenger, void *inhalt) {
    t_vL_element *neu = (t_vL_element *) (malloc(sizeof(t_vL_element)));
    if (!neu) {
        fprintf(stderr,
                "Malloc fehlgeschlagen, kein Hauptspeicher mehr verfuegbar\n"
                "Bitte Datensatze abspeichern, fluechtige Daten loeschen und erneut versuchen\n");
        return;
    }
    neu->inhalt = inhalt;
    //Vorgaenger NUll -> neues Element soll an Anfang der Liste eingefuegt werden
    if (!vorgaenger) {
        neu->davor = NULL;
        //Es existiert schon ein Liste -> verschieben
        if (liste->start) {
            liste->start->davor = neu;
            neu->danach = liste->start;
        } else {
            neu->danach = NULL;
        }
        liste->start = neu;
    } else {
        neu->danach = vorgaenger->danach;
        neu->davor = vorgaenger;
        vorgaenger->danach = neu;
    }
    //Das neue Element ist das letzte der Liste
    if (!neu->danach) {
        liste->ende = neu;
    } else {
        neu->danach->davor = neu;
    }
    //elementzaehler erhoehen
    liste->anzahlElemente++;
}

void up_verkListe_dupliziere(t_verkListe *liste, t_vL_element *klonBeginn, int zusatzAnzahl) {
    //Ueberpruefung ob Liste leer, oder klonElement = NUll usw...
    if (liste->anzahlElemente == 0) {
        fprintf(stderr, "Liste ist leer!\n");
        return;
    } else if (!klonBeginn) {
        fprintf(stderr, "Zu klonendes Element nicht vorhanden!\n");
        return;
    }
    //ueberpruefung ob klonElement in Liste
    t_vL_element *temp = klonBeginn;
    if (liste->start != klonBeginn) {
        while (temp != liste->start) {
            if (temp) temp = temp->davor;
            else {
                fprintf(stderr, "Zu klonendes Element nicht in Liste vorhanden!\n");
                return;
            }
        }
    }
    temp = klonBeginn;
    if (zusatzAnzahl < 0) {
        up_verkListe_elementEinfuegen(liste, temp->davor, up_buch_klonen(*(t_Buch *) temp->inhalt));
        temp = temp->davor->davor;
        while (temp && zusatzAnzahl != 0) {
            up_verkListe_elementEinfuegen(liste, temp->davor, up_buch_klonen(*(t_Buch *) temp->inhalt));
            temp = temp->davor->davor;
            zusatzAnzahl++;
        }
    } else {
        up_verkListe_elementEinfuegen(liste, temp, up_buch_klonen(*(t_Buch *) temp->inhalt));
        temp = temp->danach->danach;
        while (temp && zusatzAnzahl != 0) {
            up_verkListe_elementEinfuegen(liste, temp, up_buch_klonen(*(t_Buch *) temp->inhalt));
            temp = temp->danach->danach;
            zusatzAnzahl--;
        }
    }

}

//negative anzahl loescht nach oben statt nach unten
void up_verkListe_ElementeLoeschen(t_verkListe *liste, t_vL_element *loeschBeginn, int zusatzAnzahl) {
    //Ueberpruefung ob Liste leer, oder loeschelement = NUll usw...
    if (liste->anzahlElemente == 0) {
        fprintf(stderr, "Liste ist leer!\n");
        return;
    } else if (!loeschBeginn) {
        fprintf(stderr, "Zu loeschendes Element nicht vorhanden!\n");
        return;
    }
    //ueberpruefung ob loeschelement in Liste
    t_vL_element *temp = loeschBeginn, *loeschEnde = loeschBeginn;
    if (liste->start != loeschBeginn) {
        while (temp != liste->start) {
            if (temp) temp = temp->davor;
            else {
                fprintf(stderr, "Zu loeschendes Element nicht in Liste vorhanden!\n");
                return;
            }
        }
    }
    //Bestimmen des Loeschbereichs
    temp = loeschBeginn;
    int i = 0;
    if (zusatzAnzahl < 0) {
        while (loeschEnde->davor && i > zusatzAnzahl) {
            loeschEnde = loeschEnde->davor;
            i--;
            liste->anzahlElemente--;
        }
        loeschBeginn = loeschEnde;
        loeschEnde = temp;
    } else {
        while (loeschEnde->danach && i < zusatzAnzahl) {
            loeschEnde = loeschEnde->danach;
            i++;
            liste->anzahlElemente--;
        }
    }
    liste->anzahlElemente--;
    if (liste->anzahlElemente <= 0) {
        liste->anzahlElemente = 0;
        liste->start = 0;
        liste->ende = 0;
    }
    //Loeschung
    if (loeschBeginn->davor) {
        loeschBeginn->davor->danach = loeschEnde->danach;
    } else {
        liste->start = loeschEnde->danach;
    }
    if (loeschEnde->danach) {
        loeschEnde->danach->davor = loeschBeginn->davor;
    }
    while (loeschBeginn != loeschEnde) {
        temp = loeschBeginn;
        loeschBeginn = loeschBeginn->danach;
        free(temp->inhalt);
        free(temp);
    }
    free(loeschEnde->inhalt);
    free(loeschEnde);
}

//gibt das element an Index zurueck
t_vL_element *up_verkListeIndex(t_verkListe *liste, int index) {
    if (index < 0 || index >= liste->anzahlElemente) {
        return NULL;
    }
    int i = 0;
    t_vL_element *temp = liste->start;
    while (temp->danach && i < index) {
        temp = temp->danach;
        i++;
    }
    return temp;
}

t_vL_element *up_verkListeInhalt(t_verkListe *liste, void *inhalt) {
    t_vL_element *rueckgabe = NULL, *temp = liste->start;
    while (temp) {
        if (temp->inhalt == inhalt) {
            rueckgabe = temp;
            break;
        }
        temp = temp->danach;
    }
    return rueckgabe;
}

//loescht gesamte Liste
void up_verkListe_Loeschen(t_verkListe *liste) {
    up_verkListe_ElementeLoeschen(liste, liste->start, liste->anzahlElemente);
}


int up_quick_teile(t_vL_element **daten, int links, int rechts, int(*vergleiche)(t_vL_element *, t_vL_element *),
                   int absteigend) {
    if (absteigend) {
        absteigend = -1;
    } else {
        absteigend = 1;
    }
    int i = links;
    int j = rechts - 1;
    t_vL_element *pivot = daten[rechts], *temp;
    do {
        while (i < rechts && absteigend * vergleiche(daten[i], pivot) < 0) {
            i++;
        }
        while (j > links && absteigend * vergleiche(daten[j], pivot) >= 0) {
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

void up_quick(t_vL_element **daten, int links, int rechts, int(*vergleiche)(t_vL_element *, t_vL_element *),
              int absteigend) {
    if (links < rechts) {
        int teiler = up_quick_teile(daten, links, rechts, vergleiche, absteigend);
        up_quick(daten, links, teiler - 1, vergleiche, absteigend);
        up_quick(daten, teiler + 1, rechts, vergleiche, absteigend);
    }
}

void up_verkListe_sort(t_verkListe *liste, int(*vergleiche)(t_vL_element *, t_vL_element *), int absteigend) {
    //Zeiger der Liste in array schreiben
    int anzahl = liste->anzahlElemente;
    t_vL_element *daten[anzahl], *momentan = liste->start;
    for (int i = 0; i < anzahl; i++) {
        daten[i] = momentan;
        momentan = momentan->danach;
    }
    //sortieren per quicksort
    up_quick(daten, 0, anzahl - 1, vergleiche, absteigend);

    //Zeiger aus Array zurueck in Liste sortieren
    liste->start = daten[0];
    daten[0]->davor = NULL;
    for (int i = 0; i < anzahl; i++) {
        if (i < anzahl - 1)
            daten[i]->danach = daten[i + 1];
        if (i > 0)
            daten[i]->davor = daten[i - 1];
    }
    daten[anzahl - 1]->danach = NULL;
    liste->ende = daten[anzahl - 1];
}

void up_verkListe_ElementeVertauschen(t_verkListe *liste, t_vL_element *element1, t_vL_element *element2) {
    //Nur wenn beide elemente existieren
    if (element1 && element2) {
        //davor und danach zeiger vertauschen
        t_vL_element temp = *element1;
        element1->davor = element2->davor;
        element1->danach = element2->danach;
        element2->davor = temp.davor;
        element2->danach = temp.danach;
        if (element1->danach) {
            //elemente waren nebeneinander -> selbstverweis muss behoben werden
            if (element1->danach == element1) {
                element1->danach = element2;
                element2->danach = element1;
            } else {
                element1->danach->davor = element1;
            }
        }
        //elemente waren nebeneinander -> selbstverweis muss behoben werden
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
            liste->start = element1;

        if (element2->davor)
            element2->davor->danach = element2;
        else
            liste->start = element2;
    }
}

void up_verkList_ListenZeigerAnzeigen(t_verkListe *liste, int ausgabezeilen, int index) {
    t_vL_element *element = liste->start;
    int i = 0, laenge = 0, zeilenBreite[5] = {5, 15, 8, 8, 8};
    char format[STRINGLAENGE], format2[STRINGLAENGE], trennstrings[5][STRINGLAENGE], puffer[4][STRINGLAENGE];
    //bestimmen der zeilenbreiten...
    while (element) {
        sprintf(puffer[0], "0x%x", element->inhalt);
        laenge = strlen(puffer[0]);
        if (laenge > zeilenBreite[1]) zeilenBreite[1] = laenge;
        sprintf(puffer[0], "0x%x", element->davor);
        laenge = strlen(puffer[0]);
        if (laenge > zeilenBreite[2]) zeilenBreite[2] = laenge;
        sprintf(puffer[0], "0x%x", element);
        laenge = strlen(puffer[0]);
        if (laenge > zeilenBreite[3]) zeilenBreite[3] = laenge;
        sprintf(puffer[0], "0x%x", element->danach);
        laenge = strlen(puffer[0]);
        if (laenge > zeilenBreite[4]) zeilenBreite[4] = laenge;
        element = element->danach;
    }
    //ausgeben...
    for (int j = 0; j < 5; j++) {
        for (int x = 0; x < zeilenBreite[j]; x++) {
            trennstrings[j][x] = '-';
        }
        trennstrings[j][zeilenBreite[j]] = 0;
    }
    sprintf(format, "| %%%dd | %%%ds | %%%ds | %%%ds | %%%ds |\n", zeilenBreite[0], -zeilenBreite[1], zeilenBreite[2],
            zeilenBreite[3], zeilenBreite[4]);
    sprintf(format2, "| %%%ds | %%%ds | %%%ds | %%%ds | %%%ds |\n", zeilenBreite[0], -zeilenBreite[1], zeilenBreite[2],
            zeilenBreite[3], zeilenBreite[4]);
    element = liste->start;
    printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
    printf(format2, "Index", "Inhalt (Zeiger)", "davor", "momentan", "danach");
    printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
    while (element) {
        if (index >= 0 && i != index) {
            element = element->danach;
            i++;
            continue;
        }
        if (ausgabezeilen > 0 && i > 0 && (i % (ausgabezeilen + 1) == 0)) {
            printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
            up_warte();
            printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
            printf(format2, "Index", "Inhalt (Zeiger)", "davor", "momentan", "danach");
            printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
        }
        sprintf(puffer[0], "0x%x", element->inhalt);
        sprintf(puffer[1], "0x%x", element->davor);
        sprintf(puffer[2], "0x%x", element);
        sprintf(puffer[3], "0x%x", element->danach);
        printf(format, i, puffer[0], puffer[1], puffer[2], puffer[3]);
        element = element->danach;
        i++;
    }
    if (i == 0) printf(format2, "leer", "leer", "leer", "leer", "leer");
    printf(format2, trennstrings[0], trennstrings[1], trennstrings[2], trennstrings[3], trennstrings[4]);
}
