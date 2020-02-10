#include "menu.h"

t_menu *up_menu_erzeugeMenu(t_verkListe *buecherListe) {
    t_menu menu;
    t_verkListe menuEintraege;
    menu.buecherListe = buecherListe;
    menu.menuEintraege = &menuEintraege;
    return &menu;
}

void up_menu_Eintraghinzufuegen(t_menu *menu, char *titel, char *trigger, t_menu *unterMenu,
                                void(*funktion)(t_verkListe *)) {
    t_menuEintrag menuEintrag;
    menuEintrag.titel = titel;
    char format[10];
    sprintf(format, "%s%d%s", "%", MAX_TRIGGER_LAENGE, "s");
    sprintf(menuEintrag.trigger, format, trigger);
    menuEintrag.funktion = funktion;
    up_verkListe_hinzufuegen(menu->menuEintraege, &menuEintrag);
}

void up_menu_Anzeigen(t_menu *menu) {
    CLEAR_CONSOLE;
    t_vL_element *temp = menu->menuEintraege->start;
    t_menuEintrag menuEintrag;
    char format[STRINGLAENGE], puffer[STRINGLAENGE];
    printf("\n");
    sprintf(format, "%s%d%s%d%s", "%", -(MAX_TRIGGER_LAENGE + 2), "s %", -STRINGLAENGE, "s\n");
    printf("*** %s ***\n", menu->titel);
    while (temp) {
        menuEintrag = *(t_menuEintrag *) (temp->inhalt);
        sprintf(puffer, "(%s)", menuEintrag.trigger);
        printf(format, puffer, menuEintrag.titel);
        temp = temp->danach;
    }
    printf("\n");
    up_menu_Auswahl(menu);
}

void up_menu_Auswahl(t_menu *menu) {
    t_vL_element *temp = menu->menuEintraege->start;
    t_menuEintrag menuEintrag;
    char eingabe[MAX_TRIGGER_LAENGE + 1];
    int ergebnis = 0;
    do {
        ergebnis = fgets(eingabe, MAX_TRIGGER_LAENGE, stdin);
        if (!ergebnis) {
            fprintf(stderr, "Fehler bei der Eingabe: Eingabe leer\n");
            continue;
        }
        while (temp) {
            menuEintrag = *(t_menuEintrag *) (temp->inhalt);
            if (strcmp(eingabe, menuEintrag.trigger)) {
                if (menuEintrag.untermenu) {
                    up_menu_Anzeigen(menuEintrag.untermenu);
                } else {
                    menuEintrag.funktion(menu->buecherListe);
                }
                return;
            }
            temp = temp->danach;
        }
        fprintf(stderr, "Fehler bei der Eingabe: Menupunkt %s nicht gefunden\n", eingabe);
    } while (!ergebnis);
}
int up_ueberpruefeDateipfad(char* dateipfad){
    FILE *datei = fopen(dateipfad, "r");
    if(!datei)return 0;
    fclose(datei);
    return 1;
}
void up_menu_ueberpruefeDateipfad(t_menu *menu) {
    if (!up_ueberpruefeDateipfad(menu->dateipfad)) {
       up_EingabeString(menu->dateipfad, "Bitte geben sie den Dateipfad ein...\n", up_ueberpruefeDateipfad, "Datei wurde nicht gefunden");
    }
}




