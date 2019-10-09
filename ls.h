/*
 * MID - ls - list the contents of a directory
 * Author: Devharsh Trivedi
 * Email: dtrived5@stevens.edu
*/

#include <sys/stat.h>
#include <sys/types.h>

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fts.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define PATH_LIM 4096

int opt = 0; 
int fhit = 0;
int print = 0;
int total = 0;

int is_A_on = 0;
int is_a_on = 0;
int is_c_on = 0;
int is_d_on = 0;
int is_F_on = 0;
int is_f_on = 0;
int is_h_on = 0;
int is_i_on = 0;
int is_k_on = 0;
int is_l_on = 0;
int is_n_on = 0;
int is_q_on = 0;
int is_R_on = 0;
int is_r_on = 0;
int is_S_on = 0;
int is_s_on = 0;
int is_t_on = 0;
int is_u_on = 0;
int is_w_on = 0;

char F_char;
char buffer[80];
char *pp[2];

struct group* grp;
struct passwd* pwd;

FTS *ftsp;

void
fts_helper(FTSENT *ent, char *modeval, char *buffer, char *F_char);

int
name_compare      (const FTSENT ** first, const FTSENT ** second);

int
rev_name_compare  (const FTSENT ** first, const FTSENT ** second);

int
size_compare      (const FTSENT ** first, const FTSENT ** second);

int
rev_size_compare  (const FTSENT ** first, const FTSENT ** second);

int 
mtime_compare     (const FTSENT ** first, const FTSENT ** second);

int
rev_mtime_compare (const FTSENT ** first, const FTSENT ** second);

int
atime_compare     (const FTSENT ** first, const FTSENT ** second);

int
rev_atime_compare (const FTSENT ** first, const FTSENT ** second);
