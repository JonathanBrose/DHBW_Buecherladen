#include "main.h"


int main() {
    t_menu *menu = up_menu_erzeugeMenu(up_buch_erzeugeBuecherListe(),"Buecherdatenbank der DHBW");
    up_erstelleTestBuecher(menu->buecherListe);
    up_menu_EintragHinzufuegen(menu, "Datei einlesen", "o", NULL, up_dateiEinlesen);
    up_menu_EintragHinzufuegen(menu, "Datei einlesen von...", "ov", NULL, up_dateiEinlesen);
    up_menu_EintragHinzufuegen(menu, "Datei speichern", "s", NULL, up_dateiSpeichern);
    up_menu_EintragHinzufuegen(menu, "Datei speichern unter...", "su", NULL, up_dateiSpeichernUnter);
    //Datensatzmenu
    t_menu *datensatzMenu = up_menu_erzeugeUnterMenu(menu, "Datensatz einsehen");
    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz ausgeben", "a", NULL, up_BuecherAnzeigen);
    //Sortiermenu
    t_menu *sortiermenu = up_menu_erzeugeUnterMenu(datensatzMenu, "Datensatz sortieren");
    up_menu_EintragHinzufuegen(sortiermenu, "Sortieren nach Titel", "t", NULL, NULL);
    up_menu_EintragHinzufuegen(sortiermenu, NULL, "-t", NULL, NULL);
    up_menu_EintragHinzufuegen(sortiermenu, "Sortieren nach Autor", "a", NULL, NULL);
    up_menu_EintragHinzufuegen(sortiermenu, NULL, "-a", NULL, NULL);
    up_menu_EintragHinzufuegen(sortiermenu, "Sortieren nach Verlag", "v", NULL, NULL);
    up_menu_EintragHinzufuegen(sortiermenu, NULL, "-v", NULL, NULL);
    up_menu_EintragHinzufuegen(sortiermenu, "Sortieren nach Preis", "p", NULL, NULL);
    up_menu_EintragHinzufuegen(sortiermenu, NULL, "-p", NULL, NULL);
    up_menu_EintragHinzufuegen(sortiermenu, " ", "", NULL, up_void);
    up_menu_EintragHinzufuegen(sortiermenu, " [<= zurueck] ", "z", NULL, NULL);
    up_menu_EintragHinzufuegen(sortiermenu, "#Anmerkung: Um absteigend zu sortieren, ein \"-\" vor die Eingabe stellen", "#", NULL, NULL);
    //bearbeitungsmenu
    t_menu *bearbeitungsmenu = up_menu_erzeugeUnterMenu(datensatzMenu, "Datensatz bearbeiten");
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensatz hinzufuegen", "a", NULL, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze loeschen", "d", NULL, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Doppelte Datensaetze loeschen", "dd", NULL, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze kopieren", "c", NULL, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze bearbeiten", "e", NULL, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "Datensaetze kopieren & bearbeiten", "ce", NULL, NULL);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, "  ", "", NULL, up_void);
    up_menu_EintragHinzufuegen(bearbeitungsmenu, " [<= zurueck] ", "z", NULL, NULL);

    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz durchsuchen", "ds", NULL, NULL);
    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz sortieren", "s", sortiermenu, NULL);
    up_menu_EintragHinzufuegen(datensatzMenu, "  ", "", NULL, up_void);
    up_menu_EintragHinzufuegen(datensatzMenu, " [<= zurueck] ", "z", NULL, NULL);
    up_menu_EintragHinzufuegen(menu, "Datensatz betrachten", "d", datensatzMenu, NULL);
    up_menu_EintragHinzufuegen(menu, "Datensatz bearbeiten", "b", bearbeitungsmenu, NULL);

    up_menu_EintragHinzufuegen(menu, "  ", "", NULL, up_void);
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
}
void up_dateiEinlesen(t_menu *menu){
    up_menu_ueberpruefeDateipfadVorhanden(menu);
    up_dateien_Einlesen(menu->dateipfad, menu->buecherListe);
}
void up_dateiSpeichern(t_menu *menu){
    up_menu_ueberpruefeDateipfadVorhanden(menu);
    up_dateien_Speichern(menu->dateipfad, menu->buecherListe);
}
void up_dateiSpeichernUnter(t_menu *menu){
    strcpy(menu->dateipfad, "");
    up_dateiSpeichern(menu);
}
void up_BuecherAnzeigen(t_menu *menu){
    up_buch_BuecherAnzeigen(menu->buecherListe, "");
}
void up_void(t_menu *menu){

}
