#include "main.h"

#define MAX_TRIGGER_LAENGE 4

typedef struct m_menu {
    t_verkListe *menuEintraege;
    t_verkListe *buecherListe;
} t_menu;
typedef struct m_menuEintrag {
    char *titel;
    char trigger[MAX_TRIGGER_LAENGE];
    t_menu *untermenu;

    void (*funktion)(t_verkListe *);
} t_menuEintrag;

void up_menu_Eintraghinzufuegen(t_menu *menu, char *titel, char *trigger, t_menu *unterMenu, void(*funktion)(t_verkListe *));

t_menu *up_menu_erzeugeMenu(t_verkListe *buecherListe);

void up_menu_Auswahl(t_menu *menu);

void up_menu_Anzeigen(t_menu *menu);
