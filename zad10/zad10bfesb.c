#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct cities;
typedef struct cities* Position;
typedef struct cities {
    char name[50];
    Position next;
    int residents;
}Cities;

struct countries;
typedef struct countries* Tree;
typedef struct countries {
    char name[50];
    Tree L;
    Tree R;
    Position city;
}Countries;

int Search(Tree S, char* NameOfCountry, int residents);
int AddCity(Position P, char* file);
Tree AddCountry(Tree S, char* NameOfCountry, char* NameOfFile);
Tree SearchCountry(Tree S, char* NameOfCountry);
int PrintCountries(Tree S);
int PrintCities(Position P);

int main()
{
    Tree root = NULL;
    char NameOfCountry[50];
    char NameOfFile[50];
    FILE* f = NULL;

    char name[50];
    int population = 0;

    f = fopen("drzave.txt", "r");
    if (f == NULL)
    {
        printf("ERROR: File cannot be opened.\n");
        return -1;
    }
    while (!feof(f))
    {
        fscanf(f, "%s %s", NameOfCountry, NameOfFile);
        root = AddCountry(root, NameOfCountry, NameOfFile);
    }

    fclose(f);

    printf("COUNTRIES:\n");
    PrintCountries(root);

    printf("\nEnter the name of the wanted country: ");
    scanf("%s",name);

    printf("Enter the value of minimum population: ");
    scanf("%d", &population);

    Search(root, name, population);

    return 0;
}

Tree AddCountry(Tree S, char* NameOfCountry, char* NameOfFile)
{
    Tree q = NULL;
    Position c = NULL;

    if (S == NULL)
    {
        q = (Tree)malloc(sizeof(Countries));
        if (q == NULL)
        {
            printf("Memory allocation unsuccessful.\n");
            return NULL;
        }
        strcpy(q->name, NameOfCountry);

        c = (Position)malloc(sizeof(Cities));
        if (c == NULL)
        {
            printf("Memory allocation unsuccessful.\n");
            return NULL;
        }

        strcpy(c->name, "");
        c->residents = 0;
        c->next = NULL;

        q->city = c;

        AddCity(q->city, NameOfFile);
        q->L = NULL;
        q->R = NULL;

        return q;
    }
    else if (strcmp(S->name, NameOfCountry) < 0)
        S->R = AddCountry(S->R, NameOfCountry, NameOfFile);
    else if (strcmp(S->name, NameOfFile) > 0)
        S->L = AddCountry(S->L, NameOfCountry, NameOfFile);
    return S;

}

int AddCity(Position P, char* file)
{
    char name[50];
    int population = 0;

    Position q = NULL;
    FILE* f = NULL;
    f = fopen(file, "r");
    Position head = P;
    Position prev = P;

    if (f == NULL)
    {
        printf("ERROR: File cannot be opened.\n");
        return -1;
    }
    while (!feof(f))
    {
        P = head;
        prev = head;
        fscanf(f, "%s %d", name, &population);

        q = (Position)malloc(sizeof(Cities));
        if (q == NULL)
        {
            printf("Memory allocation unsuccessful.\n");
            return 0;
        }

        strcpy(q->name, name);
        q->residents = population;

        while (P != NULL)
        {
            if (P->next == NULL)
            {
                q->next = P->next;
                P->next = q;
                break;
            }

            if (q->residents < P->residents)//redamo ih u listi po br stanovnika
            {
                q->next = prev->next;
                prev->next = q;
                break;
            }

            if (strcmp(q->name, P->name) < 0)//redamo ih po abecedi
            {
                q->next = prev->next;
                prev->next = q;
                break;
            }
            prev = P;
            P = P->next;

        }
    }

    fclose(f);

    return 0;
}

Tree SearchCountry(Tree S, char* NameOfCountry)
{
    if (S == NULL)
        return NULL;
    if (strcmp(S->name, NameOfCountry) == 0)
        return S;
    if (strcmp(S->name, NameOfCountry) > 0)
        return SearchCountry(S->L, NameOfCountry);
    if (strcmp(S->name, NameOfCountry) < 0)
        return SearchCountry(S->R, NameOfCountry);
}

int Search(Tree S, char* NameOfCountry, int residents)
{
    Position q = NULL;
    Tree R = NULL;

    printf("Cities with wanted value of population:\n");

    R = SearchCountry(S, NameOfCountry);

    if (R == NULL)
    {
        printf("\nCountry doesn't exist.\n");
        return 0;
    }
    q = R->city;
    if (q == NULL)
    {
        printf("Country has no city.\n");
        return 0;
    }

    q = q->next;

    while (q != NULL)
    {
        if (q->residents >= residents)
            printf("\t%s %d\n", q->name, q->residents);
        q = q->next;
    }

    return 0;
}

int PrintCities(Position P)
{
    while (P != NULL)
    {
        printf("%s - %d residents\n", P->name, P->residents);
        P = P->next;
    }

    return 0;
}

int PrintCountries(Tree S)
{
    if (S == NULL)
        return 0;

    PrintCountries(S->L);
    printf("\n%s:\n", S->name);
    PrintCities(S->city->next);
    PrintCountries(S->R);

    return 0;
}
