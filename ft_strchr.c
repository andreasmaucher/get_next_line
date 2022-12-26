#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

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

int	main()
{
	char	str[] = "This is a test to understand the strchr function better.";
	char	search = 'z';

	printf("%s", ft_strchr(str, search));
}
