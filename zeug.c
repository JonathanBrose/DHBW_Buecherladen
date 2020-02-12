#include "main.h"

void clearInputbuffer(void) {
//    char c;
//    do {
//    c = getchar();
//    } while (c != '\n' && c != EOF);
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
            fprintf(stderr, "Fehler bei der Eingabe: Eingabe leer, oder ungültiger Character\n");
        } else if (eingabe == 'j' || eingabe == 'J') {
            return 1;
        } else if (eingabe == 'n' || eingabe == 'N') {
            return 0;
        } else {
            fprintf(stderr, "Fehler bei der Eingabe: ungültiger Character: %c\n", eingabe);
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
    return 1 < laenge && laenge <= STRINGLAENGE;
}

int up_pruefeLoeschSyntax(char *eingabe) {
    char *eingabeKopie;
    strcpy(eingabeKopie, eingabe);
    char *ptr = strtok(eingabeKopie, ",");
    int i = 0, c = 0;
    char getrennt[STRINGLAENGE][STRINGLAENGE];
    while (ptr) {
        strcpy(getrennt[c], ptr);
        ptr = strtok(NULL, ",");
        c++;
    }
    int loeschbereiche[c * 2];
    for (i = 0; i < c; i++) {
        ptr = strtok(getrennt[i], "-");
        while (ptr) {
            if(sscanf(ptr, "%d", &loeschbereiche[0]) == 0){
                return 0;
            }
            ptr = strtok(NULL, "-");
        }
    }
    return 1;
}
