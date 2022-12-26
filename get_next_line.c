#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

//helper functions
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

// helper function
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
// helper function
// strjoin joins two strings into a new string joinedstr
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

char    *ft_free_tempstore(char *tempstore, char *buf)
{
        char *bufandtemp;

        bufandtemp = ft_strjoin(tempstore, buf); //not sure yet, why we join strings and don't copy, since tempstore is empty in the beginning
        free (tempstore); // we need to empty the string before reading into it the new line;
        return (bufandtemp);
}

// not self_made!
char	*ft_next(char *buf)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	// find len of first line
	while (buf[i] && buf[i] != '\n')
		i++;
	// if eol == \0 return NULL
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	// len of file - len of firstline + 1
	line = ft_calloc((ft_strlen(buf) - i + 1), sizeof(char));
	i++;
	j = 0;
	// line == buffer
	while (buf[i])
		line[j++] = buf[i++];
	free(buf);
	return (line);
}

// not self-made!
char	*ft_line(char *buf)
{
	char	*line;
	int		i;

	i = 0;
	// if no line return NULL
	if (!buf[i])
		return (NULL);
	// go to the eol
	while (buf[i] && buf[i] != '\n')
		i++;
	// malloc to eol
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	// line = buffer
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	// if eol is \0 or \n, replace eol by \n
	if (buf[i] && buf[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
static char    *buf;
char    *line;

buf = read_fromfile(fd, buf);
line = ft_line(buf);
buf = ft_next(buf);
return (line);
}

char    *read_fromfile(int fd, char *linetempstore)
{
char    *buf;
int     count;
int     byte_read;

// count can be substituted with buf_size later, this is just for easier testing
count = 10; 
byte_read = 1;
while (byte_read > 0) // not sure yet, why we need this loop
{
        // read returns number of byte reads by default (zero indicates end of file)
        byte_read = read(fd, buf, count);
        // read returns -1 on error
                if (byte_read == -1)
	{
	        free(buf);
		return (NULL);
	}
         // ensure that the buffer is null terminated
        buf[byte_read] = '\0';
        linetempstore = ft_free(linetempstore, buf);
// strchr will print everything of a string that comes after (incl.) the searchable character if it is found
// if the character is not found withing a string it returns null
// so we say here if we have read until end of line, please stop the while loop! this is our loop terminator
        if (ft_strchr(buf, '\n'))
	        break ;
}
        free(buffer);
	return (res);
}

int	main()
{
int ptr;
 // Opening file in reading mode to get the FD
 ptr = open("test.txt", O_RDONLY);
 if (NULL == ptr)
      printf("file can't be opened \n");
printf("%s",get_next_line(ptr));
}