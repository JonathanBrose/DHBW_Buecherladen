#include "main.h"


int main() {
    //Hauptmenu
    t_menu *menu = up_menu_erzeugeMenu(up_buch_erzeugeBuecherListe(), "Buecherdatenbank der DHBW");
    up_menu_DateiEintrag(menu);
    up_menu_EintragHinzufuegen(menu, "  ", "", menu, up_void);
    up_menu_EintragHinzufuegen(menu, "Datei einlesen", "o", menu, up_dateiEinlesen);
    up_menu_EintragHinzufuegen(menu, "Datei einlesen von...", "ov", menu, up_dateiEinlesenVon);
    up_menu_EintragHinzufuegen(menu, "Datei speichern", "s", menu, up_dateiSpeichern);
    up_menu_EintragHinzufuegen(menu, "Datei speichern unter...", "su", menu, up_dateiSpeichernUnter);
    //Datensatzmenu
    t_menu *datensatzMenu = up_menu_erzeugeUnterMenu(menu, "Datensatz einsehen");
    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz ausgeben", "a", datensatzMenu, up_buecherAnzeigen);
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
    up_menu_EintragHinzufuegen(sortiermenu, "Anmerkung: Um absteigend zu sortieren, ein \"-\" vor die Eingabe stellen",
                               "#", sortiermenu, NULL);
    //Bearbeitungsmenu
    t_menu *bearbeitungsmenu = up_menu_erzeugeUnterMenu(datensatzMenu, "Datensatz bearbeiten");
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensatz hinzufuegen", "h", bearbeitungsmenu,
                               up_datensatzHinzufuegen);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze loeschen", "d", bearbeitungsmenu, up_datensaetzeLoeschen);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Alle Datensaetze loeschen", "da", bearbeitungsmenu,
                               up_alleDatensaetzeLoeschen);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze kopieren", "c", bearbeitungsmenu, up_datensaetzeKopieren);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze bearbeiten", "e", bearbeitungsmenu,
                               up_datensaetzeBearbeiten);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensatz betrachten", "a", datensatzMenu, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "  ", "", bearbeitungsmenu, up_void);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, " [<= zurueck] ", "z", menu, NULL);

    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz durchsuchen", "q", datensatzMenu, up_datensatzDurchsuchen);
    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz sortieren", "s", sortiermenu, NULL);
    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz bearbeiten", "b", bearbeitungsmenu, NULL);
    up_menu_EintragHinzufuegen(datensatzMenu, "ListenZeiger ausgeben (up_hex)", "x", datensatzMenu, up_listenZeigerAnzeigen);
    up_menu_EintragHinzufuegen(datensatzMenu, "  ", "", datensatzMenu, up_void);
    up_menu_EintragHinzufuegen(datensatzMenu, " [<= zurueck] ", "z", menu, NULL);
    up_menu_EintragHinzufuegen(menu, "Datensatz betrachten", "a", datensatzMenu, NULL);
    up_menu_EintragHinzufuegen(menu, "Datensatz bearbeiten", "b", bearbeitungsmenu, NULL);

    up_menu_EintragHinzufuegen(menu, "  ", "", menu, up_void);
    up_menu_EintragHinzufuegen(menu, "[<= Programm beenden]", "z", NULL, NULL);
    up_menu_Anzeigen(menu);
    return 0;
}

void up_listenZeigerAnzeigen(t_menu *menu){
    up_verkList_ListenZeigerAnzeigen(menu->buecherListe, AUSGABEZEILEN, -1);
    up_warte();
}
void up_dateiEinlesen(t_menu *menu) {
    up_ueberpruefeDateipfadVorhanden(menu, 'r');
    if (menu->buecherListe->anzahlElemente) {
        if (up_EingabeWeiter(
                "Datensatz ueberschreiben?\nAnsonsten wird der neue Datensatz an den alten angehaengt\n")) {
            up_verkListe_Loeschen(menu->buecherListe);
        }
    }
    up_dateien_Einlesen(menu->dateipfad, menu->buecherListe);
    up_warte();
}

