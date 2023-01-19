#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct cities;
typedef struct cities* Tree;
typedef struct cities {
    char name[50];
    Tree R;
    Tree L;
    int residents;
}Cities;

struct countries;
typedef struct countries* Position;
typedef struct countries{
    char name[50];
    Tree city;
    Position next;
}Countries;

int AddCountry(char* NameOfCountry, char* file, Position P);
int AddCity(char* file, Tree S);
Tree EnterCity(char* ime, int brojstan, Tree S);
int PrintCountries(Position P);
int PrintCities(Tree S);
Position SearchCountry(Position P, char* ime);
int SearchCity(Tree S, int brojst);

int main()
{
    Countries Head = { .name = "", .city = NULL, .next = NULL };
    char NameOfCountry[50];
    char NameOfFile[50];
    Position P = NULL;
    int residents = 0;
    FILE* f = NULL;

    f = fopen("drzave.txt", "r");
    if (f == NULL)
    {
        printf("ERROR: File cannot be opened.\n");
        return -1;
    }
    while (!feof(f))
    {
        fscanf(f, "%s %s", NameOfCountry, NameOfFile);
        AddCountry(NameOfCountry, NameOfFile, &Head);
    }
    fclose(f);
    PrintCountries(Head.next);

    printf("\nEnter the name of the wanted country: ");
    scanf("%s", NameOfCountry);
    P = SearchCountry(Head.next, NameOfCountry);
    if (P == NULL)
    {
        printf("This country doesn't exist in the current file, please try again.\n");
        return 0;
    }
    printf("Minimum population: ");
    scanf(" %d", &residents);
    printf("\nCities of %s with more than %d inhabitants:\n", P->name, residents);
    SearchCity(P->city,residents);

    return 0;
}

int AddCountry(char* NameOfCountry, char* file, Position P)
{
    Position q = NULL;
    Position prev = NULL;
    Tree c = NULL;

    q = (Position)malloc(sizeof(Countries));
    if (q == NULL)
    {
        printf("Memory allocation unsuccessful.\n");
        return -1;
    }

    strcpy(q->name, NameOfCountry);
    q->city = c;

    c = (Tree)malloc(sizeof(Cities));
    if (c == NULL)
    {
        printf("Memory allocation unsuccessful.\n");
        return -1;
    }

    strcpy(c->name, "");
    c->residents = 0;
    c->R = NULL;
    c->L = NULL;

    q->city = c;

    AddCity(file, q->city);

    prev = P;
    while (P != NULL)
    {
        if (P->next == NULL)
        {
            P->next = q;
            q->next = NULL;
            break;
        }
        if (strcmp(q->name, prev->next->name) < 0)
        {
            q->next = prev->next;
            prev->next = q;
            break;
        }
        P = P->next;
    }
    return 0;
}

int AddCity(char* file, Tree S)
{
    FILE* f = NULL;
    char name[50];
    int residents = 0;

    f = fopen(file, "r");
    if (f == NULL)
    {
        printf("ERROR: File cannot be opened.\n"); return -1;
    }
    while (!feof(f))
    {
        fscanf(f, "%s %d", name, &residents);
        S = EnterCity(name, residents, S);
    }
    fclose(f);
    return 0;
}

Tree EnterCity(char* name, int residents, Tree S)
{
    Tree q = NULL;
    if (S == NULL)
    {
        q = (Tree)malloc(sizeof(Cities));
        if (q == NULL)
        {
            printf("Memory allocation unsuccessful.\n");
            return NULL;
        }
        strcpy(q->name, name);
        q->residents = residents;
        q->R = NULL;
        q->L = NULL;
        return q;
    }

    if (S->residents < residents)
        S->R = EnterCity(name, residents, S->R);
    else if (S->residents > residents)
        S->L = EnterCity(name, residents, S->L);
    else if (residents == S->residents)
    {
        if (strcmp(name, S->name) >= 0)
            S->R = EnterCity(name, residents, S->R);
        else
            S->L = EnterCity(name, residents, S->L);

    }

    return S;
}

int PrintCountries(Position P)
{
    printf("COUNTRIES:\n");
    while (P != NULL)
    {
        printf("\n%s:\n", P->name);
        PrintCities(P->city->R);
        P = P->next;
    }
    return 0;
}

int PrintCities(Tree S)
{
    if (S == NULL)
        return 0;
    PrintCities(S->L);
    printf("%s \t", S->name);
    printf("%d\n", S->residents);
    PrintCities(S->R);
    return 0;
}

Position SearchCountry(Position P, char* name)
{


    while (P != NULL)
    {
        if (strcmp(P->name, name) == 0){
            return P;
        }
        P = P->next;
    }

    return P;
}

int SearchCity(Tree S, int searched_number)
{
    if (S == NULL){
        return 0;
    }
    SearchCity(S->R, searched_number);
    if (S->residents > searched_number) {
        printf("%s %d\n", S->name, S->residents);
    }

        SearchCity(S->L, searched_number);

    return 0;
}
