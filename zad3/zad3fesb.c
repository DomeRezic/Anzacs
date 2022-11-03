#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_MAX (50)
#define ALLOC_FAIL (-1)
#define FILE_FAIL (-1)
#define SUCCESS (0)
#define NOT_FOUND (0)
#define EXIT_FAIL (-1)
#define BUFFER_MAX (400)

typedef struct Osoba* Pozicija;

struct Osoba {
    char ime[NAME_MAX];
    char prezime[NAME_MAX];
    int godina_rodenja;
    Pozicija next;
};

typedef struct Osoba Osoba;


Pozicija DodajHead() {
    Pozicija head = NULL;
    head = (Pozicija)malloc(sizeof(Osoba));
    head->next = NULL;
    return head;
}

int DodajNaPocetak(Pozicija Head) {

    Pozicija p = NULL;
    p = Head;

    Pozicija q = NULL;

    q = (Pozicija)malloc(sizeof(Osoba));

    if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nDodan novi element liste!");
    }

    q->next = p->next;
    p->next = q;

    printf("\nUnesite ime osobe: ");
    scanf(" %s", q->ime);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s", q->prezime);
    printf("\nUnesite godinu rodenja osobe: ");
    scanf(" %d", &(q->godina_rodenja));

    printf("\nOsoba dodana na pocetak liste!");

    return SUCCESS;
}

int DodajNaKraj(Pozicija Head) {
    Pozicija p = NULL;
    p = Head;

    while (p->next != NULL) {
        p = p->next;
    }

    Pozicija q = NULL;

    q = (Pozicija)malloc(sizeof(Osoba));
    if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nDodan novi element liste!");
    }

    q->next = p->next;
    p->next = q;

    printf("\nUnesite ime osobe: ");
    scanf(" %s", q->ime);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s", q->prezime);
    printf("\nUnesite godinu rodenja osobe: ");
    scanf(" %d", &(q->godina_rodenja));

    printf("\nOsoba dodana na kraj liste!");

    return SUCCESS;
}

int IspisListe(Pozicija Head) {
    Pozicija temp;
    temp = Head->next;

    int brojac = 1;

    while (temp != NULL) {
        printf("\nOsoba br %d: ", brojac);
        printf("\nIme osobe: %s", temp->ime);
        printf("\nPrezime osobe: %s", temp->prezime);
        printf("\nGodina rodenja osobe: %d", temp->godina_rodenja);
        temp = temp->next;
        brojac++;
    }

    printf("\nLISTA ISPISANA!");

    return SUCCESS;
}

Pozicija PronadjiElement(Pozicija Head) {
    Pozicija p = Head;

    char trazenoPrezime[NAME_MAX];

    printf("\nUnesi trazeno prezime: ");
    scanf(" %s", trazenoPrezime);

    int brojac = 1;

    while (p->next != NULL && strcmp(trazenoPrezime, p->next->prezime) != 0) {
        p = p->next;
        brojac++;
    }

    if (strcmp(trazenoPrezime, p->next->prezime) == 0) {
        printf("\nPronadjeno odgovarajuce prezime, na %d. mjestu!", brojac);
        return p->next;
    }
    else {
        printf("\nNije pronadjeno odgovarajuce prezime!");
        return NOT_FOUND;
    }
}

Pozicija PronadjiPrethodni(Pozicija Head) {
    Pozicija p = Head;

    char trazenoPrezime[NAME_MAX];

    printf("\nUnesi trazeno prezime: ");
    scanf(" %s", trazenoPrezime);

    int brojac = 1;

    while (p->next != NULL && strcmp(trazenoPrezime, p->next->prezime) != 0) {
        p = p->next;
        brojac++;
    }

    if (strcmp(trazenoPrezime, p->next->prezime) == 0) {
        printf("\nPronadjeno odgovarajuce prezime, na %d. mjestu, vracen prethodni!", brojac);
        return p;
    }
    else {
        printf("\nNije pronadjeno odgovarajuce prezime!");
        return NOT_FOUND;
    }
}

