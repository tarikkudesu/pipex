/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:39:54 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/31 17:04:33 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_error(char **tab)
{
	int	i;

	i = 0;
	while (*(tab + i))
		free(*(tab + i++));
	free(tab);
	return (NULL);
}

int	ft_flen(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

char	*ft_itab(char const *s, char c, int *index)
{
	int		i;
	int		wlen;
	char	*word;

	wlen = 0;
	i = 0;
	while (*(s + (*index)) && *(s + (*index)) == c)
		(*index)++;
	i = *index;
	while (*(s + i) && *(s + i++) != c)
		wlen++;
	word = malloc(sizeof(char) * (wlen + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < wlen)
		*(word + i) = *(s + (*index)++);
	*(word + i) = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		flen;
	int		i;
	int		index;
	char	**tab;

	if (!s)
		return (NULL);
	i = -1;
	index = 0;
	flen = ft_flen(s, c);
	tab = malloc(sizeof(char *) * (flen + 1));
	if (!tab)
		return (NULL);
	while (++i < flen)
	{
		*(tab + i) = ft_itab(s, c, &index);
		if (!*(tab + i))
			return (ft_error(tab));
	}
	*(tab + i) = 0;
	return (tab);
}
