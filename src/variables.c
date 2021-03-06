/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:38:37 by fcaquard          #+#    #+#             */
/*   Updated: 2022/04/06 15:40:24 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// search for a $variable then replace it by its env value
static char	*find_var(char *str, int i, int j)
{
	while (str && str[i])
	{
		if (str[i] == '\'')
		{
			i += 1;
			while (str && str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '$')
		{
			j = end_var(str, i, i);
			if (j - i > 1)
				str = replace_var(str, get_env(str, i, j), i, j);
			else if (str[j] == '?')
				str = exit_code(str, i, j);
			else
				i++;
			if (!str[i])
				return (str);
		}
		else
			i++;
	}
	return (str);
}

// entry point for the search and replacement of env $variables
void	env_variables(void)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		g_fcmd->s_cmd[i]->s_cmd = find_var(g_fcmd->s_cmd[i]->s_cmd, 0, 0);
		i++;
	}
	return ;
}
