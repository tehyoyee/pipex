#include <stdio.h>
#include <unistd.h>
extern char **environ;

int main(char **envp)
{
	char *argv[2];
	argv[0] = "ls";
	argv[1] = NULL;
	execve("/bin/cat", argv, environ);
}