#ifndef file_io_h
#define file_io_h

#include "xeno_cyborg.h"

int file_load(int argc, char* argv[], AlienCyborg** cyborgs, int* count, size_t* capacity);
void file_save(const char* fname, int mode, AlienCyborg* cyborgs, int count);

#endif // !file_io_h
