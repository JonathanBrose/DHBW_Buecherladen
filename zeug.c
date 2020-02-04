#include "zeug.h"

void clearInputbuffer(void) {
    char c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
void up_warte(void){
    printf("Druecken sie ENTER um fortzufahren...\n");
    getchar();
}
int up_BuecherAnzahl(t_ListVerwaltung *f){
    t_BuchL *mom = f->start;
    int i = 0;
    while(mom){
        i++;
        mom = mom->danach;
    }
    return i;
}
void up_BuecherAnzeigen(t_ListVerwaltung *f) {
    t_BuchL *mom = f->start;
    int i = 0;
    printf("%-4d: %10s %10s %10s %10s\n",0,"Titel","Autor", "Verlag", "Preis");
    while (mom) {
       printf("%-4d: %10s %10s %10s %10.2f\n",i+1, mom->titel,mom->autor, mom->verlag, mom->preis);
       mom = mom->danach;
       i++;
    }
    up_warte();
}
int up_vergleichePreis(t_BuchL *buch1, t_BuchL *buch2){
    if(!(buch1 && buch2))return 0;
    return buch1->preis - buch2->preis;
}

void up_quick(t_BuchL **pointer, int links, int rechts, int(*vergleiche)(t_BuchL*, t_BuchL*)){
    int ili = links, ire = rechts, med;
    t_BuchL *temp;
    med = (ili+ire)/2;
    while(ili < ire){
        while(vergleiche(pointer[ili], pointer[med])){
            ili++;
        }
        while(-vergleiche(pointer[ire], pointer[med])){
            ire--;
        }
        temp = pointer[ili];
        pointer[ili] = pointer[ire];
        pointer[ire] = temp;
        if(ili == med) {
            med = ire;
        }
        else if(ire == med) {
            med = ili;
        }

        if(ili < med) ili++;
        if(ire > med) ire--;

        if(links < med-1) {
            up_quick(pointer,links, med-1, vergleiche);
        }
        if(rechts > med+1) {
            up_quick(pointer,med+1,rechts, vergleiche);
        }
    }
}
void up_quicksort(t_ListVerwaltung *f, int(*vergleiche)(t_BuchL*, t_BuchL*)){
    int anzahl = up_BuecherAnzahl(f);
    t_BuchL *pointer[anzahl], *momentan=f->start;
    for(int i = 0; i< anzahl; i++){
        pointer[i]= momentan;
        momentan = momentan->danach;
    }
    up_quick(pointer, 0, anzahl-1, vergleiche);
    f->start = pointer[0];
    f->ende  = pointer[anzahl];
    f->momentan = f->ende;
    for(int i = 1; i < anzahl; i++){
        if(i<anzahl-1)
            pointer[i]->danach = pointer[i+1];
        if(i > 0)
            pointer[i]->davor = pointer[i-1];
    }

}
void up_BuchVertauschen(t_ListVerwaltung *f,t_BuchL *buch1, t_BuchL *buch2) {
    if (buch1 && buch2) {
        t_BuchL buch1Kopie = *buch1, buch2Kopie = *buch2;
        buch1->davor = buch2Kopie.davor;
        buch1->danach = buch2Kopie.danach;
        buch2->davor = buch1Kopie.davor;
        buch2->danach = buch1Kopie.danach;

        if (buch1->danach){
            if(buch1->danach == buch1) {
                buch1->danach = buch2;
                buch2->danach = buch1;
            }else{
                buch1->danach->davor = buch1;
            }
        }
        if (buch2->danach){
            if(buch2->danach == buch2) {
                buch2->danach = buch1;
                buch1->davor = buch2;
            }else{
                buch2->danach->davor = buch2;
            }
        }
        if (buch1->davor)
            buch1->davor->danach = buch1;
        else
            f->start = buch1;

        if (buch2->davor)
            buch2->davor->danach = buch2;
        else
            f->start = buch2;
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
    f->momentan->davor = f->ende;
    f->momentan->danach = 0;
    if (!f->ende) f->start = f->momentan;
    else f->ende->danach = f->momentan;
    f->ende = f->momentan;
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

void up_ListenZeigerAnzeigen(t_ListVerwaltung *f) {
    f->momentan = f->start;
    printf("%-20s %10s %10s %10s\n", "Titel", "davor", "momentan", "danach");
    while (f->momentan) {
        printf("%-20s %10x %10x %10x\n", f->momentan->titel, f->momentan->davor, f->momentan, f->momentan->danach);
        f->momentan = f->momentan->danach;
    }
    if (f->momentan == f->start)printf("Liste leer\n");
    up_warte();

}

