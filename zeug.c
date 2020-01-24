#include "zeug.h";

void clear(void){
    while( getchar() != '\n');
}
void up_DateiEinlesenP(t_ListVerwaltung *f){
    FILE *file;
    file = fopen(f->datei, "r");
    if(!file) printf("kann Datei nicht öffnen\n");
    else {
        up_DateiEinlesen(f, file);
    }
}
void up_BuecherAnzeigen(t_ListVerwaltung *f){
    FILE *file;
    file = fopen(stdin, "a");
    if(!file) printf("ahhhh\n");
    else {
        up_DateiSpeichern(f, file);
    }
}
void up_DateiEinlesen(t_ListVerwaltung *f, FILE *datei){
        char buffer[FILEBUFFERLENGTH+1];
        fgets(buffer, FILEBUFFERLENGTH, datei);
        while (!feof(datei)) {
            if(buffer[0] != '#'){
                strncpy(f->titel, buffer, FILEBUFFERLENGTH);
                buffer[FILEBUFFERLENGTH]=0;
                strncpy(f->autor, buffer+FILEBUFFERLENGTH, FILEBUFFERLENGTH);
                buffer[FILEBUFFERLENGTH]=0;
                strncpy(f->verlag, buffer+2*FILEBUFFERLENGTH, FILEBUFFERLENGTH);
                buffer[FILEBUFFERLENGTH]=0;
                sscanf("%f",buffer+3*FILEBUFFERLENGTH);
                up_structListe(f);
            }
            fgets(buffer, FILEBUFFERLENGTH, datei);
        }
        fclose(datei);
}
void up_DateiSpeichernP(t_ListVerwaltung *f){
    FILE *file;
    file = fopen(f->datei, "a");
    if(!file) printf("Can´t open File\n");
    else {
        up_DateiSpeichern(f, file);
    }
}
void up_DateiSpeichern(t_ListVerwaltung *f, FILE *datei){
    char buffer[STRINGLENGTH];
    t_BuchL *mom = f-> start;
        while (!mom) {
            sprintf("%30s", buffer, mom->titel);
            fputs(buffer, datei);
            sprintf("%30s", buffer, mom->autor);
            fputs(buffer, datei);
            sprintf("%30s", buffer, mom->verlag);
            fputs(buffer, datei);
            sprintf("%30s\n", buffer, mom->preis);
            fputs(buffer, datei);
            mom = mom->danach;
        }
        fclose(datei);
}
void up_structListe(t_ListVerwaltung *f){
    strcpy(f->momentan->titel, f->titel);
    strcpy(f->momentan->autor, f->autor);
    strcpy(f->momentan->verlag, f->verlag);
    f->momentan->preis = f->preis;
}
void up_BuchHinzufuegen(t_ListVerwaltung *f){
    f->momentan = (t_BuchL*) malloc(sizeof(t_BuchL));
    up_structListe(f);
    f->momentan->davor = f->zwischen;
    f->momentan->danach = 0;
    if(!f->zwischen) f->start = f->momentan;
    else f->zwischen->danach = f->momentan;
    f->zwischen = f->momentan;
}
void up_BuchLoeschen(t_ListVerwaltung *f){
    //up_suche(f);
    t_BuchL *momentanNeu;
    if(f->momentan){
       if(f->momentan->davor && f->momentan->danach){ //normales Element
            f->momentan->davor->danach = f->momentan->danach;
            f->momentan->danach->davor = f->momentan->davor;
            momentanNeu = f->momentan->danach;
       }else if(f->momentan->danach) {  // erstes Element
           f->momentan->danach->davor = 0;
           momentanNeu = f->momentan->danach;
       }else if(f->momentan->davor){ // letztes Element
           f->momentan->davor->danach = 0;
           momentanNeu = f->momentan->davor;
       }else{ //einziges Element
            momentanNeu = 0;
       }
       free(f->momentan);
       f->momentan = momentanNeu;
    }else{
        printf("Liste leer\n");
    }
}
void up_BuchVertauschen(t_BuchL *item1, t_BuchL *item2){
    if(!item1 && !item2){
        if(!item1->davor) item1->davor->danach = item2;
        if(!item1->danach) item1->danach->davor = item2->davor;
        if(!item2->davor) item2->davor->danach = item1;
        if(!item2->danach) item2->danach->davor = item1->davor;
    }
}
void up_ListeAnzeigen(t_ListVerwaltung *f){
    f->momentan = f->start;
    printf("%-20s %10s %10s %10s\n","Titel", "momentan", "danach", "davor");
    while(f->momentan){
            printf("%-20s %10x %10x %10x\n", f->momentan->titel, f->momentan, f->momentan->danach, f->momentan->davor);
            f->momentan = f->momentan->danach;
    }
    if(f->momentan == f->start)printf("Liste leer\n");
    printf("Press any key to continue...\n");
    getchar();

}

