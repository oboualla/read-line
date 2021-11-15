/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 22:47:43 by oboualla          #+#    #+#             */
/*   Updated: 2019/06/18 04:58:31 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static int		ft_make_line(char **str, char **line)
{
	char	*chn;
	int		i;

	i = 0;
	if (!(*str))
		return (0);
	chn = *str;
	*str = NULL;
	while (chn[i] != '\0' && chn[i] != '\n')
		i++;
	if (i == 0 && chn[i] == '\0')
	{
		ft_strdel(&chn);
		return (0);
	}
	chn[i] = '\0';
	*line = ft_strdup(chn);
	*str = ft_strdup(&chn[i + 1]);
	ft_strdel(&chn);
	return (1);
}

static t_reste	*add_fd(const int fd)
{
	t_reste *new;

	if (!(new = (t_reste*)ft_memalloc(sizeof(t_reste))))
		return (NULL);
	new->fd = fd;
	if (!(new->reste = ft_strnew(0)))
		return (NULL);
	new->next = NULL;
	return (new);
}

static t_reste	*ft_check_fd(const int fd, t_reste **list)
{
	t_reste *tmp;
	t_reste *ptr;
	t_reste *new;

	if (!(*list))
	{
		new = add_fd(fd);
		*list = new;
	}
	else
	{
		ptr = *list;
		while (ptr)
		{
			if (ptr->fd == fd)
				return (ptr);
			tmp = ptr;
			ptr = ptr->next;
		}
		new = add_fd(fd);
		tmp->next = new;
	}
	return (new);
}

static int		ft_dellst(t_reste *name, t_reste **list)
{
	t_reste **ptr;
	t_reste *del;

	del = *list;
	if (del == name)
	{
		*list = del->next;
		ft_memdel((void*)&name);
		return (0);
	}
	while (del->next != name)
		del = del->next;
	ptr = &del->next;
	*ptr = name->next;
	ft_memdel((void*)&name);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_reste	*list;
	t_reste			*ptr_surn;
	char			*buff;
	char			*ptr;
	int				nbread;

	nbread = 0;
	if (read(fd, NULL, 0) < 0 || !line || fd > 4096)
		return (-1);
	if (!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	ptr_surn = ft_check_fd(fd, &list);
	while (!ft_is_separ(ptr_surn->reste, '\n') &&
			(nbread = read(fd, buff, BUFF_SIZE)))
	{
		ptr = ptr_surn->reste;
		ptr_surn->reste = ft_strjoin(ptr, buff);
		ft_strdel(&ptr);
		ft_memset((void*)buff, 0, BUFF_SIZE);
	}
	ft_strdel(&buff);
	if (!(ft_make_line(&ptr_surn->reste, &*line)))
		return (ft_dellst(ptr_surn, &list));
	return (1);
}
