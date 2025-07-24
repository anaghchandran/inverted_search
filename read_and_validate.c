#include "invert.h"

int read_and_validate(int argc, char *argv[], slist **head) 
{
    if (argc <= 1) 
    {
        printf("Invalid command line arguments\n"); //check user pass the file name 
        return FAILURE;
    }

    for (int i = 1; i < argc; i++) 
    {
        int flag = 1;
        char *str = strstr(argv[i], ".txt");      

        if (str != NULL && strcmp(str, ".txt") == 0 && (strlen(argv[i]) == 4 || strcmp(str, argv[i] + strlen(argv[i]) - 4) == 0))  //only takeing file with .txt extention
        {
            FILE *fptr = fopen(argv[i], "r");   //open in read mode
            if (fptr == NULL) 
            {
                printf("%s file does not exist\n", argv[i]);  //validation
                flag = 0;
            }
            else
            {
                fseek(fptr, 0, SEEK_END);
                long pos = ftell(fptr);        //checking file is empty or not
                fclose(fptr);

                if (pos == 0) 
                {
                    flag = 0;
                }
            }

            if (flag && remove_duplicate(head, argv[i]) == SUCCESS)    // calling function to remove duplicate file
            {
                if (insert_at_last(head, argv[i]) == SUCCESS)        //insert to single linked list if file is not repeating , not empty, and file existed
                {
                    printf("Inserted %s into linked list\n", argv[i]);
                }
                else
                {
                    printf("Failed to insert %s into linked list\n", argv[i]);
                }
            }
            else
            {
                printf("Duplicate or invalid file: %s\n", argv[i]);
                flag = 0;
            }
        }
        else
        {
            printf("Invalid file extension: %s\n", argv[i]);
            flag = 0;
        }

        if (!flag)
        {
            printf("Validation failed for: %s\n", argv[i]);
        }
    }
    return SUCCESS;
}

int insert_at_last(slist **head, char *data) 
{
    slist *new_node = malloc(sizeof(slist));  //create new node
    if (new_node == NULL)     
    {
        return FAILURE;   //validation
    }

    strcpy(new_node->file_name, data);    //copying 
    new_node->link = NULL;

    if (*head == NULL) 
    {
        *head = new_node;  //if no node
        return SUCCESS;
    }

    slist *temp = *head;
    while (temp->link != NULL)    //head have node
    {
        temp = temp->link;
    }
    temp->link = new_node;
    return SUCCESS;
}

int remove_duplicate(slist **head, char *argv)
{
    if (*head == NULL)
    {
        return SUCCESS;    //no node
    }

    slist *temp = *head;
    while (temp)
    {
        if (strcmp(temp->file_name, argv) == 0)    //comparing with already exist file in linked list
        {
            return FAILURE;	//return failure
        }
        temp = temp->link;   //incrementing
    }
    return SUCCESS;
}













