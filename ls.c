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
		printf("extra arguments: %s\n", argv[optind]);  

		char *p = argv[optind];
		char *pp[] = {p, NULL};

		FTS *ftsp = fts_open(pp, 0, NULL);
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
			
			if(ent->fts_info & FTS_D)
				printf("Enter dir: ");
			else if(ent->fts_info & FTS_DP)
				printf("Exit dir:  ");
			else if(ent->fts_info & FTS_F)
				printf("File:      ");
			else 
				printf("Other:     ");

			printf("%s\n", ent->fts_path);
		}	

		if(fts_close(ftsp) == -1)
			perror("fts_close");
	}
      
	if(!fhit) {
		char cwd[PATH_LIM];
                char *c = getcwd(cwd, sizeof(cwd));
		if(c == NULL)
			perror("getcwd");
		else
			printf("extra arguments: %s found\n", cwd);
	}

	return 0; 
} 
