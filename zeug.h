#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define DATEIPUFFERLAENGE 4096
#define STRINGLAENGE 100
#define AUSGABEZEILEN 15

void clearInputbuffer(void);

void up_warte(void);

int up_pruefeStringLaenge(char *string);

void up_EingabeString(char *eingabe, char *eingabeBeschreibung, int(*pruefeGueltigkeit)(char *), char *fehlermeldung);

int up_EingabeWeiter(char *eingabeBeschreibung);

void up_EingabeFloat(float *eingabe, char *eingabeBeschreibung);

char up_instant_getch();


