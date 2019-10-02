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
fts_helper(char *g);

int 
compare(const FTSENT** one, const FTSENT** two);
