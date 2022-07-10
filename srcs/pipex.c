/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:52:10 by taehykim          #+#    #+#             */
/*   Updated: 2022/07/10 15:52:13 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

char	**find_path(char *envp[])
{
	char	*path;

	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (*envp == NULL)
		exit_perror("PATH error", 127);
	path = *envp + 5;
	return (ft_split(path, ':'));
}

char	*make_cmd(char **path, char *cmd_arg)
{
	int		i;
	char	*tmp;
	int		fd;

	i = 0;
	fd = access(cmd_arg, X_OK);
	if (fd != -1)
		return (cmd_arg);
	while (path[i])
	{
		tmp = ft_strjoin("/", cmd_arg);
		tmp = ft_strjoin(path[i], tmp);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			return (tmp);
		}
		free(tmp);
		tmp = NULL;
		i++;
		close(fd);
	}
	return (NULL);
}

void	set_fd(int closed, int std_in, int std_out)
{
	close(closed);
	if (dup2(std_in, STDIN_FILENO) == -1)
		exit_perror("dup2 error", 1);
	if (dup2(std_out, STDOUT_FILENO) == -1)
		exit_perror("dup2 error", 1);
	close(std_in);
	close(std_out);
}

int	init(t_pipe *box, char *argv[], char *envp[])
{
	int	result;

	result = 1;
	box->infile = open(argv[1], O_RDONLY);
	if (box->infile == -1)
		perror("infile");
	box->outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (box->outfile == -1)
		exit_perror("outfile", 1);
	box->cmd1_arg = ft_split(argv[2], ' ');
	box->cmd2_arg = ft_split(argv[3], ' ');
	box->path = find_path(envp);
	box->cmd1 = make_cmd(box->path, box->cmd1_arg[0]);
	box->cmd2 = make_cmd(box->path, box->cmd2_arg[0]);
	if (box->cmd1 == NULL || box->cmd2 == NULL)
	{
		result = 127;
		perror("command not found");
	}
	return (result);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	box;
	int		result;

	if (argc != 5)
		exit_perror("incorrect argument number.", 1);
	result = init(&box, argv, envp);
	if (pipe(box.pipe_fd) < 0)
		exit_perror("pipe eroor", 1);
	box.pid = fork();
	if (box.pid == -1)
		exit_perror("fork error", 1);
	if (box.pid == 0)
	{
		set_fd(box.pipe_fd[0], box.infile, box.pipe_fd[1]);
		if (execve(box.cmd1, box.cmd1_arg, envp) == -1)
			exit_perror("execve error", result);
	}
	else
	{
		set_fd(box.pipe_fd[1], box.pipe_fd[0], box.outfile);
		waitpid(box.pid, NULL, WNOHANG);
		if (execve(box.cmd2, box.cmd2_arg, envp) == -1)
			exit_perror("execve error", result);
	}
	return (0);
}
