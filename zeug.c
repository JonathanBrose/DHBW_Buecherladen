#include "main.h"

void clearInputbuffer(void) {
    fflush(stdin);
}

void up_warte(void) {
    printf("Druecken sie ENTER um fortzufahren...\n");
    getchar();
}
void up_EingabeString(char *eingabe, char *eingabeBeschreibung, int(*pruefeGueltigkeit)(char *), char *fehlermeldung) {
    FILE *ergebnis;
    char puffer[STRINGLAENGE + 1];
    do {
        clearInputbuffer();
        printf("%s", eingabeBeschreibung);
        ergebnis = fgets(puffer, STRINGLAENGE, stdin);
        *strchr(puffer, '\n') = 0;
        if (!ergebnis) {
            fprintf(stderr, "Fehler bei der Eingabe: Eingabe leer\n");
        } else if (!pruefeGueltigkeit(puffer)) {
            fprintf(stderr, "%s\n", fehlermeldung);
            ergebnis = 0;
        }
    } while (!ergebnis);
    strcpy(eingabe, puffer);
}

int up_EingabeWeiter(char *eingabeBeschreibung) {
    int ergebnis;
    char eingabe;
    do {
        clearInputbuffer();
        printf("[J/n] %s", eingabeBeschreibung);
        ergebnis = scanf("%c", &eingabe);
        if (!ergebnis) {
            fprintf(stderr, "Fehler bei der Eingabe: Eingabe leer, oder ungueltiger Character\n");
        } else if (eingabe == 'j' || eingabe == 'J') {
            return 1;
        } else if (eingabe == 'n' || eingabe == 'N') {
            return 0;
        } else {
            fprintf(stderr, "Fehler bei der Eingabe: ungueltiger Character: %c\n", eingabe);
            ergebnis = 0;
        }
    } while (!ergebnis);
}

void up_EingabeFloat(float *eingabe, char *eingabeBeschreibung) {
    int ergebnis = 0;
    do {
        clearInputbuffer();
        printf("%s", eingabeBeschreibung);
        ergebnis = scanf("%f", eingabe);
        if (!ergebnis) {
            fprintf(stderr, "Fehler bei der Eingabe: Eingabe leer, oder kein Gleitkommawert\n");
        }
    } while (!ergebnis);
}

int up_pruefeStringLaenge(char *string) {
    long long laenge = strlen(string);
    return 0 < laenge && laenge <= STRINGLAENGE;
}
char up_instant_getch(){
    char c = 0;
    DWORD mode, count;
    HANDLE ih = GetStdHandle( STD_INPUT_HANDLE );
    SetConsoleMode( ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
    ReadConsoleA( ih, &c, 1, &count, NULL);
    SetConsoleMode( ih, mode );
    return c;
}

