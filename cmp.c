#include "cmp.h"

int 
name_compare(const FTSENT ** first, const FTSENT ** second) {
        return (strcmp((*first)->fts_name, (*second)->fts_name));
}

int
rev_name_compare(const FTSENT ** first, const FTSENT ** second) {
        return (strcmp((*second)->fts_name, (*first)->fts_name));
}

int
size_compare(const FTSENT ** first, const FTSENT ** second) {
        if ((*first)->fts_statp->st_size >= (*second)->fts_statp->st_size)
                return -1;
        else
                return 1;
}

int
rev_size_compare(const FTSENT ** first, const FTSENT ** second) {
        if ((*first)->fts_statp->st_size >= (*second)->fts_statp->st_size)
                return 1;
        else
                return -1;
}

int
mtime_compare(const FTSENT ** first, const FTSENT ** second) {
        if ((*first)->fts_statp->st_mtime >= (*second)->fts_statp->st_mtime)
                return -1;
        else
                return 1;
}

int
rev_mtime_compare(const FTSENT ** first, const FTSENT ** second) {
        if ((*first)->fts_statp->st_mtime >= (*second)->fts_statp->st_mtime)
                return 1;
        else
                return -1;
}

int
atime_compare(const FTSENT ** first, const FTSENT ** second) {
        if ((*first)->fts_statp->st_atime >= (*second)->fts_statp->st_atime)
                return -1;
        else
                return 1; 
}

int
rev_atime_compare(const FTSENT ** first, const FTSENT ** second) {
        if ((*first)->fts_statp->st_atime >= (*second)->fts_statp->st_atime)
                return 1;
        else
                return -1;
}

int
ctime_compare(const FTSENT ** first, const FTSENT ** second) {
        if ((*first)->fts_statp->st_ctime >= (*second)->fts_statp->st_ctime)
                return -1;
        else
                return 1; 
}

int
rev_ctime_compare(const FTSENT ** first, const FTSENT ** second) {
        if ((*first)->fts_statp->st_ctime >= (*second)->fts_statp->st_ctime)
                return 1;
        else
                return -1;
}
