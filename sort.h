int up_vergleicheBuchPreis(t_vL_element *buch1, t_vL_element *buch2);

int up_vergleicheBuchTitel(t_vL_element *buch1, t_vL_element *buch2);

void up_verkListe_sort(t_ListVerwaltung *f, int(*vergleiche)(t_vL_element*, t_vL_element*));