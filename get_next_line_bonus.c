/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:13:52 by amaucher          #+#    #+#             */
/*   Updated: 2023/01/02 16:13:56 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free_tempstore(char *tempstore, char *buf)
{
	char	*bufandtemp;

	bufandtemp = ft_strjoin(tempstore, buf);
	free(tempstore);
	return (bufandtemp);
}

char	*ft_rest(char *buf)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\0')
	{
		free(buf);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buf) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buf[i] != '\0')
		line[j++] = buf[i++];
	free(buf);
	return (line);
}

char	*ft_line(char *buf)
{
	char	*line;
	int		i;

	i = 0;
	if (buf[i] == '\0')
		return (NULL);
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] != '\0' && buf[i] == '\n')
		line[i++] = '\n';
	line[i++] = '\0';
	return (line);
}

char	*ft_read_fromfile(int fd, char *linetempstore)
{
	char	*buf;
	int		byte_read;

	if (!linetempstore)
		linetempstore = ft_calloc(1, 1);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buf);
			free(linetempstore);
			return (NULL);
		}
		buf[byte_read] = '\0';
		linetempstore = ft_free_tempstore(linetempstore, buf);
		if (ft_strchr(buf, '\n') != NULL)
			break ;
	}
	free(buf);
	return (linetempstore);
}

char	*get_next_line(int fd)
{
	static char	*buf[256];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (NULL);
	buf[fd] = ft_read_fromfile(fd, buf[fd]);
	if (!buf[fd])
		return (NULL);
	line = ft_line(buf[fd]);
	buf[fd] = ft_rest(buf[fd]);
	return (line);
}
