#include "get_next_line.h"

char    *ft_free_tempstore(char *tempstore, char *buf)
{
        char *bufandtemp;

        bufandtemp = ft_strjoin(tempstore, buf);
        free (tempstore);
        return (bufandtemp);
}

char	*ft_next(char *buf)
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
	
	i = 0;
	// copying buffer content into line, until end of line
	while (buf[i] != '\0' && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] != '\0' && buf[i] == '\n')
		line[i++] = '\n';
	line[i++] = '\0'; // null terminating necessary?
	return (line);
}

//linetempstore is the buf I send in ft_getnextline linetempstore equivalent to storage until end of line reached
char    *ft_read_fromfile(int fd, char *linetempstore)
{
        char    *buf;
        int     byte_read;

        // check for a null pointer, which will be returned if sth went wrong, so this is to check if the pointer can be accessed without segfaulting
        if (!linetempstore)
            linetempstore = ft_calloc(1, 1); // why do we calloc null pointer?!
        // malloc buffer, interesting that sizeof is a valid argument
        buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
        //byte_read = 1;
        while ((byte_read = read(fd, buf, BUFFER_SIZE)) > 0) // as long as we did not reach EOF and ft_strchr did not reach \n read from file
        {
                // read returns number of byte read by default (zero indicates end of file)
                //byte_read = read(fd, buf, BUFFER_SIZE);
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
        if (ft_strchr(buf, '\n') != NULL)
	        break ;
}
        free(buf);
	return (linetempstore);
}

char	*get_next_line(int fd)
{
        static char    *buf;
        char    *line;

        if (fd < 0 || BUFFER_SIZE <= 0)
                return (NULL);
        // reading from a file until end of line into the buffer, this returns a string that includes at least one line (until \n) but could also be more
        buf = ft_read_fromfile(fd, buf);
		// check for null pointer
        if (!buf)
			return (NULL);
        // this is to trim the string to only contain one line
        line = ft_line(buf);
        // to store the residual characters that were stored in the buf after \n and should be part of the next line
        buf = ft_next(buf); // we are using statics, so when running this loop again these remaining values are still saved
        return (line);
}
/*
int main()
{
	int fd;
	char *line;
  
	fd = open("test.txt", O_RDONLY);
	if (fd == 0)
      		printf("file can't be opened \n");
	while (1) // this is just to keep a loop open and we end it when we reached EOF
	{
	line = get_next_line(fd);
 	if (line == NULL)
   	 break;
   	printf("%s", line);
   	free(line);
 	}
}
*/