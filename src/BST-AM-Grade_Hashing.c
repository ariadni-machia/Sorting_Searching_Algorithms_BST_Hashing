#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int M=19; // numder of students
const int m=11; // number of buckets - Hashing
const int num_am=8; // number of char in an AM

typedef struct student{
    char AM[9];
    char name[13];
    char surname[17];
    float grade;
} student;

int amcmp(char am1[], char am2[]){ // am1>am2 -> +1 | am1<am2-> -1 | am1==am2-> 0
    int j=0, k=0;
    	while(j<9){
    		if( (am1[k]) == (am2[k])){
				k++;
				if(k==9){
					return 0;
				}
			}
			else if( (am1[k]) > (am2[k]) ){
				return 1;
			}
			else{ // (am1[k]) < (am2[k])
				return -1;
			}

		}
}

void readFile (student *ar){
	FILE *fptr;
    fptr = fopen("vathmoi.txt", "r");
    if(fptr == NULL)
   {
      printf("Error! There is no such file\n");
      exit(1);
   }
    int i=0;

    while(!feof(fptr)){
        fscanf(fptr, "%s %s %s %f", ar[i].AM , ar[i].name , ar[i].surname , &ar[i].grade );
        i++;
    }
    fclose(fptr);
}
// BST_AM
typedef struct bin_tree_AM {
student data;
struct bin_tree_AM *right, *left;
}node; //node=tree

node* min_node(node *root){
    if(root == NULL)
        return NULL;
    else if(root->left != NULL) // o kombos me to mikrotero AM den 8a exei aristero paidi
        return min_node(root->left); // o pio aristeros kombos 8a exei to mikrotero AM
    return root;
}

void insert(node ** tree, student st){
	int x;
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left =NULL;
        temp->right = NULL;
        temp->data=st;
        *tree= temp;
        return;
    }
	x = amcmp(st.AM, (*tree)->data.AM);
    if(x==-1) // st.AM < (*tree)->data
    {
        insert(&(*tree)->left, st);
    }
    else if(x==1) //st.AM > (*tree)->data
    {
        insert(&(*tree)->right, st);
    }
    else{
    	printf("Error with the insertion\n");
	}

}

node* delnode(node* root, char delam[]){
    //psaxnw to AM pou 8elw na diagrapsw
    if(root==NULL)
        return NULL;
    int x= amcmp(delam, root->data.AM);
    if (x==1) //delam>root->data.AM
        root->right= delnode(root->right, delam);
    else if(x==-1) //delam<root->data
        root->left= delnode(root->left, delam);
    else
    {
    	//Yparxoyn 3 periptwseis kombwn pros diagrafh:
        //Xwris paidia
        if(root->left==NULL && root->right==NULL){
            printf("The student with the AM: ");
			free(root);
            return NULL;
        }

        //Ena paidi
        else if(root->left==NULL || root->right==NULL){
            node *temp;
            if(root->left==NULL)
                temp = root->right;
            else
                temp = root->left;
            printf("The student with the AM: ");
            free(root);
            return temp;
        }

        //Duo paidia
        else
        {
            node *temp = min_node(root->right); //sunarthsh pou epistrefei ton kombo me thn mikrotero AM
            root->data = temp->data;
            root->right = delnode(root->right, temp->data.AM);
        }
    }
    return root;

}

node* search(node ** tree, char am[]){
	int x=0;
    if(!(*tree))
    {
        return NULL;
    }
	x = amcmp(am, (*tree)->data.AM);
    if(x==-1)//val < (*tree)->data
    {
        search(&((*tree)->left), am);
    }
    else if(x==1) //val > (*tree)->data
    {
        search(&((*tree)->right), am);
    }
    else if(x==0)//val == (*tree)->data
    {
        return *tree;
    }
}

void print_BST_inorder(node *root){
    if(root==NULL)
    	return;
    print_BST_inorder(root->left);
    printf("%s %s %s %f\n", root->data.AM, root->data.name, root->data.surname, root->data.grade);
    print_BST_inorder(root->right);
}

