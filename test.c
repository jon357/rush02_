#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "thead.h"

void	print(char c)
{
	write(1, &c, 1);
}

void	printstr(char *c)
{
	int i;

	i = 0;
	while (c[i])
	{
		print(c[i++]);
	}
}

int	size_str(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

int	is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}

char	*ft_cat(char *dest, char src)
{
	int	i;
	char	*c;

	c = malloc(sizeof(char)*size_str(dest) + 1);
	i = 0;
	while (dest[i] != '\0')
	{
		c[i] = dest[i];
		i++;
	}
	c[i++] = src;
	c[i] = '\0';
	return(c);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;
	char	*c;

	c = malloc(sizeof(char)*size_str(dest) + 1);
	i = 0;
	while (dest[i] != '\0')
	{
		c[i] = dest[i];
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		if (is_alpha(src[j]) == 1)
		{
			c[i + j] = src[j];
		}
		j++;
	}
	c[i + j] = '\0';
	return (c);
}

void	print_struct(char *c)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	swich;
	int	size;
	int	tempint;
	char	temp;
	char	*tempstr;
	Tuple	tab;

	size = size_str(c);
	i = 0;
	x = 0;
	printstr(c);
	printstr(" = ");
	while (i < size)
	{
		temp = c[i];
		tempstr = "";
		swich = 0;
		if (((size - i) == 2) || ((size - i) == 5))
		{
			tempstr = ft_cat(tempstr, c[i]);
			tempstr = ft_strcat(tempstr, "0");
			swich = 1;
		}
		else if (c[i] == '1')
		{
			tempstr = ft_cat(tempstr, c[i]);
			while (x < size - 1)
			{
				tempstr = ft_strcat(tempstr, "0");
				x++;
				swich = 1;
			}
		}
		j = 0;
		if (swich == 0)
		{
			while (tab.a[j])
			{
				if (temp == tab.a[j][0])
				{
					printstr(tab.b[j]);
					printstr(" ");
					if (((size - i) % 3) == 0)
					{
						y = 0;
						while(ft_strcmp(tab.a[y],"100"))
							y++;
						printstr(tab.b[y]);
						printstr(" ");
					}
					else if ((size - i) == 4)
					{
						y = 0;
						while (ft_strcmp(tab.a[y],"1000"))
							y++;
						printstr(tab.b[y]);
						printstr(" ");
					}
					break ;
				}
				j++;
			}
			i++;
		}
		else
		{
			while (tab.a[j])
			{
				if (ft_strcmp(tempstr,tab.a[j]) == 0)
				{
					printstr(tab.b[j]);
					printstr(" ");
					break ;
				}
				j++;
			}
			i++;
		}
	}
	print('\n');
/*	i = 0;
	while (tab.a[i])
	{
		printstr(tab.a[i]);
		printstr(" : ");
		printstr(tab.b[i++]);
		printstr(" , ");
	}*/
}

char	*ft_tab(int size, char *dic)
{
	int	i;
	int	j;
	int	fd_to_read;
	char	*temp;
	char	c;
	Tuple tab;

	i = 0;
	j = 0;
	temp = "";
	fd_to_read = open(dic, O_RDONLY);
	while ((read(fd_to_read, &c, sizeof (char))) > 0)
	{
		if (c == ':')
		{
			tab.a[i] = temp;
			temp = "";			
			j = 1;
		}
		else if (c == '\n')
		{
			tab.b[i] = temp;
			temp = "";
			i++;
			j = 0;
		}
		else
		{
			temp = ft_strcat(temp, &c);
		}
	}
	close(fd_to_read);
	return (temp);
}

int	ft_nb_line(char *dic)
{
	int	fd_to_read;
	int	i;
	char	c;

	i = 0;
	fd_to_read = open(dic, O_RDONLY);
	while ((read(fd_to_read, &c, sizeof (char))) > 0)
	{
		if (c == '\n')
			i++;
	}
	close(fd_to_read);
	return (i);
}

int	main(int argc, char **argv)
{
	int	nb_line;
	char	*dic;
	Tuple	tab;

	if (argc == 2)
	{
		dic = "numbers.dict";
		nb_line = ft_nb_line(dic);
		ft_tab(nb_line, dic);
		print_struct(argv[1]);
	}
	else if (argc == 3)
	{
		dic = argv[1];
		nb_line = ft_nb_line(dic);
		ft_tab(nb_line, dic);
		print_struct(argv[2]);
	}
	else
	{
//		dic = "numbers.dict";
//		nb_line = ft_nb_line(dic);
//		ft_tab(nb_line, dic);
//		print_struct();
	}
}
