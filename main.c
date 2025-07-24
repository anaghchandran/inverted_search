#include "invert.h"

int main(int argc, char *argv[]) {
    slist *head = NULL;
    int size = 28;
    hash array[size];
    int choice, res;

    res = read_and_validate(argc, argv, &head);
    if (res == FAILURE) {
	printf("Validation failed\n");
	return FAILURE;
    }

    printf("Validation success\n");

    // Initialize the hash array
    create_hash(array, size);

    while (1) {
	// Display the menu options to the user
	printf("\nMenu:\n");
	printf("1. create database\n");
	printf("2. Display database\n");
	printf("3. Search data\n");
	printf("4. update database\n");
	printf("5. save data\n");
	printf("6. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) {
	    case 1:
		int res1= read_from_file(&head, array, size);
		if( res1 == SUCCESS)
		{
		    printf("\n----created-----\n");
		}
		else
		{
		    printf("\n----failed to create----\n");
		}
		break;
	    case 2:
		display_database(array, size);
		break;
	    case 3:
		search_data(array, size);
		break;
	    case 5:
		int res2 = save_data_base(array,size);
		if( res2 == SUCCESS)
		    printf("\n---data saved---\n");
		else
		    printf("\n-----failed to save-----\n");

		break;
	    case 4:
		int res3=update_data_base(array, size, &head);
		if( res3 == SUCCESS)
		    printf("\n-----updated------\n");
		else
		    printf("\n-----failed to update-----\n");
		break;
	    case 6:
		// Exit the program
		printf("\n---exit---\n");
		return SUCCESS;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    }
    return SUCCESS;
}