void alternation_mode(node* search_result){
	if(search_result==NULL)
	   printf("\nThe student was NOT found.\n");
	else{
		printf("The student was found.");
		int option2=0;
		while(option2!=4){
			printf("\nHis/Her current information are:\nAM:\t  %s\nName:\t  %s\nSurname:  %s\nGrade:\t  %f\n", search_result->data.AM, search_result->data.name, search_result->data.surname, search_result->data.grade);
			printf("Press < 1 > for altering his/her name.\n");
			printf("Press < 2 > for altering his/her surname.\n");
			printf("Press < 3 > for altering his/her grade.\n");
			printf("Press < 4 > if do NOT want to make any alterations.\n");
			printf("Your choice is: ");
			scanf("%d",&option2);
			switch(option2){
				case 1: printf("Give new name: ");
						char newname[20];
						scanf("%s", newname);
						strcpy(search_result->data.name,newname);
						break;
				case 2: printf("Give new surname: ");
						char newsurname[20];
						scanf("%s", newsurname);
						strcpy(search_result->data.surname,newsurname);
						break;
				case 3: printf("Give new grade: ");
						float newgrade;
						scanf("%f",&newgrade);
						search_result->data.grade=newgrade;
						break;
				case 4: printf("Exiting alteration mode.\n");
						return;
				default:printf("Wrong input. Try again.\n");
						break;
			}
		}
		return;
	}
}

int choose_BST_AM(){
	int choice=0;
	printf("\n");
	printf("Press < 1 > to print the BST in inorder crossing.\n"); // Πατήστε < 1 > για απεικόνιση ΔΔΑ με ενδο-διατεταγμένη διάσχιση.
    printf("Press < 2 > to search for a student by AM.\n"); // Πατήστε < 2 > για αναζήτηση ενός φοιτητή με βάση το ΑΜ του
    printf("Press < 3 > to alter a student's information.\n"); //Πατήστε < 3 > για τροποιήση στοιχείων ενός φοιτητή
    printf("Press < 4 > to delete a student.\n"); // Πατήστε < 4 > για διαγραφή ενός φοιτητή
    printf("Press < 5 > to exit this app.\n"); // Πατήστε < 5 > για έξοδο από την εφαρμογή
    printf("Your choice is: ");
    scanf("%d", &choice);
    printf("\n");
    return choice;
}

int main_BST_AM(){
	//anagnwsh arxeiou
    student *pst; //pointer student
    pst = (student*) malloc(M * sizeof(student));
    readFile(pst); // anagnwsh toy arxeiou | metafora plhrofias toy arxeioy sto pointer pst

    int i=0;

	node *root= NULL;
	for(i=0;i<M;i++){
		insert(&root, pst[i]);
	}

	int option = 0;
	while(option!=5){
		option= choose_BST_AM();
		char requested_am[9];
	    node* search_result;
		switch (option){
	       case 1:  printf("You chose No 1: print the BST in inorder crossing.\n\n");
		   			print_BST_inorder(root);
	                break;
	       case 2:  printf("You chose No 2: search for a student by his/her AM.\n\n");
					printf("Give the AM you want to search: ");
		   			scanf("%s",requested_am);
		   			search_result=search(&root,requested_am);
		   			if(search_result==NULL)
					   printf("\nThe student was NOT found.\n");
					else
		   				printf("\nThe student was found. His/Her information are:\nAM:\t  %s\nName:\t  %s\nSurname:  %s\nGrade:\t  %f\n", search_result->data.AM, search_result->data.name, search_result->data.surname, search_result->data.grade);
	                break;
	       case 3:  printf("You chose No 3: alter a student's information.\n\n");
		   			printf("Give the student's AM: ");
					scanf("%s",requested_am);
					search_result=search(&root,requested_am);
					alternation_mode(search_result);
	                break;
           case 4:  printf("You chose No 4: delete a student.\n\n");
 					printf("Give the student's AM: ");
					scanf("%s",requested_am);
					root= delnode(root,requested_am);
					printf("%s was successfully deleted.\n",requested_am);
        			break;
           case 5:  printf("Exiting the BST by AM...\n----------------------\n");
           			break;
	       default: printf("Wrong input. Try again.\n");
	                break;
	    }


	}
	free(pst);
    return 0;
}

//END - BST_AM

//BEGIN - BST_GRADE

