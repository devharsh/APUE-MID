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


	/* switch overrides */
	
	if(is_d_on) {
                is_a_on = 1;
                is_R_on = 0;
        }

	if(is_a_on)
		is_A_on = 1;

	if(is_n_on)
		is_l_on = 0;

	/* get environment variables */
 
	block_value = getenv("TZ");

	if(block_value!=NULL) {
		strcpy(time_zone, getenv("TZ"));
		setenv("TZ", time_zone, 1);
   		tzset();
	}

	block_value = getenv("BLOCKSIZE");

	if(block_value!=NULL) {
        	long bs;
        	bs = strtol(block_value, &block_ptr, 10);
        	if(bs > 512)
        		block_size = bs / 512;
        }


	for(; optind < argc; optind++) {      
		fhit = 1;

		FTS_Open(&ftsp, fts_options, argv[optind],
        		 is_a_on, is_r_on, is_S_on,
        		 is_t_on, is_u_on, is_c_on);
	
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

			if(is_d_on) {
                                if(strcmp(ent->fts_path, argv[optind]) != 0)
                                        continue;
                        }

                        if((grp = getgrgid(ent->fts_statp->st_gid)) == NULL)
				continue;

			if((pwd = getpwuid(ent->fts_statp->st_uid)) == NULL)
				continue;
	
			is_print(ent, &print, &print_name, is_a_on, is_A_on);
			
			if(ent->fts_level == 0) {
				if(!is_d_on)
					continue;
			}
			if(ent->fts_level > 1) {
				if(!is_R_on)
					continue;
			}

			if(print && print_name) {
				if(is_i_on)
                                	printf("%lu ", ent->fts_statp->st_ino);
                                
				if(is_s_on) {
					if(is_h_on && (is_n_on || is_l_on)) {
						size_read(ent->
                                			fts_statp->
                                			st_blocks * 512 / block_size,
                                			size_name);

                                		printf("%s ",
                                			size_name);
                                	} else
                                		printf("%ld ",
                                			ent->fts_statp->
                                			st_blocks / block_size);
                                }

                        	if(is_n_on || is_l_on)
                        		printf("%s\t%d\t",
                        			modeval, 
						ent->fts_statp->st_nlink);
                        	if(is_n_on)
					printf("%d\t%d\t",
						pwd->pw_uid, grp->gr_gid);
				if(is_l_on)
					printf("%s\t%s\t",
						pwd->pw_name, grp->gr_name);
	
				if(is_n_on || is_l_on) {
					if(is_h_on) {
                                        	size_read(ent-> 
                                                	fts_statp->st_size,
                                                	size_name);

                                                printf("%s\t%s\t",
                                                       size_name,
                                                       buffer);
                                        } else
                                                printf("%ld\t%s\t",
                                                      ent->fts_statp->
                                                      st_size,
                                                      buffer);
				}

				if(is_n_on || is_l_on || is_s_on) {
					if(is_h_on)
						total_size +=
						ent->fts_statp->st_size;
					else
						total_blocks += 
						ent->fts_statp->st_blocks / block_size;
				}
			
				if(is_d_on)
					printf("%s", ent->fts_path);
				else	
					printf("%s", ent->fts_name);
				
				if(is_F_on) 
					printf("%c", F_char);
                        	if(is_n_on || is_l_on || is_s_on)
                        		printf("\n");
                        	else
                        		printf("\t");
                       	}	
        	}      

		if(!is_d_on) {
			if(is_n_on || is_l_on || is_s_on) {       
				if(is_h_on) {
                        		size_read(total_size, size_name);
                        		printf("total %s", size_name);
                        	} else       
                			printf("total %d", total_blocks);
                	}
		}	

		if(fts_close(ftsp) == -1)
			perror("fts_close");

        	printf("\n");
	}
      
	if(!fhit) {
		char cwd[2];
		cwd[0] = '.';
		cwd[1] = '\0';
		FTS_Open(&ftsp, fts_options, cwd,
        		 is_a_on, is_r_on, is_S_on,
        		 is_t_on, is_u_on, is_c_on);

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
			
			if(is_d_on) {
				if(strcmp(ent->fts_name, ".") != 0)
					continue;
			}
	
			if((grp = getgrgid(ent->fts_statp->st_gid)) == NULL)
                                continue;

                        if((pwd = getpwuid(ent->fts_statp->st_uid)) == NULL)
                                continue;

			is_print(ent, &print, &print_name, is_a_on, is_A_on);

			if(ent->fts_level == 1 && print && print_name) {
                               	if(is_i_on)
                                	printf("%lu ", 
						ent->fts_statp->st_ino);
                                        
				if(is_s_on) {
					if(is_h_on && (is_n_on || is_l_on)) {
						size_read(ent->
						fts_statp->
						st_blocks * 512 / block_size,
						size_name);

						printf("%s ",
						size_name);
                                	} else
						printf("%ld ", 
							ent->fts_statp->
							st_blocks / block_size);
				}

				if(is_n_on || is_l_on)
                                       	printf("%s\t%d\t",
                                               	modeval, 
						ent->fts_statp->
						st_nlink);
                               	if(is_n_on)
					printf("%d\t%d\t",
						pwd->pw_uid, 
						grp->gr_gid);
				if(is_l_on)
					printf("%s\t%s\t",
						pwd->pw_name, 
						grp->gr_name);
					
				if(is_n_on || is_l_on) {
					if(is_h_on) {
						size_read(ent->	
						fts_statp->st_size,
						size_name);

						printf("%s\t%s\t",
							size_name,
							buffer);
					} else
						printf("%ld\t%s\t",
						ent->fts_statp->
						st_size,
						buffer);
				}
 
				if(is_n_on || is_l_on || is_s_on) {
					if(is_h_on)
						total_size +=
						ent->fts_statp->
						st_size;
					else
						total_blocks += 
						ent->fts_statp->
						st_blocks / block_size;
				}
			
				printf("%s", ent->fts_name);

				if(is_F_on) 
					printf("%c", F_char);
                               	if(is_n_on || is_l_on || is_s_on)
                                       	printf("\n");
                               	else
                                       	printf("\t");
                        }                                        
		}
        
		if(!is_d_on) {	
                	if(is_n_on || is_l_on || is_s_on) {
				if(is_h_on) {
					size_read(total_size, size_name);
					printf("total %s", size_name);
				} else       
                   			printf("total %d", total_blocks);
			}
		}
 
               	if(fts_close(ftsp) == -1)
                  	perror("fts_close");

		printf("\n");
	}

	return 0; 
}

