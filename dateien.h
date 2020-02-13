
void up_dateien_Einlesen(char *dateiPfad, t_verkListe *liste);

void up_dateien_zeileSchreiben(FILE *datei, int anzahlElemente, const char *typen, ...);

void up_dateien_Speichern(char *dateiPfad, t_verkListe *liste);

void up_ueberpruefeDateipfadVorhanden(t_menu *menu, char modus);

int up_dateien_zeileLesen(FILE *datei, t_Buch *buch);

int up_ueberpruefeDateipfadErweitert(char *dateipfad);

int up_ueberpruefeDateipfad(char *dateipfad);