struct bin_tree_grade {
student data;
struct bin_tree_grade * right, * left, * inside;//deiktes se kombous de3ia, aristera kai mesa
};										// mesa 8a einai osoi komboi exoun idio ba8mo
typedef struct bin_tree_grade nod;

void insert_BST_GRADE(nod ** tree, student st)
{
    nod *temp = NULL;
    if(!(*tree))
    {
        temp = (nod *)malloc(sizeof(nod));
        temp->left = NULL;
        temp->right = NULL;
        temp->inside = NULL;
        temp->data=st;
        *tree= temp;
        return;
    }
    if(st.grade < (*tree)->data.grade)
    {
        insert_BST_GRADE(&(*tree)->left, st);
    }
    else if(st.grade > (*tree)->data.grade)
    {
        insert_BST_GRADE(&(*tree)->right, st);
    }
    else if(st.grade == (*tree)->data.grade){
    	insert_BST_GRADE(&(*tree)->inside, st);
	}
    else{
    	printf("Error with the insertion\n");
	}

}

nod* min_student(nod *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left != NULL) // o kombos me to mikrotero AM den 8a exei aristero paidi
        return min_student(root->left); // o pio aristeros kombos 8a exei to mikrotero ba8mo
    return root;
}

nod* max_student(nod *root)
{
    if(root == NULL)
        return NULL;
    else if(root->right != NULL) // o kombos me to megalutero AM den 8a exei de3i paidi
        return max_student(root->right); // o pio de3ia kombos 8a exei to megalutero ba8mo
    return root;
}

int main_BST_GRADE(){
	//anagnwsh arxeiou
    student *pst; //pointer student
    pst = (student*) malloc(M * sizeof(student));
    readFile(pst);
    int i=0;

	nod *root= NULL;
	for(i=0;i<M;i++){
		insert_BST_GRADE(&root, pst[i]);
	}
	//print_BST_inorder(root); ////gia tsekarisma ta ektupwnw

	nod* min_node= NULL;
	nod* max_node= NULL;
	int option = 0;
	//printf("Welcome to the BST by grade. Choose one of the options below:\n");
	while(option!=3){
		printf("\n");
		printf("Press < 1 > to find the student/s with the minimum grade.\n");
	    printf("Press < 2 > to find the student/s with the maximum grade.\n");
	    printf("Press < 3 > to exit BST by grade.\n");
	    printf("Your choice is: ");
	    scanf("%d", &option);
	    printf("\n");
		switch (option){
	       case 1:  printf("The student/s with the minimum grade is/are:\n");
					min_node=min_student(root);
					do{
						printf("- %s %s %s %f\n", min_node->data.AM, min_node->data.name, min_node->data.surname, min_node->data.grade);
						min_node= min_node->inside;
					}while( min_node != NULL);
	                break;
	       case 2:	printf("\nThe student/s with the maximum grade is/are:\n");
					max_node=max_student(root);
					do{
						printf("- %s %s %s %f\n", max_node->data.AM, max_node->data.name, max_node->data.surname, max_node->data.grade);
						max_node=max_node->inside;
					}while(max_node != NULL);
					break;
			case 3:	printf("Exiting the BST_GRADE...\n---------------------\n");
           			break;
	    	default:printf("Wrong input. Try again.\n");
	                break;
	    }
	}
	free(pst);
	return 0;
}

//END - BST_GRADE

//BEGIN - HASHING
typedef struct LinkedList {
	student st;
	struct LinkedList *next;
}LinkedList;

int AM_to_key(char am[]){
    int i=0, ascii=0, tascii=0, key=0;
    for(i=0; i<num_am; i++) {
        ascii = toascii(am[i]);
        tascii = ascii + tascii;
    }
    key = tascii % m;
    return key;
}

void createHashTable(LinkedList **hTable,student *stud){
	int i=0, key=0;
	for(i=0;i<M;i++){
		LinkedList *new_node, *temp;
		new_node=(LinkedList*)malloc(sizeof(LinkedList));
		new_node->st = stud[i];
		new_node->next=NULL;
		key=AM_to_key(new_node->st.AM); // briskw to kleidi
		if(hTable[key]== NULL){ // an einai adeia h 8esh toy pinaka
			hTable[key]=new_node;
		}
		else{ // an deixnei hdh se kombo
			temp=hTable[key]; // SWAP // temp deixnei ekei poy deixnei kai o hTable[key], dld ston uparxon kombo
			new_node->next=temp; // o new_node deixnei ston temp
			hTable[key]=new_node; // o hTable deixnei sto new_node
		}
	}
}

