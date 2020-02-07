#include "zeug.h"
typedef struct m_menu{
    t_verkListe *menuEintraege;
    t_verkListe *buecherListe;
}t_menu;
typedef struct m_menuEintrag{
   char* titel;
   char* trigger;
   void(*funktion)(t_verkListe *);

};
