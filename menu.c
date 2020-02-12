#include "main.h"

t_menu *up_menu_erzeugeMenu(t_verkListe *buecherListe, char *titel) {
    t_menu *menu = (t_menu *) malloc(sizeof(t_menu));
    t_verkListe *menuEintraege = up_verkListe_erzeugeListe();
    menu->buecherListe = buecherListe;
    menu->titel = (char *) malloc((strlen(titel)) * sizeof(char));
    strcpy(menu->titel, titel);
    menu->menuEintraege = menuEintraege;
    menu->fehlerEingabe[0] = 0;
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
    menuEintrag->titel = titel;
    menuEintrag->trigger = (char *) malloc(strlen(trigger) * sizeof(char));
    strcpy(menuEintrag->trigger, trigger);
    menuEintrag->untermenu = unterMenu;
    menuEintrag->funktion = funktion;
    up_verkListe_hinzufuegen(menu->menuEintraege, menuEintrag);
}

void up_menu_DateiEintrag(t_menu *menu) {

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
    ergebnis = fgets(eingabe, MAX_TRIGGER_LAENGE, stdin);
    *strchr(eingabe, '\n') = 0;
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

int up_ueberpruefeDateipfad(char *dateipfad) {
    FILE *datei = fopen(dateipfad, "r");
    if (!datei)return 0;
    fclose(datei);
    return 1;
}

int up_ueberpruefeDateipfadErweitert(char *dateipfad) {
    if (!up_ueberpruefeDateipfad(dateipfad)) {
        if (up_EingabeWeiter("Datei existiert nicht, wollen sie diese anlegen?")) {
            char *befehl;
            sprintf(befehl, "%s %s", CREATE_FILE, dateipfad);
            system(befehl);
        } else {
            return 0;
        }
    }
    return 1;
}

void up_menu_ueberpruefeDateipfadVorhanden(t_menu *menu) {
    if (!up_ueberpruefeDateipfad(menu->dateipfad)) {
        up_EingabeString(menu->dateipfad, "Bitte geben sie den Dateipfad ein...\n", up_ueberpruefeDateipfadErweitert,
                         "");
    }
}




