/*
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "cmp.h"


/*
 *
 */
void 
size_read(double size, char* buf);

/*
 *
 */
void
is_print(FTSENT *ent, int* print, int* print_name, int is_a_on, int is_A_on);

/*
 *
 */
void
FTS_Open(FTS **ftsp, int fts_options, char *p,
        int is_a_on, int is_r_on, int is_S_on,
        int is_t_on, int is_u_on);

/*
 *
 */
void
fts_helper(FTSENT *ent, char *modeval, char *buffer, char *F_char);
