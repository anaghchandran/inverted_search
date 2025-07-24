
#include "invert.h"
#include <ctype.h>

int create_hash(hash *array, int size) 
{
    for (int i = 0; i < size; i++)    //creation of hash table
    {
	array[i].index = i;		//initialize index from 0 to 28
	array[i].link = NULL;		//main node address to NULL
    }
    return SUCCESS;
}

int read_from_file(slist **head, hash *array, int size) 
{

    char word[SIZE];
    if (*head != NULL) 
    {
	slist *temp = *head;
	while (temp != NULL) 
	{
	    FILE *fptr = fopen(temp->file_name, "r"); //open the file that inserted in linked list 
	    if (fptr != NULL) 
	    {
		while (fscanf(fptr, "%s", word) != EOF) //it will take one word from file
		{

		    //printf("%s ", word);
		    insert_hash(array, word, temp->file_name);
		}
		fclose(fptr); //after eof close file
	    } else 
	    {
		printf("error in read from file\n");
	    }
	    temp = temp->link;   //next file
	}
    }
    return SUCCESS;
}

int insert_hash(hash *array, char *word, char *file_name) 
{
    int index=0;
    if(word[0]>='a'&&word[0]<='z')        
    {
	index=word[0]-'a';
    }
    else if(word[0]>='A'&&word[0]<='Z') 
    {
	index=word[0]-'A';
    }
    else if(word[0]>='0'&&word[0]<='9') 
    {
	index=26;
    }
    else
    {	
	index=special_char;
    }


     m_node *new_m = malloc(sizeof(m_node));   //main node
    if (new_m == NULL)                       
	return FAILURE;

    strcpy(new_m->word, word);         //storing word to main node
    new_m->file_count = 1;	     //default filecount 1
    new_m->main_link = NULL;          // both main and sub to null
    new_m->sub_link = NULL;

    s_node *new_s = malloc(sizeof(s_node));       //sub node
    if (new_s == NULL) 
    {
	free(new_m);
	return FAILURE;
    }

    strcpy(new_s->file_name, file_name);   //store file name
    new_s->word_count = 1;			// set word count
    new_s->sub_link = NULL;		//sub link

    if (array[index].link == NULL)      // check that index have any mainnode addtrss
    {
	array[index].link = new_m;     //if not null the add main node address to hash table and main node sublink link to sub node link
	new_m->sub_link = new_s;

    }
    else 
    {
	m_node *temp = array[index].link;    // create temp to travesal 
	while (temp != NULL)                 //till end
	{
	    if (strcmp(word, temp->word) == 0)     // comparing word (from file) with word from main node 
	    {
		s_node *temps = temp->sub_link;    // create temps for sub node travesal and set to sub node like from main node
		while (temps != NULL) 
		{
		    if (strcmp(temps->file_name, file_name) == 0)   // compare file name and filename in sub node
		    {
			temps->word_count++;            // if same update word count
			free(new_m);
			free(new_s);
			return SUCCESS;
		    }
		    if (temps->sub_link == NULL)     // travel till null 
			break;
		    temps = temps->sub_link;
		}
		temps->sub_link = new_s;  //same word diff file 
		temp->file_count++;		// update file count in main node
		free(new_m);
		return SUCCESS;
	    }
	    if (temp->main_link == NULL) // word diff 
		break;
	    temp = temp->main_link; //travese to end
	}
	temp->main_link = new_m;
	new_m->sub_link = new_s;   //add new main node and sub node
    }
    return SUCCESS;

}

