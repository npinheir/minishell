/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:04:50 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/07 12:15:46 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates all de desired files and closes 
// them but leaves the last one open
int	apply_outredir(t_scmd *scmd)
{
	int		fd;

	fd = 1;
	if (!scmd->redir->last_out)
		return (1);
	create_redir_file_s(scmd);
	if (scmd->redir->out)
	{
		fd = open(scmd->redir->out_args[scmd->redir->out - 1], \
			O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (!fd)
			clear_all();
	}
	return (fd);
}

char	**apply_heredoc(t_scmd *scmd)
{
	char	**hered;
	int		fd;
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strcat(scmd->redir->inin_args[scmd->redir->inin - 1], ".ms");
	if (!tmp)
		clear_all();
	tmp2 = ft_strcat(".", tmp);
	if (!tmp2)
		clear_all();
	hered = get_heredoc(scmd);
	fd = open(tmp2, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (!fd)
		clear_all();
	i = 1;
	while (hered[i])
		ft_putendl_fd(hered[i++], fd);
	close(fd);
	free(tmp);
	clear_array(hered, ft_arrlen(hered));
	hered = ft_realloc(scmd->tokens, tmp2);
	free(tmp2);
	return (hered);
}

static char	**heredoc_loop(char *input, char **res, t_scmd *scmd, size_t i)
{
	char	**tmp;

	if (i == scmd->redir->inin - 1)
	{
		tmp = ft_realloc(res, input);
		clear_array(res, ft_arrlen(res));
		if (input)
			free(input);
		res = tmp;
	}
	return (res);
}

char	**get_heredoc(t_scmd *scmd)
{
	char	**res;
	char	*input;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char *) * 2);
	res[0] = ft_strdup(scmd->tokens[0]);
	res[1] = NULL;
	while (i < scmd->redir->inin)
	{
		g_fcmd->active_heredoc = 1;
		input = readline("> ");
		while (ft_strcompare(input, scmd->redir->inin_args[i]) == 0)
		{
			res = heredoc_loop(input, res, scmd, i);
			input = readline("> ");
		}
		i++;
	}
	g_fcmd->active_heredoc = 0;
	return (res);
}

void	apply_inredir(t_scmd *scmd)
{
	int	fd;

	if (scmd->redir->last_in == 1)
	{
		fd = open(scmd->redir->in_args[scmd->redir->in - 1], O_RDONLY);
		if (!fd)
			clear_exit(1);
		dup2(fd, STDIN_FILENO);
	}
	else if (scmd->redir->last_in == 2)
	{
		fd = open(scmd->redir->here_name, O_RDONLY);
		if (fd < 0)
			clear_exit(1);
		else
			unlink(scmd->redir->here_name);
		free(scmd->redir->here_name);
		dup2(fd, STDIN_FILENO);
	}
}
