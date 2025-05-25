#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "file_io.h"

#define NAME_MAX 50
#define LINE_MAX 256
#define MAX_CYBORGS 10

void file_load(int argc, char* argv[], AlienCyborg** cyborgs, int* count, size_t* capacity) {
	// Get filename from argv
	if (argc > 1) {
		const char* fname = argv[1];

		// prompt for mode required
		char modeStr[LINE_MAX];
		int mode = 0;

		printf("Load '%s' as 1) binary or 2) text :", fname);

		// Read user's choice
		if (read_line(modeStr, sizeof modeStr))
			mode = (int)strtol(modeStr, NULL, 10); // Convert string to long then cast as integer

		if (mode != 1 && mode != 2) {
			puts("invalid choice");
			mode = 0;
		}

		// Open file in binary mode if mode is 1 and read file if mode is not 1
		FILE* file = fopen(fname, mode == 1 ? "rb" : "r");

		// Check if there is a file
		if (!file) {
			perror("Failed to open file");
			exit(EXIT_FAILURE);
		}

		// Open file in the specified mode
		if (mode == 1) {

			// Read 1 item size of count from file store it in count
			if (fread(count, sizeof * count, 1, file) != 1
				|| *count > MAX_CYBORGS
				|| fread(*cyborgs, sizeof * *cyborgs, *count, file) != (size_t)*count) {
					{
						perror("Failed to read cyborgs from binary file");
						exit(EXIT_FAILURE);
					}
			}
			printf("Read %d cyborgs from binary file\n", *count);
			fclose(file);
		}
		else {

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
		}
	}
}

