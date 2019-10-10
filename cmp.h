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

/*
 *
 */
void
fts_helper(FTSENT *ent, char *modeval, char *buffer, char *F_char);

/*
 *
 */
int
name_compare      (const FTSENT ** first, const FTSENT ** second);

/*
 *
 */
int
rev_name_compare  (const FTSENT ** first, const FTSENT ** second);

/*
 *
 */
int
size_compare      (const FTSENT ** first, const FTSENT ** second);

/*
 *
 */
int
rev_size_compare  (const FTSENT ** first, const FTSENT ** second);

/*
 *
 */
int 
mtime_compare     (const FTSENT ** first, const FTSENT ** second);

/*
 *
 */
int
rev_mtime_compare (const FTSENT ** first, const FTSENT ** second);

/*
 *
 */
int
atime_compare     (const FTSENT ** first, const FTSENT ** second);

/*
 *
 */
int
rev_atime_compare (const FTSENT ** first, const FTSENT ** second);
