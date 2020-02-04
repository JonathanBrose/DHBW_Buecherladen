#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define STRINGLAENGE 30
#define DATEIPUFFERLAENGE 80

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
    t_BuchL *start, *momentan, *zwischen;
} t_ListVerwaltung;

void clearInputbuffer(void);

void up_structListe(t_ListVerwaltung *f);

void menu(t_ListVerwaltung *f);

void up_BuecherAnzeigen(t_ListVerwaltung *f);

void up_ListeAnzeigen(t_ListVerwaltung *f);

void up_BuchVertauschen(t_BuchL *buch1, t_BuchL *buch2);

void up_BuchLoeschen(t_ListVerwaltung *f);

void up_DateiEinlesen(t_ListVerwaltung *f);

void up_DateiEinlesenP(t_ListVerwaltung *f);

void up_BuchHinzufuegen(t_ListVerwaltung *f);

void up_eingabeDatensatz(t_ListVerwaltung *f);

void up_DateiSpeichernP(t_ListVerwaltung *f);

void up_DateiSpeichern(t_ListVerwaltung *f);