void up_dateiEinlesenVon(t_menu *menu) {
    strcpy(menu->dateipfad, "");
    up_dateiEinlesen(menu);
}

void up_dateiSpeichern(t_menu *menu) {
    up_ueberpruefeDateipfadVorhanden(menu, 'w');
    up_dateien_Speichern(menu->dateipfad, menu->buecherListe);
    up_warte();
}

void up_dateiSpeichernUnter(t_menu *menu) {
    strcpy(menu->dateipfad, "");
    up_dateiSpeichern(menu);
}

void up_buecherAnzeigen(t_menu *menu) {
    up_buch_BuecherAnzeigen(menu->buecherListe, "", AUSGABEZEILEN, -1);
    up_warte();
}

void up_void(t_menu *menu) {}

void up_datensatzSortieren_Titel(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheTitel, 0);
    printf("Datensatz sortiert...\n");
}

void up_datensatzSortieren_TitelAbsteigend(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheTitel, 1);
    printf("Datensatz sortiert...\n");
}

void up_datensatzSortieren_Autor(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheAutor, 0);
    printf("Datensatz sortiert...\n");
}

void up_datensatzSortieren_AutorAbsteigend(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheAutor, 1);
    printf("Datensatz sortiert...\n");
}

void up_datensatzSortieren_Verlag(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheVerlag, 0);
    printf("Datensatz sortiert...");
}

void up_datensatzSortieren_VerlagAbsteigend(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleicheVerlag, 1);
    printf("Datensatz sortiert...\n");
}

void up_datensatzSortieren_Preis(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleichePreis, 0);
    printf("Datensatz sortiert...\n");
}

