#include "ls.h"

/*
* This program simulates the behaviour of a standard ls
* command on a UNIX like system. It takes the directory
* path as a argument, if it is not provided it takes
* present working directory as default. It can be used
* with some switch arguments as provided.
*/
int
main(int argc, char **argv) {
	DIR* dp;
	char ch;

	int total = 0;
	int i, c = 0;
	opterr = 0;

	struct stat st;
	struct dirent** dirpa;
	struct group* grp;
	struct passwd* pwd;
	struct tm* time_c;
 /*
	if(argc < 1) {
		perror("argument error");
		exit(1);
	}

	if (argc == 1) {
		char cwd[PATH_LIM];
		getcwd(cwd, sizeof(cwd));
		argv[1] = cwd;
		argc = 2;
	}*/
	
	/* iterate over all arguments */
	for(i=1; i<argc; i++) {
		if ((dp = opendir(argv[i])) == NULL ) {
			fprintf(stderr, "can't open '%s'\n", argv[i]);
			exit(1);
			closedir(dp); /* TODO: check for errors */
		}

		c = scandir(argv[i], &dirpa, NULL, alphasort);
		
		if (c < 0)
			perror("scandir");
		else {
			int k;
			for(k=0; k<c; k++) {
				while ((ch = getopt (argc, argv, "abc:")) != -1) {
                			switch (ch) {
                        			case 'a':
                                			break;
                        			case 'l':
                                			if (stat(dirpa[k]->d_name, &st) != 0)
                                        			perror("stat() error");
                                			else {
                                        			grp = getgrgid(st.st_gid);
                                        			pwd = getpwuid(st.st_uid);
                        
                                        			total += (int)(st.st_blocks);
                                        			char buffer[80];
                                        			time_c = localtime(&st.st_ctime);
                                        			strftime(buffer, 80, "%b %d %H:%M", time_c);
                                
                                        			char *modeval = malloc(11);
                                        			mode_t perm = st.st_mode;
                
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

                                        			printf("%s\t%d\t%s\t%s\t%ld\t%s\t%s\n",
                                        			modeval, st.st_nlink,
                                        			pwd->pw_name, grp->gr_name, 
                                        			st.st_size, buffer, dirpa[k]->d_name);
							
								printf("total = %d\n", total);
							}
							break;
                        			default:
							printf("%s\t", dirpa[k]->d_name);
                			}
        			}
				printf("%s\t", dirpa[k]->d_name);
				free(dirpa[k]);
			}
		}
		free(dirpa);
	}
	printf("\n");
	return(0);
}
