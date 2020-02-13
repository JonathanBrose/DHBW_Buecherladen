#include "main.h"

t_menu *up_menu_erzeugeMenu(t_verkListe *buecherListe, char *titel) {
    t_menu *menu = (t_menu *) malloc(sizeof(t_menu));
    if (!menu) {
        fprintf(stderr,
                "Malloc fehlgeschlagen, kein Hauptspeicher mehr verfuegbar\n"
                "Bitte andere Programme schließen und nochmal versuchen\n");
        return NULL;
    }
    t_verkListe *menuEintraege = up_verkListe_erzeugeListe();
    menu->buecherListe = buecherListe;
    menu->titel = (char *) malloc((strlen(titel)) * sizeof(char));
    if (!menu->titel) {
        fprintf(stderr,
                "Malloc fehlgeschlagen, kein Hauptspeicher mehr verfuegbar\n"
                "Bitte andere Programme schließen und nochmal versuchen\n");
        return NULL;
    }
    strcpy(menu->titel, titel);
    menu->menuEintraege = menuEintraege;
    menu->fehlerEingabe[0] = 0;
    menu->dateipfad = (char *) malloc(STRINGLAENGE * sizeof(char));
    if (!menu->titel) {
        fprintf(stderr,
                "Malloc fehlgeschlagen, kein Hauptspeicher mehr verfuegbar\n"
                "Bitte andere Programme schließen und nochmal versuchen\n");
        return NULL;
    }
    menu->dateipfad[0] = 0;
    return menu;
}

t_menu *up_menu_erzeugeUnterMenu(t_menu *menu, char *titel) {
    t_menu *untermenu = up_menu_erzeugeMenu(menu->buecherListe, titel);
    untermenu->dateipfad = menu->dateipfad;
    return untermenu;
}

void up_menu_EintragHinzufuegen(t_menu *menu, char *titel, char *trigger, t_menu *unterMenu,
                                void(*funktion)(t_menu *)) {
    t_menuEintrag *menuEintrag = (t_menuEintrag *) malloc(sizeof(t_menuEintrag));
    if (!menuEintrag) {
        fprintf(stderr,
                "Malloc fehlgeschlagen, kein Hauptspeicher mehr verfuegbar\n"
                "Bitte andere Programme schließen und nochmal versuchen\n");
        return;
    }
    menuEintrag->titel = titel;
    menuEintrag->trigger = (char *) malloc(strlen(trigger) * sizeof(char));
    if (!menuEintrag->trigger) {
        fprintf(stderr,
                "Malloc fehlgeschlagen, kein Hauptspeicher mehr verfuegbar\n"
                "Bitte andere Programme schließen und nochmal versuchen\n");
        return;
    }
    strcpy(menuEintrag->trigger, trigger);
    menuEintrag->untermenu = unterMenu;
    menuEintrag->funktion = funktion;
    up_verkListe_hinzufuegen(menu->menuEintraege, menuEintrag);
}

void up_menu_DateiEintrag(t_menu *menu) {
    up_menu_EintragHinzufuegen(menu, menu->dateipfad, "Dat:", NULL, up_void);
}

void up_menu_Anzeigen(t_menu *menu) {
    CLEAR_CONSOLE;
    t_vL_element *temp = menu->menuEintraege->start;
    t_menuEintrag menuEintrag;
    char format[STRINGLAENGE], puffer[STRINGLAENGE];
    printf("\n");
    sprintf(format, "%%%ds %%%ds\n", -(MAX_TRIGGER_LAENGE + 2), -STRINGLAENGE);
    printf("*** %s ***\n", menu->titel);
    while (temp) {
        menuEintrag = *(t_menuEintrag *) (temp->inhalt);
        if (menuEintrag.titel) {
            if (strlen(menuEintrag.trigger) > 0) {
                sprintf(puffer, "[%s]", menuEintrag.trigger);
            } else {
                puffer[0] = 0;
            }
            printf(format, puffer, menuEintrag.titel);
        }
        temp = temp->danach;
    }
    printf("\n");
    up_menu_Auswahl(menu);
}

void up_menu_Auswahl(t_menu *menu) {
    //Initialisierung
    t_vL_element *temp = menu->menuEintraege->start;
    t_menuEintrag menuEintrag;
    char eingabe[MAX_TRIGGER_LAENGE + 1], *ergebnis = 0;
    //Eingabefehler ueberpruefen
    if (strlen(menu->fehlerEingabe) > 0)
        fprintf(stderr, "Fehler bei der Eingabe: Menupunkt \"%s\" nicht gefunden\n", menu->fehlerEingabe);
    menu->fehlerEingabe[0] = 0;
    //Eingabe
    clearInputbuffer();
    ergebnis = fgets(eingabe, MAX_TRIGGER_LAENGE+1, stdin);
    char *ptr = strchr(eingabe, '\n');
    if(ptr) *ptr = 0;
    if (!ergebnis) {
        fprintf(stderr, "Fehler bei der Eingabe: Eingabe leer\n");
        return;
    }
    while (temp) {
        menuEintrag = *(t_menuEintrag *) (temp->inhalt);
        if (strcmp(eingabe, menuEintrag.trigger) == 0) {
            if (menuEintrag.funktion) {
                CLEAR_CONSOLE;
                menuEintrag.funktion(menu);
            }
            if (menuEintrag.untermenu) {
                CLEAR_CONSOLE;
                up_menu_Anzeigen(menuEintrag.untermenu);
                return;
            } else {
                return;
            }
        }
        temp = temp->danach;
    }
    strcpy(menu->fehlerEingabe, eingabe);
    up_menu_Anzeigen(menu);
}


void
up_menu_EingabeString(t_menu *menu, char *eingabe, char *eingabeBeschreibung, int(*pruefeGueltigkeit)(t_menu *, char *),
                      char *fehlermeldung) {
    FILE *ergebnis;
    char puffer[STRINGLAENGE + 1];
    do {
        clearInputbuffer();
        printf("%s", eingabeBeschreibung);
        ergebnis = fgets(puffer, STRINGLAENGE, stdin);
        *strchr(puffer, '\n') = 0;
        if (!ergebnis) {
            fprintf(stderr, "Fehler bei der Eingabe: Eingabe leer\n");
        } else if (!pruefeGueltigkeit(menu, puffer)) {
            fprintf(stderr, "%s\n", fehlermeldung);
            ergebnis = 0;
        }
    } while (!ergebnis);
    strcpy(eingabe, puffer);
}

int up_menu_pruefeLoeschSyntax(t_menu *menu, char *eingabe) {
    if(strlen(eingabe) == 0){
        fprintf(stderr,"Eingabe leer: ");
        return 0;
    }
    char *eingabeKopie;
    strcpy(eingabeKopie, eingabe);
    char *ptr = strtok(eingabeKopie, ",");
    int i = 0, c = 0;
    char getrennt[STRINGLAENGE][STRINGLAENGE];
    while (ptr) {
        strcpy(getrennt[c], ptr);
        ptr = strtok(NULL, ",");
        c++;
    }
    int loeschbereiche;
    for (i = 0; i < c; i++) {
        ptr = strtok(getrennt[i], "-");
        while (ptr) {
            if (sscanf(ptr, "%d", &loeschbereiche) == 0) {
                return 0;
            }
            if (loeschbereiche < 0 || loeschbereiche >= menu->buecherListe->anzahlElemente) {
                fprintf(stderr, "Index %d ist nicht in der Liste: ", loeschbereiche);
                return 0;
            }
            ptr = strtok(NULL, "-");
        }
    }
    return 1;
}
