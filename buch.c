#include "main.h"

int up_vergleicheStrings(char *s1, char *s2){
    return strcmp(s1, s2);
}
int up_vergleicheBuchPreis(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return ((t_Buch*)buch1->inhalt)->preis - ((t_Buch*)buch2->inhalt)->preis;
}

int up_vergleicheBuchTitel(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return up_vergleicheStrings(((t_Buch*)buch1)->titel,((t_Buch*)buch2)->titel);
}

int up_vergleicheBuchAutor(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return up_vergleicheStrings(((t_Buch*)buch1)->autor,((t_Buch*)buch2)->autor);
}
int up_vergleicheBuchVerlag(t_vL_element *buch1, t_vL_element *buch2) {
    if (!(buch1 && buch2))return 0;
    return up_vergleicheStrings(((t_Buch*)buch1)->autor,((t_Buch*)buch2)->autor);
}
//Es werden alle Buecher angezeigt, bei denen suche in min. einem der Felder enthalten ist.
void up_BuecherAnzeigen(t_verkListe *liste, char *suche){
    t_vL_element *element = liste->start;
    t_Buch *buch;
    int i = 0;
    printf("%-4d: %10s %10s %10s %10s\n", 0, "Titel", "Autor", "Verlag", "Preis");
    char *s_preis;
    while (element) {
        sprintf(s_preis,"%f",buch->preis);
        if(strstr(buch->titel, suche) || strstr(buch->autor, suche) || strstr(buch->verlag, suche) || strstr(s_preis, suche)) {
            printf("%-4d: %10s %10s %10s %10.2f\n", i + 1, buch->titel, buch->autor, buch->verlag, buch->preis);
        }
        element = element->danach;
        i++;
    }
    up_warte();
}

