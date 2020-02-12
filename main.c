#include "main.h"


int main() {
    //Hauptmenu
    t_menu *menu = up_menu_erzeugeMenu(up_buch_erzeugeBuecherListe(), "Buecherdatenbank der DHBW");
    up_erstelleTestBuecher(menu->buecherListe);
    up_menu_EintragHinzufuegen(menu, "Datei einlesen", "o", menu, up_dateiEinlesen);
    up_menu_EintragHinzufuegen(menu, "Datei einlesen von...", "ov", menu, up_dateiEinlesenVon);
    up_menu_EintragHinzufuegen(menu, "Datei speichern", "s", menu, up_dateiSpeichern);
    up_menu_EintragHinzufuegen(menu, "Datei speichern unter...", "su", menu, up_dateiSpeichernUnter);
    //Datensatzmenu
    t_menu *datensatzMenu = up_menu_erzeugeUnterMenu(menu, "Datensatz einsehen");
    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz ausgeben", "a", datensatzMenu, up_BuecherAnzeigen);
    //Sortiermenu
    t_menu *sortiermenu = up_menu_erzeugeUnterMenu(datensatzMenu, "Datensatz sortieren");
    up_menu_EintragHinzufuegen(sortiermenu, "Sortieren nach Titel", "t", datensatzMenu, up_datensatzSortieren_Titel);
    up_menu_EintragHinzufuegen(sortiermenu, NULL, "-t", datensatzMenu, up_datensatzSortieren_TitelAbsteigend);
    up_menu_EintragHinzufuegen(sortiermenu, "Sortieren nach Autor", "a", datensatzMenu, up_datensatzSortieren_Autor);
    up_menu_EintragHinzufuegen(sortiermenu, NULL, "-a", datensatzMenu, up_datensatzSortieren_AutorAbsteigend);
    up_menu_EintragHinzufuegen(sortiermenu, "Sortieren nach Verlag", "v", datensatzMenu, up_datensatzSortieren_Verlag);
    up_menu_EintragHinzufuegen(sortiermenu, NULL, "-v", datensatzMenu, up_datensatzSortieren_VerlagAbsteigend);
    up_menu_EintragHinzufuegen(sortiermenu, "Sortieren nach Preis", "p", datensatzMenu, up_datensatzSortieren_Preis);
    up_menu_EintragHinzufuegen(sortiermenu, NULL, "-p", datensatzMenu, up_datensatzSortieren_PreisAbsteigend);
    up_menu_EintragHinzufuegen(sortiermenu, " ", "", sortiermenu, up_void);
    up_menu_EintragHinzufuegen(sortiermenu, " [<= zurueck] ", "z", sortiermenu, NULL);
    up_menu_EintragHinzufuegen(sortiermenu, "#Anmerkung: Um absteigend zu sortieren, ein \"-\" vor die Eingabe stellen",
                               "#", sortiermenu, NULL);
    //Bearbeitungsmenu
    t_menu *bearbeitungsmenu = up_menu_erzeugeUnterMenu(datensatzMenu, "Datensatz bearbeiten");
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensatz hinzufuegen", "h", bearbeitungsmenu,
                               up_datensatzHinzufuegen);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze loeschen", "d", bearbeitungsmenu, up_datensaetzeLoeschen);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Doppelte Datensaetze loeschen", "dd", bearbeitungsmenu, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze kopieren", "c", bearbeitungsmenu, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze bearbeiten", "e", bearbeitungsmenu, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze kopieren & bearbeiten", "ce", bearbeitungsmenu, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensatz betrachten", "a", datensatzMenu, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "  ", "", bearbeitungsmenu, up_void);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, " [<= zurueck] ", "z", menu, NULL);

    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz durchsuchen", "ds", datensatzMenu, NULL);
    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz sortieren", "s", sortiermenu, NULL);
    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz bearbeiten", "b", bearbeitungsmenu, NULL);
    up_menu_EintragHinzufuegen(datensatzMenu, "  ", "", datensatzMenu, up_void);
    up_menu_EintragHinzufuegen(datensatzMenu, " [<= zurueck] ", "z", menu, NULL);
    up_menu_EintragHinzufuegen(menu, "Datensatz betrachten", "a", datensatzMenu, NULL);
    up_menu_EintragHinzufuegen(menu, "Datensatz bearbeiten", "b", bearbeitungsmenu, NULL);

    up_menu_EintragHinzufuegen(menu, "  ", "", menu, up_void);
    up_menu_EintragHinzufuegen(menu, "Programm beenden", "z", NULL, NULL);
    up_menu_DateiEintrag(menu);
    up_menu_Anzeigen(menu);
    return 0;
}

void up_erstelleTestBuecher(t_verkListe *buecherListe) {
    t_Buch buch1 = {"Herr der Ringe", "J.R.R. Tolkien", "Klett-verlag", 31.99};
    up_buch_BuchHinzufuegen(buecherListe, buch1);
    t_Buch buch2 = {"Spiegel", "Dummkopf", "Luegenpresse", 4.99};
    up_buch_BuchHinzufuegen(buecherListe, buch2);
    t_Buch buch3 = {"Bibel", "Gott", "Himmel", 99.99};
    up_buch_BuchHinzufuegen(buecherListe, buch3);
    t_Buch buch4 = {"Die Tragoedie Faust", "Johann Wolfgang von Goethe", "Goethe Print", 12.50};
    up_buch_BuchHinzufuegen(buecherListe, buch4);
    t_Buch buch5 = {"Mein Kampf", "Adolf Hitler", "Fuehrerprint", 2.30};
    up_buch_BuchHinzufuegen(buecherListe, buch5);
}

