#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

//For printing the current directory
void print_dir()
{
	char buff[400];
	getcwd(buff, sizeof(buff));
	printf("%s$ ", buff);

}

void  get_input(char *str)
{
	char arg_char;

	int i = 0;
	while(1)
	{
		arg_char = getchar();
		if(arg_char == EOF || arg_char == '\n')
		{
			str[i] = '\0';

			break;
		}

		str[i] = arg_char;
		i++;
		
		

	}
//	return str;
}


//To split the string
void string_splitting(char *str1, char **args)
{
	char *token;
	int i = 0;
	char *str = str1;

	int j = 0;
	int k = 0;
	char *str2 = (char *)malloc(sizeof(char) * 20);
	for(int i = 0  ; i < strlen(str) ; i++)
	{
		if(str[i] == ' ')
		{
			str2[j] = '\0';
			j = 0;
			args[k++] = str2; 

 			str2 = (char *)malloc(sizeof(char)* 20);
		}else{
			str2[j++] = str[i];
		}
	}

	str2[j] = '\0';
	args[k++] = str2;
	args[k] = NULL;


}

//To count number of argument
int count_argument(char **args)
{
        int i = 0;
        while(args[i] != NULL)
        {
                i++;
        }
	return i;

}

int is_special_char(char *str)
{
	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		if(str[i] == '<' || str[i] == '>' || str[i] == ';' || str[i] == '|')
			return 1;
	}
	return -1;
}

//To handle all shell internal command
void shell_command(char *str, char **args)
{
//	string_splitting(str, args);

  //  if(is_contain_semic)	
	//For cd command
	
	if(is_special_char(str) == 1)
        {
                int pid = fork();
                if(pid < 0)
                        perror("ERROR");
                else if(pid == 0)
                {
                        execl("a_helper", "a_helper", str, (char *)0);
                }else
		{
			wait(NULL);
		}

                return;
        }


	if(strcmp(args[0], "cd") == 0)
	{
		if(args[1] == NULL)
		{
			chdir("/");
		}
		else
		{
			if(chdir(args[1]))
			{
				fprintf(stderr, "NO SUCH DIRECTORY FOUND!\n");
			}
		}
	}else if(strcmp(args[0] , "exit") == 0) //For exit command
	{
		system("clear");
		fprintf(stderr, "****************************************HOPE YOU ENJOYED NEW SHELL************************************\n");
		exit(0);
	}else if(strcmp(args[0], "echo") == 0)  //For echo command
	{
		 int pid = fork();
                if(pid < 0)
                {
                        perror("ERROR");
                }else if(pid == 0)
                {
                        execvp(args[0], args);
                }else{
                        wait(NULL);
                }

		printf("\n");
        }else if(strcmp(args[0], "pwd") == 0)   //For pwd command
	{
		 char buff[400];
                 getcwd(buff, sizeof(buff));
                 printf("%s\n", buff);

        }else if(strcmp(args[0], "ls") == 0)   //For ls command
	{
		int pid = fork();
		if(pid < 0)
		{
			perror("ERROR");
		}else if(pid == 0)
		{
			execvp(args[0], args);
		}else{
			wait(NULL);
		//	printf("Successfully created\n");
		}
		
	}else if(strcmp(args[0], "mkdir") == 0)  //For mkdir To create 
	{                                        //to create directory
		int pid = fork();
		if(pid < 0)
		{
			perror("ERROR");
		}else if(pid == 0)
		{
			execvp(args[0], args);
		}else{
			wait(NULL);
		}
	}else if(strcmp(args[0], "cat") == 0)   //For cat command
	{
		if(args[1] == NULL)
		{
			fprintf(stderr, "INVALID COMMAND!\n");
			return;
		}
		else{                         //For normal cat function
			 int pid = fork();
               		 if(pid < 0)
               		 {
                                    perror("ERROR");
                          }else if(pid == 0)
               		 {
                     		   execvp(args[0], args);
               		 }else{
                       		 wait(NULL);
               		 }
		}

	}else if(strcmp(args[0], "cp") == 0)
	{
		if(args[1] == NULL || args[2] == NULL)
		{
			fprintf(stderr, "INVALID COMMAND!\n");
		}
		else{                         //For normal cp function
                         int pid = fork();
                         if(pid < 0)
                         {
                                    perror("ERROR");
                          }else if(pid == 0)
                         {
                                   execvp(args[0], args);
                         }else{
                                 wait(NULL);
                         }
                }

	}
	else if(strcmp(args[0], "sleep") == 0)   //For sleep command
        {
                if(args[1] == NULL)
                {
                        fprintf(stderr, "INVALID COMMAND!\n");
                        return;
                }
                else{                         
                         int pid = fork();
                         if(pid < 0)
                         {
                                    perror("ERROR");
                          }else if(pid == 0)
                         {
                                   execvp(args[0], args);
                         }else{
                                 wait(NULL);
                         }
                }

        }else if(strcmp(args[0], "chmod") == 0)   
        {
                if(args[1] == NULL)
                {
                        fprintf(stderr, "INVALID COMMAND!\n");
                        return;
                }
                else{
                         int pid = fork();
                         if(pid < 0)
                         {
                                    perror("ERROR");
                          }else if(pid == 0)
                         {
                                   execvp(args[0], args);
                         }else{
                                 wait(NULL);
                         }
                }

        }else if(strcmp(args[0], "source")== 0)
	{
		 // Open file
		char c;
		char s[100];
   		FILE * fptr = fopen(args[1], "r");
   		 if (fptr == NULL)
   		 {
       		 printf("Cannot open file \n");
       		 exit(0);
   		 }

   		 // Read contents from file
   		 c = fgetc(fptr);
		 int j = 0;
		 s[j++] = c;
   		 while (c != EOF)
   		 {
			 if(c == '\n')
			 {
				 s[j] = '\0';
				 string_splitting(s, args);
                                 shell_command(s, args);

				 j = 0;
			 }else
			 {
				 s[j++] = c;
			 }
       			 c = fgetc(fptr);
   		 }

     		 fclose(fptr); 
	}
	else{                       //In case when either command is not supported 
		fprintf(stderr, "COMMAND NOT FOUND!\n");   //in this shell
		                                           //OR invalid command
	}
  	



//	execvp(args[0], args);
//	exit(0);

}


void signal_handler(int sig_num)
{
	fflush(stdout);
}

int main()
{
	signal(SIGINT, signal_handler);
	char *str = (char *)malloc(sizeof(char) * 200);
	char **args = (char **)malloc(sizeof(char *) * 20);
//	printf("\033[H\033[j");
    	system("clear");
	printf("**************************************");
	printf("WELCOME TO LATEST SHELL***************");
	printf("***********************\n");

	printf("\n\nTHIS SHELL IS CONSTRUCTED USING TWO C FILE i.e a.c AND a_helper.c\n\n");

//	print_dir();
//	get_input(str);
//	printf("%s", str);
        
//	string_splitting(str, args);
	
/*	int i =0;
	while(args[i] != NULL)
	{
		printf("%s\n", args[i]);
		i++;
	}
*/
        while(1)
	{
		print_dir();
		get_input(str);
		string_splitting(str, args);
		shell_command(str, args);
	}
        

	printf("END OF SHELL!\n");
	

}
