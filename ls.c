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
	while((opt = getopt(argc, argv,"AacdFfhiklnqRrSstuw")) != -1) {  
        	switch(opt) {
			case 'A':
				is_A_on = 1;
				break;
			case 'a':
				is_a_on = 1;
				is_A_on = 1;	
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
				is_l_on = 0;
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

	/* switch overrides */
	if(is_n_on)
		is_l_on = 0;

	pp[1] = NULL;

	for(; optind < argc; optind++) {      
		fhit = 1;

        	pp[0] = argv[optind];
	
		if(is_a_on)
			fts_options |= FTS_SEEDOT;

		if(is_r_on) {
                	ftsp = fts_open(pp, fts_options, &rev_name_compare);

                	if(is_S_on)
                		ftsp = fts_open(pp, fts_options, &rev_size_compare);
                	if(is_t_on)
                		ftsp = fts_open(pp, fts_options, &rev_mtime_compare);
                	if(is_u_on)
                		ftsp = fts_open(pp, fts_options, &rev_atime_compare);
                } else {
                	ftsp = fts_open(pp, fts_options, &name_compare);

                	if(is_S_on)
                		ftsp = fts_open(pp, fts_options, &size_compare);
                	if(is_t_on)
                		ftsp = fts_open(pp, fts_options, &mtime_compare);
                	if(is_u_on)
                		ftsp = fts_open(pp, fts_options, &atime_compare);
                }	

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
	
			if (ent->fts_name[0] == '.') {
                        	if(is_A_on)
                        		print_name = 1;
                        	else
                        		print_name = 0;
                        } else
                        	print_name = 1;
		
			if (ent->fts_info == FTS_D) {
				print = 1;
			} else if (ent->fts_info == FTS_DC) {
				print = 0;
			} else if (ent->fts_info == FTS_DEFAULT) {
			} else if (ent->fts_info == FTS_DNR) {
			} else if (ent->fts_info == FTS_DOT) {
				if(is_a_on)
					print = 1;
				else
					print = 0;
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
			} else
				print = 0;
		
			if(ent->fts_level == 1 && print && print_name) {
				if(is_i_on)
                                	printf("%lu ", ent->fts_statp->st_ino);
                                if(is_s_on)
                                	printf("%ld ", ent->fts_statp->st_blocks);
                        	if(is_n_on || is_l_on)
                        		printf("%s\t%d\t",
                        			modeval, ent->fts_statp->st_nlink);
                        	if(is_n_on)
					printf("%d\t%d\t",
						pwd->pw_uid, grp->gr_gid);
				if(is_l_on)
					printf("%s\t%s\t",
						pwd->pw_name, grp->gr_name);
				if(is_n_on || is_l_on)
					printf("%ld\t%s\t",
						ent->fts_statp->st_size, buffer);
				if(is_n_on || is_l_on || is_s_on)
					total += ent->fts_statp->st_blocks;
					
				printf("%s", ent->fts_name);
				
				if(is_F_on) 
					printf("%c", F_char);
                        	if(is_n_on || is_l_on || is_s_on)
                        		printf("\n");
                        	else
                        		printf("\t");
                       	}	
        	}      

		if(is_n_on || is_l_on || is_s_on)       
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
			
			if(is_a_on)
				fts_options |= FTS_SEEDOT;			
		
			if(is_r_on) {
				ftsp = fts_open(pp, fts_options, &rev_name_compare);

				if(is_S_on)
					ftsp = fts_open(pp, fts_options, &rev_size_compare);
				if(is_t_on)
					ftsp = fts_open(pp, fts_options, &rev_mtime_compare);
				if(is_u_on)
					ftsp = fts_open(pp, fts_options, &rev_atime_compare);
			} else {
				ftsp = fts_open(pp, fts_options, &name_compare);

                		if(is_S_on)
					ftsp = fts_open(pp, fts_options, &size_compare);
				if(is_t_on)
					ftsp = fts_open(pp, fts_options, &mtime_compare);
				if(is_u_on)
					ftsp = fts_open(pp, fts_options, &atime_compare);
        		}    
    	
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

				if (ent->fts_name[0] == '.') {
                                        if(is_A_on)
                                                print_name = 1;
					else
						print_name = 0;
                                } else
                                        print_name = 1;

				if (ent->fts_info == FTS_D) {
					print = 1;
				} else if (ent->fts_info == FTS_DC) {
					print = 0;
				} else if (ent->fts_info == FTS_DEFAULT) {
				} else if (ent->fts_info == FTS_DNR) {
				} else if (ent->fts_info == FTS_DOT) {
					if(is_a_on)
						print = 1;
					else
						print = 0;
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
				} else
					print = 0;

				if(ent->fts_level == 1 && print && print_name) {
                                	if(is_i_on)
                                                printf("%lu ", ent->fts_statp->st_ino);
                                        if(is_s_on)
                                                printf("%ld ", ent->fts_statp->st_blocks);
					if(is_n_on || is_l_on)
                                        	printf("%s\t%d\t",
                                                	modeval, ent->fts_statp->st_nlink);
                                	if(is_n_on)
						printf("%d\t%d\t",
							pwd->pw_uid, grp->gr_gid);
					if(is_l_on)
						printf("%s\t%s\t",
							pwd->pw_name, grp->gr_name);
					if(is_n_on || is_l_on)
						printf("%ld\t%s\t",
							ent->fts_statp->st_size, buffer);
					if(is_n_on || is_l_on || is_s_on)
						total += ent->fts_statp->st_blocks;
				
					printf("%s", ent->fts_name);

					if(is_F_on) 
						printf("%c", F_char);
                                	if(is_n_on || is_l_on || is_s_on)
                                        	printf("\n");
                                	else
                                        	printf("\t");
                        	}                                        
                	}      
        	
                	if(is_n_on || is_l_on || is_s_on)       
                       		printf("total %d", total); 
                	if(fts_close(ftsp) == -1)
                       		perror("fts_close");

			printf("\n");
		}
	}

	return 0; 
}

