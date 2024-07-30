#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
struct Pytanie {
    char tresc[128];
    char odpowiedzi[4][64];
    char odpowiedzPoprawna[64];
    char odpowiedzUzytkownika;
    bool czyPoprawna;
};

typedef struct Pytanie Pytanie_t;

void przemieszaj_pytania(Pytanie_t *pytania, int liczba_pytan) {
    for (int i = 0; i < liczba_pytan - 1; i++) {
        int j = i + rand() % (liczba_pytan - i);
        Pytanie_t temp = pytania[i];
        pytania[i] = pytania[j];
        pytania[j] = temp;
    }
}
void przemieszaj_odpowiedzi(Pytanie_t *pytania, int liczba_pytan) {
    for (int i = 0; i < liczba_pytan; i++) {
        for (int k = 0; k < 4; k++) {
            int l = k + rand() % (4 - k);
            char temp_odpowiedz[64];
            strcpy(temp_odpowiedz, pytania[i].odpowiedzi[k]);
            strcpy(pytania[i].odpowiedzi[k], pytania[i].odpowiedzi[l]);
            strcpy(pytania[i].odpowiedzi[l], temp_odpowiedz);
        }
    }
}
void wczytywanie_pliku_do_struktury(Pytanie_t *pytania, int *liczba_pytan) {
    FILE *fp;
    char buffer[255];
    int nr_pytania = 0;
    fp = fopen("baza.txt", "r");

    if (fp == NULL) {
        printf("Nie udalo sie wczytac pliku");
    }

    while (fgets(buffer, 255, fp) != NULL) {
        if (buffer[0] == 'A' && buffer[1] == '.') {
            strcpy(pytania[nr_pytania].odpowiedzi[0], buffer + 2);
        } else if (buffer[0] == 'B' && buffer[1] == '.') {
            strcpy(pytania[nr_pytania].odpowiedzi[1], buffer + 2);
        } else if (buffer[0] == 'C' && buffer[1] == '.') {
            strcpy(pytania[nr_pytania].odpowiedzi[2], buffer + 2);
        } else if (buffer[0] == 'D' && buffer[1] == '.') {
            strcpy(pytania[nr_pytania].odpowiedzi[3], buffer + 2);
        } else if (buffer[1] != '.') {
            strcpy(pytania[nr_pytania].tresc, buffer);
        } else if (buffer[0] == 'O' && buffer[1] == '.') {
            strcpy(pytania[nr_pytania].odpowiedzPoprawna, buffer + 2);
            nr_pytania++;
        }
    }
    fclose(fp);
    *liczba_pytan = nr_pytania;
}

void wyswietl_strukture_pytan(const Pytanie_t *pytania, int liczba_pytan) {
    for (int i = 0; i < liczba_pytan; i++) {
        printf("Pytanie %d: %s\n", i + 1, pytania[i].tresc);
        printf("Odpowiedzi:\n");
        for (int j = 0; j < 4; j++) {
            printf("  %c. %s\n", 'A' + j, pytania[i].odpowiedzi[j]);
        }
        printf("Poprawna odpowiedź: %s\n", pytania[i].odpowiedzPoprawna);
        printf("\n");
    }
}

void zbierz_i_wyswietl_odpowiedzi(Pytanie_t *pytania, int liczba_pytan) {
    for (int i = 0; i < liczba_pytan; i++) {
        printf("Odpowiedz na pytanie %d: %s\n", i + 1, pytania[i].tresc);
        for (int j = 0; j < 4; j++) {
            printf("  %c. %s\n", 'A' + j, pytania[i].odpowiedzi[j]);
        }
        scanf(" %s", &pytania[i].odpowiedzUzytkownika);

        if (pytania[i].odpowiedzUzytkownika == 'A') {
            if (strcmp(pytania[i].odpowiedzi[0], pytania[i].odpowiedzPoprawna) == 0) {
                pytania[i].czyPoprawna = true;
            } else {
                pytania[i].czyPoprawna = false;
            }
        } else if (pytania[i].odpowiedzUzytkownika == 'B') {
            if (strcmp(pytania[i].odpowiedzi[1], pytania[i].odpowiedzPoprawna) == 0) {
                pytania[i].czyPoprawna = true;
            } else {
                pytania[i].czyPoprawna = false;
            }
        } else if (pytania[i].odpowiedzUzytkownika == 'C') {
            if (strcmp(pytania[i].odpowiedzi[2], pytania[i].odpowiedzPoprawna) == 0) {
                pytania[i].czyPoprawna = true;
            } else {
                pytania[i].czyPoprawna = false;
            }
        } else if (pytania[i].odpowiedzUzytkownika == 'D') {
            if (strcmp(pytania[i].odpowiedzi[3], pytania[i].odpowiedzPoprawna) == 0) {
                pytania[i].czyPoprawna = true;
            } else {
                pytania[i].czyPoprawna = false;
            }
        } else {
            pytania[i].czyPoprawna = false;
        }
    }
    int licznik = 0;
    printf("\nWyniki:\n");
     for (int i = 0; i < liczba_pytan; i++) {
        if (pytania[i].czyPoprawna == false) {
            licznik++;
            printf("Pytanie %d: %s\n", licznik, pytania[i].tresc);

            // Wypisz odpowiedź użytkownika
            int indeks_odpowiedzi = pytania[i].odpowiedzUzytkownika - 'A';
            printf("Twoja odpowiedź: %s\n", pytania[i].odpowiedzi[indeks_odpowiedzi]);

            // Wypisz poprawną odpowiedź
            printf("Poprawna odpowiedź: %s\n", pytania[i].odpowiedzPoprawna);
            printf("\n");
        }
    }
    float wynik_procentowy = ((float)(liczba_pytan-licznik)/liczba_pytan)*100;
    printf("Uzytkownik uzyskal %d punktow - %.2f%% poprawnych odpowiedzi",(liczba_pytan-licznik), wynik_procentowy);
}


int main() {
    srand(time(0));
    Pytanie_t pytania[64];
    int liczba_pytan = 0;

    wczytywanie_pliku_do_struktury(pytania, &liczba_pytan);
    przemieszaj_pytania(pytania, liczba_pytan);
    przemieszaj_odpowiedzi(pytania, liczba_pytan);
    wyswietl_strukture_pytan(pytania, liczba_pytan);
    zbierz_i_wyswietl_odpowiedzi(pytania, liczba_pytan);
    return 0;
}
