#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS (0)
#define NAME_MAX (100)
#define PROGRAM_EXIT (-1)
#define ALOCC_POZ_FAIL (NULL)
#define ALOCC_FAIL (-1)
#define FILE_FAIL (-1)
#define BUFFER_MAX (200)
#define ZERODIVIDE (-1)

typedef struct racun* Pozicija;

struct racun {
	float br;
	Pozicija next;
};

typedef struct racun racun;

int citanjeDatoteke(char[NAME_MAX],Pozicija);
Pozicija createHead();
int dodajNaStog(int,Pozicija);
int uzmiSaStoga(char,Pozicija);
int brisiElement(Pozicija);
int ispisRezultata(Pozicija);
int brisiSve(Pozicija);

int main()
{
	int status = 0;
	Pozicija head = NULL;
	head = createHead();

	if (head == NULL)
	{
		return PROGRAM_EXIT;
	}

	char imeDat[NAME_MAX] = { 0 };

	printf("\nUnesite ime datoteke: ");
	scanf(" %s", imeDat);

	status=citanjeDatoteke(imeDat, head);
	if (status != 0)
	{
		return PROGRAM_EXIT;
	}

   	status=ispisRezultata(head);
   	if (status != 0)
	{
		return PROGRAM_EXIT;
	}

    	status=brisiSve(head);
    	if (status != 0)
	{
		return PROGRAM_EXIT;
	}

	return SUCCESS;
}

int citanjeDatoteke(char imeDat[NAME_MAX],Pozicija p)
{
    	int status=0,n=0;
	int tmp=0, br=0;
	char buffer[BUFFER_MAX] = { 0 };
    	char *buf;
    	char operacija='\0';
	FILE* fp = NULL;
	fp = fopen(imeDat, "r");

	if (fp == NULL)
	{
		printf("\nGreska pri otvaranju datoteke!");
		return FILE_FAIL;
	}

	fgets(buffer,BUFFER_MAX,fp);
    	buf=buffer;

    	printf("\nPostfix izraz iscitan iz datoteke:\n%s",buffer);

	while(strlen(buf)!=0)
	{
		if (sscanf(buf, "%d", &br)==1)
		{
            	sscanf(buf, "%d %n",&tmp,&n);
			status=dodajNaStog(br,p);
			if (status != 0)
			{
				return FILE_FAIL;
			}
		}
		else
		{
            		sscanf(buf,"%c %n",&operacija,&n);
            		status=uzmiSaStoga(operacija,p);
            		if (status != 0)
			{
				return FILE_FAIL;
			}
		}
        buf+=n;
	}

	return SUCCESS;
}

Pozicija createHead()
{
	Pozicija head = NULL;
	head = (Pozicija)malloc(sizeof(racun));

	if (head == NULL)
	{
		printf("\nGreska pri alokaciji!");
		return ALOCC_POZ_FAIL;
	}

	head->next = NULL;

	return head;
}

int dodajNaStog(int br, Pozicija p)
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(racun));
	if (q == NULL)
	{
		printf("\nGreska pri alokaciji!");
		return ALOCC_FAIL;
	}

	q->next = p->next;
	p->next = q;

	q->br = (float) br;

    	return SUCCESS;
}

int uzmiSaStoga(char operacija, Pozicija p)
{
    	float rezultat=0;
    	Pozicija head=NULL;
    	head=p;

    	Pozicija pret=NULL;
    	p=p->next;
    	pret=p->next;

    	switch(operacija)
    	{
       	case '+':
        {
            	rezultat=(pret->br) + (p->br);
            	break;
        }
        case '*':
        {
            	rezultat=(pret->br) * (p->br);
            	break;
        }
        case '/':
        {
                if(p->br==0){
                    printf("\nDijeljenje s nulom nije dozvoljeno!");
                    return ZERODIVIDE;
                }
                else{
            	    rezultat=(pret->br) / (p->br);
            	    break;
                }
        }
        case '-':
        {
            	rezultat=(pret->br) - (p->br);
            	break;
        }
   	}

    	pret->br=rezultat;

    	brisiElement(head);

    	return SUCCESS;
}

int brisiElement(Pozicija p)
{
    	Pozicija tmp=NULL;
    	tmp=p->next;

    	p->next=tmp->next;

    	free(tmp);

    	return SUCCESS;
}

int ispisRezultata(Pozicija p)
{
    	printf("\nRezultat je %.2f", p->next->br);

    	return SUCCESS;
}

int brisiSve(Pozicija p)
{
    	Pozicija temp = NULL;

	while (p != NULL)
	{
		temp = p;
		p = p->next;
		free(temp);
	}

	return SUCCESS;
}
