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

#include "cmp.h"
#include "helper.h"

#define PATH_LIM 4096

int opt = 0; 
int fhit = 0;
int print = 0;
int print_name = 0;
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

int fts_options = FTS_COMFOLLOW | FTS_NOCHDIR | FTS_PHYSICAL;

char F_char;
char modeval[12];
char buffer[80];
char *pp[2];

struct group* grp;
struct passwd* pwd;

FTS *ftsp;
