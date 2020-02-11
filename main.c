#include "main.h"


int main() {
    t_menu *menu = up_menu_erzeugeMenu(up_buch_erzeugeBuecherListe(),"Bucherdatenbank der DHBW");
    up_erstelleTestBuecher(menu->buecherListe);
    up_menu_EintragHinzufuegen(menu, "Datei einlesen", "o", NULL, up_dateiEinlesen);
    up_menu_EintragHinzufuegen(menu, "Datei speichern", "s", NULL, up_dateiSpeichern);
    up_menu_EintragHinzufuegen(menu, "Datei speichern unter", "su", NULL, up_dateiSpeichernUnter);
    //Datensatzmenu
    t_menu *datensatzMenu = up_menu_erzeugeUnterMenu(menu, "Datensatz einsehen");
    up_menu_EintragHinzufuegen(datensatzMenu, "Datensatz ausgeben", "a", NULL, up_BuecherAnzeigen);
    up_menu_EintragHinzufuegen(datensatzMenu, "Zurück zum Hauptmenu", "z", NULL, NULL);
    up_menu_EintragHinzufuegen(menu, "Datensatz betrachten", "d", datensatzMenu, NULL);

    up_menu_EintragHinzufuegen(menu, "Programm beenden", "z", NULL, NULL);
    up_menu_Anzeigen(menu);
    return 0;
}

void up_erstelleTestBuecher(t_verkListe *buecherListe) {
    t_Buch buch1 = {"Herr der Ringe", "J.R.R. Tolkien", "Klett-verlag", 31.99};
    up_buch_BuchHinzufuegen(buecherListe, buch1);
    t_Buch buch2 = {"Spiegel", "Dummkopf", "Lügenpresse", 4.99};
    up_buch_BuchHinzufuegen(buecherListe, buch2);
    t_Buch buch3 = {"Bibel", "Gott", "Himmel", 99.99};
    up_buch_BuchHinzufuegen(buecherListe, buch3);
    t_Buch buch4 = {"Die Tragödie Faust", "Johann Wolfgang von Goethe", "Goethe Print", 12.50};
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