int BrisiElement(Pozicija Prethodni) {

    Pozicija p = NULL;

    p = Prethodni->next;

    Prethodni->next = p->next;

    free(p);

    return SUCCESS;
}

int DodajIzaOdredenog(Pozicija p)
{
    Pozicija q = NULL;

    q = (Pozicija)malloc(sizeof(Osoba));
    if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nDodan novi element liste!");
    }

    q->next = p->next;
    p->next = q;

    printf("\nUnesite ime osobe: ");
    scanf(" %s", q->ime);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s", q->prezime);
    printf("\nUnesite godinu rodenja osobe: ");
    scanf(" %d", &(q->godina_rodenja));

    printf("\nOsoba dodana iza %s %s!", p->ime, p->prezime);

    return SUCCESS;
}

int DodajIspredOdredenog(Pozicija p)
{
    Pozicija q = NULL;

    q = (Pozicija)malloc(sizeof(Osoba));
    if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nDodan novi element liste!");
    }

    q->next = p->next;
    p->next = q;

    printf("\nUnesite ime osobe: ");
    scanf(" %s", q->ime);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s", q->prezime);
    printf("\nUnesite godinu rodenja osobe: ");
    scanf(" %d", &(q->godina_rodenja));

    printf("\nOsoba dodana ispred %s %s!", q->next->ime, q->next->prezime);

    return SUCCESS;
}

int Sort(Pozicija p)
{
    printf("\nSortiranje liste...");

    Pozicija j, j_prev, temp, end;

    end = NULL;

    while (p->next != end)
    {
        j_prev = p;
        j = p->next;

        while (j->next != end)
        {
            if (strcmp(j->prezime, j->next->prezime) > 0)
            {
                temp = j->next;
                j_prev->next = temp;
                j->next = temp->next;
                temp->next = j;
                j = temp;
            }

            j_prev = j;
            j = j->next;
        }

        end = j;
    }

    return SUCCESS;
}

int UpisUDatoteku(Pozicija p)
{
    p = p->next;
    char imeDatoteke[NAME_MAX] = { 0 };

    printf("\nUnesite ime datoteke: ");
    scanf(" %s", imeDatoteke);

    FILE* f = NULL;

    f = fopen(imeDatoteke, "w");

    if (f == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke!");
        return FILE_FAIL;
    }
    else
    {
        printf("\nUspjesno otvaranje datoteke!");
    }

    fprintf(f, "IME\tPREZIME\tGODINA RODENJA");

    while (p->next != NULL)
    {
        fprintf(f, "\n%s\t%s\t%d", p->ime, p->prezime, p->godina_rodenja);
        p = p->next;

        if (p->next == NULL)
        {
            fprintf(f, "\n%s\t%s\t%d", p->ime, p->prezime, p->godina_rodenja);
        }
    }

    fclose(f);

    return SUCCESS;

}

int DodajNaKrajDat(Pozicija p, char* dat, int i)
{
    char buffer[BUFFER_MAX] = { 0 };
    int j = 0;
    int brojac = 0;
    int bufferint = 0;
    FILE* f = NULL;
    f = fopen(dat, "r");

    if (f == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke!");
        return FILE_FAIL;
    }
    else
    {
        printf("\nUspjesno otvaranje datoteke!");
    }

    while (p->next != NULL) {
        p = p->next;
    }

    Pozicija q = NULL;

    q = (Pozicija)malloc(sizeof(Osoba));
    if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nDodan novi element liste!");
    }

    fscanf(f, "%s\t%s\t%d", buffer, buffer, bufferint);

    for (j = 0; j < i; j++)
    {
        fscanf(f, "%s\t%s\t%d", buffer, buffer, bufferint);
    }
    fscanf(f, "%s\t%s\t%d", q->ime, q->prezime, q->godina_rodenja);

    while (!feof(f))
    {
        fgets(buffer, BUFFER_MAX, f);
    }

    printf("\nUspjesno uneseno u listu!");

    q->next = p->next;
    p->next = q;

    fclose(f);

    return SUCCESS;
}

