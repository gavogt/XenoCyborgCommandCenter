#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "file_io.h"

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

		// Open file in the specified mode
		if (mode) {
			// Open file in binary mode if mode is 1 and read file if mode is not 1
			FILE* file = fopen(fname, mode == 1 ? "rb" : "r");
			// Check if there is a file
			if (!file) {
				perror("Failed to open file");
				exit(EXIT_FAILURE);
			}
			else if (mode == 1) {
				// Read 1 item size of count from file store it in count
				if (fread(&count, sizeof(count), 1, file) == 1 &&
					count <= MAX_CYBORGS &&
					// Load all cyborgs into memory
					(fread(cyborgs, sizeof * cyborgs, count, file) == (size_t)count)) {
					// Successfully read cyborgs from binary file
					printf("Read %d cyborgs from binary file\n", count);
				}
				else {
					perror("Failed to read cyborgs from binary file");
					exit(EXIT_FAILURE);
				}

				fclose(file);
			}
		}
	}
}