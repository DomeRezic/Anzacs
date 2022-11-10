#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 128

struct Polinom;
typedef struct Polinom * Position;

typedef struct Polinom{

    int koef;
    int eks;
    Position  next;

} Poli;

int Read_file(Position P1, Position P2);
Position MakePol(int koef, int eks);
int ReadLine(Position head, char *buffer);
int ClearZero(Position head);
int InsertSorted(Position head, Position NewElement);
int InsertAfter(Position head, Position NewElement);
int Print(Position P);
int CleanUp(Position P);
int mnozenje(Position P1, Position P2);
int zbrajanje(Position P1, Position P2);



int main(){


    Poli head1 = { .koef = 0 , .eks = 0, .next = NULL };
    Poli head2 = { .koef = 0, .eks = 0, .next = NULL };

    Position P1 = &head1;
    Position P2 = &head2;

    int answer = 1;

	if( Read_file(P1,P2) != 0){
	perror("Ne radi lista");
	return -1;
	}

    while( answer != 0){


        printf("\nOdaberite broj ovisno o zeljenoj vrsti racunanja: \n");
        printf("Ispis binoma (1)\n");
        printf("UMNOZAK (2)\n");
        printf("zbroj je: (3)\n");
        printf(" Kraj (0)\n");
        printf("Unesite vas odabir:  ");
        scanf(" %d", &answer);



    switch (answer) // izbornik na kozoli za odabir nastavka izvrsavanja
    {

        case 0:
            printf("Program je prekinut !!");
            break;

        case 1:
            printf("\nPolinomi iz datoteke su :\n");
            printf("\n 1. RED: \n");
            Print(P1);
            printf("\n 2. RED: \n");
            Print(P2);

            break;

        case 2:
		mnozenje(P1,P2);

            break;
	    case 3:
		zbrajanje(P1,P2);

            break;

        default:
         printf("\nUnijeli ste broj koji nije poduden!\n");
         break;
        }
    }


    return 0;
}


int CleanUp(Position P){ // funkcija za ciscenje memorije

    Position temp = NULL;

    while(NULL != P -> next){
        temp = P -> next;
        P -> next = temp -> next;
        free(temp);
    }

    return 0;
}

Position MakePol( int koef, int eks){ // funkcija za sastavljanje polinoma

    Position New  = NULL;

    New = (Position) malloc (sizeof(Poli));

    New -> koef = koef;
    New -> eks = eks;
    New -> next = NULL;

    return New;
}


int Read_file(Position P1,Position P2){ // funkcija za citanje fajli

    FILE *fp = NULL;
    char buffer[MAX_SIZE] = { 0 };

    fp = fopen("polinom.txt","r");

    if( fp == NULL){
        printf("Datoteku nije moguce otvoriti!!");
        return -1;
    }


    fgets(buffer, MAX_SIZE, fp); // citanje redaka
    ReadLine(P1,buffer);
    ClearZero(P1);

    fgets(buffer, MAX_SIZE, fp);
    ReadLine(P2,buffer);
    ClearZero(P2);


    fclose(fp);

    return 0;
}

int ReadLine(Position head, char*buffer){ // funkcija za citanje redaka

    int koef,eks;
    int brojac = 0;
    int procitan_bb=0;

    // dok ima brojeva

    while( strlen(buffer) > 0){
        procitan_bb = sscanf(buffer, " %d  %d  %n ", &koef, &eks, &brojac);

        if(procitan_bb == 2 && koef != 0)
            InsertSorted(head, MakePol(koef,eks));  // sortiranje za brze izvodenje

         buffer += brojac;

    }

    return 0;
}

int InsertSorted( Position head, Position NewElement){ // funkcija za sortiranje

    // treba sortirati po potencijama od najvece do najmanje
    int n=0; // varijabla koja nam treba za provjeru je li koeficijent nula

    while( head -> next != NULL && head->next->eks < NewElement->eks){
        head = head -> next;
    }

    // ako su potencije iste odmah zbrojiti koeficijente
    if( head-> next != NULL && head->next->eks == NewElement->eks){
        head->next->koef += NewElement->koef;
        n=head->koef;

            if(n==0)
              ClearZero(head);
    }

    // ako je novi element manjeg eksponenta od ostalih samo ga stavi na pocetak liste
    else {
        MakePol(NewElement->koef, NewElement->eks );
        InsertAfter(head, NewElement);
    }

    return 0;
}


int ClearZero(Position head){ // brisanje 0 clanova
    Position temp = head;

    // Pomocna za brisanje
    Position Temp1 = NULL;

    while ( temp -> next != NULL){

        if (temp -> next -> koef == 0)
        {
            // DELETE == CleanUp
            Temp1 = temp -> next;
            temp -> next = Temp1 -> next;
            free(Temp1);
        }

        else{
            temp = temp -> next; // i++
        }

    }
    return 0;
}

int InsertAfter(Position head, Position NewElement){ // funkcija za repozicijoniranje elemenata

    NewElement -> next = head -> next;
    head -> next = NewElement;

    return 0;
}

int Print(Position P){ // print funkcija
    // od prvog clana
    Position temp = P -> next;

    // dok postoji
    while(temp){
        printf(" %dx^%d  \n", temp->koef , temp->eks);
        temp = temp-> next;  // i++
    }

    return 0;
}
int zbrajanje(Position p1,Position p2){ // funkcija za zbrajanje
	p1 = p1->next;
	p2 = p2->next;
	Position temp;
	int suma_koeficijent = 0;

	printf("zbroj je: \t\n");
	while(p1 != NULL && p2 != NULL){
		if(p1->eks == p2->eks){
			suma_koeficijent = p1->koef + p2->koef;
			printf("\t%dx^%d\n",suma_koeficijent,p1->eks);
			p1 = p1->next;
			p2 = p2->next;


		}
		else if(p1->eks > p2->eks){
			printf("\t%dx^%d\n",p2->koef,p2->eks);
			p2 = p2->next;

		}
		else{
    			printf("\t%dx^%d\n",p1->koef,p1->eks);
			p1 = p1->next;
		}
    }
	if(p1 == NULL)temp=p2;
	else if(p2 == NULL ){temp = p1;}
	while(temp != NULL){
		printf(" ovaj:\t%dx^%d",temp->koef,temp->eks);
		temp=temp->next;
	}
	return 0;

}

int mnozenje( Position p1, Position p2){ // funkcija za mnozenje
	int umnozak_koeficijenata = 1,zbroj_eksponenata=0;
	p1 = p1->next;
	p2 = p2->next;
	if(p1 == NULL){printf("null je");}
	while(p1 != NULL){
	umnozak_koeficijenata = umnozak_koeficijenata * p1->koef;
	zbroj_eksponenata = zbroj_eksponenata + p1->eks;
	printf("trenutno stanje : %dx^%d\n",umnozak_koeficijenata,zbroj_eksponenata);
	p1 = p1->next;

	}
	while(p2 != NULL){
	umnozak_koeficijenata = umnozak_koeficijenata * p2->koef;
	zbroj_eksponenata = zbroj_eksponenata + p2->eks;
	printf("trenutno stanje : %dx^%d\n",umnozak_koeficijenata,zbroj_eksponenata);
	p2 = p2->next;
	}
	printf("Rjesenje je : %dx^%d",umnozak_koeficijenata,zbroj_eksponenata);
	return 0;
}
