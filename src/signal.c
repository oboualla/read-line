/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:41:31 by oboualla          #+#    #+#             */
/*   Updated: 2019/11/14 18:32:02 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read_line.h"

static void	reprint_prompt(t_objet *obj)
{
	ed(obj);
	ft_putchar('\n');
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(obj->prompt);
	ft_bzero((void*)obj->line, LINE_SIZE);
	obj->rd.curpos = 0;
}

static void reprint_line(t_objet *obj)
{
	t_winsize ws;
	t_curpos oldpos;
	t_curpos curpos;
	size_t	index;

	index = obj->rd.curpos;
	oldpos = get_curpos(obj->rd);
	curpos = oldpos;
	ft_putstr(obj->tc->hide_curs);
	while (--curpos.y)
		to_up_line(obj->tc);
	ft_putstr(tgetstr("cd", NULL));
	sleep(1);
	obj->rd.curpos = 0;
	ioctl(0, TIOCGWINSZ, &ws);
	obj->rd.ws_col = ws.ws_col;
	obj->rd.ws_row = ws.ws_row;
	ft_putstr(obj->prompt);
	reprint(obj->line, obj->rd, obj->tc);
	obj->rd.curpos++;
	curpos = get_curpos(obj->rd);
	obj->rd.curpos = index;
	oldpos = get_curpos(obj->rd);
	curs_newpos(curpos, oldpos, obj->tc);
}

static void	sig1(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		reprint_prompt(*save_objet(NULL));
	else if (sig == SIGWINCH)
		reprint_line(*save_objet(NULL));

}

void	init_sig(void)
{
	signal(SIGINT, sig1);
	signal(SIGWINCH, sig1);
}
