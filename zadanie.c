#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CARS 100
#define VIN_LENGTH 17

typedef struct {
    char vin[VIN_LENGTH + 1];
    char marka[51];
    char model[51];
    int rok;
    int przebieg;
} Samochod;

Samochod flota[MAX_CARS];
int liczba_samochodow = 0;

int poprawny_vin(const char *vin) {
    if (strlen(vin) != VIN_LENGTH) return 0;
    for (int i = 0; vin[i]; i++) {
        if (!isalnum(vin[i])) return 0;
    }
    return 1;
}

int poprawna_nazwa(const char *nazwa) {
    for (int i = 0; nazwa[i]; i++) {
        if (!isalpha(nazwa[i]) && nazwa[i] != ' ') return 0;
    }
    return 1;
}

int poprawny_rok(int rok) {
    return rok >= 1900 && rok <= 2025;
}

int znajdz_samochod_po_vin(const char *vin) {
    for (int i = 0; i < liczba_samochodow; i++) {
        if (strcmp(flota[i].vin, vin) == 0) {
            return i;
        }
    }
    return -1;
}

void dodaj_samochod() {
    if (liczba_samochodow >= MAX_CARS) {
        printf("Flota jest pełna!\n");
        return;
    }

    Samochod nowy_samochod;

    printf("Podaj VIN: ");
    scanf("%s", nowy_samochod.vin);
    if (!poprawny_vin(nowy_samochod.vin)) {
        printf("Niepoprawny VIN!\n");
        return;
    }

    if (znajdz_samochod_po_vin(nowy_samochod.vin) != -1) {
        printf("Samochód z tym VIN już istnieje!\n");
        return;
    }

    printf("Podaj markę: ");
    scanf("%s", nowy_samochod.marka);
    if (!poprawna_nazwa(nowy_samochod.marka)) {
        printf("Niepoprawna nazwa marki!\n");
        return;
    }

    printf("Podaj model: ");
    scanf("%s", nowy_samochod.model);
    if (!poprawna_nazwa(nowy_samochod.model)) {
        printf("Niepoprawna nazwa modelu!\n");
        return;
    }

    printf("Podaj rok produkcji: ");
    scanf("%d", &nowy_samochod.rok);
    if (!poprawny_rok(nowy_samochod.rok)) {
        printf("Niepoprawny rok!\n");
        return;
    }

    printf("Podaj przebieg: ");
    scanf("%d", &nowy_samochod.przebieg);

    flota[liczba_samochodow++] = nowy_samochod;
    printf("Samochód został dodany!\n");
}

void edytuj_samochod() {
    char vin[VIN_LENGTH + 1];
    printf("Podaj VIN samochodu do edycji: ");
    scanf("%s", vin);

    int index = znajdz_samochod_po_vin(vin);
    if (index == -1) {
        printf("Nie znaleziono samochodu!\n");
        return;
    }

    printf("Podaj nowy przebieg: ");
    scanf("%d", &flota[index].przebieg);
    printf("Przebieg został zaktualizowany!\n");
}

void usun_samochod() {
    char vin[VIN_LENGTH + 1];
    printf("Podaj VIN samochodu do usunięcia: ");
    scanf("%s", vin);

    int index = znajdz_samochod_po_vin(vin);
    if (index == -1) {
        printf("Nie znaleziono samochodu!\n");
        return;
    }

    for (int i = index; i < liczba_samochodow - 1; i++) {
        flota[i] = flota[i + 1];
    }
    liczba_samochodow--;
    printf("Samochód został usunięty!\n");
}

void pokaz_samochody_starsze_niz() {
    int rok;
    printf("Podaj rok: ");
    scanf("%d", &rok);

    for (int i = 0; i < liczba_samochodow; i++) {
        if (flota[i].rok < rok) {
            printf("VIN: %s, Marka: %s, Model: %s, Rok: %d, Przebieg: %d\n",
                   flota[i].vin, flota[i].marka, flota[i].model, flota[i].rok, flota[i].przebieg);
        }
    }
}

