#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ubwt.h"
#include "ubwt_index.h"
#include "utils.h"

int ubwt_query_usage(void)
{
    err_printf("Usage: ubwt query <BWT-index> <in-query>\n\n");
    //err_printf("Options:\n\n");
    err_printf("\n");
    return 1;
}

void ubwt_query_core(ubwt_t *ubwt, const uint8_t *query, int qlen)
{
    // ubwt exact match
    ubwt_count_t ok, ol, l, i, uid, off;
    l = ubwt_exact_match(ubwt, qlen, query, &ok, &ol);
    stdout_printf("Total %lld hit", (long long)l); if (l>1) stdout_printf("s:\n"); else stdout_printf(":\n");
    for (i = 0; i < l; ++i) {
        uid = ubwt_cal_off(ubwt, ok+i, &off);
        stdout_printf("Hit #%d: Unipath #%lld, Offset %lld\n", (int)i+1, (long long)uid+1, (long long)off);
        ubwt_gen_unipath1(ubwt, uid, stdout);
        stdout_printf("\n");
    }
}

int ubwt_query(int argc, char *argv[])
{
    char *prefix, *in;
    /*int c; 
    while ((c = getopt(argc, argv, "c")) >= 0) {
        switch (c)
        {
            default: return ubwt_query_usage();
        }
    }*/
    if (optind + 2 > argc) return ubwt_query_usage();
    prefix = strdup(argv[optind]), in = strdup(argv[optind+1]);

    ubwt_t *ubwt = ubwt_restore_index(prefix);

    ubwt_count_t qlen;
    uint8_t *bquery = ubwt_read_bwt_str(in, 0, &qlen);
    ubwt_query_core(ubwt, bquery, qlen);

    free(prefix); free(in);
    ubwt_free(ubwt); free(bquery);
    return 0;
}
