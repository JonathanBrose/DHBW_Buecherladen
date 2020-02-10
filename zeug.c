#include "main.h"

void clearInputbuffer(void) {
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
void clearScreen(void){

}

void up_warte(void) {
    printf("Druecken sie ENTER um fortzufahren...\n");
    getchar();
}
void up_EingabeString(char *eingabe, char *eingabeBeschreibung, char *fehlertext) {
    FILE *ergebnis;
    char puffer[STRINGLAENGE + 1];
    do {
        clearInputbuffer();
        printf("%s",eingabeBeschreibung);
        ergebnis = fgets(puffer, STRINGLAENGE, stdin);
        if(!ergebnis){
            fprintf(stderr, "Fehler bei der Eingabe: Eingabe leer\n");
        }
    }while (!ergebnis);
    strcpy(eingabe, puffer);
}
void up_EingabeFloat(float *eingabe, char *eingabeBeschreibung, char *fehlertext) {
    int ergebnis = 0;
    do {
        clearInputbuffer();
        printf("%s",eingabeBeschreibung);
        ergebnis = scanf("%f", eingabe);
        if(!ergebnis){
            fprintf(stderr, "Fehler bei der Eingabe: Eingabe leer, oder kein Gleitkommawert\n");
        }
    }while (!ergebnis);
}
