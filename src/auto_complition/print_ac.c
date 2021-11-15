/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 23:19:12 by oboualla          #+#    #+#             */
/*   Updated: 2019/11/14 19:07:52 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libac.h"

static ushort	print_tfile(char **t_file, char *dir, size_t len, ushort ws_col)
{
	size_t i;
	ushort col;
	size_t src;
	ushort row;

	row = 0;
	if (!t_file || len > ws_col)
		return (0);
	i = 0;
	src = 0;
	col = len;
	while (t_file[i])
	{
		couleur(t_file[i], dir);
		ft_putstr(t_file[i]);
		ft_putstr("\033[0m");
		col += len;
		src = ft_strlen(t_file[i]);
		if ((col + len) >= ws_col)
		{
			row++;
			ft_putchar('\n');
			col = len;
		}
		else
			while (++src <= (len + 1))
				ft_putchar(' ');
		ft_strdel(&t_file[i++]);
	}
	free(t_file);
	return (row);
}

static void reprint_prompt(t_objet *obj)
{
	ft_putchar('\n');
	ft_putstr(obj->prompt);
	obj->rd.curpos = 0;
	reprint(obj->line, obj->rd, obj->tc);
	obj->rd.curpos++;
	ed(obj);
}

int	print_ac(t_ac *ac, t_objet *obj, size_t len)
{
	t_readl		rd;
	ushort		row;
	t_curpos	newpos;
	t_curpos	oldpos;

	rd = obj->rd;
	oldpos = get_curpos(obj->rd);
	rd.curpos = ft_strlen(obj->line);
	newpos = get_curpos(rd);
	newpos.x = 1;
	newpos.y++;
	curs_newpos(oldpos, newpos, obj->tc);
	ft_putstr(tgetstr("cd", NULL));
	row = print_tfile(ac->files, ac->path, len, rd.ws_col);
	if (((row + 1) >= obj->rd.ws_row))
		reprint_prompt(obj);
	else
	{
		newpos.y += row;
		curs_newpos(newpos, oldpos, obj->tc);
	}
	ac->files = NULL;
	return (1);
}
