/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:07:05 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/01 14:12:43 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen_g(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*(s + i))
		i++;
	return (i);
}

char	*ft_strdup_g(const char *s1)
{
	int		i;
	char	*res;

	i = ft_strlen_g(s1);
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		*(res + i) = *(s1 + i);
		i++;
	}
	*(res + i) = '\0';
	return (res);
}

char	*ft_strchr_g(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i))
	{
		if (*(s + i) == '\n')
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_g(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1)
		s1 = ft_strdup_g("");
	if (!s1 || !s2)
		return (0);
	res = malloc((ft_strlen_g(s1) + ft_strlen_g(s2) + 1) * sizeof(char));
	if (!res)
	{
		free(s1);
		return (s1 = NULL, NULL);
	}
	i = -1;
	while (*(s1 + ++i))
		*(res + i) = *(s1 + i);
	j = 0;
	while (*(s2 + j))
		*(res + i++) = *(s2 + j++);
	*(res + i) = '\0';
	free(s1);
	s1 = NULL;
	return (res);
}
