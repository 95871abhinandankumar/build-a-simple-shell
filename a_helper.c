#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include<errno.h> 
#include<sys/wait.h> 
#include <unistd.h>
#include<string.h>

struct cmdline{
	char **args;
	struct cmdline *next;
};

int file_exists(char *str)
{
	FILE *file;
	if(file = fopen(str, "r"))
	{
		fclose(file);
		return 1;
	}
        
	return -1;

}

//For handling semicolon
char** commands(char *str)
{
	char **args1 = (char **)malloc(sizeof(char *) * 20);

    char *str1 = (char *)malloc(sizeof(char) * 200);
    int j = 0;
    int k = 0;
	for(int i = 0 ;  str[i] != '\0' ; i++)
	{
		if((str[i] == ' ' && str[i+1] == ';') || (str[i] == ' ' && str[i-1] == ';'))
		{

		}
		else if(str[i] == ';')
		{
			str1[j] = '\0';
			args1[k] = str1;
			str1 = (char *)malloc(sizeof(char) * 200);
			j=0;
			k++;
		}else{
			str1[j++] = str[i];
		}
	}
	str1[j] = '\0';
	args1[k++] = str1;
	args1[k] = NULL;

	return args1;

}



void _cat(char **args)
{
	int pid = fork();
	if(pid == -1)
	{
		perror("Error");
		exit(0);
	}
	else if(pid == 0)
	{
		execvp(args[0], args);
	}else{
		wait(NULL);
	}
}

void _ls(char **args)
{
		int pid = fork();
	if(pid == -1)
	{
		perror("Error");
		exit(0);
	}
	else if(pid == 0)
	{
		execvp(args[0], args);
	}else{
		wait(NULL);
	}
}

void _mkdir(char **args)
{
		int pid = fork();
	if(pid == -1)
	{
		perror("Error");
		exit(0);
	}
	else if(pid == 0)
	{
		execvp(args[0], args);
	}else{
		wait(NULL);
	}
}

void _echo(char **args)
{
		int pid = fork();
	if(pid == -1)
	{
		perror("Error");
		exit(0);
	}
	else if(pid == 0)
	{
		execvp(args[0], args);
	}else{
		wait(NULL);
	}
}
void _sleep(char **args)
{
                int pid = fork();
        if(pid == -1)
        {
                perror("Error");
                exit(0);
        }
        else if(pid == 0)
        {
                execvp(args[0], args);
        }else{
                wait(NULL);
        }
}




//If contian semi_colon
int is_contain_semicolon(char *str)
{
	
	int flag  =0;
	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		
		if(str[i] == ';')
		    flag = 1;
	}


	if(flag == 0)
	  return -1;
    else
    	return 1;

}


//If conatin pipe (|)
int is_contain_pipe(char *str)
{
	
	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		
		if(str[i] == '|')
		    return 1;
	}


	return -1;

}

//If string contain less than (<) 
//or greter than (>) sign
int is_contain_less_gre(char *str)
{
	
	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		
		if(str[i] == '<' || str[i] == '>')
		    return 1;
	}


	return -1;

}
void _internal_command(char **args)
{
	//printf("%s %s", args[0], args[1]);
	if(strcmp(args[0], "cd") == 0)
	{
		if(args[1] == NULL)
			chdir("/");
		else
			chdir(args[1]);
	}
	else if(strcmp(args[0], "echo")== 0)
         {
                  _echo(args);
         }
         else if(strcmp(args[0] , "sleep") == 0)
         {
                  _sleep(args);
         }
	else if(strcmp(args[0],"ls") == 0)
	{
	        _ls(args);
	}
        else if(strcmp(args[0] ,"mkdir")==0)
	 {
	  	    _mkdir(args);
	 }	
        else if(strcmp(args[0], "cat")== 0)
       	{
	 	 _cat(args);
	 }
	  else
	        fprintf(stderr, "Invaid command !\n");  		
}

//For internal command
void internal_command(char *str)
{
	char **args = (char **)malloc(sizeof(char *) * 20);

    char *str1 = (char *)malloc(sizeof(char) * 200);
    int j = 0;
    int k = 0;
	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		if(str[i] == ' ')
		{
			str1[j] = '\0';
			
			args[k] = str1;
			str1 = (char *)malloc(sizeof(char) * 200);
			j=0;
			k++;
		}else{
			str1[j++] = str[i];
		}
	}
	str1[j] = '\0';
	args[k++] = str1;
	args[k] = NULL;
	//printf("%s", args[0]);
	_internal_command(args);

}

void cat_cont_command(char *str)
{
    char **args = (char **)malloc(sizeof(char *) * 20);

    char *str1 = (char *)malloc(sizeof(char) * 200);
    int j = 0;
    int k = 0;
	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		if(str[i] == ' ')
		{
			str1[j] = '\0';
			
			args[k] = str1;
			str1 = (char *)malloc(sizeof(char) * 200);
			j=0;
			k++;
		}else{
			str1[j++] = str[i];
		}
	}
	str1[j] = '\0';
	args[k++] = str1;
	args[k] = NULL;
    
    char **args1 = (char **)malloc(sizeof(char *) * 5);

      k = 0;
     int l = 0;
     while(args[k] != NULL)
     {
     	if(strcmp(args[k], "<") == 0)
     	{

     	}else if(strcmp(args[k], ">") == 0)
     	{

     	}
     	else
     	{
     		int j = 0;
     		str1 = (char *)malloc(sizeof(char) * 200);
     		for(int i = 0 ; args[k][i] != '\0' ; i++)
     		{
     			if(args[k][i] == '<' || args[k][i] == '>')
     			{

     			}
     			else
     			{
     				str1[j++] = args[k][i];
     			}

     		}

     	    str1[j] = '\0';
     	    args1[l++] = str1;
      	}
     	k++;
     }
     args1[l]  = NULL;

     if(args1[2] == NULL)
     {
	   if(file_exists(args1[1]))
	   {  
  	   	_cat(args1);
	   }
	   else
	   {
		   FILE *file;
		   file = fopen(args1[1], "w");
		   char ch ;
		   while(1)
		   {
			   ch = getchar();
			   if(ch == EOF)
			   {
				return;
			   }
			   fputc(ch, file);
		   }
		   fclose(file);



	   }
     }
     else
     {


         int fd_out = creat(args1[2], 0644);
         if(fd_out < 0)
         {
         	perror("ERROR ");
         	exit(0);
         }
        close(1);
         dup(fd_out);
         close(fd_out);

         args1[2] =NULL;
         _cat(args1);
     	
     }



}

