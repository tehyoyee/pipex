#include "pipex.h"

void	exit_perror(char *msg, int code)
{
	perror(msg);
	exit(code);
}