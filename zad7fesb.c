#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 60

typedef struct Stablo* Position;
typedef struct Lista * lPosition;

typedef struct Stablo{
    char *name;
    Position brat;
    Position dite;
}stablo;



typedef struct Lista{
    Position direktorij;

    lPosition next;
    lPosition prev;
}lista;

#pragma funkicje
int Izbornik(Position,lPosition);
int Line(lPosition,Position,Position);
lPosition FindLast(lPosition);
int StvoriStablo(Position);
Position OpenDirec(Position, lPosition);
int Push(lPosition ,Position);
Position FindByName(char*, Position);
Position ajmo_nazad(Position,lPosition);
int ispis_dice(Position trenutni);
int brisanje_stabla(Position);
#pragma end_funkcije


int main(){

    Position root;
    root = (Position) malloc (sizeof(stablo));
    root->brat=NULL;
    root->dite=NULL;

    lPosition head;
    head = (lPosition) malloc (sizeof(lista));
    head->next=NULL;
    head->prev=NULL;

    root->name=(char*)malloc(MAX_SIZE*sizeof(char));
    root->name = "C:";

    int s = 1;
    while(s){
        s=Izbornik(root,head);
    }

    return 0;
}


int Izbornik(Position root, lPosition head){

    Position trenutni = root;
    char odabir[MAX_SIZE] = { 0 };

    printf("md [...] - Dodaj novi direktorij\n");
	printf("cd [...] - Otvori direktorij\n");
	printf("cd.. - Vrati na prethodni direktorij\n");
	printf("dir - Ispis pod-direktorija trenutnog direktorija\n");
	printf("exit - KRAJ\n\n");

    while(1) {

        Line(head,root,trenutni);
        scanf(" %s",odabir);

        if(strcmp(odabir,"md") == 0)
            StvoriStablo(trenutni);

        else if(strcmp(odabir,"cd") == 0)
            trenutni=OpenDirec(trenutni,head);

        else if(strcmp(odabir,"cd..") == 0)
            trenutni=ajmo_nazad(trenutni,head);


        else if(strcmp(odabir,"dir") == 0)
            ispis_dice(trenutni);

        else if(strcmp(odabir,"exit") == 0){
            brisanje_stabla(root);
            return 0;
        }

        else
            printf("Error! Try again!\n");
    }

    return 0;
}


int Line(lPosition head, Position root, Position trenutni){

    lPosition clan;

    clan = FindLast(head);


    if(head->next == NULL)
    {
        printf("%s>",root->name);
        return 0;
    }


    while(NULL != clan->prev)
    {
        printf("%s>", clan->direktorij->name);
        clan = clan -> prev;
    }

    printf("%s>", trenutni->name);
    return 0;
}

lPosition FindLast (lPosition head){

    lPosition z;
    z = head -> next;

    if(NULL == z)
        return NULL;

    while(z -> next != NULL)
    {
        z = z -> next;
    }

    return z;
}



int StvoriStablo(Position trenutni){

    Position directory;
    directory = (Position)malloc(sizeof(stablo));
    directory->name = (char*)malloc(MAX_SIZE*sizeof(char));

    if(!directory)
        perror("Cannot alocate memory!!\n");

    if(NULL != trenutni->dite ){
        trenutni = trenutni -> dite;
        while (NULL != trenutni->brat)
        {
            trenutni = trenutni -> brat;
        }
        trenutni -> brat = directory;
    }

    else
        trenutni -> dite = directory;

    scanf(" %s", directory->name);
    directory->brat=NULL;
    directory->dite=NULL;

    return 0;
}



Position OpenDirec(Position trenutni, lPosition head){

    Position s;
    char *name;
    name = (char*)malloc(MAX_SIZE*sizeof(char));

    scanf(" %s", name);

    if(NULL == trenutni->dite ){
        printf("Nema tog direktorija!!\n");
        return trenutni;
    }

    s = FindByName(name,trenutni);
    if(!s){
        perror("Direktorij nije pronađen!!\n");
        return trenutni;
    }

    Push(head,trenutni);

    return s;
}



int Push(lPosition head,Position direktorij){

    lPosition p = (lPosition)malloc(sizeof(lista));

    p->next=head->next;
    p->prev=head;

    if(NULL != head->next)
    {
        head->next->prev=p;
    }

    head->next=p;
    p->direktorij=direktorij;

    return 0;
}



Position FindByName(char *name, Position trenutni){

    if(NULL == trenutni->dite)
    {
        printf("Direktorij je prazan!!");
        return 0;
    }

    trenutni = trenutni -> dite;

    while(strcmp(name,trenutni->name)!=0 && trenutni->brat != NULL){
            trenutni = trenutni -> brat;
    }


    if(NULL == trenutni->brat )
    {

        if(strcmp(name, trenutni->name) != 0)
            return NULL;

        else
            return trenutni;
    }

    else
        return trenutni;
}
Position ajmo_nazad(Position trenutni,lPosition ltrenutni){
    Position rjesenje = ltrenutni->next->direktorij;
    lPosition onaj_koga_brisemo = ltrenutni->next;

    onaj_koga_brisemo->next->prev = ltrenutni;
    ltrenutni->next = onaj_koga_brisemo->next;
    free(onaj_koga_brisemo);
    return rjesenje;
}


int ispis_dice(Position trenutni){
    int brojac_datoteka = 0;
    long int ukupna_zazeta_memorija_datoteka = 0;
    if(NULL==trenutni->dite){
        printf("Datoteka je prazna aka nema dice\n");
    }
    else{
        printf("Directory of %s \n ",trenutni->name);
        trenutni=trenutni->dite;
        while(NULL!=trenutni){
            brojac_datoteka++;
            printf("\n %ld B ,  %s",sizeof(trenutni),trenutni->name);
            trenutni=trenutni->brat;
            ukupna_zazeta_memorija_datoteka+= sizeof(trenutni);
        }
    printf("\n%d File(s)",brojac_datoteka);
    printf("\n%ld Bytes taken\n",ukupna_zazeta_memorija_datoteka);

    }
}
int brisanje_stabla(Position trenutni){
    if(trenutni==NULL){
        return 0;
    }
    brisanje_stabla(trenutni->brat);
    brisanje_stabla(trenutni->dite);
    free(trenutni);
    return 0;
}
