#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define BOLD   "\x1b[1m"      /* Bold */


#define STRINGLAENGE 10
#define DATEIPUFFERLAENGE 4096

typedef struct m_BuchL {
    char titel[STRINGLAENGE];
    char autor[STRINGLAENGE];
    char verlag[STRINGLAENGE];
    float preis;
    struct m_BuchL *davor, *danach;
} t_BuchL;

typedef struct {
    char titel[STRINGLAENGE];
    char autor[STRINGLAENGE];
    char verlag[STRINGLAENGE];
    float preis;
    char datei[200];
    t_BuchL *start, *momentan, *ende;
} t_ListVerwaltung;

int up_vergleichePreis(t_BuchL *buch1, t_BuchL *buch2);

int up_vergleicheTitel(t_BuchL *buch1, t_BuchL *buch2);

void up_sort(t_ListVerwaltung *f, int(*vergleiche)(t_BuchL*, t_BuchL*));

void clearInputbuffer(void);

void up_warte(void);

void up_structListe(t_ListVerwaltung *f);

void menu(t_ListVerwaltung *f);

void up_BuecherAnzeigen(t_ListVerwaltung *f);

void up_ListenZeigerAnzeigen(t_ListVerwaltung *f);

void up_BuchVertauschen(t_ListVerwaltung *f, t_BuchL *buch1, t_BuchL *buch2);

void up_BuchLoeschen(t_ListVerwaltung *f);

void up_DateiEinlesen(t_ListVerwaltung *f);

void up_BuchHinzufuegen(t_ListVerwaltung *f);

void up_eingabeDatensatz(t_ListVerwaltung *f);

void up_DateiSpeichern(t_ListVerwaltung *f);