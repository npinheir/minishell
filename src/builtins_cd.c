/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:10:45 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/01 09:26:59 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	buildins_cd(t_scmd *scmd)
{
	int	res;

	if (scmd->ntokens != 1)
	{
		printf("<cd> No more than 1 parameter allowed\n");
		return ;
	}
	res = chdir(scmd->tokens[0]->token);
	if (res == -1)
		printf("Directory doesn't exist.\n");
}
