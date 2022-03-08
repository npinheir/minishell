/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:28:02 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/08 10:45:24 by npinheir         ###   ########.fr       */
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
	else if (i == 6)
		builtins_exit();
	else if (i == 7)
		buildins_echo(scmd, apply_outredir(scmd));
}

/* checks if the single command exec is a builtin function */
static int	is_builtin(t_scmd *s_cmd)
{
	size_t		i;
	const char	*builtins[7] = {"cd",
		"pwd", "export", "unset", "env", "exit", "echo"};

	i = 0;
	while (i < 7 && builtins[i])
	{
		if (ft_strcompare(builtins[i], s_cmd->tokens[0]))
		{
			return (i + 1);
		}
		i++;
	}
	return (0);
}

void	route_exec(char **envp)
{
	size_t	i;
	size_t	res;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		res = is_builtin(g_fcmd->s_cmd[i]);
		if (res > 0)
			route_builtins(g_fcmd->s_cmd[i], res);
		else
		{
			printf("not a builtin. --> exec\n");
			exec(g_fcmd->s_cmd[i], envp);
		}
		i++;
	}
}