void up_datensatzSortieren_PreisAbsteigend(t_menu *menu) {
    up_verkListe_sort(menu->buecherListe, up_buch_vergleichePreis, 1);
    printf("Datensatz sortiert...\n");
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
    char eingabe[STRINGLAENGE], getrenntNachKomma[STRINGLAENGE][STRINGLAENGE];
    int bereichsIndex = 0, j = 0, anzahlBereiche = 0;
    up_menu_EingabeString(menu, eingabe,
                          "Bitte geben sie die zu loeschenden Indizes ein...\nDiese werden in der Form \"1-3,4,7-8,...\" eingegeben\n",
                          up_menu_pruefeLoeschSyntax, "Eingabe ungueltig!\n");
    char *ptr = strtok(eingabe, ",");
    while (ptr) {
        strcpy(getrenntNachKomma[anzahlBereiche], ptr);
        ptr = strtok(NULL, ",");
        anzahlBereiche++;
    }
    //loeschBereiche von Eingabe in int Array speichern...
    //Immer zwei folgende Eintraege gehoeren zusammen
    int loeschBereiche[anzahlBereiche * 2];
    for (bereichsIndex = 0; bereichsIndex < anzahlBereiche; bereichsIndex++) {
        j = 0;
        ptr = strtok(getrenntNachKomma[bereichsIndex], "-");
        while (ptr) {
            sscanf(ptr, "%d", &loeschBereiche[bereichsIndex * 2 + j]);
            ptr = strtok(NULL, "-");
            j++;
        }
        if (j == 1) {
            loeschBereiche[bereichsIndex * 2 + 1] = loeschBereiche[bereichsIndex * 2];
        } else if (j == 2) {
            if (loeschBereiche[bereichsIndex * 2 + 1] < loeschBereiche[bereichsIndex * 2]) {
                int temp = loeschBereiche[bereichsIndex * 2];
                loeschBereiche[bereichsIndex * 2] = loeschBereiche[bereichsIndex * 2 + 1];
                loeschBereiche[bereichsIndex * 2 + 1] = temp;
            }
        }
    }
    //loeschen
    for (bereichsIndex = 0; bereichsIndex < anzahlBereiche * 2; bereichsIndex += 2) {
        if (bereichsIndex + 2 < anzahlBereiche * 2) {
            if (loeschBereiche[bereichsIndex] <= loeschBereiche[bereichsIndex + 2]) {

                if (loeschBereiche[bereichsIndex + 1] + 1 >= loeschBereiche[bereichsIndex + 2]) {
                    //Bereich 2 faengt im aktuellen Bereich an, oder beruehrt ihn..
                    if (loeschBereiche[bereichsIndex + 1] > loeschBereiche[bereichsIndex + 3]) {
                        //Bereich inkludiert naechsten Bereich
                        loeschBereiche[bereichsIndex + 3] = loeschBereiche[bereichsIndex + 1];
                    }
                    //Bereiche werden vereinigt...
                    loeschBereiche[bereichsIndex + 2] = loeschBereiche[bereichsIndex];
                    continue;
                } else {
                    //naechster Bereich beginnt nach aktuellem Bereich
                    //Indizes werden verschoben, da loeschung die indizes aendert.
                    loeschBereiche[bereichsIndex + 2] -= loeschBereiche[bereichsIndex + 1] - loeschBereiche[bereichsIndex] + 1;
                    loeschBereiche[bereichsIndex + 3] -= loeschBereiche[bereichsIndex + 1] - loeschBereiche[bereichsIndex] + 1;
                }
            }else {
                if (loeschBereiche[bereichsIndex + 3] < loeschBereiche[bereichsIndex] - 1) {
                    //naechster Bereich liegt vor aktuellem
                } else if (loeschBereiche[bereichsIndex + 3] > loeschBereiche[bereichsIndex + 1]) {
                    //naechster Bereich inkludiert aktuellen
                    continue;
                } else {
                    //Bereiche verschraenkt
                    loeschBereiche[bereichsIndex + 3] = loeschBereiche[bereichsIndex + 1];
                    continue;
                }
            }
        }
        if (up_verkListeIndex(menu->buecherListe, loeschBereiche[bereichsIndex])) {
            up_verkListe_ElementeLoeschen(menu->buecherListe, up_verkListeIndex(menu->buecherListe, loeschBereiche[bereichsIndex]),
                                          loeschBereiche[bereichsIndex + 1] - loeschBereiche[bereichsIndex]);
        } else {
            fprintf(stderr, "Index %d nicht in der Liste!\n", loeschBereiche[bereichsIndex]);
        }
    }
    printf("Eintraege geloescht...\n");
    up_warte();
}

void up_alleDatensaetzeLoeschen(t_menu *menu) {
    up_verkListe_Loeschen(menu->buecherListe);
    printf("Alle Datensaetze geloescht\n");
    up_warte();
}

