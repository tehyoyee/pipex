#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_pipe
{
	int		outfile;
	int		infile;
	int		pipe_fd[2];
	char	*cmd1;
	char	*cmd2;
	char	**path;
	char	**cmd1_arg;
	char	**cmd2_arg;
	pid_t	pid;
}	t_pipe;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	exit_perror(char *msg, int code);

#endif
