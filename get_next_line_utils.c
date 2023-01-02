/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:14:11 by amaucher          #+#    #+#             */
/*   Updated: 2023/01/02 16:14:12 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char	*res;

	res = malloc(elementSize * elementCount);
	if (!res)
		return (NULL);
	ft_bzero(res, elementSize * elementCount);
	return (res);
}

size_t	ft_strlen(const char *theString)
{
	int	i;

	i = 0;
	while (theString[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *string, int searchedChar )
{
	char	*str;

	str = (char *)string;
	while (*str != searchedChar && *str != 0)
		str++;
	if (*str == searchedChar)
		return (str);
	else
		return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		joined_len;
	char	*joinedstr;
	int		i;
	int		j;

	i = 0;
	joined_len = ft_strlen(s1) + ft_strlen(s2);
	joinedstr = malloc(sizeof(char) * (joined_len + 1));
	if (!joinedstr || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		joinedstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		joinedstr[i] = s2[j];
		i++;
		j++;
	}
        joinedstr[joined_len] = '\0';
	return (joinedstr);
}
