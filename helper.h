/*
 * This is a library of helper functions used in the
 * implementation of ls command
 */


#include <magic.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "cmp.h"


/*
 * to print in human readable format
 */
void 
size_read(double size, char* buf);

/*
 * to determine if the name should be printed or skipped
 */
void
is_print(FTSENT *ent, int* print, int* print_name, int is_a_on, int is_A_on);

/*
 * to determine if the file is executable
 */
int
is_exec(char* name);

/*
 * helper function to traverse the directory
 */
void
FTS_Open(FTS **ftsp, int fts_options, char *p,
        int is_a_on, int is_r_on, int is_S_on,
        int is_t_on, int is_u_on, int is_c_on);

/*
 * helper function to use with -F switch, to determine file
 * permissions and to compute time for -l switch
 */
void
fts_helper(FTSENT *ent, char *modeval, char *buffer, char *F_char);