int IspisIzDatoteke(Pozicija p)
{
    int status = 0;
    int brojac = 0, i = 0;
    char imeDatoteke[NAME_MAX] = { 0 };
    char buffer[BUFFER_MAX] = { 0 };
    int bufferint = 0;

    printf("\nUnesite ime datoteke: ");
    scanf(" %s", imeDatoteke);

    FILE* f = NULL;

    f = fopen(imeDatoteke, "r");

    if (f == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke!");
        return FILE_FAIL;
    }
    else
    {
        printf("\nUspjesno otvaranje datoteke!");
    }

    while (!feof(f)) {
        fgets(buffer, BUFFER_MAX, f);
        if (strcmp("\n", buffer) != 0) {
            brojac++;
        }
    }

    brojac = brojac - 1;

    for (i = 0; i < brojac; i++)
    {
        status = DodajNaKrajDat(p, imeDatoteke, i);
        if (status != 0)
            return EXIT_FAIL;
    }


    fclose(f);



    return SUCCESS;
}

int CitanjeIzDatoteke(Pozicija Head) {
    Pozicija p = Head;
    Pozicija q = NULL;
    char imeDatoteke[NAME_MAX];

    printf("\nUpisite ime datoteke za citanje: ");
    scanf(" %s", imeDatoteke);

    FILE* fp = NULL;

    fp = fopen(imeDatoteke, "r");

    if (fp == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke!");
        return FILE_FAIL;
    }
    else
    {
        printf("\nUspjesno otvaranje datoteke!");
    }

    while (fgetc(fp) != '\n');

    while (!feof(fp)) {
        q=(Pozicija)malloc(sizeof(Osoba));
		if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
		}
		else {
        printf("\nDodan novi element liste!");
		}

		q->next=p->next;
        p->next=q;
        fscanf(fp, " %s %s %d", q->ime, q->prezime, &(q->godina_rodenja));
        p=p->next;
    }

    printf("\nUspjesno ucitavanje liste iz datoteke!");

    return SUCCESS;
}



int main()
{
    int status = 0;
    Pozicija Head = NULL;
    Head = DodajHead();

    if (Head == NULL) {
        printf("\nAlokacija neuspjesna!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nAlokacija uspjesna, kreiran Head!");
    }

    int i = 0;

    for (i = 0; i < 2; i++)
        DodajNaPocetak(Head);

    for (i = 0; i < 2; i++)
        DodajNaKraj(Head);

    IspisListe(Head);

    Pozicija trazeniElement = NULL, prethodniElement = NULL;

    trazeniElement = PronadjiElement(Head);
	if (trazeniElement == NULL) return NOT_FOUND;

    prethodniElement = PronadjiPrethodni(Head);
	if (prethodniElement == NULL) return NOT_FOUND;

    BrisiElement(prethodniElement);

    IspisListe(Head);

    DodajIzaOdredenog(PronadjiElement(Head));

    IspisListe(Head);

    DodajIspredOdredenog(PronadjiPrethodni(Head));

    IspisListe(Head);

    Sort(Head);

    IspisListe(Head);

    status = UpisUDatoteku(Head);

    if (status != 0)
        return EXIT_FAIL;

    Pozicija HeadDat = NULL;
    HeadDat = DodajHead();

    if (HeadDat == NULL) {
        printf("\nAlokacija neuspjesna!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nAlokacija uspjesna, kreiran prvi clan liste!");
    }

    status = CitanjeIzDatoteke(HeadDat);

    if (status != 0)
        return EXIT_FAIL;

    IspisListe(HeadDat);

    return SUCCESS;
}
