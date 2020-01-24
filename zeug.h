#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRINGLENGTH 30
#define FILEBUFFERLENGTH 80

typedef struct
{

}t_Datum;
typedef struct m_BuchL
{
    char titel[STRINGLENGTH];
    char autor[STRINGLENGTH];
    char verlag[STRINGLENGTH];
    float preis;
    struct m_BuchL *davor, *danach;
}t_BuchL;

typedef struct {
    char titel[STRINGLENGTH];
    char autor[STRINGLENGTH];
    char verlag[STRINGLENGTH];
    float preis;
    char datei[200];
    t_BuchL *start, *momentan, *zwischen;
}t_ListVerwaltung;

void clear(void);
void up_structListe(t_ListVerwaltung *f);
void menu(t_ListVerwaltung *f);
void up_BuecherAnzeigen(t_ListVerwaltung *f);
void up_ListeAnzeigen(t_ListVerwaltung *f);
void up_BuchVertauschen(t_BuchL *item1, t_BuchL *item2);
void up_BuchLoeschen(t_ListVerwaltung *f);
void up_DateiEinlesen(t_ListVerwaltung *f, FILE *datei);
void up_DateiEinlesenP(t_ListVerwaltung *f);
void up_BuchHinzufuegen(t_ListVerwaltung *f);
void up_eingabeDatensatz(t_ListVerwaltung *f);
void up_DateiSpeichernP(t_ListVerwaltung *f);
void up_DateiSpeichern(t_ListVerwaltung *f, FILE *datei);