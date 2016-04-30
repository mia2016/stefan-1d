#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void error_fatal(char * error_message) {
	fprintf(stderr, "\n\033[1;31mFATAL ERROR:\033[0m %s\n\n", error_message);
	exit(EXIT_FAILURE);
}

void error_warning(char * warning_message) {
    fprintf(stderr, "\n\033[1;33mWARNING:\033[0m %s\n\n", warning_message);
}
