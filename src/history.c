/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:44:37 by oboualla          #+#    #+#             */
/*   Updated: 2019/11/14 18:05:59 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read_line.h"

t_hist			*make_node(char *line)
{
	t_hist	*new;

	if (!(new = (t_hist*)ft_memalloc(sizeof(t_hist))))
		return (NULL);
	new->line = line;
	new->back = NULL;
	new->next = NULL;
	return (new);
}

void			init_hist(t_hist **lst)
{
	t_hist	*tmp;
	t_hist	*rest;
	char	*line;
	int		fd;

	rest = NULL;
	if ((fd = open(".history", O_RDONLY)) == -1)
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(tmp = make_node(line)))
			return ;
		tmp->next = rest;
		if (rest)
			rest->back = tmp;
		rest = tmp;
	}
	*lst = rest;
	close(fd);
}

void			stock_hist(t_hist **lst)
{
	int		fd;
	t_hist	*tmp;

	if ((fd = open(".history", O_WRONLY | O_CREAT, S_IRWXU)) == -1)
		return ;
	if (*lst && (*lst)->next)
		while ((*lst)->next)
			(*lst) = (*lst)->next;
	while (*lst)
	{
		tmp = (*lst)->back;
		ft_putendl_fd((*lst)->line, fd);
		ft_strdel(&(*lst)->line);
		ft_memdel((void**)lst);
		*lst = tmp;
	}
	close(fd);
}

void			add_hist(char *line, t_hist **lst)
{
	t_hist *tmp;

	if (*lst && (*lst)->back)
	{
		while ((*lst)->back->back)
			*lst = (*lst)->back;
		ft_strdel(&(*lst)->back->line);
		ft_memdel((void**)&(*lst)->back);
	}
	tmp = *lst;
	if (!(*lst = make_node(line)))
		*lst = tmp;
	else if (tmp)
	{
		(*lst)->next = tmp;
		tmp->back = *lst;
	}
}
