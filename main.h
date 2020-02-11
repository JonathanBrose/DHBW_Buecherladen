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

void up_BuecherAnzeigen(t_menu *menu);

void up_dateiEinlesen(t_menu *menu);
