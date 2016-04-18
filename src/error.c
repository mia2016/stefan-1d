#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void error_fatal(char * error_message) {
	fprintf(stderr, "\n\033[1;31mFATAL ERROR:\033[0m %s\n", error_message);
	exit(EXIT_FAILURE);
}
