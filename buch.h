typedef struct {
    char titel[STRINGLAENGE];
    char autor[STRINGLAENGE];
    char verlag[STRINGLAENGE];
    float preis;
} t_Buch;

int up_vergleicheStrings(char *s1, char *s2);

int up_buch_vergleichePreis(t_vL_element *buch1, t_vL_element *buch2);

int up_buch_vergleicheTitel(t_vL_element *buch1, t_vL_element *buch2);

int up_buch_vergleicheAutor(t_vL_element *buch1, t_vL_element *buch2);

int up_buch_vergleicheVerlag(t_vL_element *buch1, t_vL_element *buch2);

void up_buch_BuecherAnzeigen(t_verkListe *liste, char *suche, int ausgabezeilen);

t_Buch *up_buch_klonen(t_Buch buch);

t_verkListe *up_buch_erzeugeBuecherListe(void);

void up_buch_BuchHinzufuegen(t_verkListe *buecherListe, t_Buch buch);