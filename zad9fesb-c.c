#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

struct Stablo;
typedef struct Stablo* Position;

typedef struct Stablo{
	int El;
	Position L;
	Position D;
}stablo;

Position CreateElement(int element);
Position Insert(Position trenutni, Position new);
int Replace(Position trenutni);
int File(Position head);
int RandomNum(int min, int max);
int Inorder(Position trenutni);
int Inorder_file(Position trenutni ,FILE *fp);
int main()
{

	Position first = NULL;
	Position root = NULL;
	Position q = NULL;

	int niz[10] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
	int niz2[10] = {0};
	int min = 0;
	int max = 0;
	int i = 0;

	srand(time(NULL));



	for (i = 0; i < 10; i++)
	{
		q = CreateElement(niz[i]);
		if (i == 0)
		{
			first = q;
		}
		else
		{
		Insert(first, q);
		}
	}

	printf("(Inorder) ispis prije sume:  \n");
	Inorder(first);

    File(first);


	Replace(first);

	puts("\n\n");
	printf("(Inorder) ispis poslije sume:  \n");

	Inorder(first);

	File(first);


	printf("\n\n Unesite raspon brojeva 10-90\n");
	printf("Donja granica: ");
	scanf(" %d", &min);
	if (min < 10) {
		printf("Premali broj, mora biti veci ili jednak od 10\n");
		scanf(" %d", &min);
	}
	printf("Gornja granica: ");
	scanf(" %d", &max);
	if (max > 90 || max<min){
		printf("Broj je prevelik, mora biti manji ili jednak od 90\n");
		scanf(" %d", &min);
	}
	puts("\n");

	for (i = 0; i < 10; i++)
	{
		niz2[i] = RandomNum(min, max);
	}

	for (i = 0; i < 10; i++)
	{
		q = CreateElement(niz2[i]);
		if (i == 0)
		{
			first = q;
		}
		else
		{
			Insert(first, q);
		}
	}

	Inorder(first);
    File(first);
	puts("\n");

	return 0;
}

Position CreateElement(int element)
{
	Position new = NULL;
	new = (Position)malloc(sizeof(stablo));
	new->El = element;
	new->L = NULL;
	new->D = NULL;
	return new;
}

Position Insert(Position trenutni, Position new)
{
	if (trenutni == NULL)
	{
		return new;
	}
	if ((trenutni->El) <= (new->El))
	{
		trenutni->D = Insert(trenutni->D, new);
	}
	else if ((trenutni->El) > (new->El))
	{
		trenutni->L = Insert(trenutni->L, new);
	}
	return trenutni;
}

int Inorder(Position trenutni)
{
	if (trenutni)
	{
		Inorder(trenutni->L);
		printf("%d ", trenutni->El);
		Inorder(trenutni->D);
	}

	return 0;
}


int Replace(Position trenutni)
{
	int L1 = 0;
	int D1 = 0;
	int L2 = 0;
	int D2 = 0;

	if (NULL != trenutni)
	{
		if (trenutni->L != NULL)
		{
			L1 = trenutni->L->El;
		}
		if (trenutni->D != NULL)
		{
			D1 = trenutni->D->El;
		}

		Replace(trenutni->L);
		Replace(trenutni->D);

		if (trenutni->L != NULL)
		{
			L2 = trenutni->L->El;
		}

		if (trenutni->D != NULL)
		{
			D2 = trenutni->D->El;
		}

		return trenutni->El = L2 + D2 + L1 + D1;
	}

	return 0;
}

int Inorder_file(Position trenutni, FILE *fp)
{
    if(trenutni == NULL)
    {
        return 2 ;
    }

    Inorder_file(trenutni->L,fp);
    fprintf(fp,"%d\t",trenutni->El);
    Inorder_file(trenutni->D,fp);

	return 0;
}

int File(Position root)
{
	FILE* fp = NULL;

	fp = fopen("stablo.txt", "a");

	if (!fp){
		printf("ERROR: Cannot open file!\n");
        return -1;
    }

    Inorder_file(root,fp);
	fprintf(fp, "\n\n");

	fclose(fp);

	return 0;
}


int RandomNum(int min, int max)
{
	int n = 0;
	n = max - min + 1;
	int m = RAND_MAX - (RAND_MAX % n);
	int rand_num = rand();
	if (rand_num < 99 && rand_num > 100) {
	while (rand_num > m)
		rand_num = rand();
	}
	return rand_num % n + min;
}
