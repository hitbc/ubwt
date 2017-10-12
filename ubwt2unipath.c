#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ubwt.h"
#include "utils.h"

int ubwt2unipath_usage(void)
{
    err_printf("\n");
    err_printf("Usage:    ubwt unipath [option] <BWT-STR>\n\n");
    err_printf("Options:\n\n");
    err_printf("    -t    [INT] Number of threads. [1]\n");
    err_printf("    -f    [STR] Format of input bwt-str. [B]\n"); 
    err_printf("                  \"B\": binary file, 4-bit per bp, 0/1/2/3/4:A/C/G/T/#(first 64-bit: length).\n");
    err_printf("                  \"P\": plain text.\n");
    err_printf("    -o    [STR] Output file(FASTA format). [stdout]\n");
    //err_printf("    -c    [INT] Chunk size of each run when t>1. [%d]\n", CHUNK_SIZE);
    err_printf("\n");
    return 1; 
}

int ubwt2unipath(int argc, char *argv[])
{
    int c; int input_b = 1; FILE *out = stdout;
    int t=1, chunk_size = CHUNK_SIZE;
    while ((c = getopt(argc, argv, "t:f:o:c:")) >= 0) {
        switch (c) {
            case 't': t = atoi(optarg); break;
            case 'f': if (optarg[0] == 'P') input_b = 0; break;
            case 'o': out = fopen(optarg, "w"); break;
            case 'c': chunk_size = atoi(optarg); break;
            default: return ubwt2unipath_usage();
        }
    }
    if (argc - 1 != optind) return ubwt2unipath_usage();
    char *fn = strdup(argv[optind]); ubwt_count_t ubwt_l;

    // read ubwt str
    uint8_t *ubwt_bstr = ubwt_read_bwt_str(fn, input_b, &ubwt_l);
    // init ubwt
    ubwt_t *ubwt = (ubwt_t*)_err_malloc(sizeof(ubwt_t));
    ubwt_init(ubwt, ubwt_l);
    ubwt_count_t uni_c = ubwt_cal(ubwt, ubwt_bstr, ubwt_l);
    ubwt_update(ubwt);
    // gen unipath
    ubwt_gen_unipath(ubwt, ubwt_bstr, uni_c, out, t, chunk_size);

    if (out) fclose(out); free(fn);
    free(ubwt->ubwt); free(ubwt); free(ubwt_bstr);
    return 0;
}
