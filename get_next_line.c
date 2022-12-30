#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

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

char    *ft_read_fromfile(int fd, char *linetempstore)
{
        char    *buf;
        //int     count;
        int     byte_read;
        int     BUFFER_SIZE = 30;

        //count = 10; 
        // malloc if res dont exist
                if (!linetempstore)
                        linetempstore = ft_calloc(1, 1);
                // malloc buffer
                buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
        // count can be substituted with buf_size later, this is just for easier testing
        byte_read = 1;
        while (byte_read > 0) // not sure yet, why we need this loop
        {
                // read returns number of byte reads by default (zero indicates end of file)
                byte_read = read(fd, buf, BUFFER_SIZE);
                // read returns -1 on error
                        if (byte_read == -1)
                {
                        free(buf);
                        return (NULL);
                }
                // ensure that the buffer is null terminated
                buf[byte_read] = '\0';
                linetempstore = ft_free_tempstore(linetempstore, buf);
        // strchr will print everything of a string that comes after (incl.) the searchable character if it is found
        // if the character is not found withing a string it returns null
        // so we say here if we have read until end of line, please stop the while loop! this is our loop terminator
        if (ft_strchr(buf, '\n'))
	        break ;
}
        free(buf);
	return (linetempstore);
}

char	*get_next_line(int fd)
{
        static char    *buf;
        char    *line;
        int     BUFFER_SIZE = 30;

        if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
        buf = ft_read_fromfile(fd, buf);
        if (!buf)
		return (NULL);
        line = ft_line(buf);
        buf = ft_next(buf);
        return (line);
}

int main()
{
  int fd;
  int ret;
  char *line;
  
  fd = open("test.txt", O_RDONLY);
  ret = 1;
  while (ret > 0)
  {
    ret = get_next_line(fd);
    printf("ret = [%i]\t[%s]", ret, line);
    //free(line);
  }
  return (ret);
}
/*
int	main()
{
int ptr;
 // Opening file in reading mode to get the FD
 ptr = open("test.txt", O_RDONLY);
 if (ptr == 0)
      printf("file can't be opened \n");
printf("%s",get_next_line(ptr));
}


// setup for testing, probably I need a while loop to see different line
int	main()
{
int fd;
static char    *buf;
        char    *line;
 // Opening file in reading mode to get the FD
 fd = open("test.txt", O_RDONLY);
 if (fd == 0)
      printf("file can't be opened \n");
//printf("%s",get_next_line(ptr));
        buf = ft_read_fromfile(fd, buf);
        printf("%s\n", buf);
        line = ft_line(buf);
        printf("%s\n", line);
        buf = ft_next(buf);
        printf("%s\n", buf);
        //return (line);
        printf("%s\n", line);
}
*/