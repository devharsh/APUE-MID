#include <sys/stat.h>

#include <fts.h>
#include <time.h>
#include <unistd.h>

void
fts_helper(FTSENT *ent, char *modeval, char *buffer, char *F_char);
