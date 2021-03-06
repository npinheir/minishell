/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:24:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/04/07 14:34:16 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// concats previous input with new input
static char	*total_input(char *cmd, char *tmp)
{
	size_t	i;
	size_t	j;
	char	*total;

	i = 0;
	j = 0;
	total = malloc(sizeof(char) * (ft_strlen(cmd) + ft_strlen(tmp)) + 1);
	if (!total)
	{
		free(cmd);
		free(tmp);
		error_malloc(1);
	}
	while (cmd && cmd[i])
		total[j++] = cmd[i++];
	i = 0;
	while (tmp && tmp[i])
		total[j++] = tmp[i++];
	total[(ft_strlen(cmd) + ft_strlen(tmp))] = '\0';
	free (cmd);
	free (tmp);
	return (total);
}

static size_t	is_empty(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	if (len - i <= 0)
		return (1);
	return (0);
}

static void	loop_input(char *cmd)
{
	char	*tmp;

	while (cmd && !is_input_incomplete(cmd))
	{
		tmp = readline("> ");
		cmd = total_input(cmd, tmp);
	}
	if (!cmd)
		error_malloc(1);
	add_history(cmd);
	g_fcmd->f_cmd = cmd;
}

char	*take_input(void)
{
	char	*cmd;

	cmd = readline("minishell => ");
	if (!cmd)
	{
		write(0, "exit\n", 5);
		clear_exit(0);
	}
	if (!strlen(cmd) || is_empty(cmd))
	{
		if (strlen(cmd))
			add_history(cmd);
		free(cmd);
		return (NULL);
	}
	else
		loop_input(cmd);
	return (cmd);
}
