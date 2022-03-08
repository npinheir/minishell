/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:28:02 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/08 10:38:06 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* if the exec is a builtin and files pernissions are ok, calls the appropriate function */
static void	route_builtins(t_scmd *scmd, size_t i)
{
	if (!redir_files_ok(scmd))
		return;
	if (i == 0)
		buildins_echo(scmd, apply_outredir(scmd));
	else if (i == 1)
		buildins_cd(scmd);
	else if (i == 2)
		buildins_pwd(scmd, apply_outredir(scmd));
	else if (i == 3)
		builtins_export(scmd);
	else if (i == 4)
		builtin_unset(scmd);
	else if (i == 5)
		builtins_env(apply_outredir(scmd));
	else
		builtins_exit();
}

/* checks if the single command exec is a builtin function */
int	is_builtin(t_scmd *s_cmd)
{
	size_t		i;
	const char	*builtins[7] = {"echo", "cd",
		"pwd", "export", "unset", "env", "exit"};

	i = 0;
	while (i < 7 && builtins[i])
	{
		if (ft_strcompare(builtins[i], s_cmd->exec))
		{
			route_builtins(s_cmd, i);
			return (1);
		}
		i++;
	}
	return (0);
}
