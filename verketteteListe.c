#include "main.h"

//neues Element an Liste anhaengen
void up_verkListe_hinzufuegen(t_verkListe *liste, void *inhalt) {
    up_verkListe_elementEinfuegen(liste, liste->ende, inhalt);
}

t_verkListe* up_verkListe_erzeugeListe(void){
    t_verkListe *liste = (t_verkListe*) malloc(sizeof(t_verkListe));
    liste->anzahlElemente = 0;
    liste->start = NULL;
    liste->ende = NULL;
    return liste;
}

//Neues Element wird erstellt und hinter vorgaenger eingefuegt
void up_verkListe_elementEinfuegen(t_verkListe *liste, t_vL_element *vorgaenger, void *inhalt) {
    t_vL_element *neu = (t_vL_element*) (malloc(sizeof(t_vL_element)));
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

//negative anzahl loescht nach oben statt nach unten
void up_verkListe_ElementeLoeschen(t_verkListe *liste, t_vL_element *loeschBeginn, int anzahl) {
    //Ueberpruefung ob Liste leer, oder loeschelement = NUll usw...
    if (liste->anzahlElemente == 0) {
        fprintf(stderr, "Liste ist leer!\n");
        return;
    } else if (!loeschBeginn) {
        fprintf(stderr, "Zu loschendes Element nicht vorhanden!\n");
        return;
    }
    //ueberpruefung ob loeschelement in Liste
    t_vL_element *temp = loeschBeginn, *loeschEnde = loeschBeginn;
    if (liste->start != loeschBeginn) {
        while (temp != liste->start) {
            if (temp) temp = temp->davor;
            else {
                fprintf(stderr, "Zu loschendes Element nicht in Liste vorhanden!\n");
                return;
            }
        }
    }
    //Bestimmen des Loeschbereichs
    temp = loeschBeginn;
    int i = 0;
    if (anzahl < 0) {
        i--;
        while (loeschEnde->davor && i > anzahl) {
            loeschEnde = loeschEnde->davor;
            i--;
        }
        loeschBeginn = loeschEnde;
        loeschEnde = temp;
        liste->anzahlElemente += anzahl;
    } else {
        i++;
        while (loeschEnde->danach && i < anzahl) {
            loeschEnde = loeschEnde->danach;
            i++;
            liste->anzahlElemente -= anzahl;
        }
    }
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
t_vL_element* up_verkListeIndex(t_verkListe *liste, int index) {
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

t_vL_element* up_verkListeInhalt(t_verkListe *liste, void *inhalt){
    t_vL_element *rueckgabe, *temp = liste->start;
    while(temp){
        if(temp->inhalt == inhalt){
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


int up_quick_teile(t_vL_element **daten, int links, int rechts, int(*vergleiche)(t_vL_element *, t_vL_element *), int absteigend) {
    if(absteigend){
        absteigend = -1;
    }else{
        absteigend = 1;
    }
    int i = links;
    int j = rechts - 1;
    t_vL_element *pivot = daten[rechts], *temp;
    do {
        while (i < rechts && absteigend*vergleiche(daten[i], pivot) < 0) {
            i++;
        }
        while (j > links && absteigend*vergleiche(daten[j], pivot) >= 0) {
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

void up_quick(t_vL_element **daten, int links, int rechts, int(*vergleiche)(t_vL_element *, t_vL_element *), int absteigend) {
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
void up_ListenZeigerAnzeigen(t_verkListe *liste) {
    if(liste->anzahlElemente == 0) {
       fprintf(stderr, "Liste ist leer!\n");
       return;
    }
    t_vL_element *element = liste->start;
    printf("%-27s %10s %10s %10s\n", "Inhalt (Zeiger)", "davor", "momentan", "danach");
    int i = 0;
    while (element) {
        printf("%5d.:%-20x %10x %10x %10x\n", i, element->inhalt, element->davor, element, element->danach);
        i++;
        element = element->danach;
    }
}

