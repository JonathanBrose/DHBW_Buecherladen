typedef struct m_verkListe {
    void *inhalt;
    struct m_verkListe *davor, *danach;
} t_vL_element;
typedef struct{
    t_vL_element *start, *ende;
    int anzahlElemente;
}t_verkListe;
int up_verkListe_AnzahlElemente(t_vL_element *liste);
