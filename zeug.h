#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define DATEIPUFFERLAENGE 4096
#define STRINGLAENGE 30

typedef struct{
    char titel[STRINGLAENGE];
    char autor[STRINGLAENGE];
    char verlag[STRINGLAENGE];
    float preis;
}t_Buch;

typedef struct {
    char titel[STRINGLAENGE];
    char autor[STRINGLAENGE];
    char verlag[STRINGLAENGE];
    float preis;
    char datei[200];
    t_vL_element *start, *momentan, *ende;
} t_ListVerwaltung;



void clearInputbuffer(void);

void up_warte(void);

void up_structListe(t_ListVerwaltung *f);

void menu(t_ListVerwaltung *f);

void up_BuecherAnzeigen(t_ListVerwaltung *f);

void up_ListenZeigerAnzeigen(t_ListVerwaltung *f);

void up_verkListe_Vertauschen(t_ListVerwaltung *f, t_vL_element *element1, t_vL_element *element2);

void up_BuchLoeschen(t_ListVerwaltung *f);

void up_DateiEinlesen(t_ListVerwaltung *f);

void up_BuchHinzufuegen(t_ListVerwaltung *f);

void up_eingabeDatensatz(t_ListVerwaltung *f);

void up_DateiSpeichern(t_ListVerwaltung *f);