LinkedList* search_hashing(LinkedList **hTable, char am[], bool show_text){
	int key=0;
	LinkedList *temp1, *found_student=NULL;
	int found=1; // 1= DEN bre8hke | 0= bre8hke

	key= AM_to_key(am);
	temp1= hTable[key]; // temp1 deixnei ston prwto kombo
	while(temp1!=NULL && found!=0){
		found=amcmp(temp1->st.AM, am);
		if(found==0) // bre8hke o ma8hths kai kanoume break na bgei apo thn while kai 3eroume oti oi plhrofories tou ma8hth einai ston temp1
			found_student=temp1;
		temp1= temp1->next;
	}
	if(show_text==true)	{
		if(found==0)
			printf("The student was found. His/Her information is:\n%s %s %s %f\n", found_student->st.AM , found_student->st.name , found_student->st.surname , found_student->st.grade);
		else
			printf("The student was NOT found. There is no student register with AM: %s\n", am);
	}
	return found_student;
}

void alter(LinkedList **hTable, char am[]){
	LinkedList* search_result;
	search_result=search_hashing(hTable, am,false); // epistrefei 0 ean brhke ton ma8hth

	if(search_result==NULL)
	   printf("\nThe student was NOT found. There is no student register with AM: %s\n", am);
	else{
		printf("The student was found.");
		int option=0;
		while(option!=4){
			printf("\nHis/Her current information are:\nAM:\t  %s\nName:\t  %s\nSurname:  %s\nGrade:\t  %f\n", search_result->st.AM, search_result->st.name, search_result->st.surname, search_result->st.grade);
			printf("Press < 1 > for altering his/her name.\n");
			printf("Press < 2 > for altering his/her surname.\n");
			printf("Press < 3 > for altering his/her grade.\n");
			printf("Press < 4 > if do NOT want to make any alterations.\n");
			printf("Your choice is: ");
			scanf("%d",&option);
			switch(option){
				case 1: printf("Give new name: ");
						char newname[20];
						scanf("%s", newname);
						strcpy(search_result->st.name,newname);
						break;
				case 2: printf("Give new surname: ");
						char newsurname[20];
						scanf("%s", newsurname);
						strcpy(search_result->st.surname,newsurname);
						break;
				case 3: printf("Give new grade: ");
						float newgrade;
						scanf("%f",&newgrade);
						search_result->st.grade=newgrade;
						break;
				case 4: return;
				default:printf("Wrong input. Try again.\n");
						break;
			}
		}
		return;
	}
}

void delete_student(LinkedList **hTable, char am[]){
	int found=1;
	int key=0;
	LinkedList *temp1, *temp2;
	key=AM_to_key(am);
	found=amcmp(hTable[key]->st.AM,am); // epistrefei 0 ean ta AM einai idia
	if(found==0){ // 8eloume na diagrapsoyme ton prwto kombo
		temp1=hTable[key]; // temp1 deixnei ston kombo pou 8eloume na diagrapsoume
		hTable[key]=hTable[key]->next; //hTable[key] deixnei ston epomeno kombo
		free(temp1); // eleu8erwnoume ton pointer temp1 dhladh diagrafoume ton kombo pou 8eloume na diagrapsoume
		printf("\nThe student with AM: %s, was successfully deleted.\n", am);
		return;
	}
	else{
		temp1=hTable[key]->next;
		temp2=hTable[key]; // temp2 deixnei se prhgoumeno kombo
		while(temp1!=NULL && found!=0){
			found=amcmp(temp1->st.AM,am);
			if(found==0){
				temp2->next=temp1->next;
				free(temp1);
				printf("\nThe student with AM: %s, was successfully deleted.\n", am);
				return;
			}
			temp2=temp1;
			temp1=temp1->next;
		}
	}
	if(temp1==NULL && found==0){
		printf("\nDeleting the student with AM: %s, was not possible because was not found.\n", am);
	}
	return;
}

