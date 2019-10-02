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
                char *c = getcwd(cwd, sizeof(cwd));
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
        char *pp[] = {g, NULL};

        FTS *ftsp = fts_open(pp, 0, &compare);
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

		int print = 0; 
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
                
		if(print && ent->fts_level == 1)
                	printf("%s\t", ent->fts_name);
	}       

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
