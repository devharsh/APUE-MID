#include "helper.h"

void
fts_helper(FTSENT *ent, char *modeval, char *buffer, char *F_char) {
        mode_t perm = ent->fts_statp->st_mode;
 	strmode(perm, modeval);
       
        if(S_ISREG(perm))
                *F_char = 0;
        else if(S_ISDIR(perm))
                *F_char = '/';
        else if(S_ISCHR(perm))
                *F_char = 0;
        else if(S_ISBLK(perm))
                *F_char = 0;
        else if(S_ISFIFO(perm))
                *F_char = '|';
        else if(S_ISLNK(perm))
                *F_char = '@';
        else if(S_ISSOCK(perm))
                *F_char = '=';
        else if(S_ISWHT(perm))
                *F_char = '%';
        else
                *F_char = 0;
 
        struct tm* time_c = localtime(&ent->fts_statp->st_ctime);
        strftime(buffer, 80, "%b %d %H:%M", time_c);
}
