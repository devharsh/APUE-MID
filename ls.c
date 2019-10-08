#include "ls.h"  


/*
* This program simulates the behaviour of a standard ls
* command on a UNIX like system. It takes the directory
* path as a argument, if it is not provided it takes
* present working directory as default. It can be used
* with some switch arguments as provided.
*/  
int main
(int argc, char * argv[]) {  
	
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
	char *modeval = malloc(11);
	char *pp[2];

	struct group* grp;
	struct passwd* pwd;

	FTS *ftsp;

	while((opt = getopt(argc, argv,"AacdFfhiklnqRrSstuw")) != -1) {  
        	switch(opt) {
			case 'A':
				is_A_on = 1;
				break;
			case 'a':
				is_a_on = 1;
				break;
			case 'c':
				is_c_on = 1;
				break;
			case 'd':
				is_d_on = 1;
				break;
			case 'F':
				is_F_on = 1;
				break;
			case 'f':
				is_f_on = 1;
				break;
  			case 'h':
				is_h_on = 1;
				break;
            		case 'i':
				is_i_on = 1;
				break;
			case 'k':
				is_k_on = 1;
				break;
            		case 'l':
				is_l_on = 1;
				break;
			case 'n':
				is_n_on = 1;
				break;
			case 'q':
				is_q_on = 1;
				break;
			case 'R':
				is_R_on = 1;
				break;
			case 'r':  
				is_r_on = 1;
				break;
            		case 'S':
				is_S_on = 1;
				break;
			case 's':
				is_s_on = 1;
				break;
			case 't':
				is_t_on = 1;
				break;
			case 'u':
				is_u_on = 1;
				break;
			case 'w':
				is_w_on = 1;
				break;
			default:
				break;
        	}  
    	}  

	pp[1] = NULL;

	for(; optind < argc; optind++) {      
		fhit = 1;

        	pp[0] = argv[optind];

		if(is_r_on)
			ftsp = fts_open(pp, 0, &rev_compare);
		else
        		ftsp = fts_open(pp, 0, &compare);
        	
		if(ftsp == NULL) {
                	perror("fts_open");
                	exit(1);
        	}

        	while(1) {
			FTSENT *ent = fts_read(ftsp);

                	if(ent == NULL) {
                        	if(errno == 0)
                                	break;
                        	else {
                                	perror("fts_read");
                                	exit(1);
                        	}
                	}

			fts_helper(ent, modeval, buffer, &F_char);

                        grp = getgrgid(ent->fts_statp->st_gid);
                        pwd = getpwuid(ent->fts_statp->st_uid);

                        if(print && ent->fts_level == 1 && ent->fts_info != 1) {
                        	if(is_l_on)
                        		printf("%s\t%d\t%s\t%s\t%ld\t%s\t",
                        			modeval, ent->fts_statp->st_nlink,
                        			pwd->pw_name, grp->gr_name, 
                        			ent->fts_statp->st_size, buffer);
                        	if(is_l_on || is_s_on) {
                        		printf("%d ", ent->fts_statp->st_blocks);
                        		total += ent->fts_statp->st_blocks;
                        	}
                        	printf("%s", ent->fts_name);
                        	if(is_F_on) 
                        		printf("%c", F_char);
                        	if(is_l_on)
                        		printf("\n");
                        	else
                        		printf("\t");
                        }
        	}      
 	
		if(is_s_on)
			printf("\n");	
		if(is_l_on || is_s_on)       
        		printf("total %d", total); 
		if(fts_close(ftsp) == -1)
			perror("fts_close");

        	printf("\n");
	}
      
	if(!fhit) {
		char cwd[PATH_LIM];
                char* c = getcwd(cwd, sizeof(cwd));
		if(c == NULL)
			perror("getcwd");
		else {
                	pp[0] = cwd;

			if(is_r_on)
				ftsp = fts_open(pp, 0, &rev_compare);
                	else
				ftsp = fts_open(pp, 0, &compare);
                	
			if(ftsp == NULL) {
                        	perror("fts_open");
                        	exit(1);
                	}

                	while(1) {
                       		FTSENT *ent = fts_read(ftsp);
                                
				if(ent == NULL) {
                                        if(errno == 0)
                                                break;
                                        else {
                                                perror("fts_read");
                                                exit(1);
                                        }
                                }	 
	
				fts_helper(ent, modeval, buffer, &F_char);

				grp = getgrgid(ent->fts_statp->st_gid);
                                pwd = getpwuid(ent->fts_statp->st_uid);

				if (ent->fts_info == FTS_D) {
					if(is_A_on)
						print = 1;
					else
						print = 0;
				} else if (ent->fts_info == FTS_DC) {
					print = 0;
				} else if (ent->fts_info == FTS_DEFAULT) {
				} else if (ent->fts_info == FTS_DNR) {
				} else if (ent->fts_info == FTS_DOT) {
					print = 1;
				} else if (ent->fts_info == FTS_DP) {
					print = 0;
				} else if (ent->fts_info == FTS_ERR) {
					print = 0;
				} else if (ent->fts_info == FTS_F) {
					print = 1;
				} else if (ent->fts_info == FTS_INIT ) {
				} else if (ent->fts_info == FTS_NS) {
				} else if (ent->fts_info == FTS_NSOK) {
				} else if (ent->fts_info == FTS_SL) {
				} else if (ent->fts_info == FTS_SLNONE) {
				} else if (ent->fts_info == FTS_W) {
				}

				if(ent->fts_level == 1 && print) {
                                	if(is_l_on)
                                        	printf("%s\t%d\t%s\t%s\t%ld\t%s\t",
                                                	modeval, ent->fts_statp->st_nlink,
                                                	pwd->pw_name, grp->gr_name, 
                                                	ent->fts_statp->st_size, buffer);
                                	if(is_s_on)
						printf("%d ", ent->fts_statp->st_blocks);
					if(is_l_on || is_s_on)
						total += ent->fts_statp->st_blocks;
					printf("%s", ent->fts_name);
					if(is_F_on) 
						printf("%c", F_char);
                                	if(is_l_on)
                                        	printf("\n");
                                	else
                                        	printf("\t");
                        	}                                        
                	}      
        		
			if(is_s_on)
				printf("\n");        
                	if(is_l_on || is_s_on)       
                        	printf("total %d", total); 
                	if(fts_close(ftsp) == -1)
                        	perror("fts_close");

                	printf("\n");
		}
	}

	return 0; 
}

