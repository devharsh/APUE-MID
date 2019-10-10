#include <sys/stat.h>

#include <dirent.h>
#include <fts.h>
#include <string.h>

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
