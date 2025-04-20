#include <stdio.h>
#include <string.h>
#include "util.h"

// Read line from stdin, strip newline, replace with null terminator, return 1 on sucesss
int read_line(char* buffer, size_t length) {
	if (fgets(buffer, (int)length, stdin) == NULL) return 0;
	buffer[strcspn(buffer, "\n")] = '\0'; // Replace newline with null terminator
	return 1;

}