void up_dateiEinlesen(t_menu *menu) {
    up_menu_ueberpruefeDateipfadVorhanden(menu);
    up_dateien_Einlesen(menu->dateipfad, menu->buecherListe);
}

void up_dateiEinlesenVon(t_menu *menu) {
    strcpy(menu->dateipfad, "");
    up_dateiEinlesen(menu);
}

void up_dateiSpeichern(t_menu *menu) {
    up_menu_ueberpruefeDateipfadVorhanden(menu);
    up_dateien_Speichern(menu->dateipfad, menu->buecherListe);
}

void up_dateiSpeichernUnter(t_menu *menu) {
    strcpy(menu->dateipfad, "");
    up_dateiSpeichern(menu);
}

void up_BuecherAnzeigen(t_menu *menu) {
    up_buch_BuecherAnzeigen(menu->buecherListe, "");
    up_warte();
}

void up_void(t_menu *menu) {}

void up_datensatzSortieren_Titel(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheTitel, 0);
    printf("Datensatz sortiert...\n");
    up_BuecherAnzeigen(menu);
}

void up_datensatzSortieren_TitelAbsteigend(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheTitel, 1);
    printf("Datensatz sortiert...\n");
    up_BuecherAnzeigen(menu);
}

void up_datensatzSortieren_Autor(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheAutor, 0);
    printf("Datensatz sortiert...\n");
    up_BuecherAnzeigen(menu);
}

void up_datensatzSortieren_AutorAbsteigend(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheAutor, 1);
    printf("Datensatz sortiert...\n");
    up_BuecherAnzeigen(menu);
}

void up_datensatzSortieren_Verlag(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheVerlag, 0);
    printf("Datensatz sortiert...");
    up_BuecherAnzeigen(menu);
}

void up_datensatzSortieren_VerlagAbsteigend(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheVerlag, 1);
    printf("Datensatz sortiert...\n");
    up_BuecherAnzeigen(menu);
}

void up_datensatzSortieren_Preis(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleichePreis, 0);
    printf("Datensatz sortiert...\n");
    up_BuecherAnzeigen(menu);
}

void up_datensatzSortieren_PreisAbsteigend(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleichePreis, 1);
    printf("Datensatz sortiert...\n");
    up_BuecherAnzeigen(menu);
}

void up_datensatzHinzufuegen(t_menu *menu) {
    t_Buch buch;
    char puffer[STRINGLAENGE];
    up_EingabeString(buch.titel, "Bitte geben sie den Namen des Buches ein: ", up_pruefeStringLaenge,
                     "Eingabe zu kurz");
    sprintf(puffer, "Autor von \"%s\": ", buch.titel);
    up_EingabeString(buch.autor, puffer, up_pruefeStringLaenge, "Eingabe zu kurz");
    sprintf(puffer, "Verlag von \"%s\": ", buch.titel);
    up_EingabeString(buch.verlag, puffer, up_pruefeStringLaenge, "Eingabe zu kurz");
    sprintf(puffer, "Preis von \"%s\": ", buch.titel);
    up_EingabeFloat(&buch.preis, puffer);
    up_buch_BuchHinzufuegen(menu->buecherListe, buch);
    if (up_EingabeWeiter("Weiteren Datensatz eingeben?\n")) up_datensatzHinzufuegen(menu);
}

void up_datensaetzeLoeschen(t_menu *menu) {
    char eingabe[STRINGLAENGE];
    int i = 0, j = 0, c = 0;
    char getrennt[STRINGLAENGE][STRINGLAENGE];
    up_EingabeString(eingabe,
                     "Bitte geben sie die zu loeschenden Indizes ein...\nDiese werden in der Form \"1-3,4,7-8,...\" eingegeben\n",
                     up_pruefeLoeschSyntax, "Eingabe ungueltig!");
    char *ptr = strtok(eingabe, ",");
    while (ptr) {
        strcpy(getrennt[c], ptr);
        ptr = strtok(NULL, ",");
        c++;
    }
    int loeschbereiche[c * 2];
    for (i = 0; i < c; i++) {
        j = 0;
        ptr = strtok(getrennt[i], "-");
        while (ptr) {
            sscanf(ptr, "%d", &loeschbereiche[i*2 + j]);
            ptr = strtok(NULL, "-");
            j++;
        }
        if (j == 1) {
            loeschbereiche[i*2 + j] = 0;
        } else {
            loeschbereiche[i*2 + 1] -= loeschbereiche[i*2];
        }
    }
    //loeschen
    for (i = 0; i < c * 2; i += 2) {
        if (i > 0) {
            if (loeschbereiche[i] == loeschbereiche[i - 2]) {
                loeschbereiche[i + 1] = loeschbereiche[i - 1];
                continue;
            } else if (loeschbereiche[i] > loeschbereiche[i - 2]) {
                if (loeschbereiche[i - 1] < 0)
                    loeschbereiche[i - 1] *= -1;
                loeschbereiche[i] -= loeschbereiche[i-1]-1;
            }
        }
        if (up_verkListeIndex(menu->buecherListe, loeschbereiche[i])) {
            up_verkListe_ElementeLoeschen(menu->buecherListe, up_verkListeIndex(menu->buecherListe, loeschbereiche[i]),
                                          loeschbereiche[i + 1]);
        } else {
            fprintf(stderr, "Index %d nicht in der Liste!\n", loeschbereiche[i]);
        }
    }
    printf("Eintraege geloescht...\n");
    up_warte();
}

void up_doppelteDatensaetzeLoeschen(t_menu *menu) {

}

void up_datensaetzeKopieren(t_menu *menu);

void up_datensaetzeBearbeiten(t_menu *menu);

void up_datensaetzeKopierenBearbeiten(t_menu *menu);

void up_datensatzDurchsuchen(t_menu *menu);
