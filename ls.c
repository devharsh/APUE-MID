#include "ls.h"
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

char* permissions(char* file) {
	struct stat st;
	char *modeval = malloc(11);

	if(stat(file, &st) == 0) {
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

		return modeval; 
	} else {
		return strerror(errno);
	}
}

int
main(int argc, char **argv) {
	DIR *dp;
	int aflag = 0;
	int bflag = 0;
	char* cvalue = NULL;
	int index;
	int c;
	opterr = 0;

	if (argc != 2) {
		fprintf(stderr, "usage: %s dir_name\n", argv[0]);
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL ) {
		fprintf(stderr, "can't open '%s'\n", argv[1]);
		exit(1);
	}

	struct stat st;
	struct group *grp;
	struct passwd *pwd;

	int total = 0;
	
	struct dirent** dirpa;
	c = scandir(".", &dirpa, NULL, alphasort);
	if (c < 0)
		perror("scandir");
	else {
		int k;
		for(k=0; k<c; k++) {
			if (stat(dirpa[k]->d_name, &st) != 0)
    				perror("stat() error");
			else {
				grp = getgrgid(st.st_gid);
				pwd = getpwuid(st.st_uid);
			
				total += (int)(st.st_blocks);
				char buffer[80];
				struct tm* time_c;
				time_c = localtime(&st.st_ctime);
				strftime(buffer, 80, "%b %d %H:%M", time_c);
			
				printf("%s\t%d\t%s\t%s\t%ld\t%s\t%s\n",
				permissions(dirpa[k]->d_name), st.st_nlink,
				pwd->pw_name, grp->gr_name, 
				st.st_size, buffer, dirpa[k]->d_name);

				free(dirpa[k]);
			}
		}
		free(dirpa);
	}

	printf("total = %d\n", total);
	while ((c = getopt (argc, argv, "abc:")) != -1) {
		switch (c) {
			case 'a':
				aflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			case 'c':
				cvalue = optarg;
				break;
			case '?':
				if (optopt == 'c') {
					fprintf (stderr,
						 "Option -%c requires an argument.\n",
						 optopt);
				}
				else if (isprint (optopt)) {
					fprintf (stderr,
						 "Unknown option '-%c'.\n",
						 optopt);
				}
				else {
					fprintf (stderr,
						"Unknown option '-%c' character.\n",
						optopt);
				}
				return 1;
			default:
				abort ();
		}
	}

	printf ("aflag = %d, bflag = %d, cvalue = %s\n",
		aflag, bflag, cvalue);

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);
	
	closedir(dp);
	return(0);
}
