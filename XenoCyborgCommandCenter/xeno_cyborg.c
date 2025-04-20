#include <stdio.h>
#include <stdlib.h>
#include "xeno_cyborg.h"

GetUserChoice() {
	// Variable declarations
	char buffer[50];
	int choice;

	puts("*** MENU OPTIONS ***");
	puts("1) Add new cyborg");
	puts("2) List cyborgs");
	puts("3) Search cyborgs");
	puts("4) Sort cyborgs");
	puts("5) Save & Exit");
	puts("6) Exit without saving");
	printf("Enter your choice: ");

	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character		
		choice = atoi(buffer); // Convert string to integer

		if (choice < 1 || choice > 6) {
			fprintf(stderr, "Invalid choice. Please enter a number between 1 and 6.\n");
			EXIT_FAILURE;
		}
		else {
			printf("You selected option %d\n", choice);
			return choice;
		}
	}
	else {
		fprintf(stderr, "Error reading input\n");
		EXIT_FAILURE;
	}
}