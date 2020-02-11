#define MAX_TRIGGER_LAENGE 4

typedef struct m_menu {
    t_verkListe *menuEintraege;
    t_verkListe *buecherListe;
    char *dateipfad;
    char *titel;
} t_menu;

typedef struct m_menuEintrag {
    char *titel;
    char *trigger;
    t_menu *untermenu;
    void(*funktion)(t_menu *);
} t_menuEintrag;

void
up_menu_EintragHinzufuegen(t_menu *menu, char *titel, char *trigger, t_menu *unterMenu, void(*funktion)(t_menu *));

t_menu* up_menu_erzeugeMenu(t_verkListe *buecherListe, char *titel);

t_menu* up_menu_erzeugeUnterMenu(t_menu *menu, char *titel);

void up_menu_Auswahl(t_menu *menu);

void up_menu_Anzeigen(t_menu *menu);

void up_menu_ueberpruefeDateipfadVorhanden(t_menu *menu);

int up_ueberpruefeDateipfadErweitert(char *dateipfad);

int up_ueberpruefeDateipfad(char *dateipfad);

void up_dateiSpeichernUnter(t_menu *menu);
