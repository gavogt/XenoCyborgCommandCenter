#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "ui.h"
#include "util.h"
#include "xeno_cyborg.h"

#define DATA_FILE "cyborgs.txt"
#define DATA_FILE_BINARY "cyborgs.bin"

int main(int argc, char* argv[]) {

	// Initialize variables
	int count = 0;
	size_t capacity = 0;
	AlienCyborg* cyborgs = malloc(capacity * sizeof * cyborgs);
	int choice = 0;

	// Print welcome message
	WelcomeMessage();

	FILE* touch = fopen(DATA_FILE, "a");
	if (touch == NULL) {
		perror("Failed to create or open data file");
		exit(EXIT_FAILURE);
	}


	FILE* touch_binary = fopen(DATA_FILE_BINARY, "a");
	if (touch_binary == NULL) {
		perror("Failed to create or open data file");
		exit(EXIT_FAILURE);
	}

	// Load File
	file_load(argc, argv, &cyborgs, &count, &capacity);

	while (1) {

		// first‐time allocation
		if (cyborgs == NULL) {
			capacity = 4; // Initial capacity
			cyborgs = malloc(capacity * sizeof * cyborgs);
			if (cyborgs == NULL) {
				perror("Failed to allocate memory");
				exit(EXIT_FAILURE);
			}
			else {
				printf("Memory allocated successfully\n");
			}
		}

		// Get user choice from menu
		choice = GetUserChoice();

		// Process user choice
		MenuSwitch(choice, &cyborgs, &capacity, &count);


	}


	return 1;
}

/*
Assignment: Alien Cyborg Command Core – main.c

Objective:
  Create a robust, menu‑driven C program to register, inspect, and persist
  a fleet of Alien Cyborgs. You’ll build on basic data management by adding:
	• Dynamic memory growth
	• Dual‑format file loading/saving (text & binary)
	• Search and sort functionality
	• Age‑based classification
	• Rigorous error checks and input sanitization

Hints & Tasks:

1. Data Model
   – Define an enum for cyborg roles.
   – Define a struct for each cyborg with at least: ID, name, age, role.
   – Think about how you’ll map enum values to human‑readable strings later.

2. Dynamic Array Storage
   – Start with a `NULL` pointer, zero count & capacity.
   – On first add, allocate a small block (e.g., capacity = 4).
   – When full, double capacity via `realloc`.
   – Always check for allocation failures.

3. Startup File Loading
   – Read the target filename from `argv`.
   – Prompt user for “binary or text” mode.
   – In binary mode: read count, then raw structs.
   – In text mode: parse lines of comma‑separated values.
   – If file is missing or malformed, proceed with an empty list.

4. Main Menu Loop
   – Present numbered options until “Exit”:
	   1) Add new cyborg
	   2) List cyborgs
	   3) Search cyborgs
	   4) Sort cyborgs
	   5) Save & Exit
	   6) Exit without saving
   – Read exactly one character per choice; reject invalid input.

5. Add New Cyborg
   – Prompt for ID (int), name (string), age (int), and role (enum).
   – Sanitize each entry and clear stray input.
   – Grow storage if needed, then store the new record.

6. List Cyborgs with Age Category
   – For each record, determine “Minor/Adult/Senior” from age.
   – Print ID, name, age, category, and role name.

7. Search Functionality
   – Ask user: search by ID or by role.
   – For ID: scan for a matching integer.
   – For role: scan for matching enum value.
   – Display found entries using the same format as “List.”

8. Sort Functionality
   – Ask user: sort by ID or by name.
   – Implement comparison callbacks.
   – Call `qsort()` on your array of pointers.

9. Save & Exit
   – Based on initial mode, open file in “wb” or “w”.
   – In binary: write count and raw structs.
   – In text: write lines of comma‑separated fields.
   – Check every return value (`fopen`, `fwrite`, `fprintf`, etc.).
   – Free all allocated memory before exiting.

10. Exit Without Saving
   – Skip file operations.
   – Still free all memory before exiting.

11. Error Handling & Validation
   – After every I/O or allocation call, test for errors.
   – Use `perror()` (or similar) to report failures.
   – Always clear the input buffer when mixing `scanf`/`fgets`.

12. Documentation
   – At the top of `main.c`, include your name, date, and a one‑line
	 summary of the program’s purpose.
   – Before each logical block (loading, menu, add, list, search, sort,
	 save, cleanup), write a brief comment explaining its role.

Stretch Goals (Optional):
  – Replace the array with a linked list.
  – Add a union inside your struct for role‑specific stats.
  – Allow CLI flags to set initial capacity or force text/binary mode.
  – Implement unit tests for search & sort routines in a separate file.
*/