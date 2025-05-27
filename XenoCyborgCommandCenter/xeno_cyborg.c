#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
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
	if (!read_line(buffer, sizeof(buffer))) exit(EXIT_FAILURE);
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

void MenuSwitch(int choice, AlienCyborg** cyborgs, int* capacity, int* count, const char* save_fname, int save_mode)
{
	switch (choice) {
	case 1: {

		// create new cyborg
		AlienCyborg newCyborg = AddXenoCyborg();

		if (newCyborg.id != 0) {
			// grow if needed
			if (*count == *capacity) {
				*capacity *= 2; // Double capacity
				AlienCyborg* tmp =
					realloc(*cyborgs, *capacity * sizeof * *cyborgs);
				if (!tmp) {
					perror("Failed to reallocate memory");
					exit(EXIT_FAILURE);
				}
				*cyborgs = tmp;
			}

			// Display Age
			DetermineAge(&newCyborg); // Determine age based on role

			// store cyborgs and increment count
			(*cyborgs)[(*count)++] = newCyborg;
			printf("Cyborg added successfully. Total cyborgs: %d\n", *count);
		}
	}
		  break;

	case 2:
		ListXenoCyborgs(*cyborgs, *count);
		break;
	case 3:
		SearchCyborgs(*cyborgs, *count);
		break;
	case 4: {
		char buffer[4];
		puts("Sort by: \n1) ID\n2) Name");
		if (read_line(buffer, sizeof buffer)) {
			if (buffer[0] == '1') {
				SortCyborgsByID(*cyborgs, *count);
				puts("Cyborgs sorted by ID.");
			}
			else if (buffer[0] == '2') {
				SortCyborgsByName(*cyborgs, *count);
				puts("Cyborgs sorted by Name.");
			}
			else {
				puts("Invalid choice. Please enter 1 or 2.");
			}

			ListXenoCyborgs(*cyborgs, *count);
		}
	}
		  break;

	case 5:
		file_save(save_fname, save_mode, *cyborgs, *count); // Save in binary format
		exit(EXIT_SUCCESS);
		break;
	case 6:
		puts("Exiting....");
		exit(EXIT_SUCCESS);
		break;
	default:
		puts("You entered an invalid choice.");
		break;
	}
}

static int CmpByID(const void* a, const void* b) {
	const AlienCyborg* c1 = a, * c2 = b;
	return c1->id - c2->id; // Compare by ID
}

static int CmpByName(const void* a, const void* b) {
	const AlienCyborg* c1 = a, * c2 = b;
	return strcmp(c1->name, c2->name); // Compare by Name
}

// Function to sort cyborgs by ID
void SortCyborgsByID(AlienCyborg* cyborgs, int count) {
	qsort(cyborgs, count, sizeof * cyborgs, CmpByID);
}

// Function to sort cyborgs by name
void SortCyborgsByName(AlienCyborg* cyborgs, int count) {
	qsort(cyborgs, count, sizeof * cyborgs, CmpByName);
}

// Function to search for cyborgs by name
void SearchCyborgs(const AlienCyborg* cyborgs, int count) {
	char query[50];
	puts("Enter name to search for:");
	if (!read_line(query, sizeof(query))) exit(EXIT_FAILURE);

	bool found = false;

	for (int i = 0; i < count; i++) {
		if (strcmp(cyborgs[i].name, query) == 0) {
			printf("Found Cyborg: ID: %d, Name: %s, Age: %d, Role: %s\n",
				cyborgs[i].id, cyborgs[i].name, cyborgs[i].age,
				CyborgRoleToString(cyborgs[i].role));
			found = true;
		}
	}
	if (!found) {
		puts("No cyborgs found with that name.");
	}
	else {
		puts("Search completed.");
	}
}

CyborgRole StringToCyborgRole(const char* str) {
	if (strcmp(str, "SCOUT") == 0) return SCOUT;
	else if (strcmp(str, "WARRIOR") == 0) return WARRIOR;
	else if (strcmp(str, "ENGINEER") == 0) return ENGINEER;
	else if (strcmp(str, "MEDIC") == 0) return MEDIC;
	else return -1; // Invalid role
}

const char* CyborgRoleToString(CyborgRole role) {
	switch (role) {
	case SCOUT:    return "SCOUT";
	case WARRIOR:  return "WARRIOR";
	case ENGINEER: return "ENGINEER";
	case MEDIC:    return "MEDIC";
	default:       return "UNKNOWN";
	}
}

void ListXenoCyborgs(const AlienCyborg* cyborgs, int count) {
	if (count == 0) {
		puts("No cyborgs to display.");
		return;
	}
	puts("Cyborg List:");
	for (int i = 0; i < count; i++) {
		printf("ID: %d, Name: %s, Age: %d, Role: %s\n",
			cyborgs[i].id, cyborgs[i].name, cyborgs[i].age, CyborgRoleToString(cyborgs[i].role));
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

void DetermineAge(AlienCyborg *cyborg) {
	if (cyborg->age < 18) {
		puts("Age Category: Minor");
	}
	else if (cyborg->age < 65) {
		puts("Age Category: Adult");
	}
	else {
		puts("Age Category: Senior");
	}
}

