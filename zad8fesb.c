#include<stdio.h>
#include<stdlib.h>

typedef struct Stablo * Position;

typedef struct Stablo{
    int El;
    Position L;
    Position D;
} stablo;

int System(){
 #ifdef LINUX_KEY_WORD

  #elif WINDOWS_KEY_WORD

  #else
     "OS not supported!";
  #endif

  return 0;
}


Position Unos(Position trenutni, Position q);
int PrintInOrder(Position trenutni);
int PrintPreOrder(Position trenutni);
int PrintPostorder(Position trenutni);
void printLevelOrder(Position root);
void printCurrentLevel(Position root, int level);
int height(Position node);
Position minValueNode(Position node);
Position deleteNode(Position root, int key);

int main(){

    Position root =NULL;
    Position  q = NULL;
    int answer,number,number_za_brisanje = 0;

    do {
        printf("\n********\n");
        printf("\nOdaberite zeljenu operaciju:\n");
        printf(" 1 -dodaj element u stablo\n");
        printf(" 2 -ispis elemenata <INORDER>\n");
        printf(" 3 -ispis elemenata <PREORDER>\n");
        printf(" 4 -ispis elemenata <POSTORDER>\n");
        printf(" 5 -ispis elemenata <LEVEL ORDER>\n");
        printf(" 6 -trazi i izbrisi element\n");
        printf(" 8 -exit\n");
        printf("\n********\n");

        printf("Unos: ");
        scanf("%d", &answer);

        system("cls");
        switch(answer){

            case 1:
                printf("Unesite broj koji zelite unijeti u stablo :\n");
                scanf("%d", &number);
                q = (Position)malloc(sizeof(stablo));
                q->El = number;

                root = Unos (root,q);
                break;

            case 2:
                printf("\n\t***ISPIS*\n");
                PrintInOrder(root);
                break;

            case 3:
                PrintPreOrder(root);
                break;

            case 4:
                PrintPostorder(root);
                break;
            case 5:
                printLevelOrder(root);
                break;
            case 6:
                printf("Unesite broj koji zelite izbrisati iz stabla :\n");
                scanf("%d", &number_za_brisanje);
                root = deleteNode(root,number_za_brisanje);
                break;
            case 8:
                return 0;

            default:
                printf("Unijeli ste krivi broj, pokusajte ponovno! :)\n");
        }

    } while( answer != '8');

    return 0;
}

Position Unos(Position trenutni, Position q){

    if(NULL == trenutni){
        return q;
    }

    else if(trenutni -> El < q->El){
        trenutni->D = Unos(trenutni->D,q);
    }

    else if(trenutni->El > q->El){
        trenutni->L = Unos(trenutni->L, q);
    }
    else
    free (q->El);

    return trenutni;
}


int PrintInOrder(Position trenutni){

    if(trenutni != NULL){
        PrintInOrder(trenutni->L);
        printf(" \t%d\n", trenutni->El);
        PrintInOrder(trenutni->D);
    }
    return 0;
}


int PrintPreOrder(Position trenutni){

    if(trenutni != NULL){
        printf(" %d\n", trenutni->El);
        PrintPreOrder(trenutni->L);
        PrintPreOrder(trenutni->D);
    }
    return 0;
}


int PrintPostorder(Position trenutni){

   if(trenutni){
        PrintPreOrder(trenutni->L);
        PrintPreOrder(trenutni->D);
        printf(" %d\n", trenutni->El);
    }
    return 0;
}


void printLevelOrder(Position root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}


void printCurrentLevel(Position root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->El);
    else if (level > 1) {
        printCurrentLevel(root->L, level - 1);
        printCurrentLevel(root->D, level - 1);
    }
}

int height(Position node)
{
    if (node == NULL)
        return 0;
    else {

        int lheight = height(node->L);
        int rheight = height(node->D);


        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}
Position deleteNode(Position root, int key)
{

	if (root == NULL)
		return root;

	if (key < root->El)
		root->L = deleteNode(root->L, key);

	else if (key > root->El)
		root->D = deleteNode(root->D, key);

	else {

		if (root->L == NULL) {
			Position temp = root->D;
			free(root);
			return temp;
		}
		else if (root->D == NULL) {
			Position temp = root->L;
			free(root);
			return temp;
		}


		Position temp = minValueNode(root->D);


		root->El = temp->El;


		root->D = deleteNode(root->D, temp->El);
	}
	return root;
}
Position minValueNode(Position node)
{
	Position current = node;


	while (current && current->L != NULL)
		current = current->L;

	return current;
}
