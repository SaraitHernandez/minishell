/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:38 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/01 21:23:47 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*new_str;

	i = 0;
	while (s[i] && i < n)
		i++;
	new_str = (char *)malloc(i + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*concat_content(char *existing, char *new_line)
{
	char	*result;

	if (!existing)
		return (ft_strdup(new_line));
	result = malloc(ft_strlen(existing) + ft_strlen(new_line) + 2);
	if (!result)
	{
		free_all(2, FREE_STRING, existing, FREE_STRING, new_line);
		exit_with_error("Memory allocation failed");
	}
	ft_strcpy(result, existing);
	ft_strcat(result, " ");
	ft_strcat(result, new_line);
	free_all(2, FREE_STRING, existing, FREE_STRING, new_line);
	return (result);
}

char	**copy_argv(char **argv_local, int argc)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		exit_with_error("Memory allocation failed for argv");
	i = 0;
	while (i < argc)
	{
		argv[i] = argv_local[i];
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