/*
 *
 */
void
fts_helper(FTSENT *ent, char *modeval, char *buffer, char *F_char) {
        mode_t perm = ent->fts_statp->st_mode;
        
	if(S_ISREG(perm))
                *F_char = 0;
        if(S_ISDIR(perm))
                *F_char = '/';
        if(S_ISCHR(perm))
        if(S_ISBLK(perm))
        if(S_ISFIFO(perm))
                *F_char = '|';
        if(S_ISLNK(perm))
                *F_char = '@';
        if(S_ISSOCK(perm))
                *F_char = '=';
        if(S_ISWHT(perm))
                *F_char = '%';
        
	modeval[0] = (perm & S_IFDIR) ? 'd' : '-';
        modeval[1] = (perm & S_IRUSR) ? 'r' : '-';
        modeval[2] = (perm & S_IWUSR) ? 'w' : '-';
        modeval[3] = (perm & S_IXUSR) ? 'x' : '-';
        modeval[4] = (perm & S_IRGRP) ? 'r' : '-';
        modeval[5] = (perm & S_IWGRP) ? 'w' : '-';
        modeval[6] = (perm & S_IXGRP) ? 'x' : '-';
        modeval[7] = (perm & S_IROTH) ? 'r' : '-';
        modeval[8] = (perm & S_IWOTH) ? 'w' : '-';
        modeval[9] = (perm & S_IXOTH) ? 'x' : '-';
        modeval[10] = '\0';

        struct tm* time_c = localtime(&ent->fts_statp->st_ctime);
        strftime(buffer, 80, "%b %d %H:%M", time_c);
}

/*
*
*/
int compare(const FTSENT ** first, const FTSENT ** second) {
	return (strcmp((*first)->fts_name, (*second)->fts_name));
}


/*
*
*/
int rev_compare(const FTSENT ** first, const FTSENT ** second) {
	return (strcmp((*second)->fts_name, (*first)->fts_name));
} 
