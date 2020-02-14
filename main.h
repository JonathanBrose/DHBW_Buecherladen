#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <rpc.h>
#include "verketteteListe.h"
#include "zeug.h"
#include "buch.h"
#include "menu.h"
#include "dateien.h"

#define CLEAR_CONSOLE system("cls")

void up_dateiSpeichern(t_menu *menu);

void up_dateiSpeichernUnter(t_menu *menu);

void up_buecherAnzeigen(t_menu *menu);

void up_dateiEinlesen(t_menu *menu);

void up_dateiEinlesenVon(t_menu *menu);

void up_listenZeigerAnzeigen(t_menu *menu);

void up_void(t_menu *menu);

void up_datensatzSortieren_Titel(t_menu *menu);

void up_datensatzSortieren_TitelAbsteigend(t_menu *menu);

void up_datensatzSortieren_Autor(t_menu *menu);

void up_datensatzSortieren_AutorAbsteigend(t_menu *menu);

void up_datensatzSortieren_Verlag(t_menu *menu);

void up_datensatzSortieren_VerlagAbsteigend(t_menu *menu);

void up_datensatzSortieren_Preis(t_menu *menu);

void up_datensatzSortieren_PreisAbsteigend(t_menu *menu);

void up_datensatzHinzufuegen(t_menu *menu);

void up_datensaetzeLoeschen(t_menu *menu);

void up_alleDatensaetzeLoeschen(t_menu *menu);

void up_datensaetzeKopieren(t_menu *menu);

void up_datensaetzeBearbeiten(t_menu *menu);

void up_datensatzDurchsuchen(t_menu *menu);
