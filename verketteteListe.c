#include "main.h"
int up_verkListe_AnzahlElemente(t_vL_element *liste) {
    int i = 0;
    while (liste) {
        i++;
        liste = liste->danach;
    }
    return i;
}
void up_verkListe_hinzufuegen(t_verkListe *liste, void *inhalt){
    t_vL_element neu;
    neu.inhalt = inhalt;
    neu.davor = liste->ende;
    neu.danach = 0;
    if(!liste->ende) liste->start = &neu;
    else liste->ende->danach = &neu;
    liste->ende = &neu;
}
void up_verkListe_ElementeLoeschen(t_verkListe *liste, t_vL_element *opfer, int anzahl){
    if(liste->anzahlElemente == 0) {
        fprintf(stderr, "Liste ist leer!\n");
        return;
    }else if(!opfer){
        printf(stderr, "Zu löschendes Element nicht vorhanden!\n");
        return;
    }
    t_vL_element *temp = opfer;
    if(liste->start != opfer) {
        while (temp != liste){
            if(temp) temp = temp->davor;
            else {
                printf(stderr, "Zu löschendes Element nicht vorhanden!\n");
                return;
            }
        }
    }

}
void up_verkListe_Loeschen(t_verkListe *liste){
    up_verkListe_ElementeLoeschen(liste, liste->start, liste->anzahlElemente);
}