void up_datensaetzeKopieren(t_menu *menu) {
    char eingabe[STRINGLAENGE], getrenntNachKomma[STRINGLAENGE][STRINGLAENGE];
    int bereichsIndex = 0, j = 0, bereichsAnzahl = 0;
    up_menu_EingabeString(menu, eingabe,
                          "Bitte geben sie die zu klonenden Indizes ein...\nDiese werden in der Form \"1-3,4,7-8,...\" eingegeben\n",
                          up_menu_pruefeLoeschSyntax, "Eingabe ungueltig!\n");
    char *ptr = strtok(eingabe, ",");
    while (ptr) {
        strcpy(getrenntNachKomma[bereichsAnzahl], ptr);
        ptr = strtok(NULL, ",");
        bereichsAnzahl++;
    }
    //Kopierbereiche von Eingabe in int Array speichern...
    //Immer zwei folgende Eintraege gehoeren zusammen
    int klonBereiche[bereichsAnzahl * 2];
    for (bereichsIndex = 0; bereichsIndex < bereichsAnzahl; bereichsIndex++) {
        j = 0;
        ptr = strtok(getrenntNachKomma[bereichsIndex], "-");
        while (ptr) {
            sscanf(ptr, "%d", &klonBereiche[bereichsIndex * 2 + j]);
            ptr = strtok(NULL, "-");
            j++;
        }
        if (j == 1) {
            klonBereiche[bereichsIndex * 2 + 1] = klonBereiche[bereichsIndex * 2];
        } else if (j == 2) {
            if (klonBereiche[bereichsIndex * 2 + 1] < klonBereiche[bereichsIndex * 2]) {
                int temp = klonBereiche[bereichsIndex * 2];
                klonBereiche[bereichsIndex * 2] = klonBereiche[bereichsIndex * 2 + 1];
                klonBereiche[bereichsIndex * 2 + 1] = temp;
            }
        }
    }
    for (bereichsIndex = 0; bereichsIndex < bereichsAnzahl * 2; bereichsIndex += 2) {
        if (bereichsIndex + 2 < bereichsAnzahl * 2) {
            if (klonBereiche[bereichsIndex] <= klonBereiche[bereichsIndex + 2]) {

                if (klonBereiche[bereichsIndex + 1] + 1 >= klonBereiche[bereichsIndex + 2]) {
                    //Bereich 2 faengt im aktuellen Bereich an, oder beruehrt ihn..
                    if (klonBereiche[bereichsIndex + 1] > klonBereiche[bereichsIndex + 3]) {
                        //Bereich inkludiert naechsten Bereich
                        klonBereiche[bereichsIndex + 3] = klonBereiche[bereichsIndex + 1];
                    }
                    //Bereiche werden vereinigt...
                    klonBereiche[bereichsIndex + 2] = klonBereiche[bereichsIndex];
                    continue;
                } else {
                    //naechster Bereich beginnt nach aktuellem Bereich
                    //Indizes werden verschoben, da das einfuegen der Klone die Indizes aendert.
                    klonBereiche[bereichsIndex + 2] += klonBereiche[bereichsIndex + 1] - klonBereiche[bereichsIndex] + 1;
                    klonBereiche[bereichsIndex + 3] += klonBereiche[bereichsIndex + 1] - klonBereiche[bereichsIndex] + 1;
                }
            }else {
                if (klonBereiche[bereichsIndex + 3] < klonBereiche[bereichsIndex] - 1) {
                    //naechster Bereich liegt vor aktuellem
                } else if (klonBereiche[bereichsIndex + 3] > klonBereiche[bereichsIndex + 1]) {
                    //naechster Bereich inkludiert aktuellen
                    continue;
                } else {
                    //Bereiche verschraenkt
                    klonBereiche[bereichsIndex + 3] = klonBereiche[bereichsIndex + 1];
                    continue;
                }
            }
        }
        if (up_verkListeIndex(menu->buecherListe, klonBereiche[bereichsIndex])) {
            up_verkListe_dupliziere(menu->buecherListe, up_verkListeIndex(menu->buecherListe, klonBereiche[bereichsIndex]),
                                    klonBereiche[bereichsIndex + 1] - klonBereiche[bereichsIndex]);
        } else {
            fprintf(stderr, "Index %d nicht in der Liste!\n", klonBereiche[bereichsIndex]);
        }
    }
    printf("Klone erstellt...\n");
    up_warte();
}

void up_preisBearbeiten(t_menu *menu) {
    up_buch_BuecherAnzeigen(menu->buecherListe, "", 0, menu->index);
    up_EingabeFloat(&((t_Buch *) up_verkListeIndex(menu->buecherListe, menu->index)->inhalt)->preis,
                    "Bitte geben sie den neuen Preis ein\n");
    CLEAR_CONSOLE;
    up_buch_BuecherAnzeigen(menu->buecherListe, "", 0, menu->index);
    up_warte();
}

