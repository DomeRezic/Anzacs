#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_MAX (50)
#define ALLOC_FAIL (-1)
#define SUCCESS (0)
#define NOT_FOUND (0)

typedef struct Osoba * Pozicija;

struct Osoba{
    char ime[NAME_MAX];
    char prezime[NAME_MAX];
    int godina_rodenja;
    Pozicija next;
};

typedef struct Osoba Osoba;


Pozicija DodajHead(){
    Pozicija head=NULL;
    head=(Pozicija)malloc(sizeof(Osoba));
    head->next=NULL;
    return head;
}

int DodajNaPocetak(Pozicija Head){

    Pozicija p=NULL;
    p=Head;

    Pozicija q=NULL;

    q=(Pozicija)malloc(sizeof(Osoba));

    if(q==NULL){
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else{
        printf("\nDodan novi element liste!");
    }

    q->next=p->next;
    p->next=q;

    printf("\nUnesite ime osobe: ");
    scanf(" %s", q->ime);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s", q->prezime);
    printf("\nUnesite godinu rodenja osobe: ");
    scanf(" %d", &(q->godina_rodenja));

    printf("\nOsoba dodana na pocetak liste!");

    return SUCCESS;
}

int DodajNaKraj(Pozicija Head){
    Pozicija p=NULL;
    p=Head;

    while(p->next != NULL){
        p=p->next;
    }

    Pozicija q=NULL;

    q=(Pozicija)malloc(sizeof(Osoba));
    if(q==NULL){
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else{
        printf("\nDodan novi element liste!");
    }

    q->next=p->next;
    p->next=q;

    printf("\nUnesite ime osobe: ");
    scanf(" %s", q->ime);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s", q->prezime);
    printf("\nUnesite godinu rodenja osobe: ");
    scanf(" %d", &(q->godina_rodenja));

    printf("\nOsoba dodana na kraj liste!");

    return SUCCESS;
}

int IspisListe(Pozicija Head){
    Pozicija temp;
    temp=Head->next;

    int brojac=1;

    while(temp != NULL){
        printf("\nOsoba br %d: ",brojac);
        printf("\nIme osobe: %s", temp->ime);
        printf("\nPrezime osobe: %s", temp->prezime);
        printf("\nGodina rodenja osobe: %d", temp->godina_rodenja);
        temp=temp->next;
        brojac++;
    }

    printf("\nLISTA ISPISANA!");

    return SUCCESS;
}

Pozicija PronadjiElement(Pozicija Head){
    Pozicija p=Head;

    char trazenoPrezime[NAME_MAX];

    printf("\nUnesi trazeno prezime: ");
    scanf(" %s", trazenoPrezime);

    int brojac=1;

    while(p->next != NULL && strcmp(trazenoPrezime,p->next->prezime)!=0){
        p=p->next;
        brojac++;
    }

    if(strcmp(trazenoPrezime,p->next->prezime)==0){
    printf("\nPronadjeno odgovarajuce prezime, na %d. mjestu!", brojac);
    return p->next;
    }
    else{
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

int BrisiElement(Pozicija Prethodni){

    Pozicija p=NULL;

    p=Prethodni->next;

    Prethodni->next=p->next;

    free(p);

    return SUCCESS;
}

int main(){

    Pozicija Head=NULL;
    Head=DodajHead();

    if(Head==NULL){
        printf("\nAlokacija neuspjesna!");
        return ALLOC_FAIL;
    }
    else{
        printf("\nAlokacija uspjesna, kreiran Head!");
    }

    int i=0;

    for(i=0;i<2;i++)
        DodajNaPocetak(Head);

    for(i=0;i<2;i++)
        DodajNaKraj(Head);

    IspisListe(Head);

    Pozicija trazeniElement=NULL, prethodniElement=NULL;

    trazeniElement = PronadjiElement(Head);

    prethodniElement = PronadjiPrethodni(Head);

    BrisiElement(prethodniElement);

    IspisListe(Head);

    return SUCCESS;
}
