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

void
fts_helper(FTSENT *ent, char *modeval, char *buffer, char *F_char, int *print);

int 
compare(const FTSENT ** first, const FTSENT ** second);

int
rev_compare(const FTSENT ** first, const FTSENT ** second);
