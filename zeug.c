#include "main.h"

void clearInputbuffer(void) {
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void up_warte(void) {
    printf("Druecken sie ENTER um fortzufahren...\n");
    getchar();
}


//todo: regex Suche
void up_BuecherAnzeigen(t_verkListe *liste, ) {
    t_vL_element *element = liste->start;
    t_Buch *buch;
    int i = 0;
    printf("%-4d: %10s %10s %10s %10s\n", 0, "Titel", "Autor", "Verlag", "Preis");
    while (element) {
        prin
        buch = (*buch)(element->inhalt);
        if() printf("%-4d: %10s %10s %10s %10.2f\n", i + 1, buch->titel, buch->autor, buch->verlag, buch->preis);
        element = element->danach;
        i++;
    }
    up_warte();
}
int regexVergleich(char *s, char *regex){
    regmatch_t matches[1];
    int rv;
    regex_t exp;
    rv = regcomp(&exp, "-?[0-9]+(\\.[0-9]+)?", REG_EXTENDED);
    if (rv != 0) {
        printf("regcomp failed with %d\n", rv);
    }
    if (regexec(&exp, s, 1, matches, 0) == 0) {
        printf("\"%s\" matches characters %d - %d\n", s, matches[0].rm_so, matches[0].rm_eo);
    } else {
        printf("\"%s\" does not match\n", s);
    }
}


void up_structListe(t_ListVerwaltung *f) {
    strcpy(f->momentan->titel, f->titel);
    strcpy(f->momentan->autor, f->autor);
    strcpy(f->momentan->verlag, f->verlag);
    f->momentan->preis = f->preis;
}

void up_BuchHinzufuegen(t_ListVerwaltung *f) {
    f->momentan = (t_vL_element *) malloc(sizeof(t_vL_element));
    up_structListe(f);
    f->momentan->davor = f->ende;
    f->momentan->danach = 0;
    if (!f->ende) f->start = f->momentan;
    else f->ende->danach = f->momentan;
    f->ende = f->momentan;
}

void up_BuchLoeschen(t_ListVerwaltung *f) {
    //up_suche(f);
    t_vL_element *momentanNeu;
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

