#include <stdio.h>
#include <stdlib.h>

#include "util.h"
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
	printf("Enter your choice (1-6): ");

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

AlienCyborg MenuSwitch(int choice) {
	switch (choice) {
	case 1:
		return AddXenoCyborg();
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
		exit(EXIT_SUCCESS);
		break;
	default:
		EXIT_FAILURE;
	}
}

AlienCyborg AddXenoCyborg(void) {
	// Variable declarations
	AlienCyborg newCyborg;
	char buffer[50];

	// Initialize new cyborg to default scout
	CyborgRole role = (CyborgRole)0;

	printf("Enter ID: ");
	if (!read_line(buffer, sizeof(buffer))) exit(EXIT_FAILURE);
	newCyborg.id = atoi(buffer); // Convert string to integer

	printf("Enter Name: ");
	if (!read_line(newCyborg.name, sizeof(newCyborg.name))) exit(EXIT_FAILURE);

	printf("Enter Age: ");
	if (!read_line(buffer, sizeof(buffer))) exit(EXIT_FAILURE);
	newCyborg.age = atoi(buffer); // Convert string to integer

	// Choose role input
	while (1) {
		puts("Select Role:");
		puts("1) SCOUT");
		puts("2) WARRIOR");
		puts("3) ENGINEER");
		puts("4) MEDIC");
		printf("Enter your choice (1-4): ");

		if (!read_line(buffer, sizeof(buffer))) exit(EXIT_FAILURE);
		int roleChoice = atoi(buffer); // Convert string to integer

		if (roleChoice >= 1 && roleChoice <= 4) {
			newCyborg.role = (CyborgRole)(roleChoice - 1); // Convert to enum
			break;
		}
		else {
			printf(stderr, "Invalid choice. Please enter a number between 1 and 4.\n");
		}
	}

	// Confirm and print new cyborg
	puts("New Cyborg Details:");
	printf("ID: %d\n", newCyborg.id);
	printf("Name: %s\n", newCyborg.name);
	printf("Age: %d\n", newCyborg.age);
	printf("Role: %d\n", newCyborg.role);

	return newCyborg; // Return the new cyborg struct
}


