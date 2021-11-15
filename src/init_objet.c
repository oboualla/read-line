/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:17:12 by oboualla          #+#    #+#             */
/*   Updated: 2019/11/14 18:31:33 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read_line.h"

static t_readl	init_readl(const char *prompt)
{
	t_readl		rl;
	t_winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	rl.ws_col = ws.ws_col;
	rl.ws_row = ws.ws_row;
	rl.prompt_len = ft_strlen(prompt);
	rl.curpos = 0;
	return (rl);
}

char			*exit_readline(t_objet **objet, t_hist **lst, int flag)
{
	char *line;

	if (!objet || !*objet)
		return (NULL);
	line = NULL;
	ed(*objet);
	ft_putchar('\n');
	if (flag == 1)
	{
		line = ft_strdup((*objet)->line);
		add_hist(ft_strdup(line), lst);
	}
	stock_hist(lst);
	*save_objet(NULL) = NULL;
	ft_memdel((void**)&(*objet)->tc);
	ft_memdel((void**)objet);
	return (line);
}

t_objet			*init_objet(const char *prompt)
{
	t_objet *objet;

	if (!(objet = (t_objet*)ft_memalloc(sizeof(t_objet))))
		return (NULL);
	ft_bzero((void*)objet->line, LINE_SIZE);
	objet->prompt = (char*)prompt;
	if (init_tc(&objet->tc) == -1)
	{
		ft_memdel((void**)&objet);
		return (NULL);
	}
	if (init_mode() == -1)
	{
		ft_memdel((void**)&objet);
		return (NULL);
	}
	objet->rd = init_readl(prompt);
	return (objet);
}
