/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:39:19 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/08 10:48:50 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_option_ok(char *str)
{
	size_t	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] == 'n')
				return (1);
			i++;
		}
	}
	return (0);
}

// Runs the echo command
void	buildins_echo(t_scmd *scmd, int fd_out)
{
	size_t	i;

	i = 1;
	if (scmd->tokens && scmd->tokens[1])
	{
		if (scmd->tokens[1][0] == '-')
			i++;
		ft_putstr_fd(scmd->tokens[i], fd_out);
		while (++i < scmd->ntokens)
		{
			ft_putchar_fd(' ', fd_out);
			ft_putstr_fd(scmd->tokens[i], fd_out);
		}
		if (!is_option_ok(scmd->tokens[0]))
			ft_putchar_fd('\n', fd_out);
	}
	else
		ft_putchar_fd('\n', fd_out);
	if (fd_out > 2)
		close(fd_out);
}
