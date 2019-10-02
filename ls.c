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
      
	while((opt = getopt(argc, argv,":if:lrx")) != -1) {  
        	switch(opt) {  
            		case 'i':  
            		case 'l':  
				break;
			case 'r':  
                		printf("option: %c\n", opt);  
                		break;  
            		case 'f':  
                		printf("filename: %s\n", optarg);  
                		break;  
            		case ':':  
                		printf("option needs a value\n");  
                		break;  
            		case '?':  
                		printf("unknown option: %c\n", optopt); 
                		break;  
        	}  
    	}  

	for(; optind < argc; optind++) {      
		fhit = 1;
		fts_helper(argv[optind]);
	}
      
	if(!fhit) {
		char cwd[PATH_LIM];
                char* c = getcwd(cwd, sizeof(cwd));
		if(c == NULL)
			perror("getcwd");
		else
			fts_helper(cwd);
	}

	return 0; 
}

/*
*
*/
void
fts_helper(char *g) {
	int total = 0;
	int print = 0;

	struct group* grp;
	struct passwd* pwd;
	struct tm* time_c;

	char buffer[80];
	char *modeval = malloc(11);
	char * pp[2];

	FTS *ftsp;

	pp[0] = g;
	pp[1] = NULL;

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

		switch (ent->fts_info) { 
                	case FTS_D :
				print = 1;
				break;
                	case FTS_F :
				print = 1;
				break; 
                	case FTS_SL:
                    		break;
                	default:
                    		break;
            	}
               
		/* 
		if(print && ent->fts_level == 1)
                	printf("%s\t", ent->fts_name);
		*/



		grp = getgrgid(ent->fts_statp->st_gid);
                pwd = getpwuid(ent->fts_statp->st_uid);
                      
                total += (int)(ent->fts_statp->st_blocks);
                time_c = localtime(&ent->fts_statp->st_ctime);
                strftime(buffer, 80, "%b %d %H:%M", time_c);
                mode_t perm = ent->fts_statp->st_mode;
                
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

		if(print && ent->fts_level == 1)
                	printf("%s\t%d\t%s\t%s\t%ld\t%s\t%s\n",
                		modeval, ent->fts_statp->st_nlink,
                		pwd->pw_name, grp->gr_name, 
                		ent->fts_statp->st_size, buffer, ent->fts_name);
                                                        
	}      
	
	printf("total %d\n", total); 

        if(fts_close(ftsp) == -1)
        	perror("fts_close");

	printf("\n");
}

/*
*
*/
int compare(const FTSENT ** first, const FTSENT ** second) {
	return (strcmp((*first)->fts_name, (*second)->fts_name));
} 
