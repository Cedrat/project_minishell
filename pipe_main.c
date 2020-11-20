
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *env[])
{
  pid_t          pid;
  int pipefd[2];
  int fd;
  int next_fd = 0;
  char buff[256];
  int ret;
  char *str[] = {"/bin/ls", "/bin/wc" , NULL};
size_t i = 0;


while(str[i] != NULL)
{
	pipe(pipefd);
	pid = fork();
		  if (pid == 0)
		  {
			dup2(next_fd, 0);                 // on recupere ou sont ecris les precedentes reponses
			if ((str[i + 1] != NULL))
				dup2(pipefd[1], 1);           // Si la commande suivante est non nulle, on transmet au futur arguments
			close(pipefd[0]);
			execve(str[i], argv, env); //sort du fils :(
		  }
		  else
		  {
			wait(NULL);
			close(pipefd[1]);
			next_fd = pipefd[0]; //on recupere next_fd , les arguments sont sur pipefd[0]
			i++;
		  }
	}
}
