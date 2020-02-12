#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "verketteteListe.h"
#include "zeug.h"
#include "buch.h"
#include "menu.h"
#include "dateien.h"

#ifdef __linux__
#define CLEAR_CONSOLE system("clear")
#define CREATE_FILE "touch "
#endif
#ifdef _WIN32
#define CLEAR_CONSOLE system("cls")
#define CREATE_FILE "echo \"\" > "
#endif

void up_erstelleTestBuecher(t_verkListe *buecherListe);

void up_dateiSpeichern(t_menu *menu);
void up_dateiSpeichernUnter(t_menu *menu);

void up_BuecherAnzeigen(t_menu *menu);

void up_dateiEinlesen(t_menu *menu);
void up_dateiEinlesenVon(t_menu *menu);

void up_void(t_menu *menu);

void up_datensatzSortieren_Titel(t_menu *menu);
void up_datensatzSortieren_TitelAbsteigend(t_menu *menu);
void up_datensatzSortieren_Autor(t_menu *menu);
void up_datensatzSortieren_AutorAbsteigend(t_menu *menu);
void up_datensatzSortieren_Verlag(t_menu *menu);
void up_datensatzSortieren_VerlagAbsteigend(t_menu *menu);
void up_datensatzSortieren_Preis(t_menu *menu);
void up_datensatzSortieren_PreisAbsteigend(t_menu *menu);
