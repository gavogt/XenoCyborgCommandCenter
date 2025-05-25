#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "file_io.h"

#define NAME_MAX 50
#define LINE_MAX 256
#define MAX_CYBORGS 10

void file_save(const char* fname, int mode, AlienCyborg* cyborgs, int count) {

	FILE* f = NULL;
	errno_t err = fopen_s(&f, fname, mode == 1 ? "w" : "wb");
	if (err != 0 || f == NULL) {
		char errbuf[256];
		strerror_s(errbuf, sizeof errbuf, err);
		fprintf(stderr, "Could not open save file '%s' in %s mode: %s\n",
			fname,
			(mode == 1 ? "text" : "binary"),
			errbuf);
		return;
	}


	if (mode == 1) {
		// Save in text mode
		for (int i = 0; i < count; i++) {
			fprintf(f, "%d,%s,%d,%s\n",
				cyborgs[i].id,
				cyborgs[i].name,
				cyborgs[i].age,
				CyborgRoleToString(cyborgs[i].role));
		}
	}
	else {
		// Save in binary mode
		if (fwrite(&count, sizeof count, 1, f) != 1 ||
			fwrite(cyborgs, sizeof * cyborgs, count, f) != (size_t)count);
		fclose(f);
	}
}

int file_load(int argc, char* argv[], AlienCyborg** cyborgs, int* count, size_t* capacity) {

	const char* fname;
	if (argc > 1) {
		// Get filename from argv
		fname = argv[1];
	}
	else {
		printf("No filename provided.\n");
		exit(EXIT_FAILURE);
	}

	// prompt for mode required
	char modeStr[LINE_MAX];
	int mode = 0;

	printf("Load as 1) text [%s]\nor 2) binary [%s]:\n", argv[1], argv[2]);

	// Read user's choice
	if (read_line(modeStr, sizeof modeStr))
		mode = (int)strtol(modeStr, NULL, 10); // Convert string to long then cast as integer

	if (mode != 1 && mode != 2) {
		puts("invalid choice");
		mode = 0;
	}

	if (mode == 1) {
		printf("Loading file '%s' in text mode\n", fname);
		fname = argv[1];
	}
	else if (mode == 2) {
		printf("Loading file '%s' in binary mode\n", fname);
		fname = argv[2];
	}
	else {
		puts("Invalid mode selected. Exiting.");
		exit(EXIT_FAILURE);
	}

	// Open file in binary mode if mode is 1 and read file if mode is not 1
	FILE* file = fopen(fname, mode == 2 ? "rb" : "r");

	// Check if there is a file
	if (!file) {
		perror("Failed to open file");
		exit(EXIT_FAILURE);
	}


	// Open file in the specified mode
	if (mode == 1) {

		// Open file in text mode/
		char line[LINE_MAX];
		while (fgets(line, sizeof(line), file)) {
			int id, age;
			char name[NAME_MAX];
			char roleBuf[32];

			// Parse CSV line into id, name, age, and role
			if (sscanf_s(line, "%d,%49[^,],%d,%31s", &id, name, (unsigned)NAME_MAX, &age, roleBuf, (unsigned)sizeof roleBuf) == 4)
			{
				// Grow the array if at capacity
				if (*count == *capacity) {
					size_t new_capacity = *capacity * 2;
					AlienCyborg* tmp = realloc(*cyborgs, *capacity * sizeof * *cyborgs);
					if (!tmp) {
						perror("Failed to reallocate memory");
						fclose(file);
						exit(EXIT_FAILURE);
					}
					*cyborgs = tmp;
					*capacity = new_capacity;
				}

				// Add new cyborg to the array
				(*cyborgs)[*count].id = id;
				strncpy_s(
					(*cyborgs)[*count].name,
					NAME_MAX,
					name,
					_TRUNCATE
				);
				(*cyborgs)[*count].age = age;
				(*cyborgs)[*count].role = StringToCyborgRole(roleBuf);
				(*count)++;
			}
			else {
				fprintf(stderr, "Malformed line: %s", line);
			}
		}
		printf("Read %d cyborgs from text file\n", *count);
		fclose(file);
		return 1;
	}
	else {

		// Open file in binary mode
		// Read 1 item size of count from file store it in count
		if (fread(count, sizeof * count, 1, file) != 1
			|| *count > MAX_CYBORGS) {
			perror("Failed to read count");
		}

		*capacity = *count;
		if (*capacity < 4) *capacity = 4; // Ensure minimum capacity
		*cyborgs = malloc(*capacity * sizeof * *cyborgs);
		if (!*cyborgs) {
			perror("Failed to allocate memory for cyborgs");
			fclose(file);
			exit(EXIT_FAILURE);
		}

		if (fread(*cyborgs, sizeof * *cyborgs, *count, file) != (size_t)*count) {
			perror("Failed to read cyborg data");
			fclose(file);
			exit(EXIT_FAILURE);
		}

		printf("Read %d cyborgs from binary file\n", *count);
		fclose(file);
		return 2;

	}

}

