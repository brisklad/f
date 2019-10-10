/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:45:13 by bjasper           #+#    #+#             */
/*   Updated: 2019/10/10 17:25:16 by bjasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "/Users/bjasper/bjasper/libft/libft.h"
#include "fillit.h"
#include <fcntl.h>

void	ft_save(char *buf, t_list *tetromino)
{
	
	if (tetromino->content == NULL)
		tetromino->content = ft_strdup(buf);
	else
		tetromino->next = ft_lstnew(buf, 21);
	printf("%s", tetromino->content);
}

int		ft_cmp(int a, int *mass)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (a == mass[i])
			return (1);
		++i;
	}
	return (0);
}

int		ft_tetrovalid(int *p)
{
	int	connect;
	int	i;

	connect = 0;
	i = 0;
	while (i < 4)
	{
		if (ft_cmp(p[i] + 1, p))
			++connect;
		if (ft_cmp(p[i] - 1, p))
			++connect;
		if (ft_cmp(p[i] + 5, p))
			++connect;
		if (ft_cmp(p[i] - 5, p))
			++connect;
		++i;
	}
	if (connect == 6 || connect == 8)
	{
		printf("da");
		return (1);
	}
	return (0);
}

int		ft_check_simbol(char *s)
{
	int		*sharp;
	int		i;
	int		j;
	t_list	*tetromino;

	i = 0;
	j = 0;
	sharp = (int *)malloc(sizeof(int) * 4);
	tetromino = ft_lstnew(NULL, 21);
	while (i < 20)
	{
		if (s[i] == '#' && (i + 1) % 5 != 0 && j < 4)
			sharp[j++] = i++ + 1;
		else if (s[i] == '\n' && (i + 1) % 5 == 0)
			++i;
		else if (s[i] == '.' && (i + 1) % 5 != 0)
			++i;
		else
			return (0);
	}
	if ((!ft_tetrovalid(sharp)) || j != 4)
		return (0);
	ft_save(s, tetromino);
	int a = ft_list_size(tetromino);
	printf("%d\n", a );
	return (1);
}

int		ft_strvalid(int fd, char *buf)
{	
	int		red;

	while ((red = read(fd, buf, BUFF_SIZE)))
	{
		if (red != 21 || (buf[20] != '\n' && buf[20] != '\0'))
			return (0);
		if (ft_check_simbol(buf) == 0)
			return (0);		
	}
	return (1);
}

int		main(int ac, char **av)
{
	int		fd;
	char	buf[BUFF_SIZE];

	fd = open(av[1], O_RDONLY);
	ft_strvalid(fd, buf);
	return (0);
}