void print_hash_table(LinkedList **hTable){
	LinkedList *tempTable;
	int j=0;

	tempTable=(LinkedList*)malloc(sizeof(LinkedList)); //8a deixnei se ka8e grammh sou hTable

	printf("[KEY] -  Hash Table  - \n\n");
	for(j=0; j<m; j++){
		tempTable=hTable[j];
        printf("| %d |\t->\t%s\t",j, tempTable);
		while(tempTable!=NULL){
			printf("->\t%s\t", tempTable->next);
			tempTable= tempTable->next;
		}
        printf("\n");
    }
}

int choose_hashing(){
	int choice=0;
	printf("\n");
    printf("Press < 1 > to search for a student by AM.\n");
    printf("Press < 2 > to alter a student's information.\n");
    printf("Press < 3 > to delete a student.\n");
    printf("Press < 4 > to exit the Hash Table Chaining.\n");
    printf("Press < 5 > to print the Hash Table.\n");
    printf("Your choice is: ");
    scanf("%d", &choice);
    printf("\n");
    return choice;
}

int main_HASHING() {
    student *pst; //pointer student
    pst = (student*) malloc(M * sizeof(student));
    readFile(pst); // anagnwsh toy arxeiou | metafora plhrofias toy arxeioy sto pointer pst
    int i=0, j=0;
    int key=0; // to kleidi
    int option = 0; // h epilogh toy xrhsth gia to menu
    char given_am[9]; // to am poy dinei o xrhsths apo to plhktrologio

    LinkedList **hTable; // Hash Table
    hTable= (LinkedList**)malloc(m*sizeof(LinkedList*));
    for(i=0; i<m; i++) {
	hTable[i] = (LinkedList*)malloc(m*sizeof(LinkedList));
    }

    for(j=0; j<m; j++){
    		hTable[j]=NULL;
    }

	createHashTable(hTable,pst); // Gemisma hTable me Linked List

	while(option!=4){
		option= choose_hashing();
		switch (option){
	       case 1:  printf("Give the student's AM you want to search: ");
				    scanf("%s",given_am);
				    search_hashing(hTable, given_am,true); // kalw thn sunarthsh search
	                break;
	       case 2:  printf("Give the student's AM you want to alter his/her information: ");
				    scanf("%s",given_am);
				    alter(hTable, given_am);
	                break;
	       case 3:  printf("Give the student's AM you want to delete: ");
		   			scanf("%s",given_am);
    				delete_student(hTable, given_am);
	                break;
           case 4:  printf("Exiting the Hash Table Chainig...\n------------------");
		   			break;
           case 5:  print_hash_table(hTable);
           			break;
	       default: printf("Wrong input. Try again.\n");
	                break;
	    }
	}
	free(pst);
	return 0;
}
//END - HASHING

// MAIN
int main() {
	int choice1=0;
	int choice2=0;

	printf("Welcome to the app. Choose one of the options below:\n\n");
	while(choice1!=3){
		printf("\nDo you want to load your file?\nPress < 1 > if you want with a BST\nPress < 2 > if you want with a Hash Table Chainig?\nPress < 3 > if you to exit the app\n");
		printf("Your choice is: ");
	    scanf("%d", &choice1);
		switch (choice1){
	       case 1:  choice2=0;
                    while(choice2!=1 && choice2!=2){
				       	printf("\nDo you to be based by the student's AM or by their grade?\nPress < 1 > if you to by the AM\nPress < 2 > if you to by the grade\nPress < 3 > if you to exit the BST\n");
                        printf("Your choice is: ");
                        scanf("%d", &choice2);
                        if(choice2==1)
                            main_BST_AM();
                        else if(choice2==2)
                            main_BST_GRADE();
                        else if(choice2==3)
                             break;
                        else
                            printf("Wrong input. Try again.\n");
					}
	                break;
	       case 2:  main_HASHING();
                    break;
	       case 3:  printf("\nExiting the app...\n------------------\n\n");
		   			break;
	       default: printf("Wrong input. Try again.\n");
	                break;
	    }
	}
	//system("pause");
	return 0;
}
