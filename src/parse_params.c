/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:45:23 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/05 15:10:03 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check block start ' "
int	is_block_start(char c)
{
	if ((unsigned char) c == '\''
		|| (unsigned char) c == '"')
		return (1);
	return (0);
}

// returns 0 when no blockend is not found / end position on success
size_t	find_block_end(char *input, size_t position)
{
	char	target;

	target = input[position];
	if (input[position] == '(')
		target = ')';
	position++;
	while (input && input[position])
	{
		if (input[position] == target)
			return (position);
		position++;
	}
	return (0);
}

size_t	find_param_end(char *input, size_t position)
{
	while (input && input[position])
	{
		if (ft_isspace(input[position]))
			return (position);
		else
			position++;
	}
	if (input[position] == '\0')
		return (position);
	return (0);
}

// extracts token from single command's string
static char	*tokenize(char *input, size_t start, size_t end)
{
	char	*token;
	size_t	i;

	i = 0;
	token = malloc(sizeof(char) * (end - start) + 1);
	if (!token)
		return (NULL);
	token[end - start] = '\0';
	while (input && input[start] && start < end)
		token[i++] = input[start++];
	return (token);
}

/**	Looks for the end of a parameter
	(anything that isn't a space, a blockstart
	or a delimiter) then tokenizes it */
int	parse_param(t_scmd *s_cmd, size_t *start, size_t *i)
{
	size_t	end;
	char	*token;

	end = find_param_end(s_cmd->instructions, *start);
	if (end == 0)
		return (0);
	else
	{
		token = tokenize(s_cmd->instructions, *start, end);
		if (!token)
			error_malloc();
		s_cmd->tokens[(*i)++]->token = token;
	}
	*start = end;
	return (1);
}
