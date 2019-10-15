#include "helper.h"


void 
size_read(double size, char* buf) {
	int i = 0;
	char units[10] = {'B', 'K', 'M', 'G', 'T', 
			'P', 'E', 'Z', 'Y', '\0'};
	while (size >= 1024) {
		size /= 1024;
		i++;
	}
	sprintf(buf, "%.*f%c", i, size, units[i]);
}


void
is_print(FTSENT *ent, int *print, int* print_name, int is_a_on, int is_A_on) {
	if (ent->fts_name[0] == '.') {
		if(is_A_on)
			*print_name = 1;
		else
			*print_name = 0;
	} else
		*print_name = 1;

	if (ent->fts_info == FTS_D)
		*print = 1;
	else if (ent->fts_info == FTS_DC)
		*print = 0;
	else if (ent->fts_info == FTS_DEFAULT) {
	} else if (ent->fts_info == FTS_DNR) {
	} else if (ent->fts_info == FTS_DOT) {
		if(is_a_on)
			*print = 1;
		else
			*print = 0;
	} else if (ent->fts_info == FTS_DP)
		*print = 0;
	else if (ent->fts_info == FTS_ERR) 
		*print = 0;
	else if (ent->fts_info == FTS_F) 
		*print = 1;
	else if (ent->fts_info == FTS_INIT) {
	} else if (ent->fts_info == FTS_NS) {
	} else if (ent->fts_info == FTS_NSOK) {
	} else if (ent->fts_info == FTS_SL) {
	} else if (ent->fts_info == FTS_SLNONE) {
	} else if (ent->fts_info == FTS_W) {
	} else
		*print = 0;
}


int
is_exec(char* name) {
	struct magic_set *ms;
   	const char *result;

   	ms = magic_open(MAGIC_RAW);
   	
	if (ms == NULL) {
      		(void)fprintf(stderr, "ERROR opening MAGIC_NONE: out of memory\n");
      		return -1;
   	}
   
	if (magic_load(ms, NULL) == -1) {
		(void)fprintf(stderr, "ERROR loading with NULL file: %s\n", magic_error(ms));
      		return -1;
   	}

	if ((result = magic_file(ms, name)) == NULL) {
		(void)fprintf(stderr, "ERROR loading file %s: %s\n", name, magic_error(ms));
            	return -1;
        } else {
             	if (strstr(result, (const char *)"executable")) 
        		return 1;
		else
			return 0;
	}

	magic_close(ms);
}


void
FTS_Open(FTS **ftsp, int fts_options, char *p,
	int is_a_on, int is_r_on, int is_S_on,
	int is_t_on, int is_u_on) {
	char *pp[2];
	pp[0] = p;
	pp[1] = NULL;

	if(is_a_on)
		fts_options |= FTS_SEEDOT;                      
                
	if(is_r_on) {
		*ftsp = fts_open(pp, fts_options, 
				&rev_name_compare);

		if(is_S_on)
			*ftsp = fts_open(pp, fts_options, 
					&rev_size_compare);
		if(is_t_on)
			*ftsp = fts_open(pp, fts_options, 
					&rev_mtime_compare);
		if(is_u_on)
			*ftsp = fts_open(pp, fts_options, 
					&rev_atime_compare);
	} else {
		*ftsp = fts_open(pp, fts_options, &name_compare);

		if(is_S_on)
			*ftsp = fts_open(pp, fts_options, 
					&size_compare);
		if(is_t_on)
			*ftsp = fts_open(pp, fts_options, 
					&mtime_compare);
		if(is_u_on)
			*ftsp = fts_open(pp, fts_options, 
					&atime_compare);
	}    
        
	if(*ftsp == NULL) {
		perror("fts_open");
		exit(1);
	}
}


void
fts_helper(FTSENT *ent, char *modeval, char *buffer, char *F_char) {
        struct tm* time_c;
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

	if(is_exec(ent->fts_name) == 1)
		*F_char = '*';
 
	time_c = localtime(&ent->fts_statp->st_ctime);
        strftime(buffer, 80, "%b %d %H:%M", time_c);
}
