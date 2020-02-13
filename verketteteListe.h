//Element der doppelt verketteten Liste
typedef struct m_verkListe {
    void *inhalt;
    struct m_verkListe *davor, *danach;
} t_vL_element;

//Verwaltungsobjekt der verketteten Liste
typedef struct {
    t_vL_element *start, *ende;
    int anzahlElemente;
} t_verkListe;

t_verkListe* up_verkListe_erzeugeListe(void);

void up_verkListe_elementEinfuegen(t_verkListe *liste, t_vL_element *vorgaenger, void *inhalt);

int up_buch_vergleichePreis(t_vL_element *buch1, t_vL_element *buch2);

int up_buch_vergleicheTitel(t_vL_element *buch1, t_vL_element *buch2);

void up_verkListe_sort(t_verkListe *liste, int(*vergleiche)(t_vL_element *, t_vL_element *), int absteigend);

void up_verkListe_ElementeLoeschen(t_verkListe *liste, t_vL_element *loeschBeginn, int zusatzAnzahl);

void up_verkListe_Loeschen(t_verkListe *liste);

void up_verkListe_ElementeVertauschen(t_verkListe *liste, t_vL_element *element1, t_vL_element *element2);

void up_verkListe_hinzufuegen(t_verkListe *liste, void *inhalt);

t_vL_element* up_verkListeInhalt(t_verkListe *liste, void *inhalt);

t_vL_element* up_verkListeIndex(t_verkListe *liste, int index);