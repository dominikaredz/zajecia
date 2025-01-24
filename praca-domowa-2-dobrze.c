#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char autor[30];
    char tytul[50];
    char kat[40];
    float cena;
    int strony;
    int read;
    int regal;
} Book;

void displayBooks(Book books[], int n);
void findCheapestBook(Book books[], int n);
void findThickestBooksByCategory(Book books[], int n);
void writeReadBooksAboveAveragePrice(Book books[], int n, const char* filename);
void findMostExpensiveUnreadBookByAuthor(Book books[], int n, const char* author);

int main() {
    FILE *file = fopen("biblioteka.txt", "r");

    int n;
    fscanf(file, "%d", &n);
    printf("Ilosc ksiazek: %d\n", n);
    Book *books = malloc(n * sizeof(Book));
    
    for (int i = 0; i < n; i++) {
        fscanf(file, "%29s %49s %39s %f %d %d %d",
               books[i].autor,
               books[i].tytul,
               books[i].kat,
               &books[i].cena,
               &books[i].strony,
               &books[i].read,
               &books[i].regal);
    }
    fclose(file);

    displayBooks(books, n);
    findCheapestBook(books, n);
    findThickestBooksByCategory(books,n);
    
    char filename[100];    
    printf("Przeczytane ksiazki powyzej sredniej ceny, podaj nazwe pliku: ");
    scanf("%99s", filename);
    printf("\n");
    
    writeReadBooksAboveAveragePrice(books,n,filename);
    char author[30];
    while (1){
        printf("Dla jakiego autora chcesz znalezc ksiazke\n");
        printf("\n");
        scanf("%29s", author);
        if (strcmp(author, "Agatha_Christie") == 0 ||
            strcmp(author, "Suzanne_Collins") == 0 ||
            strcmp(author, "Stephane_Meyer") == 0 ||
            strcmp(author, "Brandon_Sanderson") == 0 ||
            strcmp(author, "J_Rowling") == 0 ||
            strcmp(author, "Neil_Gaiman") == 0) {
    break;
        } else{
            printf("nieznany autor\n");
        }
    }
    printf("\n");
    
    findMostExpensiveUnreadBookByAuthor(books,n,author);
    free(books);
    return 0;
}

void displayBooks(Book books[], int n) {
    printf("%-20s %-40s %-20s %-10s %-10s %-10s %-10s\n",
    "Autor", "Tytul", "Kategoria", "Cena", "Strony", "Przeczytane?", "Polka\n");
    for (int i = 0; i < n; i++) {
        printf("%-20s %-40s %-20s %-10.2f %-10d %-10d %-10d\n",
               books[i].autor,
               books[i].tytul,
               books[i].kat,
               books[i].cena,
               books[i].strony,
               books[i].read,
               books[i].regal);
    }
    printf("\n");
}
void findCheapestBook(Book books[], int n){
    int index = 0;
    for (int i = 1; i<n;i++){
        if(books[i].cena < books[index].cena){
            index = i;
        }
        
    }
    printf("Najtansza ksiazka to: %s (%.2f)\n",
           books[index].tytul,
           books[index].cena);
printf("\n");
}

void findThickestBooksByCategory(Book books[], int n){
    for (int i = 0; i < n; i++) {
        int found = 0;
        
        for (int j = 0; j < i; j++) {
            if (books[j].kat[0] == books[i].kat[0]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int maxPages = books[i].strony;
            int maxIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (books[j].kat[0] == books[i].kat[0] && 
                    books[j].strony > maxPages) {
                    maxPages = books[j].strony;
                    maxIndex = j;
                }
            }
            
            printf("Najgrubsza ksiazka w kategorii %s to: %s (%d stron)\n",
                   books[maxIndex].kat,
                   books[maxIndex].tytul,
                   books[maxIndex].strony);
        }
    }
printf("\n");    
}
void writeReadBooksAboveAveragePrice(Book books[],int n, const char* filename){
    float overallprice = 0;
    
    for (int i = 0; i<n; i++){
        overallprice += books[i].cena;
    }
    float avargeprice = overallprice / n;
    
    FILE *write = fopen(filename,"w");

    for (int i = 0; i<n; i++){
        if (books[i].read == 1 && books[i].cena > avargeprice){
            
            fprintf(write,"%-20s %-40s %-20s %-10.2f %-10d %-10d %-10d\n",
               books[i].autor,
               books[i].tytul,
               books[i].kat,
               books[i].cena,
               books[i].strony,
               books[i].read,
               books[i].regal);


        }
    }
    fflush(write);
    fclose(write);
}

void findMostExpensiveUnreadBookByAuthor(Book books[], int n, const char* author) {
    int mostExpIndex = -1;
    float highestPrice = 0.0f;

    for (int i = 0; i < n; i++) {
        if (strcmp(books[i].autor, author) == 0 && books[i].read == 0) {
            if (books[i].cena > highestPrice) {
                highestPrice = books[i].cena;
                mostExpIndex = i;
            }
        }
    }

    if (mostExpIndex == -1) {
        printf("Brak nieprzeczytanych ksiazek tego autora: %s\n", author);
    } else {
        printf("Najdrozsza nieprzeczytana ksiazka  %s to \"%s\" za cene %.2f\n",
               author,
               books[mostExpIndex].tytul,
               highestPrice);
    }
}