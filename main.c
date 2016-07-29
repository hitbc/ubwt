#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ubwt2unipath.h"
#include "ubwt_index.h"
#include "ubwt_query.h"
#include "utils.h"

int usage(void)
{
    err_printf("\n");
	err_printf("Program: ubwt\n");
	err_printf("Usage:   ubwt <command> [options]\n\n");
	err_printf("Commands: \n");
	err_printf("         unipath     generate unipath seq from bwt-str\n");
    err_printf("         index       index unipath's bwt-str\n");
	err_printf("         query       query the unipath with the bwt index\n");
	err_printf("\n");
	return 1;
}

int main(int argc, char *argv[])
{
    if (argc < 2) return usage();
    if (strcmp(argv[1], "unipath") == 0)      return ubwt2unipath(argc-1, argv+1);
    else if (strcmp(argv[1], "index") == 0)   return ubwt_index(argc-1, argv+1);
	else if (strcmp(argv[1], "query") == 0)   return ubwt_query(argc-1, argv+1);
	else {
		fprintf(stderr, "[main] unrecognized command '%s'\n", argv[1]);
		return 1;
	}

    return 0;
}
