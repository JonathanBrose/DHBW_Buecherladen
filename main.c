#include "main.h"


int main() {
    t_menu *menu = up_menu_erzeugeMenu(up_buch_erzeugeBuecherListe());
    up_erstelleTestBuecher(menu->buecherListe);
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