void pokaz_samochody_marki() {
    char marka[50];
    printf("Podaj markę: ");
    scanf("%s", marka);

    for (int i = 0; i < liczba_samochodow; i++) {
        if (strcmp(flota[i].marka, marka) == 0) {
            printf("VIN: %s, Marka: %s, Model: %s, Rok: %d, Przebieg: %d\n",
                   flota[i].vin, flota[i].marka, flota[i].model, flota[i].rok, flota[i].przebieg);
        }
    }
}

void pokaz_raport() {
    char unikalne_marki[MAX_CARS][50];
    int liczba_marki[MAX_CARS] = {0};
    int liczba_unikalnych = 0;
    int suma_przebiegow = 0;

    for (int i = 0; i < liczba_samochodow; i++) {
        int znaleziono = 0;
        for (int j = 0; j < liczba_unikalnych; j++) {
            if (strcmp(flota[i].marka, unikalne_marki[j]) == 0) {
                liczba_marki[j]++;
                znaleziono = 1;
                break;
            }
        }
        if (!znaleziono) {
            strcpy(unikalne_marki[liczba_unikalnych], flota[i].marka);
            liczba_marki[liczba_unikalnych++] = 1;
        }
        suma_przebiegow += flota[i].przebieg;
    }

    printf("Raport:\n");
    for (int i = 0; i < liczba_unikalnych; i++) {
        printf("Marka: %s, Liczba: %d\n", unikalne_marki[i], liczba_marki[i]);
    }
    if (liczba_samochodow > 0) {
        printf("Średni przebieg: %.2f\n", (double)suma_przebiegow / liczba_samochodow);
    }
}

void zapisz_do_pliku() {
    FILE *plik = fopen("flota.txt", "w");
    if (!plik) {
        printf("Błąd otwarcia pliku!\n");
        return;
    }

    for (int i = 0; i < liczba_samochodow; i++) {
        fprintf(plik, "%s %s %s %d %d\n", flota[i].vin, flota[i].marka, flota[i].model, flota[i].rok, flota[i].przebieg);
    }

    fclose(plik);
    printf("Dane zapisano do pliku!\n");
}

void wczytaj_z_pliku() {
    FILE *plik = fopen("flota.txt", "r");
    if (!plik) {
        printf("Błąd otwarcia pliku!\n");
        return;
    }

    liczba_samochodow = 0;
    while (fscanf(plik, "%s %s %s %d %d", flota[liczba_samochodow].vin, flota[liczba_samochodow].marka, flota[liczba_samochodow].model,
                  &flota[liczba_samochodow].rok, &flota[liczba_samochodow].przebieg) == 5) {
        liczba_samochodow++;
    }

    fclose(plik);
    printf("Dane wczytano z pliku!\n");
}

int main() {
    int wybor;

    do {
        printf("\nSystem zarządzania flotą samochodów\n");
        printf("1. Dodaj samochód\n");
        printf("2. Edytuj samochód\n");
        printf("3. Usuń samochód\n");
        printf("4. Pokaż samochody starsze niż podany rok\n");
        printf("5. Pokaż samochody danej marki\n");
        printf("6. Pokaż raport\n");
        printf("7. Zapisz dane do pliku\n");
        printf("8. Wczytaj dane z pliku\n");
        printf("9. Wyjdź\n");
        printf("Wybierz opcję: ");
        scanf("%d", &wybor);

        switch (wybor) {
            case 1:
                dodaj_samochod();
                break;
            case 2:
                edytuj_samochod();
                break;
            case 3:
                usun_samochod();
                break;
            case 4:
                pokaz_samochody_starsze_niz();
                break;
            case 5:
                pokaz_samochody_marki();
                break;
            case 6:
                pokaz_raport();
                break;
            case 7:
                zapisz_do_pliku();
                break;
            case 8:
                wczytaj_z_pliku();
                break;
            case 9:
                printf("Koniec programu...\n");
                break;
            default:
                printf("Niepoprawny wybór!\n");
        }
    } while (wybor != 9);

    return 0;
}
