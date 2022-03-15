/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_toarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:48:43 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/15 19:23:57 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_len(t_env *env)
{
	size_t	len;

	len = 0;
	env = env_first(env);
	while (env)
	{
		len++;
		if (!env->next)
			break ;
		env = env->next;
	}
	return (len);
}

size_t	envp_len(char **envp)
{
	size_t	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

// copy src into dest starting at a given dest position
// Does not NULL terminate dest
char	*ft_strcopy(char *dest, char *src, size_t index_dest)
{
	size_t	i;

	i = 0;
	while (dest && src && src[i])
	{
		dest[index_dest] = src[i];
		index_dest++;
		i++;
	}
	return (dest);
}

// concats three strings
// NULL terminates the returning str
char	*strrebuild(char *src1, char *src2, char *src3)
{
	char	*str;
	size_t	lsrc1;
	size_t	lsrc2;
	size_t	lsrc3;

	lsrc1 = ft_strlen(src1);
	lsrc2 = ft_strlen(src2);
	lsrc3 = ft_strlen(src3);
	str = malloc(sizeof(char) * lsrc1 + lsrc2 + lsrc3 + 1);
	if (!str)
		error_malloc();
	str = ft_strcopy(str, src1, 0);
	str = ft_strcopy(str, src2, lsrc1);
	str = ft_strcopy(str, src3, lsrc1 + lsrc2);
	str[lsrc1 + lsrc2 + lsrc3] = '\0';
	return (str);
}

char	**env_listtoarray(t_env *env)
{
	char	**array;
	size_t	len;
	size_t	i;

	i = 0;
	len = env_len(env);
	env = env_first(env);
	array = malloc(sizeof(char *) * len + 1);
	while (env)
	{
		array[i] = malloc(sizeof(char) * ft_strlen(env->line) + 1);
		if (!array[i])
		{
			clear_array(array, i);
			error_malloc();
		}
		array[i] = ft_strcopy(array[i], env->line, 0);
		array[i][ft_strlen(env->line)] = '\0';
		i++;
		if (!env->next)
			break;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}
