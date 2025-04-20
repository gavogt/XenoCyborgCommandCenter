#include <stdio.h>
#include <stdlib.h>
#include "xeno_cyborg.h"

int GetUserChoice() {
	// Variable declarations
	char buffer[50];
	int choice;

	// Print menu options
	puts("*** MENU OPTIONS ***");
	puts("1) Add new cyborg");
	puts("2) List cyborgs");
	puts("3) Search cyborgs");
	puts("4) Sort cyborgs");
	puts("5) Save & Exit");
	puts("6) Exit without saving");
	printf("Enter your choice: ");

	// Get User Choice
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character		
		choice = atoi(buffer); // Convert string to integer

		if (choice < 1 || choice > 6) {
			printf(stderr, "Invalid choice. Please enter a number between 1 and 6.\n");
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

MenuSwitch(int choice) {
	switch (choice) {
	case 1:
		AddXenoCyborg();
		break;
	case 2:
		// List cyborgs
		break;
	case 3:
		// Search cyborgs
		break;
	case 4:
		// Sort cyborgs
		break;
	case 5:
		// Save & Exit
		break;
	case 6:
		puts("Exiting....");
		EXIT_FAILURE;
		break;
	default:
		EXIT_FAILURE;
	}
}

AddXenoCyborg() {
	// Variable declarations
	AlienCyborg newCyborg;
	char buffer[50];

	CyborgRole role;

	printf("Enter ID: ");
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
		newCyborg.id = atoi(buffer); // Convert string to integer
	}
	else {
		printf(stderr, "Error reading id input\n");
		EXIT_FAILURE;
	}

	printf("Enter Name: ");
	if (fgets(newCyborg.name, sizeof(newCyborg.name), stdin) != NULL) {
		newCyborg.name[strcspn(newCyborg.name, "\n")] = '\0'; // Remove newline character
	}
	else {
		printf(stderr, "Error reading name input\n");
		EXIT_FAILURE;
	}

	printf("Enter Age: ");
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
		newCyborg.age = atoi(buffer); // Convert string to integer
	}
	else {
		printf(stderr, "Error reading age input\n");
		EXIT_FAILURE;
	}

	// Choose role input
}