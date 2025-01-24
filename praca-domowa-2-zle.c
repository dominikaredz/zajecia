#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KSIAZKI 1000
#define MAX_AUTOR 30
#define MAX_TYTUL 50
#define MAX_KATEGORIA 40

struct ksiazka {
    char autor[MAX_AUTOR];
    char tytul[MAX_TYTUL];
    char kategoria[MAX_KATEGORIA];
    float cena;
    int strony;
    int przeczytane;
    int polka;
};

struct ksiazka zapisz(char *filename){
    struct ksiazka k;
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Nie można otworzyć pliku: %s\n", filename);
        exit(1);
    }

    fscanf(file, "%s %s %s %f %d %d %d",
    k.autor,
    k.tytul,
    k.kategoria,
    &k.cena,
    &k.strony,
    &k.przeczytane,
    &k.polka);

    fclose(file);

    return k;

    };

struct ksiazka* wczytaj_ksiazki(char *filename, int n){
    struct ksiazka *t = calloc(n, sizeof(struct ksiazka));

    char plik=filename;

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Nie można otworzyć pliku: %s\n", filename);
        exit(1);
    }

    if(t==NULL) return NULL;

    for(int i=0;i<n;i++){
        t[i] = zapisz(plik);
    }

    fclose(file);
    return t;
};

void wypisz_ksiazke(struct  ksiazka k)
{
    printf("Autor: %s\nTytuł: %s\nCena: %f\nStrony: %d\nCzy przeczytana: %d\nRegał: %d\n",
    k.autor,
    k.tytul,
    k.kategoria,
    k.cena,
    k.strony,
    k.przeczytane,
    k.polka);
};

void wypisz_ksiazki(struct ksiazka *t, int n){
    for(int i=0; i<n; ++i){
        printf("Ksiazka %d.\n", i);
        wypisz_ksiazke(t[i]);
    }
};

void najtansza(struct ksiazka *t, int n) {
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (t[i].cena < t[minIndex].cena) {
            minIndex = i;
        }
    }
    printf("Najtańsza książka: %s %s %s %.2f %d %d %d\n",
    t[minIndex].autor,
    t[minIndex].tytul,
    t[minIndex].kategoria,
    t[minIndex].cena,
    t[minIndex].strony,
    t[minIndex].przeczytane,
    t[minIndex].polka);
}

void najgrubsza(struct ksiazka *t, int n){
    int najgr=0;
    for (int i=0;i<n;i++){
        if(najgr < t[i].strony){
        najgr=t[i].strony;
        }
    }

    for (int i=0;i<n;i++){
        if(najgr == t[i].strony){
        printf("Najgrubsza ksiazka: \n%s %s %s %f %d %d %d",
            t[i].autor,
            t[i].tytul,
            t[i].kategoria,
            &t[i].cena,
            &t[i].strony,
            &t[i].przeczytane,
            &t[i].polka);
        }
    }
};

void przepisz_ksiazke(struct ksiazka *t,char *plikw){
    FILE *file = fopen(plikw, "w");
    if (!file) {
        printf("Nie można otworzyć pliku: %s\n", plikw);
        exit(1);
    }

    float cala_cena;
    int x=0; int n;

    fscanf(file, "%d", &n); 

    for (int i = 0; i < n; i++) {
    cala_cena += t[i].cena;
    x++;
    }

    float srednia = cala_cena/x;

    for(int i=0;i<n;i++){
        if(t[i].przeczytane == 1 && t[i].cena > srednia){
            fprintf(file, "%s %s %s %f %d %d %d",
            t[i].autor,
            t[i].tytul,
            t[i].kategoria,
            &t[i].cena,
            &t[i].strony,
            &t[i].przeczytane,
            &t[i].polka);
        }
    }

    fclose(file);
}

int main(){
    int n=10;
    struct ksiazka *ksiazki = wczytaj_ksiazki("zadanie.txt", n);
    wypisz_ksiazki(ksiazki, n);
    najtansza(ksiazki,n);
    najgrubsza(ksiazki,n);
    przepisz_ksiazke(ksiazki,"inny.txt");
    free(ksiazki);
}
