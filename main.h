#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "verketteteListe.h";
#include "zeug.h";
#include "buch.h"
#include "menu.h"
#ifdef __linux__
#define CLEAR_CONSOLE system("clear")
#endif
#ifdef _WIN32
#define CLEAR_CONSOLE system("cls")
#endif

void up_erstelleTestBuecher(t_verkListe *buecherListe);
