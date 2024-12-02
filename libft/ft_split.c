/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:21:43 by akacprzy          #+#    #+#             */
/*   Updated: 2024/03/14 01:15:06 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_counter(char const *str, char c)
{
	size_t	i;
	size_t	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			counter++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
		else if (str[i] == c)
			i++;
	}
	return (counter);
}

static size_t	ft_word_length(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static void	ft_free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(*(array + i));
	}
	free(array);
}

static char	**ft_split_help(char const *str, char c, char **array, size_t words)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (str[j] && str[j] == c)
			j++;
		*(array + i) = ft_substr(str, j, ft_word_length(&*(str + j), c));
		if (!*(array + i))
		{
			ft_free_array(i, array);
			return (NULL);
		}
		while (str[j] && str[j] != c)
			j++;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_word_counter(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = ft_split_help(s, c, array, words);
	return (array);
}