void up_verlagBearbeiten(t_menu *menu) {
    up_buch_BuecherAnzeigen(menu->buecherListe, "", 0, menu->index);
    up_EingabeString(((t_Buch *) up_verkListeIndex(menu->buecherListe, menu->index)->inhalt)->verlag,
                     "Bitte geben sie den neuen Verlag ein\n", up_pruefeStringLaenge,
                     "Eingabe fehlerhaft: String zu kurz");
    CLEAR_CONSOLE;
    up_buch_BuecherAnzeigen(menu->buecherListe, "", 0, menu->index);
    up_warte();
}

void up_autorBearbeiten(t_menu *menu) {
    up_buch_BuecherAnzeigen(menu->buecherListe, "", 0, menu->index);
    up_EingabeString(((t_Buch *) up_verkListeIndex(menu->buecherListe, menu->index)->inhalt)->autor,
                     "Bitte geben sie den neuen Autor ein\n", up_pruefeStringLaenge,
                     "Eingabe fehlerhaft: String zu kurz");
    CLEAR_CONSOLE;
    up_buch_BuecherAnzeigen(menu->buecherListe, "", 0, menu->index);
    up_warte();
}

void up_titelBearbeiten(t_menu *menu) {
    up_buch_BuecherAnzeigen(menu->buecherListe, "", 0, menu->index);
    up_EingabeString(((t_Buch *) up_verkListeIndex(menu->buecherListe, menu->index)->inhalt)->titel,
                     "Bitte geben sie den neuen Titel ein\n", up_pruefeStringLaenge,
                     "Eingabe fehlerhaft: String zu kurz");
    CLEAR_CONSOLE;
    up_buch_BuecherAnzeigen(menu->buecherListe, "", 0, menu->index);
    up_warte();
}

void up_datensaetzeBearbeiten(t_menu *menu) {
    char eingabe[STRINGLAENGE], titel[STRINGLAENGE];
    up_menu_EingabeString(menu, eingabe, "Bitte zu bearbeitenden Index eingeben: ", up_ueberpruefeIndexEingabe,
                          "eingabe keine ganzzahl, oder index nicht in liste\n");
    sscanf(eingabe, "%d", &menu->index);
    t_Buch *buch = (t_Buch *) (up_verkListeIndex(menu->buecherListe, menu->index)->inhalt);
    sprintf(titel, "Bearbeiten von Datensatz nr.%d", menu->index);
    t_menu *bearbeitungsmenu = up_menu_erzeugeMenu(menu->buecherListe, titel);
    bearbeitungsmenu->index = menu->index;
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "  ", "", bearbeitungsmenu, up_void);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, buch->titel, "Buch", bearbeitungsmenu, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "  ", "", bearbeitungsmenu, up_void);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Titel bearbeiten", "t", bearbeitungsmenu, up_titelBearbeiten);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Autor bearbeiten", "a", bearbeitungsmenu, up_autorBearbeiten);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Verlag bearbeiten", "v", bearbeitungsmenu, up_verlagBearbeiten);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Preis bearbeiten", "p", bearbeitungsmenu, up_preisBearbeiten);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "  ", "", bearbeitungsmenu, up_void);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, " [<= zurueck] ", "z", menu, NULL);
    up_menu_Anzeigen(bearbeitungsmenu);
}

void up_datensatzDurchsuchen(t_menu *menu) {
    char suchbegriff[STRINGLAENGE] = "", temp;
    int i = 0;
    do {
        CLEAR_CONSOLE;
        printf("um zu suchen suchtext tippen, enter um zurueck ins menu zu gehen\n\n");
        up_buch_BuecherAnzeigen(menu->buecherListe, suchbegriff, 0, -1);
        printf("\nsuche: %s", suchbegriff);
        temp = up_instant_getch();
        if (temp == 8) {
            i--;
            suchbegriff[i] = 0;
        } else if (temp == 13) {
            break;
        } else if (temp != 0) {
            suchbegriff[i] = temp;
            i++;
            suchbegriff[i] = 0;
        }
    } while (1);
    printf("\n");
}