int display_database(hash *array, int size) 
{
    // Print the header with appropriate alignment
    printf("\nIndex\t\tWord\t\tFilecount\tFilename\tWordcount\n");
    printf("-------------------------------------------------------------------------------------\n");

    // Loop through the hash array
    for (int i = 0; i < size; i++) 
    {
	if (array[i].link != NULL) 
	{  // Only process entries with a main node
	    m_node *temp = array[i].link;
	    while (temp != NULL) 
	    {
		// Print the main node information
		printf("[%d]\t\t%-15s\t%-10d", array[i].index, temp->word, temp->file_count);

		if (temp->sub_link != NULL) 
		{
		    s_node *temps = temp->sub_link;  // Process the sub-nodes
		    while (temps != NULL) 
		    {
			// Print the sub-node information
			printf("\t%-20s %d", temps->file_name, temps->word_count);
			printf("\n\t\t\t\t\t");
			temps = temps->sub_link;
		    }
		}
		printf("\n");
		temp = temp->main_link;
	    }
	}
    }

    printf("-------------------------------------------------------------------------------------\n");
    return SUCCESS;
}


int search_data( hash *array, int size)
{
    char string[30];
    printf("\nenter the search data\n");   //take the data to search
    getchar();
    scanf("%[^\n]",string);

    int index = tolower(string[0]) - 'a';  //find the index 

    if( array[index].link == NULL)  //check index link
    {
	printf("\n---not found----\n");
	return 0;
    }
    else
    {
	m_node *temp=array[index].link;
	while( temp != NULL)
	{
	    if( strcmp( string, temp->word) ==0) //comparing
	    {
		printf("in index %d found search word %s in files\n",index, string);	//printing
		s_node *temp1=temp->sub_link;
		while( temp1 != NULL)
		{
		    printf("\n%s and word count: %d \n",temp1->file_name, temp1->word_count);  //print info in sub node
		    temp1=temp1->sub_link;
		}
		return 0;
	    }
	    temp=temp->main_link;
	}



    }
    printf("\nentered data %s not found\n",string);
    return FAILURE;
}

int save_data_base(hash *array, int size)
{
    char file[30];
    printf("enter the file name with .txt extention\n");
    getchar();
    scanf("%[^\n]",file);
    FILE *fptr = fopen(file, "w");    //open file in write mode
    if( fptr == NULL)
    {
	printf("provide a valid file\n");   //validation
	return FAILURE;
    }

    for( int i=0; i< size; i++)
    {
	if( array[i].link != NULL)
	{

	    m_node *temp=array[i].link;
	    while( temp != NULL)
	    {

		fprintf(fptr,"#%d;#%s;#%d;",i,temp->word,temp->file_count);     //saving it into file
		if( temp->sub_link != NULL)
		{
		    s_node *temps = temp->sub_link;
		    while( temps != NULL)
		    {
			fprintf(fptr,"#%s;#%d;",temps->file_name,temps->word_count);
			temps=temps->sub_link;
		    }
		}
		fprintf(fptr,"\n");
		temp= temp->main_link;
	    }
	}
    }
    fclose(fptr);
    return SUCCESS;
}


int update_data_base(hash *array, int size, slist **head)
{
    char buffer[100];
    char file[30];
    printf("enter the file name to update\n");
    getchar();
    scanf("%[^\n]",file);


    slist *temp=*head;
    while( temp != NULL)
    {
	if( strcmp(temp->file_name, file) == 0)
	{
	    return FAILURE;
	}
	temp=temp->link;
    }

    insert_at_last( head, file);


    char word[SIZE];
    if (*head != NULL) 
    {
	slist *temp = *head;
	slist *prev=NULL;
	while (temp != NULL) 
	{
	    prev=temp;
	    temp=temp->link;               //only taking the last added file else it over write with old values

	}
	FILE *fptr = fopen(prev->file_name, "r"); //open the file that inserted in linked list 
	if (fptr != NULL) 
	{
	    while (fscanf(fptr, "%s", word) != EOF) //it will take one word from file
	    {

		insert_hash(array, word, prev->file_name);
	    }
	    fclose(fptr); //after eof close file
	} else 
	{
	    printf("error in read from file\n");
	    return FAILURE;
	}
    }

    return SUCCESS;
}