char** pipe_command(char *str)
{
	char **args1 = (char **)malloc(sizeof(char *) * 20);

    char *str1 = (char *)malloc(sizeof(char) * 200);
    int j = 0;
    int k = 0;
	for(int i = 0 ; i < str[i] != '\0' ; i++)
	{ 
		if(str[i] == ' ')
		{
			str1[j] = '\0';
			args1[k] = str1;
			str1 = (char *)malloc(sizeof(char) * 200);
			j=0;
			k++;
		}else{
			str1[j++] = str[i];
		}
	}
	str1[j] = '\0';
	args1[k++] = str1;
	args1[k] = NULL;

	return args1;
}
int countPipes(char *userInput)
{
	int count = 0;
	for(int i = 0 ; i < strlen(userInput) ; i++)
	{
		if(userInput[i] == '|')
			count++;
	}

	return count;
}

void _pipe_cont_command(struct cmdline* command, char* userInput) {
    int numPipes = countPipes(userInput);


    int status;
    int i = 0;
    pid_t pid;

    int pipefds[2*numPipes];

    for(i = 0; i < (numPipes); i++){
        if(pipe(pipefds + i*2) < 0) {
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }
    }


    int j = 0;
    while(command) {
        pid = fork();
        if(pid == 0) {

            //if not last command
            if(command->next){
                if(dup2(pipefds[j + 1], 1) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            //if not first command&& j!= 2*numPipes
            if(j != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    perror(" dup2");///j-2 0 j+1 1
                    exit(EXIT_FAILURE);

                }
            }


            for(i = 0; i < 2*numPipes; i++){
                    close(pipefds[i]);
            }

            if( execvp(*command->args, command->args) < 0 ){
                    perror(*command->args);
                    exit(EXIT_FAILURE);
            }
        } else if(pid < 0){
            perror("error");
            exit(EXIT_FAILURE);
        }

        command = command->next;
        j+=2;
    }
    /**Parent closes the pipes and wait for children*/

    for(i = 0; i < 2 * numPipes; i++){
        close(pipefds[i]);
    }

    for(i = 0; i < numPipes + 1; i++)
        wait(&status);
}
void pipe_cont_command(char *str)
{

	struct cmdline *command = NULL, *temp1;
	struct cmdline *temp = (struct cmdline *)malloc(sizeof(struct cmdline));

	char str1[200];
	int j = 0;
	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		if(str[i] == '|')
		{
			i+=1;
		}else if((str[i] == ' ') && (str[i + 1] == '|'))
		{
			str1[j] = '\0';
			if(command == NULL)
			{
				temp->args = pipe_command(str1);
				temp->next = NULL;
				command = temp;
				temp1 = temp;
			}else{
				temp = (struct cmdline *)malloc(sizeof(struct cmdline));
				temp->args = pipe_command(str1);
				temp->next = NULL;
				temp1->next = temp;
				temp1 = temp;
			}

			j = 0;
		}else{
			str1[j++] =str[i];
		}
	}
		str1[j] = '\0';
	    temp = (struct cmdline *)malloc(sizeof(struct cmdline));
		temp->args = pipe_command(str1);
		temp->next = NULL;
		temp1->next = temp;
       
        _pipe_cont_command(command, str);

}


int main(int argc, char *argv[])
{
	char *str;
	str = argv[1];
	//char **args;
/*	int p = 0;

	char ch;

		scanf("%c", &ch);
		while(ch != '\n'){
	    str[p] = ch;
	    scanf("%c", &ch);
	    p++;}
	str[p] = '\0';
*/	//printf("%s", str);
    //scanf("%[^\n]%*c", str);

//	int n;
//	scanf("%d", &n);

	//for(int i = 0 ; i < n ; i++)
	//{
		//args[i] = (char *)malloc(sizeof(char) * 30);
	//}
    

    if(is_contain_semicolon(str) == 1)
    {
    	
    	char **args1 = commands(str);
    	int k = 0;
    	while(args1[k] != NULL)
    	{
    		
    		if(is_contain_pipe(args1[k]) == 1)
    		{
    			//printf("hello\n");
    			pipe_cont_command(args1[k]);
    		}
    		else if(is_contain_less_gre(args1[k]) == 1)
    		{
    			//printf("hello\n");
    			cat_cont_command(args1[k]);
    		}
    		else
    		{ 
    			

    			internal_command(args1[k]);
    		}
    		k++;
    	}
    }else{
    	
    	if(is_contain_pipe(str) == 1)
    		{
    			pipe_cont_command(str);
    		}else if(is_contain_less_gre(str) == 1)
    		{
    			cat_cont_command(str);
    		}else
    		{
    			internal_command(str);
    		}
    }


}
